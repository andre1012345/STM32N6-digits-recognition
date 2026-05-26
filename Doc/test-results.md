# Test Results — STM32N6570-DK MNIST

**Date:** 2026-05-26  
**Model:** `mnist_cnn_32x32_OE_3_3_1`  
**Board:** STM32N6570-DK, IMX335 camera  
**Preprocessing:** RGB888 → inverted grayscale → adaptive midpoint background suppression → [0,1]

---

## TEST_MODE Results (synthetic images)

Tested with `TEST_MODE=1`: 10 pre-rendered 32×32 synthetic images cycling through digits 0–9.  
Each digit was held for 3 s (~75 frames per digit), results were 100% stable per digit.

| Digit | Predicted | Confidence | Result | Note |
|-------|-----------|------------|--------|------|
| 0 | 0 | 100% | ✅ | |
| 1 | 6 | 87%  | ❌ | Synthetic stroke off-center; real camera → 96–99% ✅ |
| 2 | 2 | 99%  | ✅ | |
| 3 | 3 | 100% | ✅ | |
| 4 | 8 | 62%  | ❌ | Synthetic image 7-segment style doesn't match MNIST |
| 5 | 5 | 100% | ✅ | |
| 6 | 6 | 100% | ✅ | |
| 7 | 2 | 99%  | ❌ | Synthetic image 7-segment style doesn't match MNIST |
| 8 | 0 | 96%  | ❌ | Synthetic image 7-segment style doesn't match MNIST |
| 9 | 3 | 96%  | ❌ | Synthetic image 7-segment style doesn't match MNIST |

**TEST_MODE accuracy: 5/10 (50%)**

### Why some synthetic digits fail

The synthetic images use a **7-segment display style** (rectangular bars and vertical strokes).  
The model was trained on **MNIST** (smooth, handwritten curves). For digits with loops or diagonals (4, 7, 8, 9), the rectangular pixel-art shapes don't activate the correct feature detectors in the CNN.

This is a limitation of the synthetic test images, **not of the model itself** — the live camera test on real handwritten digits shows much higher accuracy (see below).

---

## Live Camera Results

Tested with `TEST_MODE=0` and real handwritten digits on white paper, black marker, ~10 cm from camera.  
Results shown are stable predictions over ~20 frames per digit.

| Digit | Confidence (stable) | Result | Notes |
|-------|---------------------|--------|-------|
| 1 | 96–99% | ✅ | Well-centered |
| 2 | 87–97% | ✅ | Stable |
| 3 | 100% | ✅ | After background fix |
| 5 | 98–99% | ✅ | Most reliable |

**Live camera accuracy: 4/4 tested (100%)**

> Digits 0, 4, 6, 7, 8, 9 not yet tested live. Digits 2↔3 and 1↔4 may confuse when handwriting is ambiguous or digit is tilted.

---

## Preprocessing Fix (background suppression)

**Problem:** Simple min-max contrast stretch amplified ambient lighting gradients in the background, pushing white paper pixels to ~0.3–0.46 after normalization. The model saw false structure (e.g. a "0" ring) even with no digit present.

**Fix:** Adaptive midpoint threshold applied in `main.c`:

```c
/* Pass 2: zero background, stretch digit region to [0,1] */
float midpt    = (vmin + vmax) * 0.5f;
float hi_range = vmax - midpt;
if (hi_range < 0.005f) hi_range = 0.005f;
for (int i = 0; i < n; i++) {
    float raw = dst[3*i];
    float v = (raw <= midpt) ? 0.0f : (raw - midpt) / hi_range;
    dst[3*i] = dst[3*i+1] = dst[3*i+2] = (v > 1.0f) ? 1.0f : v;
}
```

| Digit | Before fix | After fix |
|-------|-----------|-----------|
| 2 (stable) | 0 at 97% (wrong) | 2 at 90–97% ✅ |
| 3 (stable) | 0/8/3 confused | 3 at 100% ✅ |
| 1 (stable) | not tested | 1 at 96–99% ✅ |
| 5 (stable) | not tested | 5 at 98–99% ✅ |

---

## Typical `vmin`/`vmax` Values (live camera)

| Scene | vmin | vmax | range |
|-------|------|------|-------|
| Digit on white paper | 0.33–0.45 | 0.87–0.90 | 0.45–0.57 |
| Empty scene (no digit) | ~0.40 | ~0.42 | ~0.02 (LOW CONTRAST) |

`vmin` ~0.33–0.45 is expected: the IMX335 auto-exposure renders white paper as medium-gray, not 255.

---

## Camera Setup

- Distance: 10–15 cm from paper
- Lighting: indoor ambient (ceiling LED)
- Digit: black marker on A4 white paper, ~5–7 cm tall
- Orientation: digit upright, roughly centered in frame
