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

    start = .005f;
    rotate = gameover = {false};
    diry = 0;
    timercount = 1.f;

    int number = std::rand() % shapes;
    for (auto i{0}; i < squares; ++i) {
        z[i].x = forms[number][i] % 2;
        z[i].y = forms[number][i] / 2;
    }
}

auto TermTetris::run() -> void {
    while (true) {
        clear();
        draw();
        events();
        if (!gameover) {
            changePosition();
            setRotate();
            moveToDown();
            setScore();
            resetValues();
        } else {
            std::cout << "\033c";
            logoGameOver();
            std::cout << "\033[1;34mSua pontuação: " + std::to_string(score)
                      << "\033[0m" << '\n';
            std::quick_exit(true);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(70000));
    }
}
