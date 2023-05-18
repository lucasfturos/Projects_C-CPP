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
    static constexpr int lines{30};
    static constexpr int cols{30};
    static constexpr int squares{4};
    static constexpr int shapes{7};

    std::vector<std::vector<std::string>> area;
    std::vector<std::vector<int>> forms;
    std::vector<std::vector<bool>> board;

    struct Coords {
        int x, y;
    } z[squares], k[squares];

    int diry, color, move_down;
    bool rotate, gameover;
    float timercount, start;
    long int score;

  protected:
    void events();
    void moveToDown();
    void setRotate();
    void resetValues();
    void changePosition();
    bool maxLimit();
    void setScore();
    void clear();
    void draw();
    void generatePiece();
    void draw_shapes(int);
    void logoGameOver();

    std::string scoreLimit();

  public:
    TermTetris();
    void run();
};
