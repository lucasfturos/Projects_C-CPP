#include "pendulo.hpp"

void Pendulo::draw() {
    for (std::size_t i{}; i < HEIGHT / dH - 1; ++i) {
        platno[i][WIDTH / dW] = '\n';
    }

    platno[HEIGHT / dH - 1][WIDTH / dW] = '\0';

    for (std::size_t i{}; i < HEIGHT / dH; ++i) {
        for (std::size_t j{}; j < WIDTH / dW; ++j) {
            platno[i][j] = ' ';
        }
    }

    for (std::size_t i{}; i < HEIGHT / dH; i++) {
        for (std::size_t j{}; j < WIDTH / dW; ++j) {
            trace[i][j] = 0;
        }
    }
    
    // loop
    while (true) {
        system("clear");
        d.gotoxy(0, 0);

        // Tempo
        accumulator += currentTime - frameStart;
        frameStart = currentTime;

        if (accumulator >= 1.0f / 30.0f) {
            accumulator = 1.0f / 30.0f;
        }

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

        // drawing
        for (std::size_t i{}; i < HEIGHT / dH; i++) {
            for (std::size_t j{}; j < WIDTH / dW; ++j) {
                if (platno[i][j] == '@') {
                    trace[i][j] = fps;
                }

                if (trace[i][j] >= 3 * static_cast<std::uint32_t>(fps / 4)) {
                    platno[i][j] = ':';
                } else if (trace[i][j] >=
                           2 * static_cast<std::uint32_t>(fps / 4)) {
                    platno[i][j] = '.';
                } else if (trace[i][j] >= static_cast<std::uint32_t>(fps / 4)) {
                    (i + j) % 2 ? platno[i][j] = '.' : platno[i][j] = ' ';
                } else {
                    platno[i][j] = ' ';
                }
            }
        }

        std::uint32_t x1 = (WIDTH / 2 + sin(O1) * l1 + dW * 0.5f) / dW;
        std::uint32_t y1 = (cos(O1) * l1 + dH * 0.5f) / dH + HEIGHT / dH / 2;

        std::uint32_t x2 = x1 + (sin(O2) * l2 + dW * 0.5f) / dW;
        std::uint32_t y2 = y1 + (cos(O2) * l2 + dH * 0.5f) / dH;

        d.drawLine(platno, WIDTH / 2 / dW, HEIGHT / dH / 2, x1, y1, '#');
        d.drawLine(platno, x1, y1, x2, y2, '#');

        d.drawPoint(platno, WIDTH / 2 / dW, HEIGHT / dH / 2, 'O');
        d.drawPoint(platno, x1, y1, '@');
        d.drawPoint(platno, x2, y2, '@');
        
        for (std::size_t i{}; i < HEIGHT / dH; i++) {
            for (std::size_t j{}; j < WIDTH / dW; ++j) {
                buffer[sizeBuff + j] = platno[i][j];
            }
        }
        std::cout << "\x1b[H";
        for (std::size_t k{}; k < (HEIGHT / dH) * (WIDTH / dW); ++k) {
            std::putchar(k % (WIDTH / dW + 1) ? buffer[k] : 10);
        }

    }
}

