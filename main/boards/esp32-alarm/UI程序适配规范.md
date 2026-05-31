# UI程序适配规范

本文档定义 GUI Guider UI 和固件程序的适配边界。

## 1. 责任划分

- `main/ui/` 负责业务状态、路由、页面状态、数据更新。
- `main/display/lcd_display.cc` 负责显示适配、页面切换、UI 控件绑定。
- `main/boards/esp32-alarm/ui_generated/` 负责 GUI Guider 生成代码。
- `main/boards/esp32-alarm/esp32-alarm.cc` 负责板级启动、硬件桥接和状态桥接。

## 2. `main/ui/` 里能做什么

- 维护当前路由。
- 维护首页、AI、学习、闹钟等业务状态。
- 触发页面切换回调。
- 维护需要展示给 UI 的数据文本。

## 3. `main/ui/` 里不能做什么

- 不能创建 LVGL 控件。
- 不能写页面坐标。
- 不能直接引用 GUI Guider 生成的控件树。
- 不能复制一份手写 UI 逻辑去和 GUI Guider 并存。

## 4. `lcd_display.cc` 的职责

- 初始化屏幕、LVGL 和触摸。
- 把路由映射到对应 screen。
- 把 `SetHomeTime`、`SetHomeStatus`、`SetAiState`、`SetAiMessage` 等状态接口映射到生成控件。
- 绑定首页按钮、返回按钮和页面内事件。

## 5. `ui_generated/` 的职责

- 保存 GUI Guider 导出结果。
- 保存页面控件名和资源名。
- 保存页面的默认样式和控件树。

## 6. 适配规则

- 适配层只做“映射”，不做“重画”。
- 如果 GUI Guider 页面里控件字段变了，先改 GUI Guider 工程，再导出。
- 不要在固件里直接补 GUI Guider 没有导出的控件字段。

## 7. 验证要求

- 导出后至少执行一次 `idf.py build`。
- 编译通过后再调试触摸和路由。
- 页面显示异常时，优先检查导出字段名和资源符号名。
