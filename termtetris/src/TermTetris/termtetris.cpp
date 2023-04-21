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

    delay = .005f;
    rotate = gameover = {false};
    diry = 0;
    timercount = 1.f;

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
        }
    }

    for (auto k{0}; k < squares; ++k) {
        area[z[k].x][z[k].y] = "\033[1;31m▣\033[0m";
    }
}

auto TermTetris::draw() -> void {
    std::cout << "\033[5;30m\033[1;34mTermTetris\t\t "
              << scoreLimit() + "\033[0m" << '\n';
    for (auto i{0}; i < lines; ++i) {
        for (auto j{0}; j < cols; ++j) {
            std::cout << area[i][j];
        }
        std::cout << '\n';
    }

    std::cout << "\033[1;35mClique 'c' para começar o jogo\033[0m" << '\n';
    std::cout << "\033[1;35mClique 'x' para sair do jogo\033[0m" << '\n';
    if (gameover) {
        std::cout << "\033c";
        logoGameOver();
        std::cout << "\033[1;34mSua pontuação: " + std::to_string(score)
                  << "\033[0m" << '\n';
        std::quick_exit(true);
    }
}

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
        case 'c':
            delay++;
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
    if (timercount < delay) {
        for (auto i{0}; i < squares; ++i) {
            k[i] = z[i];
            ++z[i].x;
        }
        for (auto i{0}; i < squares; ++i) {
            area[k[i].x][k[i].y] = "\033[1;32m▣\033[0m";
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
    delay = .005f;
}

auto TermTetris::changePosition() -> void {
    for (auto i{0}; i < squares; ++i) {
        k[i] = z[i];
        z[i].y += diry;
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
            z[i].y < 1) {
            return true;
        } else if (area[z[i].y][z[i].x] == "█") {
            return true;
        }
    }
    return false;
}

auto TermTetris::run() -> void {
    while (true) {
        std::cout << "\033c";
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
        std::this_thread::sleep_for(std::chrono::microseconds(70000));
    }
}
