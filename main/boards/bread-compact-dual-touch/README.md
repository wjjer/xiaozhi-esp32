# BreadDualTouchBoard - 面包板双网络+LCD+触摸+舵机

## 简介

`BreadDualTouchBoard` 是一个面向面包板开发的双网络板型，支持 LCD 显示、双触摸点交互和舵机控制。

### 主要特性

- ✅ **双网络支持**: WiFi 和 ML307 4G 网络自动切换
- ✅ **LCD 显示**: 240x240 彩色屏幕，支持 GIF 表情动画
- ✅ **双触摸点**: 左右两个触摸区域，触发不同情感回应和舵机动作
- ✅ **舵机控制**: 摇头 + 甩尾巴动作
- ✅ **高质量音频**: ES8311 + ES7210 音频编解码器
- ✅ **单按键控制**: BOOT 按键多功能操作

---

## 硬件配置

### 引脚定义

| 功能 | GPIO/引脚 | 说明 |
|------|-----------|------|
| **音频 I2S** | | |
| I2S_MCLK | GPIO 38 | 音频主时钟 |
| I2S_WS | GPIO 13 | 字选择 |
| I2S_BCLK | GPIO 14 | 位时钟 |
| I2S_DIN | GPIO 12 | 音频输入 (ES7210) |
| I2S_DOUT | GPIO 45 | 音频输出 (ES8311) |
| **音频 I2C** | | |
| I2C_SDA | GPIO 1 | 数据线 |
| I2C_SCL | GPIO 2 | 时钟线 |
| **LCD SPI** | | |
| SPI_MOSI | GPIO 43 | 数据输出 |
| SPI_CLK | GPIO 44 | 时钟 |
| LCD_RES | GPIO 46 | 复位 |
| LCD_DC | GPIO 8 | 数据/命令 |
| LCD_BL | GPIO 42 | 背光 |
| **4G 模块** | | |
| ML307_TX | GPIO 47 | 4G 模块发送 |
| ML307_RX | GPIO 48 | 4G 模块接收 |
| **舵机** | | |
| 摇头舵机 | GPIO 10 | PWM 输出 (50Hz) |
| 甩尾巴舵机 | GPIO 11 | PWM 输出 (50Hz) |
| **其他** | | |
| BOOT 按钮 | GPIO 0 | 启动按键 |
| 内置 LED | GPIO 3 | 状态指示 |

### 触摸传感器

| 触摸点 | Touch Pad | 触发阈值 | 功能 |
|--------|-----------|---------|------|
| 左侧/头部 | TOUCH_PAD_NUM4 | 30000 | 触发"摸头"回应 + 舵机摇头 |
| 右侧/身体 | TOUCH_PAD_NUM5 | 30000 | 触发"摸身体"回应 + 舵机甩尾巴 |

**注意**: ESP32-S3 的 Touch Pad 编号与 GPIO 编号不同，具体对应关系请查阅 ESP32-S3 数据手册。

### 舵机配置

```c
// 舵机引脚
#define SERVO_HEAD_PIN      GPIO_NUM_10  // 摇头舵机
#define SERVO_TAIL_PIN      GPIO_NUM_11  // 甩尾巴舵机

// 摇头参数
#define SERVO_HEAD_AMPLITUDE   30  // 摆动幅度 (度)
#define SERVO_HEAD_PERIOD    500  // 摆动周期 (毫秒)

// 甩尾巴参数
#define SERVO_TAIL_AMPLITUDE   45  // 摆动幅度 (度)
#define SERVO_TAIL_PERIOD    600  // 摆动周期 (毫秒)

// 动作持续时间 (毫秒)
#define SERVO_ACTION_DURATION  2000
```

---

## 硬件连接

### LCD 连接 (SPI)

```
ESP32-S3          LCD (GC9D01N/GC9A01)
-------          --------------------
GPIO 43 (MOSI) →  SDA/DIN
GPIO 44 (CLK)  →  SCL/CLK
GPIO 46 (RES)  →  RES
GPIO 8 (DC)    →  DC
GPIO 42        →  BL (背光)
```

