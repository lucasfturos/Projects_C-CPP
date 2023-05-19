#pragma once

#include "../KbhitGetch/kbhit_getch.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

class TermTetris : public KbhitGetch {
  private:
    static constexpr int cols{25};
    static constexpr int lines{25};
    static constexpr int shapes{7};
    static constexpr int squares{4};

    std::vector<std::vector<int>> forms;
    std::vector<std::vector<bool>> board;
    std::vector<std::vector<std::string>> area;

    struct Coords {
        int x, y;
    } z[squares], k[squares];

    long int score;
    int diry, move_down;
    bool rotate, gameover;
    float timercount, start;

  protected:
    void draw();
    void clear();
    void events();
    bool maxLimit();
    void setScore();
    void setRotate();
    void spawPiece();
    void moveToDown();
    void resetValues();
    void logoGameOver();
    void checkGameOver();
    void changePosition();

    std::string scoreLimit();

  public:
    TermTetris();
    void run();
};
