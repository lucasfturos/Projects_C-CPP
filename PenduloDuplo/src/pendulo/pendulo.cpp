#include "pendulo.hpp"

void Pendulo::planSetup() {
    for (std::size_t i{}; i < HEIGHT / dH - 1; ++i) {
        plan[i][WIDTH / dW] = '\n';
    }

    plan[HEIGHT / dH - 1][WIDTH / dW] = '\0';

    for (std::size_t i{}; i < HEIGHT / dH; ++i) {
        for (std::size_t j{}; j < WIDTH / dW; ++j) {
            plan[i][j] = ' ';
        }
    }
}

void Pendulo::traceSetup() {
    for (std::size_t i{}; i < HEIGHT / dH; i++) {
        for (std::size_t j{}; j < WIDTH / dW; ++j) {
            trace[i][j] = 0;
        }
    }
}

void Pendulo::tempoSetup() {
    // Tempo
    accumulator += currentTime - frameStart;
    frameStart = currentTime;

    if (accumulator >= 1.0f / 30.0f) {
        accumulator = 1.0f / 30.0f;
    }
}

void Pendulo::formulaSetup() {
    tempoSetup();
    while (accumulator > dt) {
        // Formula lagrangiana aplicada nos dois pendulos
        double alpha1{(-g * (2 * m1 + m2) * sin(O1) -
                       g * m2 * sin(O1 - 2 * O2) -
                       2 * m2 * sin(O1 - O2) *
                       (w2 * w2 * l2 + w1 * w1 * l1 * cos(O1 - O2))) /
                      (l1 * (2 * m1 + m2 - m2 * cos(2 * O1 - 2 * O2)))};
        double alpha2{(2 * sin(O1 - O2)) *
                      (w1 * w1 * l1 * (m1 + m2) + g * (m1 + m2) * cos(O1) +
                       w2 * w2 * l2 * m2 * cos(O1 - O2)) /
                       l2 / (2 * m1 + m2 - m2 * cos(2 * O1 - 2 * O2))};

        // O tempo esta com uma aceleração de 10 vezes por segundo para
        // melhorar o efeito
        w1 += 10 * dt * alpha1;
        w2 += 10 * dt * alpha2;
        O1 += 10 * dt * w1;
        O2 += 10 * dt * w2;

        accumulator -= dt;

        for (std::size_t i{}; i < HEIGHT / dH; i++) {
            for (std::size_t j{}; j < WIDTH / dW; ++j) {
                if (trace[i][j] > 0) {
                    trace[i][j]--;
                }
            }
        }
    }
}

void Pendulo::draw() {
    planSetup();

    traceSetup();
 
    // loop
    while (true) {
        system("clear");
        Draw::gotoxy(0, 0);
        
        formulaSetup();

        // drawing
        for (std::size_t i{}; i < HEIGHT / dH; i++) {
            for (std::size_t j{}; j < WIDTH / dW; ++j) {
                if (plan[i][j] == '@') {
                    trace[i][j] = fps;
                }
                if (trace[i][j] >= 3 * static_cast<int>(fps / 4)) {
                    plan[i][j] = ':';
                } else if (trace[i][j] >=
                           2 * static_cast<int>(fps / 4)) {
                    plan[i][j] = '.';
                } else if (trace[i][j] >= static_cast<int>(fps / 4)) {
                    (i + j) % 2 ? plan[i][j] = '.' : plan[i][j] = ' ';
                } else {
                    plan[i][j] = ' ';
                }
            }
        }

        int x1 = (WIDTH / 2 + sin(O1) * l1 + dW * 0.5f) / dW;
        int y1 = (cos(O1) * l1 + dH * 0.5f) / dH + HEIGHT / dH / 2;

        int x2 = x1 + (sin(O2) * l2 + dW * 0.5f) / dW;
        int y2 = y1 + (cos(O2) * l2 + dH * 0.5f) / dH;

        Draw::drawLine(plan, WIDTH / 2 / dW, HEIGHT / dH / 2, x1, y1, '#');
        Draw::drawLine(plan, x1, y1, x2, y2, '#');

        Draw::drawPoint(plan, WIDTH / 2 / dW, HEIGHT / dH / 2, 'O');
        Draw::drawPoint(plan, x1, y1, '@');
        Draw::drawPoint(plan, x2, y2, '@');

        // char buffer[(HEIGHT / dH) * ( WIDTH / dW + 1)];
        std::printf(plan[0]);
        std::getchar();
    }
}

