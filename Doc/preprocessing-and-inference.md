# Preprocessing and Inference — Technical Detail

This document explains step by step what happens between the camera capture and the UART output, with the reasoning behind each design choice.

---

## 1 — Camera Capture (DCMIPP)

The STM32N6570-DK has a hardware camera pipeline called **DCMIPP** (Digital Camera Interface and Pixel Processing).

Two pipes run in parallel:

| Pipe | Purpose | Output |
|------|---------|--------|
| Pipe 1 (display) | Full-resolution stream → LCD | Continuous, no CPU involvement |
| Pipe 2 (NN) | Downscale snapshot → 32×32 RGB888 | Triggered on demand, 3072 bytes |

Pipe 2 captures a single 32×32 frame at each inference cycle. The output is a flat byte array `nn_raw[3072]` where each pixel occupies 3 consecutive bytes (R, G, B), stored in CPU SRAM.

**DCache note:** the DMA writes the camera data directly to SRAM. Before the CPU reads it, the DCache line covering that buffer must be invalidated:
```c
SCB_InvalidateDCache_by_Addr((uint32_t*)nn_raw, sizeof(nn_raw));
```
Without this, the CPU would read stale cached values rather than the fresh DMA data.

---

## 2 — Preprocessing

The CNN was trained on **MNIST**: 28×28 grayscale images, float32 in [0,1], where **white = digit, black = background** (bright strokes on dark background).

The camera produces the opposite: a colour image where a dark marker on white paper yields **dark strokes on a bright background**. Preprocessing bridges this gap.

### Pass 1 — Inverted grayscale

Each RGB888 pixel is converted to a single luminance value using the **Rec.601** coefficients, then inverted:

```
val = (255 − (0.299·R + 0.587·G + 0.114·B)) / 255
```

- White paper (R≈G≈B≈200) → luminance ≈ 200 → inverted ≈ 55/255 ≈ **0.22** (dark)
- Black ink  (R≈G≈B≈30)  → luminance ≈ 30  → inverted ≈ 225/255 ≈ **0.88** (bright)

After this pass, the image matches the MNIST convention (bright digit, dark background). The pass also scans all 1024 pixels to record `vmin` and `vmax`.

Typical values on a real scene:

| Scene | vmin | vmax | range |
|-------|------|------|-------|
| Digit on paper, good lighting | 0.33–0.45 | 0.87–0.90 | ~0.50 |
| Empty scene (no digit) | ~0.40 | ~0.42 | ~0.02 |

Note: `vmin` is never near 0.0 because the IMX335 auto-exposure does not render white paper as pure white.

### Pass 2 — Adaptive background suppression

**Problem with simple normalisation:**  
A naive min-max stretch `v = (val − vmin) / (vmax − vmin)` maps the full observed range to [0,1]. This looks correct but causes a critical failure: ambient lighting gradients push the white-paper background pixels to 0.3–0.46 after inversion. The normalised background is not zero — it is a noisy grey field. The CNN sees this grey field as spurious structure (e.g. a faint "0" ring) and produces wrong predictions even with no digit in frame.

**The fix — midpoint threshold:**

```c
float midpt    = (vmin + vmax) * 0.5f;
float hi_range = vmax - midpt;          // = (vmax - vmin) / 2
if (hi_range < 0.005f) hi_range = 0.005f;  // guard against flat scenes

for (int i = 0; i < 1024; i++) {
    float raw = val[i];
    float v   = (raw <= midpt) ? 0.0f
                               : (raw - midpt) / hi_range;
    nn_in[i]  = (v > 1.0f) ? 1.0f : v;
}
```

**What this does:**
- Pixels at or below `(vmin+vmax)/2` → forced to **0.0** (background zeroed completely)
- Pixels above the midpoint → rescaled over the upper half of the range → **[0,1]**

The midpoint is the natural boundary between background and digit: background pixels cluster around `vmin`, digit pixels cluster around `vmax`. Cutting at the midpoint eliminates all background noise without knowing the absolute pixel values.

**Before / after the fix:**

| Digit | Without suppression | With suppression |
|-------|---------------------|-----------------|
| 2 | predicted 0 at 97% ❌ | predicted 2 at 90–97% ✅ |
| 3 | confused 0/8/3 ❌ | predicted 3 at 100% ✅ |

**Low-contrast guard:**  
When no digit is present, `vmax − vmin ≈ 0.02` (flat scene). `hi_range` would be ~0.01, causing amplification of pure noise. The `if (hi_range < 0.005f)` clamp prevents this: the output stays near zero and the confidence threshold discards the prediction.

### Result fed to the NPU

Each pixel's processed value is written to all three channels of `nn_in`:

```c
nn_in[3*i] = nn_in[3*i+1] = nn_in[3*i+2] = v;
```

The model expects `float32[32×32×3]` (RGB channel-last). Replicating the grayscale value across R, G, B satisfies the shape contract without retraining on a grayscale-only model.

Before the NPU reads the buffer, the DCache must be flushed:
```c
SCB_CleanInvalidateDCache_by_Addr((uint32_t*)nn_in, sizeof(nn_in));
```

---

## 3 — NPU Inference (Neural-ART)

The model is a small CNN compiled by **STEdgeAI** for the Neural-ART (ATON) accelerator:

```
Input [1×32×32×3]
  Conv2D(16, 3×3, relu) + MaxPool2D      →  [1×16×16×16]
  Conv2D(32, 3×3, relu) + MaxPool2D      →  [1×8×8×32]
  Conv2D(64, 3×3, relu) + GlobalAvgPool  →  [1×64]
  Dense(64, relu)                         →  [1×64]
  Dense(10, softmax)                      →  [1×10]
```

Total: **28 394 parameters** (110.91 KB). The weights are stored in NOR flash at `0x71000000` and read directly by the NPU — they are never copied to RAM.

Inference is triggered with a single API call:
```c
stai_network_run(&network, &nn_input, &nn_output);
```

Execution time: **< 5 ms** at 1 GHz. The NPU runs fully autonomously; the CPU waits on a completion flag.

---

## 4 — Postprocessing and Output

The NPU writes 10 float32 values (softmax probabilities) to `nn_out[10]`.

```c
// Find the class with highest probability
int   best_class = 0;
float best_prob  = nn_out[0];
for (int i = 1; i < 10; i++) {
    if (nn_out[i] > best_prob) {
        best_prob  = nn_out[i];
        best_class = i;
    }
}

// Reject low-confidence predictions
if (best_prob < 0.70f) return;   // display nothing

// Output
printf("[%d] %.0f%%  (%lums)\r\n", best_class, best_prob * 100.0f, elapsed_ms);
```

The **70% confidence threshold** rejects ambiguous frames (digit partially out of frame, transition between digits, empty scene with low contrast).

The predicted class and confidence are also overlaid on the LCD in real time.

---

## 5 — Full Timing Budget

| Stage | Time |
|-------|------|
| DCMIPP snapshot (32×32) | ~1 ms |
| DCache invalidate + preprocessing | ~1 ms |
| NPU inference | < 5 ms |
| Postprocess + UART print | < 1 ms |
| **Total per frame** | **~8 ms → ~125 fps** |

In practice the loop runs at ~38 ms per frame (observed on UART timestamps) because the display pipe and ISP processing add latency.
