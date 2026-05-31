# esp32-alarm GUI Guider Designer

本目录存放 `esp32-alarm` 的 GUI Guider 设计工程。

## 正式工程

```text
alarm/alarm.guiguider
```

该工程是 AI 闹钟 UI 的唯一布局来源。页面坐标、控件树、图片摆放、字号、颜色和视觉层级都应在 GUI Guider 中编辑。

## 参考工程

```text
GUI/GUI.guiguider
```

该工程是用户新建的 GUI Guider v1.9.0 可运行参考工程，只用于对照工程结构和排查 GUI Guider 兼容问题，不作为产品 UI 来源。

## 工作流

1. 使用 GUI Guider v1.9.0 打开 `alarm/alarm.guiguider`。
2. 修改页面布局和控件命名。
3. 运行 `tools_generate_guiguider_images.py --clean` 生成图片索引。
4. 从 GUI Guider 导出代码到 `../ui_generated/`。
5. 固件侧只绑定生成控件，不在 C/C++ 中重画页面布局。

## 修复命令

如果工程打不开，或编译/导出/运行时报图片格式、路径、模板元数据问题，先执行：

```powershell
python main\boards\esp32-alarm\tools_repair_alarm_guiguider_project.py
python main\boards\esp32-alarm\tools_generate_guiguider_images.py --clean
```

## 约束

- 不导入 `ui_effect_*.png`，它们只作为整屏效果图参考。
- 不在 `ui_designer/` 内手写固件业务逻辑。
- 不把 `GUI/` 参考工程当作正式导出来源。
