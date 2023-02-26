#include "draw.hpp"

void Draw::gotoxy(short x, short y) {
    printf("\033[%d;%dH", y + 1, x + 1);}


void Draw::drawPoint(
    std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
    int A, int B, char c) {
    if (A < 0 || B < 0 || A >= WIDTH / dW || B >= HEIGHT / dH) {
        return;
    };
    platno[B][A] = c;
}

void Draw::drawLine(
    std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
    int A, int B, int C, int D,
    char c) {
    // Ordenação
    if (A > C) {
        int t;
        t = A;
        A = C;
        C = t;
        t = B;
        B = D;
        D = t;
    }
    // algoritmo
    if (B == D) {
        for (int i = A; i <= C; i++) {
            drawPoint(platno, i, B, c);  // platno[B][i]=c;
        }
        return;
    }
    if (A == C) {
        int min = B, max = D;
        if (D < B) {
            min = D;
            max = B;
        }
        for (int i = min; i <= max; i++) {
            drawPoint(platno, A, i, c);  // platno[i][A]=c;
        }
        return;
    }
    if (std::abs(static_cast<int>(D - B)) < std::abs(static_cast<int>(C - A))) {
        plotLineLow(platno, A, B, C, D, c);
    } else {
        if (B > D) {
            plotLineHigh(platno, C, D, A, B, c);
        } else {
            plotLineHigh(platno, A, B, C, D, c);
        }
    }
}

void Draw::plotLineLow(
    std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
    int x0, int y0, int x1, int y1,
    char c) {
    int dx = x1 - x0, dy = y1 - y0, yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int D = 2 * dy - dx;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
        drawPoint(platno, x, y, c);
        if (D > 0) {
            y += yi;
            D -= 2 * dx;
        }
        D += 2 * dy;
    }
}

void Draw::plotLineHigh(
    std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
    int x0, int y0, int x1, int y1,
    char c) {
    int dx = x1 - x0, dy = y1 - y0, xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = 2 * dx - dy;
    int x = x0;

    for (int y = y0; y <= y1; y++) {
        drawPoint(platno, x, y, c);
        if (D > 0) {
            x += xi;
            D -= 2 * dy;
        }
        D += 2 * dx;
    }
}
