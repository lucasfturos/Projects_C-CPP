#include "termtetris.hpp"

auto TermTetris::scoreLimit() -> std::string {
    setScore();
    switch (score) {
    case 10 ... 99:
        return "\b\b\bSCORE: " + std::to_string(score);
    case 100 ... 999:
        return "\b\b\b\bSCORE: " + std::to_string(score);
    case 1000 ... 9999:
        return "\b\b\b\b\bSCORE: " + std::to_string(score);
    case 10000 ... 99999:
        return "\b\b\b\b\b\bSCORE: " + std::to_string(score);
    case 100000 ... 999999:
        return "\b\b\b\b\b\b\bSCORE: " + std::to_string(score);
    case 1000000 ... 9999999:
        return "\b\b\b\b\b\b\b\bSCORE: " + std::to_string(score);
    case 10000000 ... 99999999:
        return "\b\b\b\b\b\b\b\b\bSCORE: " + std::to_string(score);
    case 100000000 ... 999999999:
        return "\b\b\b\b\b\b\b\b\b\bSCORE: " + std::to_string(score);
    default:
        return "\b\bSCORE: " + std::to_string(score);
    }
}

auto TermTetris::setScore() -> void {
    int match = lines - 1;
    for (auto i = match; i >= 1; --i) {
        int sum{};
        for (auto j{0}; j < cols; ++j) {
            if (area[i][j] == "▣") {
                if (i == 1) {
                    gameover = true;
                    std::quick_exit(true);
                }
                ++sum;
            }
            area[match][j] = area[i][j];
        }
        if (sum < cols) {
            --match;
        } else {
            ++score;
        }
    }
}
