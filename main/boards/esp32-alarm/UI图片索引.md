# ESP32-Alarm UI 图片索引

本文用于把 `UI图片需求说明.md` 对应的图片资源整理成开发索引。图片目录为 `main/boards/esp32-alarm/图片/`，目标 UI 尺寸为横屏 `320x240`，状态栏约 `320x24`，内容区约 `320x216`。

## 使用说明

| 类型 | 用法 |
| --- | --- |
| 整屏效果图 | `ui_effect_*.png`，用于对照页面视觉，不建议直接全部塞进固件 |
| 切图素材 | 具体图标、按钮、背景，导入 GUI Guider 工程并可按需转成运行时资源 |
| 当前代码策略 | UI 布局由 GUI Guider v1.9.0 完成，固件侧只绑定导出控件和状态数据 |
| 固件过渡状态 | 当前固件仍有手写 LVGL UI，下一阶段迁移到 `ui_generated/` 导出物 |

## 整屏效果图

| 页面名 | 图片文件名 | 用途 | 建议使用位置 | 类型 |
| --- | --- | --- | --- | --- |
| 启动页 | `ui_effect_launch.png` | 启动页视觉参考 | 开机/初始化阶段 | 整屏效果图 |
| 首页 | `ui_effect_home.png` | 首页横屏布局参考 | 首页主界面 | 整屏效果图 |
| 应用网格 | `ui_effect_app_grid.png` | 应用中心布局参考 | 应用中心 | 整屏效果图 |
| AI 页面 | `ui_effect_ai.png` | AI 对话页面参考 | AI 伙伴页 | 整屏效果图 |
| 闹钟页 | `ui_effect_alarm.png` | 闹钟管理页面参考 | 闹钟列表/编辑入口 | 整屏效果图 |
| 倒计时页 | `ui_effect_timer.png` | 倒计时页面参考 | 时间工具 | 整屏效果图 |
| 秒表页 | `ui_effect_stopwatch.png` | 秒表页面参考 | 时间工具 | 整屏效果图 |
| 专注页 | `ui_effect_focus.png` | 专注时间页面参考 | 专注工具 | 整屏效果图 |
| 夜灯页 | `ui_effect_night_light.png` | 夜灯控制页面参考 | 夜灯工具 | 整屏效果图 |
| 学习页 | `ui_effect_study.png` | 学习占位页参考 | 学习首页 | 整屏效果图 |
| 效果总览 | `ui_effect_gallery.png` | 全部效果图总览 | 设计评审 | 整屏效果图 |

## 启动与状态栏

| 页面名 | 图片文件名 | 用途 | 建议使用位置 | 类型 |
| --- | --- | --- | --- | --- |
| 启动页 | `launch_logo.png` | 产品 Logo | 启动页居中 | 切图素材 |
| 启动页 | `loading_spinner_1.png` 到 `loading_spinner_8.png` | 加载动画帧 | 启动页 Logo 下方 | 切图素材 |
| 状态栏 | `status_wifi.png` | Wi-Fi 状态 | 顶部状态栏左侧 | 切图素材 |
| 状态栏 | `status_4g.png` | 4G 状态 | 顶部状态栏左侧 | 切图素材 |
| 状态栏 | `status_battery.png` | 电量状态 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_charging.png` | 充电状态 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_weather.png` | 天气入口/状态 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_volume.png` | 音量状态 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_alarm.png` | 闹钟状态 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_mic.png` | 麦克风状态 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_network.png` | 网络汇总状态 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_ai.png` | AI 状态 | 顶部状态栏/AI 页 | 切图素材 |
| 状态栏 | `status_bluetooth.png` | 蓝牙状态 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_sleep.png` | 睡眠状态 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_night.png` | 夜间模式 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_day.png` | 白天模式 | 顶部状态栏 | 切图素材 |
| 状态栏 | `status_focus.png` | 专注状态 | 顶部状态栏 | 切图素材 |

## 首页与应用中心

