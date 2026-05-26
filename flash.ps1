<#
.SYNOPSIS
    Flash the STM32N6570-DK board (FSBL + application).

.DESCRIPTION
    Flashes the two required images to NOR flash via SWD/ST-LINK:
      1. FSBL      → 0x70000000  (first-stage bootloader, rarely changes)
      2. Application → 0x70100000 (Project_sign.bin, rebuilt every time)

    Model weights are NOT re-flashed here; run with -Weights to include them
    (only needed when the ONNX model changes, not on code changes).

.PARAMETER Weights
    Also flash Model/STM32N6570-DK/network_data.hex.

.PARAMETER AppOnly
    Skip the FSBL, flash only the application binary.

.EXAMPLE
    .\flash.ps1               # FSBL + app
    .\flash.ps1 -AppOnly      # app only (faster, FSBL already on board)
    .\flash.ps1 -Weights      # FSBL + app + model weights
#>
param(
    [switch]$Weights,
    [switch]$AppOnly
)

$ErrorActionPreference = "Stop"

# ── Paths ────────────────────────────────────────────────────────────────────
$ROOT   = $PSScriptRoot
$CLI    = "C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe"
$DKEL   = "C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\ExternalLoader\MX66UW1G45G_STM32N6570-DK.stldr"
$FSBL   = "$ROOT\FSBL\ai_fsbl.hex"
$APP    = "$ROOT\Application\STM32N6570-DK\STM32CubeIDE\Debug\Project_sign.bin"
$MODEL  = "$ROOT\Model\STM32N6570-DK\network_data.hex"

# ── Checks ───────────────────────────────────────────────────────────────────
if (-not (Test-Path $CLI))   { Write-Error "STM32CubeProgrammer not found at:`n  $CLI`nInstall it from st.com"; exit 1 }
if (-not (Test-Path $DKEL))  { Write-Error "External loader not found:`n  $DKEL"; exit 1 }
if (-not (Test-Path $APP))   { Write-Error "Signed binary not found:`n  $APP`nBuild the project in STM32CubeIDE first."; exit 1 }

Write-Host ""
Write-Host "Board  : STM32N6570-DK"
Write-Host "Binary : $APP"
Write-Host ""
Write-Host "Boot switch: DEV mode for flashing. Switch to BOOT FROM FLASH only after."
Write-Host ""

# ── Flash ────────────────────────────────────────────────────────────────────
function Flash($label, $file, $addr) {
    Write-Host "=== $label ===" -ForegroundColor Cyan
    $args = @("-c", "port=SWD", "mode=HOTPLUG", "-el", $DKEL, "-hardRst", "-w", $file)
    if ($addr) { $args += $addr }
    & $CLI @args
    if ($LASTEXITCODE -ne 0) { Write-Error "$label failed (exit $LASTEXITCODE)"; exit 1 }
    Write-Host ""
}

if (-not $AppOnly) {
    Flash "FSBL" $FSBL $null
}
Flash "Application" $APP "0x70100000"

if ($Weights) {
    if (-not (Test-Path $MODEL)) { Write-Error "Model weights not found: $MODEL"; exit 1 }
    Flash "Model weights" $MODEL $null
}

Write-Host "Done. Set boot switch to BOOT FROM FLASH and power cycle." -ForegroundColor Green
