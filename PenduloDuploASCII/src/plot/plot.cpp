#include "plot.hpp"

void Plot::drawPoint(char canvas[col][line + 1], int A, int B, int c) {
    if (A < 0 || B < 0 || A >= line || B >= col) {
        return;
    };
    canvas[B][A] = c;
}

void Plot::drawLine(char canvas[col][line + 1], int A, int B, int C, int D,
                    int c) {
    // Ordenação
    if (A > C) {
        int t{};

        t = A;
        A = C;
        C = t;
        t = B;
        B = D;
        D = t;
    }

    // algoritmo
    if (B == D) {
        for (auto i{A}; i <= C; i++) {
            drawPoint(canvas, i, B, c); // canvas[B][i]=c;
        }
        return;
    }

    if (A == C) {
        int min{B};
        int max{D};

        if (D < B) {
            min = D;
            max = B;
        }
        for (auto i{min}; i <= max; i++) {
            drawPoint(canvas, A, i, c); // canvas[i][A]=c;
        }
        return;
    }

    if (std::abs(static_cast<int>(D - B)) < std::abs(static_cast<int>(C - A))) {
        plotLineLow(canvas, A, B, C, D, c);
    } else {
        if (B > D) {
            plotLineHigh(canvas, C, D, A, B, c);
        } else {
            plotLineHigh(canvas, A, B, C, D, c);
        }
    }
}

void Plot::plotLineLow(char canvas[col][line + 1], int x0, int y0, int x1,
                       int y1, int c) {
    int dx{x1 - x0};
    int dy{y1 - y0};
    int yi{1};

    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }

    int D{2 * dy - dx};
    int y{y0};

    for (auto x{x0}; x <= x1; x++) {
        drawPoint(canvas, x, y, c);
        if (D > 0) {
            y += yi;
            D -= 2 * dx;
        }
        D += 2 * dy;
    }
}

void Plot::plotLineHigh(char canvas[col][line + 1], int x0, int y0, int x1,
                        int y1, int c) {
    int dx{x1 - x0};
    int dy{y1 - y0};
    int xi{1};

    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }

    int D{2 * dx - dy};
    int x{x0};

    for (auto y{y0}; y <= y1; y++) {
        drawPoint(canvas, x, y, c);
        if (D > 0) {
            x += xi;
            D -= 2 * dy;
        }
        D += 2 * dx;
    }
}
