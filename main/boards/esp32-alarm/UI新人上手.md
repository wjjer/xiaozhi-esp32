# UI新人上手

这份文档给第一次接手 `esp32-alarm` UI 的人用。

## 你先看什么

1. 看 [UI文档总览.md](./UI文档总览.md)。
2. 再看 [UI制作规范.md](./UI制作规范.md)。
3. 然后看 [UI素材导入规范.md](./UI素材导入规范.md)。
4. 最后看 [UI程序适配规范.md](./UI程序适配规范.md) 和 [UI跳转控制规范.md](./UI跳转控制规范.md)。

## 你先改哪里

- 页面布局改 `main/boards/esp32-alarm/ui_designer/alarm/alarm.guiguider`
- 生成结果看 `main/boards/esp32-alarm/ui_generated/`
- 页面路由改 `main/ui/ui_router.*`
- 页面适配改 `main/display/lcd_display.cc`

## 你先不要动哪里

- 不要直接在 `main/ui/` 里重画页面。
- 不要同时维护手写 LVGL 和 GUI Guider 两套首页。
- 不要在没有导出物的情况下直接改 `ui_generated/` 的控件定义。

## 标准操作流程

1. 在 GUI Guider 里改页面。
2. 导出到 `ui_generated/`。
3. 确认 `alarm_ui_assets.cpp` 的资源映射没有错。
4. 绑定点击事件和路由。
5. 跑 `idf.py build`。
6. 看到真机后再修触摸和视觉细节。

## 常见问题

- 如果编译报 `struct lv_ui has no member`，说明 GUI Guider 导出字段名和固件适配层不一致。
- 如果编译报图片符号不存在，说明 `alarm_ui_assets.cpp` 和导出的 `images/` 不一致。
- 如果能显示但不能点，优先检查按钮外层是否绑定了事件，图标是否还在抢点击。
- 如果页面跳错，先看 `UiRouter` 的路由常量是否一致。
