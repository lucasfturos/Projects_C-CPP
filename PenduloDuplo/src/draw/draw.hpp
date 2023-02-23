#ifndef DRAW_HPP
#define DRAW_HPP

#include <iostream>

class Draw {
   public:
    std::uint32_t WIDTH = 800;
    std::uint32_t HEIGHT = 600;
    std::uint32_t dW = 8;
    std::uint32_t dH = 16;
    void gotoxy(std::uint32_t x, std::uint32_t y);
    void plotLineLow(char platno[HEIGHT / dH][WIDTH / dW + 1], std::uint32_t x0,
                     std::uint32_t y0, std::uint32_t x1, std::uint32_t y1,
                     char c);
    void plotLineHigh(char platno[HEIGHT / dH][WIDTH / dW + 1],
                      std::uint32_t x0, std::uint32_t y0, std::uint32_t x1,
                      std::uint32_t y1, char c);
    void drawPoint(char platno[HEIGHT / dH][WIDTH / dW + 1], std::uint32_t A,
                   std::uint32_t B, char c);
    void drawLine(char platno[HEIGHT / dH][WIDTH / dW + 1], std::uint32_t A,
                  std::uint32_t B, std::uint32_t C, std::uint32_t D, char c);
};

#endif  // !DRAW_HPP
