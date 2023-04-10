#include "termtetris.hpp"

TermTetris::TermTetris() {
    area.resize(lines);
    for (auto i{0}; i < area.size(); ++i) {
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

    delay = 0.3f;
    rotate = gameover = {false};
    dirx = 0;

    int number = std::rand() % shapes;
    for (auto i{0}; i < squares; ++i) {
        z[i].x = forms[number][i] % 2;
        z[i].y = forms[number][i] / 2;
    }
}

auto TermTetris::clear() -> void {
    for (auto i{0}; i < lines; ++i) {
        for (auto j{0}; j < cols; ++j) {
            if (i == 0 || i == lines - 1 || j == 0 || j == cols - 1) {
                area[i][j] = "\033[1;32m█\033[0m";
            } else {
                area[i][j] = " ";
            }
            for (auto k{0}; k < squares; ++k) {
                if (j == z[k].y && i == z[k].x) {
                    area[i][j] = "\033[1;31m▣\033[0m";
                }
            }
        }
    }
}

auto TermTetris::draw() -> void {
    std::cout << "\033c";
    std::cout << "TermTetris\t\t" << scoreLimit() << '\n';
    for (auto i{0}; i < lines; ++i) {
        for (size_t j{0}; j < cols; ++j) {
            std::cout << area[i][j];
        }
        std::cout << '\n';
    }
}

auto TermTetris::events() -> void {
    if (KbhitGetch::kbhit()) {
        switch (KbhitGetch::getch()) {
        case 'w':
            rotate = true;
        case 'a':
            --dirx;
        case 'd':
            ++dirx;
        case 's':
            delay = 0.05f;
        case 'x':
            gameover = true;
            std::quick_exit(true);
            break;
        }
    }
}

auto TermTetris::moveToDown() -> void {
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
    dirx = 0;
    rotate = false;
    delay = 0.3f;
}

auto TermTetris::changePosition() -> void {
    for (auto i{0}; i < squares; ++i) {
        k[i] = z[i];
        z[i].x += dirx;
    }

    if (maxLimit()) {
        for (auto i{0}; i < squares; ++i) {
            z[i] = k[i];
        }
    }
}

auto TermTetris::maxLimit() -> bool {
    for (auto i{0}; i < squares; ++i) {
        if (z[i].x < 1 || z[i].x >= lines - 1 || z[i].y >= cols - 1 ||
            z[i].y < 1 || area[z[i].y][z[i].x] == "\0") {
            return true;
        }
    }
    return false;
}

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

auto TermTetris::setScore() -> void {}

auto TermTetris::run() -> void {
    while (true) {
        events();
        if (!gameover) {
            changePosition();
            setRotate();
            moveToDown();
            setScore();
            resetValues();
        }
        clear();
        draw();
        std::this_thread::sleep_for(std::chrono::microseconds(60000));
    }
}
