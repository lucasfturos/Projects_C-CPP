#include "tone_generate.hpp"

ToneGenerator::ToneGenerator(double frequency, double duration)
    : frequency(frequency), duration(duration) {}

std::vector<int16_t> ToneGenerator::generateSineWave() {
    std::vector<int16_t> samples;
    for (int i = 0; i < duration * sampleRate; i++) {
        double sample_double =
            amplitude * sin(2.0 * PI * frequency * i / sampleRate);
        int16_t sample = static_cast<int16_t>(sample_double * 32767.0);
        samples.push_back(sample);
    }
    return samples;
}

std::vector<int16_t> ToneGenerator::generateSquareWave() {
    std::vector<int16_t> samples;
    for (int i = 0; i < duration * sampleRate; i++) {
        double sample_double =
            amplitude *
            (sin(2.0 * PI * frequency * i / sampleRate) > 0 ? 1.0 : -1.0);
        int16_t sample = static_cast<int16_t>(sample_double * 32767.0);
        samples.push_back(sample);
    }
    return samples;
}

std::vector<int16_t> ToneGenerator::generateWaveTriangle() {
    std::vector<int16_t> samples;
    for (int i = 0; i < duration * sampleRate; i++) {
        double sample_double =
            amplitude * asin(sin(2.0 * PI * frequency * i / sampleRate));
        int16_t sample = static_cast<int16_t>(sample_double * 32767.0);
        samples.push_back(sample);
    }
    return samples;
}

std::vector<int16_t> ToneGenerator::generateWaveSawtooth() {
    std::vector<int16_t> samples;
    for (int i = 0; i < duration * sampleRate; i++) {
        double sample_double =
            amplitude *
            (2.0 * (i % (int)(sampleRate / frequency)) / sampleRate - 1.0);
        int16_t sample = static_cast<int16_t>(sample_double * 32767.0);
        samples.push_back(sample);
    }
    return samples;
}
