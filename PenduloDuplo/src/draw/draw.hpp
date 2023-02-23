#ifndef DRAW_HPP
#define DRAW_HPP

class Draw {
  constexpr std::uint32_t WIDTH = 800, HEIGHT = 600;
  constexpr std::uint32_t dW = 8, dH = 16;

public: 
  void gotoxy(std::uint16_t x, std::uint16_t y);
  void plotLineLow(char platno[HEIGHT / dH][WIDTH / dW + 1], int x0, int y0, int x1, int y1, char c);
  void plotLineHigh(char platno[HEIGHT / dH][WIDTH / dW + 1], int x0, int y0, int x1, int y1, char c);
  void drawPoint(char platno[HEIGHT / dH][WIDTH / dW + 1], int A, int B, char c);
  void drawLine(char platno[HEIGHT / dH][WIDTH / dW + 1], int A, int B, int C, int D, char c);
};

#endif // !DRAW_HPP
