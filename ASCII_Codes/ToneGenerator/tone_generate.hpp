#pragma once

#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

const double PI = M_PI;

class ToneGenerator {
  public:
    int sampleRate = 44100;

    std::vector<int16_t> generateSineWave();
    std::vector<int16_t> generateSquareWave();
    std::vector<int16_t> generateWaveTriangle();
    std::vector<int16_t> generateWaveSawtooth();

    ToneGenerator(double frequency, double duration);

  private:
    double frequency;
    double duration;
    double amplitude = 0.5;
};
