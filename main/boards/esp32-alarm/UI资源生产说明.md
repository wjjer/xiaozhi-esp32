# ESP32-Alarm UI 资源生产说明

本文定义 `esp32-alarm` 横屏 UI 从设计素材到固件运行时的生产规则。当前策略是：GUI Guider 负责布局和视觉，固件负责状态和数据。

## 目录职责

| 目录 | 职责 | 是否进固件 |
| --- | --- | --- |
| `图片/` | 设计源 PNG、整屏效果图、切图源文件 | 否 |
| `ui_designer/alarm/` | 正式 GUI Guider 源工程，页面布局和控件结构只在这里编辑 | 否 |
| `ui_designer/alarm/import/image/` | GUI Guider 工程内使用的图片素材副本 | 否 |
| `ui_designer/alarm/generated/images/` | GUI Guider 编译/运行/导出所需的图片转换产物 | 否，除非后续明确复用 |
| `ui_generated/` | GUI Guider 导出后的生成代码，后续作为固件 UI 主来源 | 是 |
| `assets/runtime/` | 固件运行时打包的 PNG/JSON 资源 | 是 |
| `generated_assets/` | 后续性能优化用 LVGL `.bin`、CBin、RGB565、C 数组 | 视接入方式 |

`ui_effect_*.png` 是整屏效果图，只用于视觉对照和评审，不进入 GUI Guider 组件树，也不进入运行时资源目录。

## 当前生产策略

P0 阶段采用“GUI Guider 布局 + PNG 素材”的方式：

1. 源素材保留在 `main/boards/esp32-alarm/图片/`。
2. GUI Guider 使用的素材同步到 `ui_designer/alarm/import/image/`。
3. GUI Guider 工程只使用切图素材，不导入 `ui_effect_*.png`。
4. GUI Guider 编译/运行/导出前，生成 `ui_designer/alarm/generated/images/`。
5. GUI Guider 导出代码输出到 `main/boards/esp32-alarm/ui_generated/`。
6. 固件运行时仍按 PNG 资源名从 assets 分区读取，例如 `icon_ai.png`。

当前不强制把所有 PNG 转成 `.bin` 或 C 数组。只有在启动速度、RAM 峰值、动画流畅度出现明确瓶颈后，再切换为优化格式。

## GUI Guider 工程维护

正式工程：

```text
main/boards/esp32-alarm/ui_designer/alarm/alarm.guiguider
```

维护命令：

```powershell
python main\boards\esp32-alarm\tools_repair_alarm_guiguider_project.py
python main\boards\esp32-alarm\tools_generate_guiguider_images.py --clean
```

说明：

- `tools_repair_alarm_guiguider_project.py` 用于修复 `.guiguider` 的工程元数据、图片字段、编码和路径问题。
- `tools_generate_guiguider_images.py --clean` 用于重建 GUI Guider 的 `generated/images` 索引和图片 C 文件。
- 如果 GUI Guider 打开、编译、导出、运行报图片格式或路径问题，先执行这两个命令。
- 完整脚本分层见 `工具脚本说明.md`。

## 固件运行时资源

同步运行时 PNG：

```powershell
python main\boards\esp32-alarm\tools_sync_runtime_assets.py --clean
```

该脚本会复制非 `ui_effect_*.png` 的 PNG 到 `assets/runtime/`，并生成运行时清单。

`main/CMakeLists.txt` 在 `CONFIG_BOARD_TYPE_ESP32_ALARM` 分支下将 `assets/runtime/` 打包进 `assets.bin`。

## 性能优化转换

`tools_convert_runtime_assets.py` 不是当前主链路。只有后续需要降低 PNG 解码成本时，才生成 LVGL v9 image `.bin`：

```powershell
python main\boards\esp32-alarm\tools_convert_runtime_assets.py --clean
```

默认输出目录：

```text
main/boards/esp32-alarm/generated_assets/lvgl_bin/
```

格式策略：

| 源图片 | 默认转换 |
| --- | --- |
| 不透明 PNG | `RGB565` LVGL `.bin` |
| 带透明 PNG | `RGB565A8` LVGL `.bin` |
| 整屏效果图 | 默认不转换、不进固件 |

加载约束：`tools_convert_runtime_assets.py` 生成的是 LVGL v9 原生 image `.bin`，后续运行时应通过 LVGL image decoder 路径加载，不要传给项目内面向 CBin 的加载器。

注意：生成 `.bin` 后还需要同步修改固件资源加载逻辑；只生成文件不会自动切换运行时资源路径。

## 生产检查清单

发布前确认：

1. `alarm.guiguider` 可在 GUI Guider v1.9.0 中打开、运行、导出。
2. `ui_designer/alarm/import/image/` 不包含 `ui_effect_*.png`。
3. `ui_designer/alarm/generated/images/` 已由脚本重新生成。
4. `ui_generated/` 来自 GUI Guider 导出，不手写页面布局。
5. `assets/runtime/` 不包含 `ui_effect_*.png`。
6. 固件侧没有新增手写 LVGL 页面坐标。
7. `main/ui/` 只保留业务状态、数据更新和页面路由。
8. `idf.py build` 在 `esp32-alarm` 目标下通过。
