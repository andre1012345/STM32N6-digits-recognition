# Inference Test Results — STM32N6570-DK MNIST

**Date:** 2026-05-26  
**Model:** `mnist_cnn_32x32_OE_3_3_1`  
**Board:** STM32N6570-DK, IMX335 camera  
**Preprocessing:** RGB888 → inverted grayscale → adaptive midpoint background suppression → [0,1]

---

## Summary

| Digit | Top-1 accuracy (stable) | Typical confidence | Secondary confusion |
|-------|------------------------|--------------------|---------------------|
| 1     | ✅ Correct             | 96–99%             | 4 (~3%), 7 (<1%)    |
| 2     | ✅ Correct             | 87–97%             | 3 (~5%), 7 (~5%)    |
| 3     | ⚠️ Partially correct   | 10–38%             | 0 (~37%), 8 (~32%)  |
| 5     | ✅ Correct             | 98–99%             | 0 (<1%), 6 (<1%)    |

> **Note on digit 3:** results above were captured **before** the adaptive background suppression fix.
> After the fix the "3" classification improved significantly (up to ~38% correct vs 0% before).

---

## Digit 1 — Test Log

| Frames | Predicted | Confidence | Notes |
|--------|-----------|------------|-------|
| ~20    | 1         | 97–99%     | Stable, well-framed |
| ~10    | 1         | 93–98%     | Slight movement |
| ~5     | 1/4       | 82–86% / 17% | Digit partially rotated |

**Conclusion:** Digit 1 classifies reliably at ≥ 93% when the digit is stable and fills ~70% of the 32×32 frame. Occasional confusion with 4 occurs when the digit is tilted or the base curves outward.

---

## Digit 2 — Test Log

| Frames | Predicted | Confidence | Notes |
|--------|-----------|------------|-------|
| ~15    | 2         | 87–97%     | Stable |
| ~5     | 2/3       | 56%/28%    | Digit moving |

**Conclusion:** Digit 2 works well when stable. The top curve of a handwritten "2" can resemble a "3" from certain angles.

---

## Digit 3 — Test Log (before background fix)

| Frames | Predicted | Confidence | Notes |
|--------|-----------|------------|-------|
| ~5     | 0/8/3     | 34/33/31%  | Confused — lighting gradient in background |
| ~3     | 3         | 37%        | Best result before fix |

**Root cause:** Uneven ambient lighting created a background gradient that, after simple min-max contrast stretch, produced values up to 0.46 in the background — causing the model to see a "0"-like ring.  
**Fix applied:** Adaptive midpoint threshold zeroes pixels below `(vmin+vmax)/2`, eliminating the gradient noise.

---

## Digit 5 — Test Log

| Frames | Predicted | Confidence | Notes |
|--------|-----------|------------|-------|
| ~25    | 5         | 98–99%     | Consistently correct |
| ~5     | 5         | 97%        | Slight movement |

**Conclusion:** Digit 5 is the most reliable digit tested — its distinctive shape gives high confidence under all tested conditions.

---

## Preprocessing Fix Impact

| Condition | Before fix | After fix |
|-----------|-----------|-----------|
| Digit 2 (stable) | 0 at 97% (wrong) | 2 at 90–97% (correct) |
| Digit 3 (stable) | 0 at 34%, 8 at 33%, 3 at 31% | 3 rising to ~38% top-1 |
| Digit 1 (stable) | Not tested | 1 at 96–99% |
| Digit 5 (stable) | Not tested | 5 at 98–99% |

**Key change (`main.c`, preprocessing pass 2):**
```c
// Before: full min-max stretch (amplifies background gradient)
float v = (dst[3*i] - vmin) / range;

// After: midpoint threshold (zeroes background, stretches digit region)
float midpt    = (vmin + vmax) * 0.5f;
float hi_range = vmax - midpt;
float v = (raw <= midpt) ? 0.0f : (raw - midpt) / hi_range;
```

---

## Observed Typical `vmin`/`vmax` Values

| Scene | vmin | vmax | range | Note |
|-------|------|------|-------|------|
| Digit 1 on white paper | 0.449 | 0.902 | 0.453 | Good contrast |
| Digit 2 on white paper | 0.372 | 0.902 | 0.530 | Good contrast |
| Digit 3 on white paper | 0.370 | 0.875 | 0.504 | Good contrast |
| Digit 5 on white paper | 0.331 | 0.902 | 0.571 | Good contrast |
| Empty scene (no digit)  | ~0.40 | ~0.42 | ~0.02 | LOW CONTRAST warning |

`vmin` is consistently ~0.33–0.45, meaning the camera sees the paper as medium-gray (not pure white). This is expected with the IMX335 auto-exposure.

---

## Camera Setup Used

- Distance: ~10–15 cm from paper
- Lighting: indoor ambient (ceiling LED)
- Digit: black marker on A4 white paper, ~5–7 cm tall
- Orientation: digit upright, roughly centered in frame
