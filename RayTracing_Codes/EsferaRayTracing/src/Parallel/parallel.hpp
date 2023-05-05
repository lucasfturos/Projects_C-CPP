#include "../Render/render.hpp"
#include <array>
#include <mutex>
#include <thread>

class Parallel {
  private:
    static const int n_thread{12};
    std::mutex mtx;
    std::array<std::thread, n_thread> th_colors;

    void parallelColor();

  public:
    Parallel();
};
