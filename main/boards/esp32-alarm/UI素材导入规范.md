# UI素材导入规范

本文档定义 PNG 素材、图标、背景、导出资源的导入方式。

## 1. 资源目录

- 原始和可视化参考资源：`main/boards/esp32-alarm/参考/`
- 运行时 PNG：`main/boards/esp32-alarm/assets/runtime/`
- GUI Guider 工程导入目录：`main/boards/esp32-alarm/ui_designer/alarm/import/image/`
- GUI Guider 生成图片目录：`main/boards/esp32-alarm/ui_designer/alarm/generated/images/`

## 2. 导入原则

- 设计稿里的参考图只用于对照，不直接进固件。
- GUI Guider 需要什么素材，就把对应 PNG 导入到工程。
- 运行时如果仍使用 PNG，就放在 `assets/runtime/`。
- 如果某张图在 GUI Guider 和运行时都要用，两个目录都要同步，但文件名要一致。

## 3. 命名规则

- 文件名使用小写加下划线，如 `icon_ai.png`、`home_bg.png`。
- 同一图标不同尺寸允许保留后缀，如 `icon_ai_36_36.png`。
- 如果 GUI Guider 导出符号名变化，先同步资源文件名，再更新 `alarm_ui_assets.cpp`。

## 4. 同步规则

- 先同步 `ui_designer/alarm/import/image/`。
- 再导出 GUI Guider 到 `ui_generated/`。
- 再同步运行时 PNG 到 `assets/runtime/`。
- 如果资源改名，优先用脚本或统一替换，不要手工拆散多套文件。

## 5. 不要做的事

- 不要把 `ui_effect_*.png` 当成运行时资源。
- 不要把 GUI Guider 工程里的中间文件当成固件依赖。
- 不要随意删除 `ui_generated/images/` 里已经被导出的符号对应资源，除非确认代码里没有引用。

## 6. 常见检查项

- `ui_generated/alarm_ui_assets.cpp` 的映射名与导出符号一致。
- `ui_generated/gui_guider.h` 里的资源声明与 `images/` 中的 `.c` 文件一致。
- `assets/runtime/` 中的文件名与固件查找逻辑一致。
