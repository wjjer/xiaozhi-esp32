#include "audio_analyzer.h"
#include <esp_log.h>

static const char* TAG = "AudioAnalyzer";

AudioAnalyzer::AudioAnalyzer() : display_(nullptr), task_handle_(nullptr), running_(false) {
    current_spectrum_.resize(8, 0);
    audio_buffer_.reserve(BUFFER_SIZE);
}

AudioAnalyzer::~AudioAnalyzer() {
    Stop();
}

void AudioAnalyzer::Initialize() {
    ESP_LOGI(TAG, "Initializing audio analyzer");
    // 初始化音频分析器
}

void AudioAnalyzer::Start() {
    if (!running_) {
        running_ = true;
        xTaskCreate(AudioAnalysisTask, "AudioAnalysisTask", 4096, this, 5, &task_handle_);
        ESP_LOGI(TAG, "Audio analysis task started");
    }
}

void AudioAnalyzer::Stop() {
    if (running_) {
        running_ = false;
        if (task_handle_) {
            vTaskDelete(task_handle_);
            task_handle_ = nullptr;
        }
        ESP_LOGI(TAG, "Audio analysis task stopped");
    }
}

void AudioAnalyzer::SetDisplay(TM1629ADisplay* display) {
    display_ = display;
}

void AudioAnalyzer::ProcessAudioData(const std::vector<int16_t>& audio_data) {
    // 将音频数据添加到缓冲区
    for (int16_t sample : audio_data) {
        audio_buffer_.push_back(sample);
        if (audio_buffer_.size() >= BUFFER_SIZE) {
            // 计算频谱
            current_spectrum_ = FFT::AudioToSpectrum(audio_buffer_, SAMPLE_RATE);
            
            // 更新LED显示
            if (display_) {
                display_->SetSpectrum(current_spectrum_.data());
            }
            
            // 清空缓冲区
            audio_buffer_.clear();
        }
    }
}

std::vector<uint8_t> AudioAnalyzer::GetCurrentSpectrum() const {
    return current_spectrum_;
}

void AudioAnalyzer::AudioAnalysisTask(void* arg) {
    AudioAnalyzer* analyzer = static_cast<AudioAnalyzer*>(arg);
    
    while (analyzer->running_) {
        // 这里可以添加音频数据采集逻辑
        // 目前假设音频数据通过ProcessAudioData方法传入
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    
    vTaskDelete(nullptr);
}