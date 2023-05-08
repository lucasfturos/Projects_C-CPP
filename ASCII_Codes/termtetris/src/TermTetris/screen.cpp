#include "termtetris.hpp"

auto TermTetris::clear() -> void {
    for (auto i{0}; i < lines; ++i) {
        for (auto j{0}; j < cols; ++j) {
            if (i == lines - 1 || j == 0 || j == cols - 1) {
                area[i][j] = "\033[1;32m█\033[0m";
            } else {
                area[i][j] = " ";
            }
            for (auto k{0}; k < squares; ++k) {
                if (j == z[k].y && i == z[k].x) {
                    area[i][j] = "\033[1;35m▣\033[0m";
                }
            }
        }
    }
}

auto TermTetris::draw() -> void {
    std::cout << "\033c";
    std::cout << "\033[5;30m\033[1;34mTermTetris\t\t"
              << scoreLimit() + "\033[0m" << '\n';

    for (auto i{0}; i < lines; ++i) {
        for (auto j{0}; j < cols; ++j) {
            std::cout << area[i][j];
        }
        std::cout << '\n';
    }

    std::cout << "\033[1;35mClique 'c' para começar o jogo\033[0m" << '\n';
    std::cout << "\033[1;35mClique 'x' para sair do jogo\033[0m" << '\n';
}

auto TermTetris::maxLimit() -> bool {
    for (auto i{0}; i < squares; ++i) {
        if (z[i].x < 1 || z[i].x >= lines - 1 || z[i].y >= cols - 1 ||
            z[i].y < 1 || area[z[i].x][z[i].y] == "▣") {
            return true;
        }
    }
    return false;
}