| 页面名 | 图片文件名 | 用途 | 建议使用位置 | 类型 |
| --- | --- | --- | --- | --- |
| 首页 | `home_bg.png` | 首页内容区背景 | 首页 320x216 内容区 | 切图素材 |
| 首页/应用网格 | `icon_ai.png` | AI 入口图标 | 首页快捷入口/应用中心 | 切图素材 |
| 首页/应用网格 | `icon_study.png` | 学习入口图标 | 首页快捷入口/应用中心 | 切图素材 |
| 首页/应用网格 | `icon_alarm.png` | 闹钟入口图标 | 首页快捷入口/应用中心 | 切图素材 |
| 首页/应用网格 | `icon_tools.png` | 工具入口图标 | 首页快捷入口/应用中心 | 切图素材 |
| 首页 | `card_bg.png` | 通用卡片背景 | 首页信息卡片 | 切图素材 |
| 首页 | `clock_bg.png` | 时钟区域背景 | 首页左侧时钟卡片 | 切图素材 |

## AI 页面

| 页面名 | 图片文件名 | 用途 | 建议使用位置 | 类型 |
| --- | --- | --- | --- | --- |
| AI 页面 | `ai_character_idle.png` | AI 待机角色 | AI 页面左侧角色区 | 切图素材 |
| AI 页面 | `ai_character_listening.png` | AI 聆听角色 | AI 状态切换 | 切图素材 |
| AI 页面 | `ai_character_thinking.png` | AI 思考角色 | AI 状态切换 | 切图素材 |
| AI 页面 | `ai_character_speaking.png` | AI 说话角色 | AI 状态切换 | 切图素材 |
| AI 页面 | `mic_button_idle.png` | 麦克风待机按钮 | AI 页面语音按钮 | 切图素材 |
| AI 页面 | `mic_button_listening.png` | 麦克风聆听按钮 | AI 页面语音按钮 | 切图素材 |
| AI 页面 | `mic_button_thinking.png` | 麦克风思考按钮 | AI 页面语音按钮 | 切图素材 |
| AI 页面 | `mic_button_speaking.png` | 麦克风说话按钮 | AI 页面语音按钮 | 切图素材 |
| AI 页面 | `speech_bubble.png` | 对话气泡背景 | AI 页面右侧对话区 | 切图素材 |
| AI 页面 | `quick_question_bg.png` | 快捷问题按钮背景 | AI 页面底部快捷问答 | 切图素材 |

## 天气

| 页面名 | 图片文件名 | 用途 | 建议使用位置 | 类型 |
| --- | --- | --- | --- | --- |
| 天气页 | `weather_sun.png` | 晴天图标 | 当前天气/预报卡片 | 切图素材 |
| 天气页 | `weather_cloud.png` | 多云图标 | 当前天气/预报卡片 | 切图素材 |
| 天气页 | `weather_rain.png` | 雨天图标 | 当前天气/预报卡片 | 切图素材 |
| 天气页 | `weather_snow.png` | 雪天图标 | 当前天气/预报卡片 | 切图素材 |
| 天气页 | `weather_thunder.png` | 雷雨图标 | 当前天气/预报卡片 | 切图素材 |
| 天气页 | `weather_fog.png` | 雾天图标 | 当前天气/预报卡片 | 切图素材 |
| 天气页 | `weather_wind.png` | 风力图标 | 当前天气/预报卡片 | 切图素材 |
| 天气页 | `weather_night.png` | 夜间天气图标 | 夜间天气状态 | 切图素材 |

## 闹钟与时间工具

| 页面名 | 图片文件名 | 用途 | 建议使用位置 | 类型 |
| --- | --- | --- | --- | --- |
| 闹钟页 | `alarm_bg.png` | 闹钟页背景 | 闹钟管理页面 | 切图素材 |
| 倒计时/秒表 | `stopwatch_bg.png` | 时间工具背景 | 秒表/倒计时页面 | 切图素材 |
| 首页/时间工具 | `clock_bg.png` | 时钟背景 | 首页时钟/时间工具 | 切图素材 |
| 时间工具 | `button_start_stopwatch.png` | 开始按钮 | 秒表/倒计时控制区 | 切图素材 |
| 时间工具 | `button_pause_stopwatch.png` | 暂停按钮 | 秒表/倒计时控制区 | 切图素材 |
| 时间工具 | `button_lap.png` | 计次按钮 | 秒表控制区 | 切图素材 |
| 时间工具 | `button_reset_stopwatch.png` | 重置按钮 | 秒表/倒计时控制区 | 切图素材 |
| 秒表页 | `lap_item_bg.png` | 计次列表项背景 | 秒表右侧计次列表 | 切图素材 |
| 通用 | `button_item_bg.png` | 通用按钮背景 | 各工具按钮 | 切图素材 |

