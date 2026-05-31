# alarm_ui_assets 说明

`alarm_ui_assets.cpp` / `alarm_ui_assets.h` 是 `esp32-alarm` 的 UI 图片资源桥接层。

它的职责很单一：

- 维护 PNG 文件名到 GUI Guider 导出图像符号的映射
- 向运行时代码提供 `alarm_ui_set_png_src()` 和 `alarm_ui_set_png_fit()` 两个接口
- 让 `lcd_display.cc`、`esp32-alarm.cc` 之类的运行时代码不用关心 GUI Guider 的内部图片符号名

## 文件位置

- 源文件：`main/boards/esp32-alarm/ui_generated/alarm_ui_assets.cpp`
- 头文件：`main/boards/esp32-alarm/ui_generated/alarm_ui_assets.h`

## 生成来源

这两个文件不建议手工长期维护，原则上应从当前 GUI Guider 导出物同步生成或同步更新。

当前流程：

1. 在 `main/boards/esp32-alarm/ui_designer/alarm/alarm.guiguider` 中编辑页面与资源
2. 从 GUI Guider 导出到 `main/boards/esp32-alarm/ui_designer/alarm/generated/`
3. 将导出结果同步到 `main/boards/esp32-alarm/ui_generated/`
4. 确认 `alarm_ui_assets.cpp` 中的资源表和导出的 `gui_guider.h`、`images/` 符号一致

## 资源对齐原则

- 如果 GUI Guider 导出的是 `*_36x36`，运行时资源表也应使用 `*_36x36`
- 如果导出物里只有 `*_28x28`，则资源表改为对应的 `*_28x28`
- 资源表里只保留当前项目实际用到的图片，不保留过期别名

## 使用方式

示例：

```cpp
alarm_ui_set_png_src(ui->screen_home_card_ai_img, "icon_ai.png");
alarm_ui_set_png_fit(ui->screen_home_card_weather_img, "weather_home.png", 36, 36);
```

## 常见问题

### 1. 编译报找不到图片符号

说明 `alarm_ui_assets.cpp` 里的符号名和当前 GUI Guider 导出结果不一致。优先重新导出，再同步 `ui_generated/`。

### 2. 资源文件找得到，但界面不显示

确认：

- `ui_generated/images/` 下是否有对应 `.c` 文件
- `alarm_ui_assets.cpp` 是否把文件名映射到了正确符号
- `ui_generated/generated.mk` 是否仍把这些 image 文件纳入编译

### 3. 后续要切换到 `.bin`

再单独调整桥接层和资源加载路径，不要和当前 GUI Guider PNG 导出混在一起改。
