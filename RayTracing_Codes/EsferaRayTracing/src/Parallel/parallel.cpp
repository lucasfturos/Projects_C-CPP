#include "parallel.hpp"

Parallel::Parallel() {
    for (auto i{0}; i < n_thread; i++) {
        th_colors[i] = std::thread();
    }

    for (auto &th_color : th_colors) {
        th_color.join();
    }
}

