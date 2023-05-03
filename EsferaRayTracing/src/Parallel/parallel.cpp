#include "parallel.hpp"

Parallel::Parallel(){
  for (auto i {0}; i < n_thread; i++) {
    th_color[i] = std::thread();
  }
}
