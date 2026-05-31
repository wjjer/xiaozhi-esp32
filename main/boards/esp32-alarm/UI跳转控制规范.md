# UI跳转控制规范

本文档定义首页按钮、返回手势、路由和页面切换的统一规则。

## 1. 路由原则

- 路由由 `UiRouter` 统一管理。
- 页面切换由路由回调通知显示层。
- 首页按钮点击后先走路由，再走页面 setup。

## 2. 首页入口

首页 21 个按钮必须有点击事件。原则如下：

- 每个按钮都有外层点击事件。
- 图标图片不单独负责跳转。
- 点击后先打印日志，再切路由，再切页面。

## 3. 返回规则

- 二级页面最左侧右滑返回上一级。
- `KEY_BACK` 优先执行 UI 返回。
- 如果没有上一级，返回首页。

## 4. 路由映射

建议遵守下面的映射方式：

| 首页入口 | 建议路由 |
| --- | --- |
| AI | `RouteAI` |
| 学习总入口 | `RouteStudy` 或 `RouteStudyHub` |
| 闹钟 | `RouteAlarm` |
| 工具 | `RouteAppGrid` |
| 天气 | `RouteWeather` |
| 倒计时 | `RouteTimer` |
| 秒表 | `RouteStopwatch` |
| 专注 | `RouteFocus` |
| 夜灯 | `RouteNightLight` |
| 词库 / 词汇 / 生词本 | `RouteWordbook` / `RouteVocab` |
| 翻译 / 英语查询 | `RouteTranslate` |
| K12 | `RouteK12` |

## 5. 事件处理规则

- 每次点击都要能打印日志。
- 页面不存在时，先跳占位页，不要吞点击。
- 新页面上线后，再把占位路由改成真实页面。

## 6. 推荐实现位置

- 首页事件绑定：`main/display/lcd_display.cc`
- 路由常量：`main/ui/ui_router.h`
- 路由状态机：`main/ui/ui_router.cc`

## 7. 验收标准

- 首页 21 个按钮都能点击。
- 每个点击都能看到日志。
- 至少 AI、学习、闹钟、工具、天气、计时器、秒表、专注可跳转。
