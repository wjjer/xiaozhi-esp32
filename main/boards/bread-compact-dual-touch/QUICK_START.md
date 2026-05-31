# BreadDualTouchBoard 快速开始

## 功能概述

- ✅ **双网络**: WiFi + ML307 4G 自动切换
- ✅ **LCD 显示**: 240x240 GIF 表情动画
- ✅ **双触摸**: 左侧/头部 + 右侧/身体 触摸交互
- ✅ **舵机控制**: 摇头 + 甩尾巴动作
- ✅ **音频**: ES8311 输出 + ES7210 输入

---

## 编译步骤

### 1. 配置项目

```bash
idf.py menuconfig
```

在菜单中选择：
```
Xiaozhi Assistant -> Board Type -> 面包板双网络+LCD+触摸
Xiaozhi Assistant -> BREAD_COMPACT_DUAL_TOUCH LCD Type -> GC9A01, 分辨率240*240 (推荐)
```

### 2. 编译固件

```bash
idf.py build
```

### 3. 烧录固件

```bash
idf.py -p COM端口 flash monitor
```

---

## 硬件连接

### LCD (SPI)
```
ESP32-S3    LCD
---------   ------
GPIO 43 →   SDA/MOSI
GPIO 44 →   SCL/CLK
GPIO 46 →   RES
GPIO 8  →   DC
GPIO 42 →   BL (背光)
VCC    →   3.3V
GND    →   GND
```

### 音频编解码器 (ES8311 + ES7210)
```
ESP32-S3    Codec
---------   ------
GPIO 38 →   MCLK
GPIO 13 →   LRCK/WS
GPIO 14 →   SCK/BCLK
GPIO 12 →   SDIN (ES7210)
GPIO 45 →   SOUT (ES8311)
GPIO 1  →   SDA (I2C)
GPIO 2  →   SCL (I2C)
VCC    →   3.3V
GND    →   GND
```

### ML307 4G 模块 (可选)
```
ESP32-S3    ML307
---------   ------
GPIO 47 →   RX
GPIO 48 →   TX
VCC    →   3.3V
GND    →   GND
```

### 舵机
```
ESP32-S3    舵机
---------   -----
GPIO 10 →   摇头舵机信号线
GPIO 11 →   甩尾巴舵机信号线
VCC    →   5V (独立电源)
GND    →   GND
```

**注意**: 舵机需要独立 5V 电源供电，不要直接使用 ESP32 的 3.3V

---

## 触摸操作

| 触摸位置 | 触发动作 |
|---------|---------|
| 左侧 (TOUCH_PAD_NUM4) | 舵机摇头 + AI 提供情绪价值 |
| 右侧 (TOUCH_PAD_NUM5) | 舵机甩尾巴 + AI 提供情绪价值 |

**注意**: 触摸功能仅在设备空闲状态（`kDeviceStateIdle`）时触发

---

## 按键操作

| 操作 | 功能 |
|------|------|
| 单击 BOOT | 切换对话状态（启动/停止） |
| 双击 BOOT | 切换网络类型（WiFi ↔ 4G） |
| 长按 BOOT | 重置 WiFi 配置 |

---

## 触摸阈值校准

### 步骤

1. 在代码中添加调试任务（参考 README.md）
2. 运行固件，观察串口输出的触摸值
3. 调整 `config.h` 中的 `TOUCH_THRESHOLD`

```c
// config.h
#define TOUCH_THRESHOLD 30000  // 根据实际情况调整
```

---

## 默认引脚配置

| 功能 | GPIO | 说明 |
|------|------|------|
| 音频 I2S | 38,13,14,12,45 | MCLK,WS,BCLK,DIN,DOUT |
| 音频 I2C | 1,2 | SDA,SCL |
| LCD SPI | 43,44,46,8,42 | MOSI,CLK,RES,DC,BL |
| ML307 | 47,48 | TX,RX |
| 舵机 | 10,11 | 摇头,甩尾巴 |
| BOOT 按键 | 0 | |
| LED | 3 | 内置 LED |

---

## 故障排查

### LCD 不显示
- 检查 SPI 引脚连接
- 确认背光连接 (GPIO 42)
- 检查 LCD 驱动类型（GC9A01 或 GC9D01N）

### 触摸无响应
- 运行校准任务查看触摸值
- 调整 `TOUCH_THRESHOLD`
- 确认 Touch Pad 编号正确 (4, 5)

### 舵机无响应
- 检查舵机电源 (需要 5V 独立供电)
- 确认 GPIO 引脚正确 (10, 11)
- 检查地线是否共地
- 查看串口日志确认舵机初始化成功

### 音频无输出
- 检查 ES8311 I2C 地址 (默认 0x18)
- 确认 I2S 引脚连接
- 检查音量设置（默认 100）

---

## 相关文档

- [完整说明文档](README.md)
- [双眼显示与触摸交互技术文档](../../docs/zhengchen-eye-touch-and-display-guide.md)
- [自定义开发板指南](../README.md)
