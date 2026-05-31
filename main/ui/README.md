# UI Subsystem

`main/ui/` 现在只作为 `esp32-alarm` 的业务状态与路由层，不再承担页面布局、控件树或视觉样式。

## 文档入口

| 文档 | 作用 |
| --- | --- |
| [../boards/esp32-alarm/UI文档总览.md](../boards/esp32-alarm/UI文档总览.md) | UI 总目录。 |
| [../boards/esp32-alarm/UI程序适配规范.md](../boards/esp32-alarm/UI程序适配规范.md) | 适配边界和职责划分。 |
| [../boards/esp32-alarm/UI跳转控制规范.md](../boards/esp32-alarm/UI跳转控制规范.md) | 路由、点击和返回规则。 |

## Current Role

- `UiSystem` 维护 UI 业务状态，例如 Boot、Home、AppGrid、AI 聆听/思考/回答、闹钟响铃。
- `UiRouter` 维护当前路由，并通过回调通知显示适配层切换页面。
- 页面布局、坐标、控件树、图片摆放必须在 GUI Guider 工程中维护。

## Runtime Flow

```text
business code / board bridge
        |
        v
main/ui/UiSystem + UiRouter
        |
        v
main/display/lcd_display.cc
        |
        v
main/boards/esp32-alarm/ui_generated/
```

## Boundary

- `main/ui/` 不创建 LVGL 控件。
- `main/ui/` 不保存页面坐标。
- `main/ui/` 不直接引用 GUI Guider 生成控件。
- `lcd_display.cc` 只把路由和状态映射到 `ui_generated` 的 screen 与控件。
- `ui_scene_*`、`ui_scene_manager`、`ui_status_bar` 属于旧手写 LVGL 过渡代码，`esp32-alarm` 当前不再编译它们。

## Active Files

| File | Role |
| --- | --- |
| `ui_system.h/.cc` | 全局 UI 状态与首页状态文本 |
| `ui_router.h/.cc` | 路由常量、当前路由、跳转回调 |

## Adding New UI

1. 在 `main/boards/esp32-alarm/ui_designer/alarm/alarm.guiguider` 中新增页面或控件。
2. 从 GUI Guider 导出到 `main/boards/esp32-alarm/ui_generated/`。
3. 在 `lcd_display.cc` 中绑定生成 screen 或控件。
4. 如需业务状态，再扩展 `UiSystem` 或 `UiRouter`。

不要在 `main/ui/` 中新增手写 LVGL 场景类。
