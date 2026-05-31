#ifndef AUDIO_ANALYZER_H
#define AUDIO_ANALYZER_H

#include "fft.h"
#include "display/tm1629a_display.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class AudioAnalyzer {
public:
    AudioAnalyzer();
    ~AudioAnalyzer();
    
    // 初始化音频分析器
    void Initialize();
    
    // 启动音频分析任务
    void Start();
    
    // 停止音频分析任务
    void Stop();
    
    // 设置LED显示对象
    void SetDisplay(TM1629ADisplay* display);
    
    // 处理音频数据
    void ProcessAudioData(const std::vector<int16_t>& audio_data);
    
    // 获取当前频谱数据
    std::vector<uint8_t> GetCurrentSpectrum() const;
    
private:
    // 音频分析任务
    static void AudioAnalysisTask(void* arg);
    
    // 音频数据缓冲区
    std::vector<int16_t> audio_buffer_;
    
    // 当前频谱数据
    std::vector<uint8_t> current_spectrum_;
    
    // LED显示对象
    TM1629ADisplay* display_;
    
    // 任务句柄
    TaskHandle_t task_handle_;
    
    // 运行状态
    bool running_;
    
    // 采样率
    static constexpr int SAMPLE_RATE = 16000;
    
    // 缓冲区大小
    static constexpr size_t BUFFER_SIZE = 1024;
};

#endif // AUDIO_ANALYZER_H