# Generated UI Assets

This directory is reserved for converted firmware-ready assets generated from `../图片/` or `../assets/runtime/`.

Recommended future outputs:

| Format | Use case |
| --- | --- |
| LVGL `.bin` / CBin | Preferred for many image assets loaded from `assets.bin`. |
| RGB565/RGB565A8 binary | Preferred when decode speed and RAM usage matter. |
| LVGL C arrays | Good for a small fixed set of critical icons. |

Keep generated files reproducible from scripts and avoid editing them manually.

Use the board conversion script to generate LVGL binary images:

```powershell
python main\boards\esp32-alarm\tools_convert_runtime_assets.py --clean
```

Default conversion policy:

| Input | Output |
| --- | --- |
| Opaque PNG | `RGB565` LVGL `.bin` |
| PNG with alpha | `RGB565A8` LVGL `.bin` |

The default output directory is `generated_assets/lvgl_bin/`.

The generated files are LVGL v9 native image `.bin` files. Load them with the
LVGL image decoder path, not with `LvglCBinImage`.
