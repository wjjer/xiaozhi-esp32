# esp32-alarm

`esp32-alarm` 是一块横屏 320x240 的 AI 闹钟板，目标是儿童桌面学习陪伴场景。

当前实现只影响 `esp32-alarm`，其他板子保持原有逻辑不变。

## 当前约定

| 项目 | 说明 |
| --- | --- |
| 板级基类 | `DualNetworkBoard` |
| 网络 | `Wi-Fi + ML307C 4G` |
| UI 方案 | GUI Guider 生成 `ui_generated/`，`main/ui/` 只保留路由与状态层 |
| 运行时图片 | 继续使用 `assets/runtime/` 下的 PNG |
| 屏幕 | SPI，`320x240` |
| 触摸 | I2C 触摸，当前代码对接 `CST328`，`INT GPIO4` |

## UI 文档入口

| 文档 | 作用 |
| --- | --- |
| [UI文档总览.md](./UI文档总览.md) | UI 文档入口和目录索引。 |
| [UI制作规范.md](./UI制作规范.md) | GUI Guider 页面制作规范。 |
| [UI素材导入规范.md](./UI素材导入规范.md) | PNG / 图标 / 导出资源导入规范。 |
| [UI程序适配规范.md](./UI程序适配规范.md) | 固件适配层职责边界。 |
| [UI跳转控制规范.md](./UI跳转控制规范.md) | 页面跳转和按钮事件规范。 |
| [UI新人上手.md](./UI新人上手.md) | 新人快速上手说明。 |

## 引脚定义

| 模块 | 定义 |
| --- | --- |
| 音频 I2S | `MCLK GPIO13` `WS GPIO11` `BCLK GPIO12` `DIN GPIO10` `DOUT GPIO14` |
| 音频 Codec | `I2C SDA GPIO1` `I2C SCL GPIO2` `ES8311` `PA_EN GPIO6` |
| 显示 | `ST7789V`，`SCLK GPIO39` `MOSI GPIO40` `DC GPIO41` `CS GPIO42` `RST GPIO38` `BL GPIO21` |
| 显示参数 | `320x240`，`swap_xy=true`，`mirror_x=true`，`mirror_y=false`，`spi_mode=0` |
| 触摸 | `CST328`，`SDA/SCL GPIO1/GPIO2`，`RST GPIO8` |
| 4G | `ML307C_TX GPIO43`，`ML307C_RX GPIO44`，`DTR NC` |
| 按键 | `KEY_AI GPIO0`，`KEY_BACK GPIO20`，`KEY_UP GPIO21` |
| 蓝牙串口 | `BL_TX GPIO17`，`BL_RX GPIO18` |

## 按键语义

- `KEY_AI`：进入 AI 对话，并切换聊天状态。
- `KEY_BACK`：UI 返回上一级；如果没有上一级，则回到首页。
- `KEY_UP`：软关机/唤醒相关控制，当前实现会停止听写并回到 idle。

## 文件职责

| Path | 作用 |
| --- | --- |
| `esp32-alarm.cc` | 板级启动、触摸、网络桥接、按键桥接 |
| `config.h` | `esp32-alarm` 的硬件引脚与显示参数 |
| `ui_designer/alarm/` | GUI Guider 源工程 |
| `ui_generated/` | GUI Guider 导出代码 |
| `assets/runtime/` | 当前运行时 PNG 资源 |
| `参考/` | 原理图与测试参考代码 |

## 备注

- 这块板的 UI 由 GUI Guider 负责布局生成，板级代码只负责桥接控件状态。
- 触摸驱动依赖必须和 `idf_component.yml` 保持一致，否则会出现头文件或符号缺失。
