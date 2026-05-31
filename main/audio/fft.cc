#include "fft.h"
#include <cmath>
#include <algorithm>

#define PI 3.14159265358979323846

void FFT::BitReverse(std::vector<std::complex<float>>& data) {
    int n = data.size();
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i < j) {
            std::swap(data[i], data[j]);
        }
        int k = n / 2;
        while (k <= j) {
            j -= k;
            k /= 2;
        }
        j += k;
    }
}

void FFT::Forward(std::vector<std::complex<float>>& data) {
    int n = data.size();
    BitReverse(data);
    
    for (int s = 1; s <= log2(n); s++) {
        int m = 1 << s;
        std::complex<float> w_m(cos(2 * PI / m), sin(2 * PI / m));
        for (int k = 0; k < n; k += m) {
            std::complex<float> w(1, 0);
            for (int j = 0; j < m / 2; j++) {
                std::complex<float> t = w * data[k + j + m / 2];
                std::complex<float> u = data[k + j];
                data[k + j] = u + t;
                data[k + j + m / 2] = u - t;
                w *= w_m;
            }
        }
    }
}

void FFT::Inverse(std::vector<std::complex<float>>& data) {
    int n = data.size();
    for (auto& c : data) {
        c = std::conj(c);
    }
    Forward(data);
    for (auto& c : data) {
        c = std::conj(c) / static_cast<float>(n);
    }
}

std::vector<float> FFT::ComputeMagnitude(const std::vector<std::complex<float>>& data) {
    std::vector<float> magnitude(data.size());
    for (size_t i = 0; i < data.size(); i++) {
        magnitude[i] = std::abs(data[i]);
    }
    return magnitude;
}

std::vector<float> FFT::ComputePower(const std::vector<std::complex<float>>& data) {
    std::vector<float> power(data.size());
    for (size_t i = 0; i < data.size(); i++) {
        float mag = std::abs(data[i]);
        power[i] = mag * mag;
    }
    return power;
}

std::vector<uint8_t> FFT::AudioToSpectrum(const std::vector<int16_t>& audio_data, int sample_rate) {
    // 确定FFT大小（取2的幂次）
    int fft_size = 1;
    while (fft_size < audio_data.size()) {
        fft_size <<= 1;
    }
    
    // 准备FFT输入数据
    std::vector<std::complex<float>> fft_input(fft_size, 0);
    for (size_t i = 0; i < audio_data.size() && i < fft_size; i++) {
        fft_input[i] = static_cast<float>(audio_data[i]) / 32768.0f;
    }
    
    // 执行FFT
    Forward(fft_input);
    
    // 计算幅度谱
    auto magnitude = ComputeMagnitude(fft_input);
    
    // 计算频率范围
    float freq_step = static_cast<float>(sample_rate) / fft_size;
    
    // 定义8个频段的频率范围
    const float band_frequencies[] = { 60, 250, 500, 1000, 2000, 4000, 8000, 16000 };
    std::vector<uint8_t> spectrum(8, 0);
    
    // 计算每个频段的平均幅度
    for (int band = 0; band < 8; band++) {
        float start_freq = (band == 0) ? 0 : band_frequencies[band - 1];
        float end_freq = band_frequencies[band];
        
        int start_bin = static_cast<int>(start_freq / freq_step);
        int end_bin = static_cast<int>(end_freq / freq_step);
        end_bin = std::min(end_bin, static_cast<int>(magnitude.size() / 2));
        
        if (start_bin < end_bin) {
            float sum = 0;
            for (int i = start_bin; i < end_bin; i++) {
                sum += magnitude[i];
            }
            float avg = sum / (end_bin - start_bin);
            
            // 将幅度映射到0-5的范围（适合5行LED显示）
            spectrum[band] = static_cast<uint8_t>(std::min(5.0f, avg * 10.0f));
        }
    }
    
    return spectrum;
}