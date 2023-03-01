#include "pendulo.hpp"

void Pendulo::canvasSetup() {
    for (int i{}; i < HEIGHT / dH - 1; ++i) {
        canvas[i][WIDTH / dW] = '\n';
    }

    canvas[HEIGHT / dH - 1][WIDTH / dW] = '\0';

    for (int i{}; i < HEIGHT / dH; ++i) {
        for (int j{}; j < WIDTH / dW; ++j) {
            canvas[i][j] = ' ';
        }
    }
}

void Pendulo::traceSetup() {
    trace.resize(HEIGHT / dH);
    for (int k{}; k < trace.size(); k++) {
        trace[k].resize(WIDTH / dW);
    }

    for (int i{}; i < HEIGHT / dH; i++) {
        for (int j{}; j < WIDTH / dW; ++j) {
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
        w1 += 10 * dt * static_cast<float>(alpha1);
        w2 += 10 * dt * static_cast<float>(alpha2);
        O1 += 10 * dt * w1;
        O2 += 10 * dt * w2;

        accumulator -= dt;

        for (int i{}; i < HEIGHT / dH; i++) {
            for (int j{}; j < WIDTH / dW; ++j) {
                if (trace[i][j] > 0) {
                    trace[i][j]--;
                }
            }
        }
    }
}

void Pendulo::draw() {
    system("clear || cls");
    formulaSetup();
    // drawing
    for (int i{}; i < HEIGHT / dH; i++) {
        for (int j{}; j < WIDTH / dW; ++j) {
            if (canvas[i][j] == '@') {
                trace[i][j] = fps;
            }

            if (trace[i][j] >= 3 * static_cast<int>(fps / 4)) {
                canvas[i][j] = ':';
            } else if (trace[i][j] >= 2 * static_cast<int>(fps / 4)) {
                canvas[i][j] = '.';
            } else if (trace[i][j] >= static_cast<int>(fps / 4)) {
                (i + j) % 2 ? canvas[i][j] = '.' : canvas[i][j] = ' ';
            } else {
                canvas[i][j] = ' ';
            }
        }
    }
    int x1 = (WIDTH / 2 + sin(O1) * l1 + dW * 0.5f) / dW;
    int y1 = (cos(O1) * l1 + dH * 0.5f) / dH + HEIGHT / dH / 2;

    int x2 = x1 + (sin(O2) * l2 + dW * 0.5f) / dW;
    int y2 = y1 + (cos(O2) * l2 + dH * 0.5f) / dH;

    Plot::drawLine(canvas, WIDTH / dW / 2, HEIGHT / dH / 2, x1, y1, '#');
    Plot::drawLine(canvas, x1, y1, x2, y2, '#');

    Plot::drawPoint(canvas, WIDTH / 2 / dW, HEIGHT / dH / 2, 'O');
    Plot::drawPoint(canvas, x1, y1, '@');
    Plot::drawPoint(canvas, x2, y2, '@');
    puts(canvas[0]);
}
