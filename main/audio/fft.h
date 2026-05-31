#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>

class FFT {
public:
    // 执行快速傅里叶变换
    static void Forward(std::vector<std::complex<float>>& data);
    
    // 执行逆快速傅里叶变换
    static void Inverse(std::vector<std::complex<float>>& data);
    
    // 计算幅度谱
    static std::vector<float> ComputeMagnitude(const std::vector<std::complex<float>>& data);
    
    // 计算功率谱
    static std::vector<float> ComputePower(const std::vector<std::complex<float>>& data);
    
    // 将音频数据转换为频谱数据（8个频段）
    static std::vector<uint8_t> AudioToSpectrum(const std::vector<int16_t>& audio_data, int sample_rate);
    
private:
    // 位反转
    static void BitReverse(std::vector<std::complex<float>>& data);
};

#endif // FFT_H