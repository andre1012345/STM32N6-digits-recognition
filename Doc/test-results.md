# Test Results — STM32N6570-DK MNIST

**Date:** 2026-05-26  
**Model:** `mnist_cnn_32x32_OE_3_3_1`  
**Board:** STM32N6570-DK, IMX335 camera  
**Preprocessing:** RGB888 → inverted grayscale → adaptive midpoint background suppression → [0,1]

---

## TEST_MODE Results (synthetic images)

Tested with `TEST_MODE=1`: 10 pre-rendered 32×32 synthetic images cycling through digits 0–9.  
Each digit was held for 3 s (~75 frames per digit), results were 100% stable per digit.

### Run 1 — original digits.h

| Digit | Predicted | Confidence | Result | Note |
|-------|-----------|------------|--------|------|
| 0 | 0 | 100% | ✅ | |
| 1 | 6 | 87%  | ❌ | Synthetic stroke off-center |
| 2 | 2 | 99%  | ✅ | |
| 3 | 3 | 100% | ✅ | |
| 4 | 8 | 62%  | ❌ | 7-segment style |
| 5 | 5 | 100% | ✅ | |
| 6 | 6 | 100% | ✅ | |
| 7 | 2 | 99%  | ❌ | 7-segment style |
| 8 | 0 | 96%  | ❌ | 7-segment style |
| 9 | 3 | 96%  | ❌ | 7-segment style |

**Run 1 accuracy: 5/10 (50%)**

### Run 2 — redesigned digits.h (1, 4, 7, 8, 9)

| Digit | Predicted | Confidence | Result | Note |
|-------|-----------|------------|--------|------|
| 0 | 0 | 100% | ✅ | |
| 1 | 6 | 78%  | ❌ | Thin stroke still ambiguous |
| 2 | 2 | 99%  | ✅ | |
| 3 | 3 | 100% | ✅ | |
| 4 | 4 | 42%  | ✅ | Fixed by asymmetric redesign |
| 5 | 5 | 100% | ✅ | |
| 6 | 6 | 100% | ✅ | |
| 7 | 2 | 100% | ❌ | Still fails — diagonal not captured at 32×32 |
| 8 | 0 | 89%  | ❌ | Still fails — rectangular loops ≠ MNIST |
| 9 | 2 | 84%  | ❌ | Still fails |

**Run 2 accuracy: 6/10 (60%)**

### Why some synthetic digits fail

The synthetic images use a **7-segment display style** (rectangular bars and vertical strokes).  
The model was trained on **MNIST** (smooth, handwritten curves). For digits with loops or diagonals (7, 8, 9), the rectangular pixel-art shapes don't activate the correct feature detectors in the CNN.

This is a limitation of the synthetic test images, **not of the model itself** — the live camera and screen tests show much higher accuracy.

---

## Live Camera Results — Handwritten digits (paper)

Tested with `TEST_MODE=0` and real handwritten digits on white paper, black marker, ~10 cm from camera.  
Results shown are stable predictions over ~20 frames per digit.

| Digit | Confidence (stable) | Result | Notes |
|-------|---------------------|--------|-------|
| 1 | 96–99% | ✅ | Well-centered |
| 2 | 87–97% | ✅ | Stable |
| 3 | 100%   | ✅ | After background fix |
| 5 | 98–99% | ✅ | Most reliable |

**Handwritten accuracy: 4/4 tested (100%)**

> Digits 0, 4, 6, 7, 8, 9 not tested on paper.

---

## Live Camera Results — PC screen (digits 1–9)

Tested with `TEST_MODE=0`, showing digits 1–9 from a PC monitor ~10–15 cm from camera.  
Note: screen fonts differ from MNIST handwriting — lower contrast and different stroke style.

| Digit | Stable prediction | Confidence | Result | Notes |
|-------|-------------------|------------|--------|-------|
| 0 | 0 | 96–100% | ✅ | Very stable |
| 1 | 1 | 50–72%  | ⚠️ | Low confidence; sometimes confused with 7 |
| 2 | 2 | 89–96%  | ✅ | Stable |
| 3 | 3 | 97–100% | ✅ | Very stable |
| 4 | 4 | 86–98%  | ✅ | Stable |
| 5 | 5 | 81–88%  | ✅ | Stable |
| 6 | — | —       | ❌ | Not reliably detected from screen (single frame at 68%) |
| 7 | 7 | 89–96%  | ✅ | Very stable |
| 8 | 8 | 52–65%  | ⚠️ | Correct but low confidence; needs better framing |
| 9 | 9 | 79–93%  | ✅ | Stable |

**Screen accuracy: 7/9 reliable ✅, 2/9 weak ⚠️, 1/9 not detected (6)**

> Digits 1 and 8 benefit from handwritten input rather than screen fonts.  
> Digit 6 was not reliably recognised from the screen — likely because sans-serif "6" looks different from MNIST handwritten 6.

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

- Distance: 10–15 cm from paper / screen
- Lighting: indoor ambient (ceiling LED)
- Digit on paper: black marker on A4 white paper, ~5–7 cm tall
- Orientation: digit upright, roughly centered in frame
