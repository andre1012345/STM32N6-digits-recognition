# MNIST Digit Classification on STM32N6570-DK

Real-time handwritten digit recognition (0–9) running on the STM32N6570-DK board.  
The camera captures a 32×32 image, the Neural-ART NPU runs a CNN model, and the predicted digit with confidence is shown on the LCD and sent over UART.

---

## Hardware

| Component | Details |
|-----------|---------|
| Board | [STM32N6570-DK](https://www.st.com/en/evaluation-tools/stm32n6570-dk.html) Discovery Kit |
| Camera | Onboard IMX335 module |
| Connection | USB-C to ST-LINK (CN6) |

> **Note:** OTP fuses must be programmed for xSPI IOs (200 MHz). This is done automatically on first flash if not already set.

---

## Model

| Property | Value |
|----------|-------|
| File | `mnist_cnn_32x32_OE_3_3_1` |
| Input | 32 × 32 × 3 float32 (RGB, channel-last) |
| Output | 10-class softmax (digits 0–9) |
| Inference | < 5 ms on Neural-ART NPU @ 1 GHz |
| Weights location | NOR flash @ `0x71000000` |

---

## Preprocessing Pipeline

The camera produces a 32×32 RGB888 frame. Before feeding the model:

1. **Grayscale** — Rec. 601 luma: `gray = 0.299·R + 0.587·G + 0.114·B`
2. **Invert** — `val = (255 − gray) / 255`  
   Dark ink on white paper → bright digit on dark background, matching the MNIST convention (white digit, black background).
3. **Adaptive background suppression** — the midpoint between `vmin` and `vmax` is used as a threshold:
   - Pixels **below** the midpoint → 0 (background zeroed)
   - Pixels **above** the midpoint → rescaled to [0, 1]  
   This removes lighting gradients that would otherwise push background values to ~0.3 and confuse the classifier.

---

## Test Mode

Set `#define TEST_MODE 1` in [main.c](Application/STM32N6570-DK/Src/main.c) to cycle through 10 synthetic digit images from [digits.h](Application/STM32N6570-DK/Inc/digits.h) instead of using the camera.  
Each digit is displayed for `DIGIT_HOLD_MS` milliseconds. Useful to verify the model and preprocessing without physical setup.

---

## UART Output

Connect at **115200 baud, 8N1** on USART1 (PE5 TX / PE6 RX).

Startup:
```
========================================
MNIST Digit Classification - STM32N6570-DK
Model : mnist_cnn_32x32_OE_3_3_1
Build : May 26 2025 10:30:00
========================================
```

Per-frame (live mode):
```
[2] 94%  (3ms)
[2] 97%  (3ms)
```

Per-frame (TEST_MODE):
```
digit=3  predicted=3  OK  (3ms)
digit=7  predicted=7  OK  (3ms)
```

---

## Camera Tips

- Hold the digit **10–15 cm** from the camera so it fills most of the 32×32 frame
- Use **black marker on white paper** under uniform ambient light
- Avoid shadows falling across the digit
- A **printed** (computer-generated) digit works better than handwriting
- The confidence threshold for a valid classification is **70%** (`nn_top1_output_class_proba < 0.7` shows "Failed to classify")

---

## Build & Flash

### Requirements

- [STM32CubeIDE](https://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-ides/stm32cubeide.html) v1.17.0
- [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) v2.18.0 (with N6 external loader)
- [STEdgeAI](https://www.st.com/en/development-tools/stedgeai-core.html) v4.0.0

### Boot Modes

The STM32N6 has no internal flash. Two modes are available:

| Mode | Use |
|------|-----|
| **Development** | Load firmware into SRAM via debugger (lost on power cycle) |
| **Boot from Flash** | Boot from external NOR flash (persistent) |

![Boot switches](_htmresc/STM32N6570-DK_Boot_from_flash.png)

### Development Mode (debug session)

1. Set board to **development mode** (boot switch toward DEV).
2. Open `Application/STM32N6570-DK/STM32CubeIDE/.project` in STM32CubeIDE.
3. Build and run with the debugger.

### Flash Model Weights (once, or when changing model)

```powershell
$DKEL = "<STM32CubeProgrammer>/bin/ExternalLoader/MX66UW1G45G_STM32N6570-DK.stldr"
STM32_Programmer_CLI -c port=SWD mode=HOTPLUG -el $DKEL -hardRst `
    -w Model/STM32N6570-DK/network_data.hex
```

### Boot from Flash (persistent)

After building the application:

```powershell
# 1. Sign the binary
STM32_SigningTool_CLI -bin build/Application/STM32N6570-DK/Project.bin `
    -nk -t ssbl -hv 2.3 -o build/Application/STM32N6570-DK/Project_sign.bin

$DKEL = "<STM32CubeProgrammer>/bin/ExternalLoader/MX66UW1G45G_STM32N6570-DK.stldr"

# 2. Flash FSBL
STM32_Programmer_CLI -c port=SWD mode=HOTPLUG -el $DKEL -hardRst -w FSBL/ai_fsbl.hex

# 3. Flash application
STM32_Programmer_CLI -c port=SWD mode=HOTPLUG -el $DKEL -hardRst `
    -w build/Application/STM32N6570-DK/Project_sign.bin 0x70100000

# 4. Flash model weights
STM32_Programmer_CLI -c port=SWD mode=HOTPLUG -el $DKEL -hardRst `
    -w Model/STM32N6570-DK/network_data.hex
```

Set board to **boot from flash** mode and power cycle.

> Steps 2 and 4 only need to be repeated if the FSBL or model weights change.

---

## Project Structure

```
Application/STM32N6570-DK/
├── Src/main.c              Main loop, preprocessing, inference, display
├── Inc/app_config.h        Class names, display config, aspect ratio mode
├── Inc/digits.h            Synthetic 32×32 RGB test images for TEST_MODE
└── STM32CubeIDE/           IDE project files

Model/STM32N6570-DK/
├── stai_network.h          Model I/O dimensions and formats (autogenerated)
└── network_data.hex        Model weights for NOR flash programming

Doc/
├── Application-Overview.md
├── Boot-Overview.md
├── Build-Options.md
└── Program-Hex-Files-STM32CubeProgrammer.md
```

---

## Known Limitations

- Only RGB888 camera format tested.
- Digits with very similar shapes (e.g. 2↔3, 1↔4) may be confused when the digit is partially out of frame or poorly lit.
- The model was trained on MNIST (digital-style digits); heavily stylised or cursive handwriting may reduce accuracy.

---

## References

- [STEdgeAI documentation](https://stedgeai-dc.st.com/assets/embedded-docs/stneuralart_faqs_update_version.html)
- [Application Overview](Doc/Application-Overview.md)
- [Boot Overview](Doc/Boot-Overview.md)
- [Neural-ART Description](Doc/Neural-ART-Description-and-Operation.md)