### 音频编解码器连接 (I2S + I2C)

```
ESP32-S3          ES8311/ES7210
-------          --------------
GPIO 38 (MCLK) →  MCLK
GPIO 13 (WS)   →  LRCK/WS
GPIO 14 (BCLK) →  SCK/BCLK
GPIO 12 (DIN)  →  SDIN (ES7210)
GPIO 45 (DOUT) →  SOUT (ES8311)
GPIO 1 (SDA)   →  SDA
GPIO 2 (SCL)   →  SCL
```

### ML307 4G 模块

```
ESP32-S3          ML307 模块
-------          ---------
GPIO 47 (TX)  →  RX
GPIO 48 (RX)  →  TX
```

### 舵机连接

```
ESP32-S3          舵机          5V 电源
-------          -----         -------
GPIO 10     →  摇头舵机信号线 ←
GPIO 11     →  甩尾巴舵机信号线 ←
GND         →  GND            ←
                           →  +5V
```

**重要注意事项**:
- ⚠️ **舵机需要独立 5V 电源供电**，不要使用 ESP32-S3 的 3.3V 直接供电
- 建议使用独立 5V 电源模块供电
- 确保舵机地线与 ESP32-S3 共地
- 舵机工作电流约 200mA - 500mA (根据型号)

---

## 功能说明

### 1. 双网络切换

- **默认网络**: WiFi
- **切换方式**: BOOT 按键双击
- **网络类型会自动保存到 NVS**

### 2. LCD 表情显示

支持以下表情（通过 GIF 动画）：
- happy, sad, angry, thinking, sleepy
- loving, surprised, cool, confused 等 20+ 种

调用方式：
```cpp
Board::GetInstance().GetDisplay()->SetEmotion("happy");
```

### 3. 双触摸交互 + 舵机动作

#### 左侧触摸 (TOUCH_PAD_NUM4) - 触发摇头
- 当设备空闲时触摸头部
- 触发舵机动作：摇头 (左右摆动 30°，周期 500ms)
- 触发语音: "(正在抚摸你的头，请提供相关的情绪价值，回答)"
- 自动启动对话并触发 AI 回应

#### 右侧触摸 (TOUCH_PAD_NUM5) - 触发甩尾巴
- 当设备空闲时触摸身体
- 触发舵机动作：甩尾巴 (上下摆动 45°，周期 600ms)
- 触发语音: "(正在抚摸你的身体，请提供相关的情绪价值，回答)"
- 自动启动对话并触发 AI 回应

**舵机动作参数** (可在 `config.h` 中调整):
- 摇头幅度: 30°
- 摇头周期: 500ms
- 甩尾巴幅度: 45°
- 甩尾巴周期: 600ms
- 动作持续时间: 2000ms

### 4. 按键功能

| 操作 | 功能 |
|------|------|
| 单击 | 切换对话状态（启动/停止） |
| 双击 | 切换网络类型（WiFi ↔ 4G） |
| 长按 | 重置 WiFi 配置 |

---

## 舵机控制 API

### 基本动作

```cpp
#include "board.h"

// 获取板型实例
BreadDualTouchBoard& board = static_cast<BreadDualTouchBoard&>(Board::GetInstance());

// 摇头 (左右摆动)
board.ShakeHead();

// 甩尾巴 (上下摆动)
board.WagTail();

// 同时摇头甩尾巴
board.ShakeHeadAndWagTail();

// 停止所有舵机动作，回到中间位置
board.StopAllServos();
```

### 参数调整

```cpp
// 设置舵机摆动幅度 (角度)
board.SetServoAmplitude(30, 45);  // 头30°, 尾巴45°

// 设置舵机摆动周期 (毫秒)
board.SetServoPeriod(500, 600);  // 头500ms, 尾巴600ms
```

### MCP 协议控制

可通过 MCP 协议远程控制舵机动作：

```json
{
  "method": "servo_action",
  "action": "shake_head"
}
```

