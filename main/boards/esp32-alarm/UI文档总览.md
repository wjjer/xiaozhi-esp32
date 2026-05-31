# esp32-alarm UI 文档总览

本目录把 `esp32-alarm` 的 GUI Guider UI 工作流拆成标准文档。目标是让新人可以按文档直接完成 UI 制作、资源导入、程序适配和页面跳转接入。

## 文档入口

| 文档 | 作用 |
| --- | --- |
| [UI制作规范.md](./UI制作规范.md) | 说明 GUI Guider 工程如何制作页面、控件、状态和视觉规范。 |
| [UI素材导入规范.md](./UI素材导入规范.md) | 说明 PNG、图标、背景、导出物如何导入和同步。 |
| [UI程序适配规范.md](./UI程序适配规范.md) | 说明 `lcd_display.cc`、`main/ui/`、`ui_generated/` 的职责边界。 |
| [UI跳转控制规范.md](./UI跳转控制规范.md) | 说明路由、返回、首页入口、二级页跳转和点击事件如何绑定。 |
| [UI新人上手.md](./UI新人上手.md) | 说明新人从 0 到能改 UI 的最短路径。 |
| [UI资源生产说明.md](./UI资源生产说明.md) | 说明图片资源与导出资源的生产、同步、打包方式。 |
| [UI图片索引.md](./UI图片索引.md) | 说明当前项目里各 PNG 的用途和落点。 |
| [主页素材表.md](./主页素材表.md) | 说明主页需要的所有素材和按钮资源。 |

## 目录约定

- `main/boards/esp32-alarm/ui_designer/alarm/` 是 GUI Guider 源工程。
- `main/boards/esp32-alarm/ui_generated/` 是 GUI Guider 导出物，固件直接编译使用。
- `main/boards/esp32-alarm/assets/runtime/` 是当前运行时 PNG 资源。
- `main/ui/` 只保留业务状态、路由和数据更新，不再放页面布局。

## 推荐流程

1. 先看 [UI制作规范.md](./UI制作规范.md)。
2. 再看 [UI素材导入规范.md](./UI素材导入规范.md)。
3. 页面做好后，按 [UI程序适配规范.md](./UI程序适配规范.md) 接到固件。
4. 最后按 [UI跳转控制规范.md](./UI跳转控制规范.md) 补齐点击和返回。
5. 新人直接看 [UI新人上手.md](./UI新人上手.md) 走一遍。
