#pragma once

#include <array>
#include <cmath>
#include <iostream>

class Draw {
   public:
    static constexpr std::uint32_t WIDTH{800};
    static constexpr std::uint32_t HEIGHT{600};
    static constexpr std::uint32_t dW{8};
    static constexpr std::uint32_t dH{16};

    void gotoxy(short x, short y);

    void SetCursorPos(std::uint32_t XPos, std::uint32_t YPos);

    void drawPoint(
        std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
        std::uint32_t A, std::uint32_t B, char c);

    void drawLine(
        std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
        std::uint32_t A, std::uint32_t B, std::uint32_t C, std::uint32_t D,
        char c);

   private:
    void plotLineLow(
        std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
        std::uint32_t x0, std::uint32_t y0, std::uint32_t x1, std::uint32_t y1,
        char c);

    void plotLineHigh(
        std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
        std::uint32_t x0, std::uint32_t y0, std::uint32_t x1, std::uint32_t y1,
        char c);
};
