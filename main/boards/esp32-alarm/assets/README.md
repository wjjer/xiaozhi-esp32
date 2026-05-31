# ESP32-Alarm UI Assets

This directory is the production resource area for the `esp32-alarm` board.

## Directory Contract

| Path | Purpose | Firmware usage |
| --- | --- | --- |
| `runtime/` | PNG/JSON files packaged into `assets.bin` by `main/CMakeLists.txt` when `CONFIG_BOARD_TYPE_ESP32_ALARM` is selected. | Runtime UI resources. |
| `../图片/` | Source PNGs and full-screen UI mockups. | Design/source only. |
| `../generated_assets/` | Generated LVGL `.bin`, CBin, RGB565, or C array outputs. | Future optimized runtime resources. |

Do not put full-screen `ui_effect_*.png` files in `runtime/`. They are visual references and should not be flashed as production UI assets unless flash/RAM budget and decode performance are explicitly reviewed.

