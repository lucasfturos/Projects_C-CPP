#pragma once

#include <array>
#include <cmath>
#include <iostream>

class Draw {
   public:
    static constexpr int WIDTH{800};
    static constexpr int HEIGHT{600};
    static constexpr int dW{8};
    static constexpr int dH{16};

    void gotoxy(short x, short y);

    void drawPoint(
        std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
        int A, int B, char c);

    void drawLine(
        std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
        int A, int B, int C, int D,
        char c);

   protected:
    void plotLineLow(
        std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
        int x0, int y0, int x1, int y1,
        char c);

    void plotLineHigh(
        std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
        int x0, int y0, int x1, int y1,
        char c);
};
