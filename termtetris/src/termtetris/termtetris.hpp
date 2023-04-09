#include <cmath>
#include <iostream>
#include <memory>
#include <ncurses.h>
#include <vector>

class TermTetris {
  private:
    static const std::uint32_t lines{20};
    static const std::uint32_t cols{10};
    static const std::uint32_t squares{4};
    static const std::uint32_t shapes{7};

    std::vector<std::vector<std::uint32_t>> area;
    std::vector<std::vector<std::uint32_t>> forms;

    struct Coords {
        std::uint32_t x, y;
    } z[squares], k[squares];

    int dirx, color, score;
    bool rotate, gameover;
    float timercount, delay;

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

  public:
    TermTetris();
    void run();
};
