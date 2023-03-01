#ifndef DRAW_HPP
#define DRAW_HPP

#include <cstdio>
#include <vector>
#include <cmath>
#include <iostream>

class Draw {
   public:
    static constexpr int WIDTH{600};
    static constexpr int HEIGHT{600};
    static constexpr int dW{8};
    static constexpr int dH{16};
    
    void gotoxy(short x, short y);

    void drawPoint(
        std::vector<std::vector<char>> plan,
        int A, int B, char c);

    void drawLine(
        std::vector<std::vector<char>> plan,
        int A, int B, int C, int D,
        char c);

   protected:
    void plotLineLow(
        std::vector<std::vector<char>> plan,
        int x0, int y0, int x1, int y1,
        char c);

    void plotLineHigh(
        std::vector<std::vector<char>> plan,
        int x0, int y0, int x1, int y1,
        char c);
};

#endif // !DRAW_HPP
