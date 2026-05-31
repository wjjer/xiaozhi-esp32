#ifndef ML307C_BOARD_H
#define ML307C_BOARD_H

#include "ml307_board.h"
#include "at_command_tester.h"
#include <memory>
#include <at_modem.h>

class Ml307CBoard : public Ml307Board {
protected:
    virtual void OnModemReady() override;
    virtual void StartNetwork() override;  // 重写StartNetwork以提供自定义的网络初始化逻辑
    virtual std::string GetBoardJson() override;
    virtual std::string GetDeviceStatusJson() override;
    
    // 等待调制解调器就绪
    bool WaitForModemReady(AtUart* uart);

public:
    Ml307CBoard(gpio_num_t tx_pin, gpio_num_t rx_pin, gpio_num_t dtr_pin = GPIO_NUM_NC);
    virtual ~Ml307CBoard();

    // AT命令测试
    void TestAtCommands(const std::string& category = "all");

    // 软SIM卡切换
    bool SwitchSoftSimSlot(int target_slot);
    int GetCurrentSoftSimSlot() const { return current_soft_sim_slot_; }
    
    // 手动模式：处理Boot按键长按事件
    void HandleBootButtonLongPress();
    
    // 重启ML307C
    void RestartModem();

protected:
    int current_soft_sim_slot_ = 0;  // 当前软SIM卡槽（0或1）
    
    // 信号强度历史记录
    int sim0_signal_strength_ = -1;
    int sim1_signal_strength_ = -1;
    
    // 自动模式任务
    TaskHandle_t auto_mode_task_handle_ = NULL;
    
    // 自定义网络任务,包含SIM切换逻辑
    void NetworkTaskWithSimFailover();
    bool TryReuseExistingModem();
    bool DetectModemAtFixedBaud(int baud_rate, int timeout_ms, int max_retries);
    
    // 自动模式任务函数
    static void AutoModeTaskEntry(void* arg);
    void AutoModeTask();
    
    // 检测指定SIM卡的信号强度
    int GetSimSignalStrength(int slot);
    
    // 切换到信号更强的SIM卡
    bool SwitchToStrongerSignalSim();
    
    // 停止重连标志
    bool stop_reconnect_ = false;
    
    /**
     * Stop network reconnect attempts
     */
    void StopNetworkReconnect();
    
    /**
     * Resume network reconnect attempts
     */
    void ResumeNetworkReconnect();
};

#endif // ML307C_BOARD_H
