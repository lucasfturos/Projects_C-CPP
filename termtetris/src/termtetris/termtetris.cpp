#include "termtetris.hpp"

TermTetris::TermTetris() {
    area.resize(lines);
    for (std::size_t i{}; i < area.size(); ++i) {
        area[i].resize(cols);
    }
    forms = {
        {1, 3, 5, 7}, // I
        {2, 4, 5, 7}, // Z
        {3, 5, 4, 6}, // S
        {3, 5, 4, 7}, // T
        {2, 3, 5, 7}, // L
        {3, 5, 7, 6}, // J
        {2, 3, 4, 5}, // O
    };
}

auto TermTetris::clear() -> void {}

auto TermTetris::draw() -> void {}

auto TermTetris::events() -> void {}

auto TermTetris::moveToDown() -> void {}

auto TermTetris::setRotate() -> void {}

auto TermTetris::resetValues() -> void {}

auto TermTetris::changePosition() -> void {}

auto TermTetris::maxLimit() -> void {}

auto TermTetris::setScore() -> void {}

auto TermTetris::run() -> void { std::cout << "Ola" << '\n'; }