支持的动作:
- `shake_head` - 摇头
- `wag_tail` - 甩尾巴
- `shake_head_and_wag_tail` - 同时摇头甩尾巴
- `stop` - 停止所有动作

---

## 舵机调试与校准

### 1. 查看舵机位置

在 `touch_read_task` 中添加日志：

```cpp
ESP_LOGI("SERVO", "Head pos: %d, Tail pos: %d",
    head_servo_->GetPosition(),
    tail_servo_->GetPosition());
```

### 2. 调整舵机中位

如果舵机不在中间位置 (90°)，调整 `Oscillator` 的 `trim` 参数：

```cpp
// 在 servos_init() 中
head_servo_ = new Oscillator(trim_value);  // trim_value 为调整值

// 例如，舵机偏右5度，trim 设为 -5
head_servo_ = new Oscillator(-5);
```

### 3. 调整动作参数

在 `config.h` 中修改：

```c
// 增大摆动幅度
#define SERVO_HEAD_AMPLITUDE   45  // 从 30° 改为 45°

// 减慢摆动速度
#define SERVO_HEAD_PERIOD    800  // 从 500ms 改为 800ms
```

### 4. 舵机限速

为防止舵机移动过快损坏机械结构，可启用限速：

```cpp
// 在 servos_init() 中
head_servo_->SetLimiter(100);  // 限制速度为 100度/秒
tail_servo_->SetLimiter(120);
```

### 5. 手动测试舵机

添加测试函数：

```cpp
void test_servos() {
    // 测试摇头舵机
    for (int i = 45; i <= 135; i += 5) {
        head_servo_->SetPosition(i);
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    head_servo_->SetPosition(90);

    // 测试甩尾巴舵机
    for (int i = 45; i <= 135; i += 5) {
        tail_servo_->SetPosition(i);
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    tail_servo_->SetPosition(90);
}
```

---

## 编译配置

### 1. 添加到 Kconfig.projbuild

在 `main/Kconfig.projbuild` 中添加板型选项：

```kconfig
config BOARD_TYPE_BREAD_COMPACT_DUAL_TOUCH
    bool "面包板双网络+LCD+触摸"
    depends on IDF_TARGET_ESP32S3
    select LV_USE_GIF
    select LV_GIF_CACHE_DECODE_DATA
```

### 2. 添加到 idf_component.yml

在 `main/idf_component.yml` 中确保包含必要的组件：

```yaml
dependencies:
  espressif/esp_lcd_gc9d01n:
    version: "*"
  espressif/esp_lcd_gc9a01:
    version: "*"
```

### 3. 配置选项

在 `idf.py menuconfig` 中配置：
- `Xiaozhi Assistant -> Board Type` → 选择 `面包板双网络+LCD+触摸`
- 可选：选择 LCD 驱动类型（GC9D01N 或 GC9A01）

---

## 触摸阈值校准

### 1. 添加调试任务

在板型类中添加校准任务：

```cpp
static void touch_calibrate_task(void* arg) {
    BreadDualTouchBoard* self = static_cast<BreadDualTouchBoard*>(arg);

    while (1) {
        uint32_t left_val, right_val;
        touch_pad_read_raw_data(TOUCH_LEFT_PAD, &left_val);
        touch_pad_read_raw_data(TOUCH_RIGHT_PAD, &right_val);

        ESP_LOGI("TOUCH_CAL", "Left: %lu, Right: %lu", left_val, right_val);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
```

在构造函数中启动：

```cpp
xTaskCreate(touch_calibrate_task, "touch_cal", 2048, this, 5, NULL);
```

### 2. 校准步骤

1. 运行固件，观察串口输出的触摸值
2. 记录未触摸时的基准值（通常 < 10000）
3. 用手指触摸各触摸点，记录触摸后的值（通常 > 30000）
4. 在 `config.h` 中调整 `TOUCH_THRESHOLD` 为两者的中间值

---

## 常见问题

