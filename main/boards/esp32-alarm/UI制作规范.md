# UI制作规范

本文档定义 `esp32-alarm` 使用 GUI Guider v1.9.0 制作 UI 的规则。

## 1. 设计边界

- 只在 GUI Guider 工程里做页面布局、控件树、视觉样式和资源引用。
- 不在 `main/ui/` 里写布局，不手写页面坐标。
- 页面必须按 `320x240` 横屏设计。
- 首页、AI 页、学习页、闹钟页、天气页等都以 GUI Guider 页面为主。

## 2. 工程位置

- GUI Guider 源工程：`main/boards/esp32-alarm/ui_designer/alarm/`
- 导出代码：`main/boards/esp32-alarm/ui_generated/`
- 运行时 PNG：`main/boards/esp32-alarm/assets/runtime/`

## 3. 页面命名

- 页面名使用 `screen_boot`、`screen_home`、`screen_ai`、`screen_study`、`screen_alarm`、`screen_weather`、`screen_timer`、`screen_stopwatch`、`screen_focus`、`screen_night_light`、`screen_app_grid`。
- 首页卡片采用 `screen_home_card_*` 命名。
- 如果 GUI Guider 导出的字段名变了，先修正工程，再导出代码，不要在固件里硬猜字段。

## 4. 视觉规则

- 启动页用单独图片，不混入内容态逻辑。
- 首页内容态保留时间、日期、状态卡、卡片入口。
- AI 页保留对话区、状态图标、快捷问句和语音状态。
- 学习页保留词库、翻译历史、生词本、K12 入口占位。
- 需要等待接入的内容，直接在页面上显示“待接入”提示，不要空白。

## 5. 按钮规则

- 所有可点击入口必须是真正的按钮或可绑定事件的对象。
- 卡片内部的图片只负责显示，不单独承担路由。
- 触摸点击优先绑定到卡片外层按钮，避免图片抢事件。

## 6. 导出规则

- GUI Guider 导出后必须同步到 `ui_generated/`。
- 导出物中只保留一套来源，不保留两套 UI 逻辑。
- 导出后立即执行编译验证，避免 GUI Guider 和固件字段名不一致。

## 7. 验收标准

- GUI Guider 工程能打开、能导出、能运行模拟器。
- `idf.py build` 通过。
- 首页、AI 页、学习页、闹钟页至少有可见骨架和可点击入口。
