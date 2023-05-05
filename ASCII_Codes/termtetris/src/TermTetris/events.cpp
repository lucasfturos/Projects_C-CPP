#include "termtetris.hpp"

auto TermTetris::events() -> void {
    if (KbhitGetch::kbhit()) {
        switch (KbhitGetch::getch()) {
        case 'w':
            rotate = true;
            break;
        case 'a':
            --diry;
            break;
        case 'd':
            ++diry;
            break;
        case 's':
            for (auto i{0}; i < squares; ++i) {
                ++z[i].x;
            }
            break;
        case 'c':
            start++;
            break;
        case 'x':
            gameover = true;
            break;
        default:
            break;
        }
    }
}

auto TermTetris::moveToDown() -> void {
    if (timercount < start) {
        for (auto i{0}; i < squares; ++i) {
            k[i] = z[i];
            ++z[i].x;
        }

        if (maxLimit()) {
            int number = std::rand() % shapes;
            for (auto i{0}; i < squares; ++i) {
                z[i].x = forms[number][i] % 2;
                z[i].y = forms[number][i] / 2;
            }
        }
        timercount = 0;
    }
}

auto TermTetris::setRotate() -> void {
    if (rotate) {
        Coords coords = z[1];
        for (auto i{0}; i < squares; ++i) {
            int x = z[i].y - coords.y;
            int y = z[i].x - coords.x;

            z[i].x = coords.x - x;
            z[i].y = coords.y + y;
        }

        if (maxLimit()) {
            for (auto i{0}; i < squares; ++i) {
                z[i] = k[i];
            }
        }
    }
}

auto TermTetris::resetValues() -> void {
    diry = 0;
    rotate = false;
}

auto TermTetris::changePosition() -> void {
    for (auto i{0}; i < squares; ++i) {
        k[i] = z[i];
        z[i].y += diry * 4;
    }

    if (maxLimit()) {
        for (auto i{0}; i < squares; ++i) {
            z[i] = k[i];
        }
    }
}
