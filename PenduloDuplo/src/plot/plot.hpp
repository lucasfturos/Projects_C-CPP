#ifndef PLOT_HPP
#define PLOT_HPP

#include <cmath>

class Plot {
   public:
    static constexpr int WIDTH{600};
    static constexpr int HEIGHT{600};
    static constexpr int dW{8};
    static constexpr int dH{16};

    void drawPoint(char canvas[HEIGHT / dH][WIDTH / dW + 1], int A, int B,
                   char c);

    void drawLine(char canvas[HEIGHT / dH][WIDTH / dW + 1], int A, int B, int C,
                  int D, char c);

   protected:
    void plotLineLow(char canvas[HEIGHT / dH][WIDTH / dW + 1], int x0, int y0,
                     int x1, int y1, char c);

    void plotLineHigh(char canvas[HEIGHT / dH][WIDTH / dW + 1], int x0, int y0,
                      int x1, int y1, char c);
};

#endif  // !PLOT_HPP