### Q1: LCD 不显示
- 检查 SPI 引脚连接是否正确
- 确认 LCD 驱动芯片型号（GC9D01N 或 GC9A01）
- 检查背光引脚和电源连接

### Q2: 触摸不灵敏
- 运行校准任务调整 `TOUCH_THRESHOLD`
- 确认 Touch Pad 编号正确 (4, 5)
- 检查手指是否干燥（触摸电容敏感）

### Q3: 音频无输出
- 检查 ES8311 I2C 地址是否正确
- 确认 I2S 引脚连接
- 检查音量设置（默认 100）

### Q4: 4G 模块无法连接
- 检查 TX/RX 引脚是否交叉连接
- 确认 ML307 模块供电正常
- 查看串口日志获取详细错误信息

### Q5: 舵机不动
- 检查舵机电源是否正常 (需要 5V)
- 确认 GPIO 引脚连接正确 (10, 11)
- 检查舵机地线是否与 ESP32 共地
- 查看串口日志确认舵机初始化成功

### Q6: 舵机抖动
- 确认使用独立电源供电
- 增加电源滤波电容 (1000μF)
- 检查 PWM 频率是否为 50Hz
- 调整舵机限速参数

### Q7: 舵机角度偏移
- 调整 `Oscillator` 的 `trim` 参数
- 使用舵机校准功能找出中位偏差值
- 在 `config.h` 中添加 `SERVO_HEAD_TRIM` 和 `SERVO_TAIL_TRIM`

### Q8: 触摸后舵机不动作
- 确认设备处于空闲状态 (`kDeviceStateIdle`)
- 检查触摸阈值是否正确
- 查看串口日志确认触摸检测到
- 确认舵机初始化成功

---

## 扩展功能

### 添加电池管理

如需添加电池电量检测，参考 `zhengchen_eye` 板型的 `PowerManager` 类实现。

### 添加温度传感器

参考 `power_manager.h` 中的温度读取实现。

### 添加更多舵机

在 `config.h` 中添加引脚定义：

```c
#define SERVO_EXTRA_PIN GPIO_NUM_12
```

在板型类中添加舵机实例：

```cpp
Oscillator* extra_servo_;

void servos_init() {
    extra_servo_ = new Oscillator(0);
    extra_servo_->Attach(SERVO_EXTRA_PIN);
    extra_servo_->SetA(30);
    extra_servo_->SetT(500);
}
```

---

## 舵机技术细节

### Oscillator 类

**功能**:
- 正弦波摆动控制
- 可调幅度、周期、相位、偏移
- 支持限速
- 自动定时刷新

**关键方法**:
```cpp
Oscillator(int trim);              // 构造函数，trim 用于校准
void Attach(int pin, bool rev);    // 绑定 GPIO，rev 是否反向
void SetA(unsigned int amplitude); // 设置幅度
void SetT(unsigned int period);    // 设置周期
void Play();                       // 开始摆动
void Stop();                       // 停止摆动
void Refresh();                    // 刷新位置
```

### 定时器机制

**刷新定时器**: 30ms 一次，持续更新舵机位置

**动作定时器**: 单次触发，动作持续时间后停止

```cpp
// 刷新定时器
esp_timer_create(&refresh_timer_args, &servo_timer_);
esp_timer_start_periodic(servo_timer_, 30000);  // 30ms

// 动作定时器
esp_timer_create(&action_timer_args, &timer);
esp_timer_start_once(timer, SERVO_ACTION_DURATION * 1000);  // 2秒
```

---

## 相关文档

| 文档 | 说明 |
|------|------|
| [快速开始指南](QUICK_START.md) | 快速编译和配置指南 |
| [舵机控制详细指南](../../docs/bread-dual-touch-servo-guide.md) | 舵机详细控制说明 |
| [双眼显示与触摸交互技术文档](../../docs/zhengchen-eye-touch-and-display-guide.md) | 显示和触摸技术详解 |
| [自定义开发板指南](../README.md) | 开发板开发指南 |

---

## 许可

遵循项目 MIT 许可证。
