#pragma once

#include <chrono>

class Timer {
  public:
    Timer() : beg_(clock_::now()) {}
    void reset();
    float elapsed() const;

  private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<float, std::ratio<1>> second_;
    std::chrono::time_point<clock_> beg_;
};
