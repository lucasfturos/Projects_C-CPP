#include "timer.hpp"

void Timer::reset() { beg_ = clock_::now(); }

float Timer::elapsed() const {
  return std::chrono::duration_cast<second_>(clock_::now() - beg_).count();
}
