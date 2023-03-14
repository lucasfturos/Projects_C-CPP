#pragma once

#include <cmath>

// Variaveis globais da janela
constexpr int WIDTH{600};
constexpr int HEIGHT{600};
constexpr int dW{8};
constexpr int dH{16};
constexpr int line{WIDTH / dW};
constexpr int col{HEIGHT / dH};

class Plot {
public:
  void drawPoint(char canvas[col][line + 1], int A, int B, int c);

  void drawLine(char canvas[col][line + 1], int A, int B, int C, int D, int c);

protected:
  void plotLineLow(char canvas[col][line + 1], int x0, int y0, int x1, int y1,
                   int c);

  void plotLineHigh(char canvas[col][line + 1], int x0, int y0, int x1, int y1,
                    int c);
};