## 专注时间

| 页面名 | 图片文件名 | 用途 | 建议使用位置 | 类型 |
| --- | --- | --- | --- | --- |
| 专注页 | `focus_progress_bg.png` | 进度背景 | 专注圆环/进度条底层 | 切图素材 |
| 专注页 | `focus_progress_fill.png` | 进度填充 | 专注进度显示 | 切图素材 |
| 专注页 | `focus_stats_bg.png` | 统计卡片背景 | 专注页右侧统计区 | 切图素材 |
| 专注页 | `focus_tomato.png` | 番茄图标 | 专注页主视觉 | 切图素材 |
| 专注页 | `button_focus_start.png` | 开始专注按钮 | 专注控制区 | 切图素材 |
| 专注页 | `button_focus_pause.png` | 暂停专注按钮 | 专注控制区 | 切图素材 |
| 专注页 | `button_focus_skip.png` | 跳过按钮 | 专注控制区 | 切图素材 |
| 专注页 | `button_focus_settings.png` | 专注设置按钮 | 专注控制区 | 切图素材 |

## 夜灯

| 页面名 | 图片文件名 | 用途 | 建议使用位置 | 类型 |
| --- | --- | --- | --- | --- |
| 夜灯页 | `night_light_on.png` | 夜灯开启状态 | 夜灯主视觉 | 切图素材 |
| 夜灯页 | `night_light_off.png` | 夜灯关闭状态 | 夜灯主视觉 | 切图素材 |
| 夜灯页 | `slider_bg.png` | 亮度滑条背景 | 夜灯亮度调节 | 切图素材 |
| 夜灯页 | `slider_thumb.png` | 滑块 | 亮度/色温拖动控件 | 切图素材 |
| 夜灯页 | `temperature_slider_bg.png` | 色温滑条背景 | 夜灯色温调节 | 切图素材 |
| 夜灯页 | `button_auto_mode.png` | 自动模式按钮 | 夜灯控制区 | 切图素材 |
| 夜灯页 | `button_timer.png` | 定时按钮 | 夜灯控制区 | 切图素材 |
| 夜灯页 | `button_scene_mode.png` | 情景模式按钮 | 夜灯控制区 | 切图素材 |
| 夜灯页 | `button_toggle_light.png` | 开关按钮 | 夜灯控制区 | 切图素材 |

## 学习占位

| 页面名 | 图片文件名 | 用途 | 建议使用位置 | 类型 |
| --- | --- | --- | --- | --- |
| 学习页 | `placeholder_icon_dictionary.png` | 查词入口图标 | 学习首页卡片 | 切图素材 |
| 学习页 | `placeholder_icon_vocabulary.png` | 生词本入口图标 | 学习首页卡片 | 切图素材 |
| 学习页 | `placeholder_icon_word_study.png` | 背单词入口图标 | 学习首页卡片 | 切图素材 |
| 学习页 | `placeholder_icon_k12.png` | K12 入口图标 | 学习首页卡片 | 切图素材 |
| 学习页 | `placeholder_msg_bg.png` | 占位说明背景 | 学习功能占位说明 | 切图素材 |
| 学习页 | `placeholder_face.png` | 占位表情 | 学习占位提示 | 切图素材 |

## 图片预处理建议

| 方案 | 说明 | 建议阶段 |
| --- | --- | --- |
| LVGL C 数组 | 用 LVGL image converter 转为 RGB565/RGB565A8 C 数组，编译进固件，稳定但占 flash | P0/P1 关键图标 |
| RGB565 binary | 图片转 `.bin` 后从分区或文件系统读取，适合较多中等素材 | P1 |
| PNG 文件系统加载 | 保留 PNG，挂载 LittleFS/SPIFFS，并确认 LVGL PNG 解码开启 | P1/P2 |
| 整屏效果图直接使用 | 资源占用较大，且页面无法灵活更新 | 仅设计验证，不建议产品化 |
