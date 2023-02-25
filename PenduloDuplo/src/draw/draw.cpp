#include "draw.hpp"

void Draw::gotoxy(std::uint32_t x, std::uint32_t y) {
    std::cout << "\x1b[2J";
    std::cout << "\033[" << y + 1 << ";" << x + 1 << "H";
}

void Draw::drawPoint(
    std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
    std::uint32_t A, std::uint32_t B, char c) {
    if (A < 0 || B < 0 || A >= WIDTH / dW || B >= HEIGHT / dH) {
        return;
    };
    platno[B][A] = c;
}

void Draw::drawLine(
    std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> platno,
    std::uint32_t A, std::uint32_t B, std::uint32_t C, std::uint32_t D,
    char c) {
    // Ordenação
    if (A > C) {
        std::uint32_t t;
        t = A;
        A = C;
        C = t;
        t = B;
        B = D;
        D = t;
    }
    // algoritmo
    if (B == D) {
        for (std::uint32_t i = A; i <= C; i++) {
            drawPoint(platno, i, B, c);  // platno[B][i]=c;
        }
        return;
    }
    if (A == C) {
        std::uint32_t min = B, max = D;
        if (D < B) {
            min = D;
            max = B;
        }
        for (std::uint32_t i = min; i <= max; i++) {
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
    std::uint32_t x0, std::uint32_t y0, std::uint32_t x1, std::uint32_t y1,
    char c) {
    std::uint32_t dx = x1 - x0, dy = y1 - y0, yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    std::uint32_t D = 2 * dy - dx;
    std::uint32_t y = y0;

    for (std::uint32_t x = x0; x <= x1; x++) {
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
    std::uint32_t x0, std::uint32_t y0, std::uint32_t x1, std::uint32_t y1,
    char c) {
    std::uint32_t dx = x1 - x0, dy = y1 - y0, xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    std::uint32_t D = 2 * dx - dy;
    std::uint32_t x = x0;

    for (std::uint32_t y = y0; y <= y1; y++) {
        drawPoint(platno, x, y, c);
        if (D > 0) {
            x += xi;
            D -= 2 * dy;
        }
        D += 2 * dx;
    }
}
