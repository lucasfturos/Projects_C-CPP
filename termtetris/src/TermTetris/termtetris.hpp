#pragma once

#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

class TermTetris {
  private:
    static constexpr int lines{30};
    static constexpr int cols{30};
    static constexpr int squares{4};
    static constexpr int shapes{7};

    std::vector<std::vector<std::string>> area;
    std::vector<std::vector<int>> forms;

    struct Coords {
        int x, y;
    } z[squares], k[squares];

    int dirx, color, flags;
    bool rotate, gameover;
    float timercount, delay;
    long int score;

  protected:
    void events();
    void moveToDown();
    void setRotate();
    void resetValues();
    void changePosition();
    bool maxLimit();
    std::string scoreLimit();
    void setScore();
    void clear();
    void draw();

  public:
    TermTetris();
    void run();
};
