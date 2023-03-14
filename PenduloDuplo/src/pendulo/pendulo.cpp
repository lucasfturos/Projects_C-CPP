#include "pendulo.hpp"

Pendulo::Pendulo() {
  // Inicializa a area
  for (auto i{0}; i < col - 1; ++i) {
    canvas[i][line] = 10; // ascii code \n
  }

  canvas[col - 1][line] = 0; // ascii code \0

  for (auto i{0}; i < col; ++i) {
    for (auto j{0}; j < line; ++j) {
      canvas[i][j] = 32; // ascii code space ' '
    }
  }

  // Inicializa a área do traço
  trace.resize(col);
  for (auto k{0}; k < trace.size(); ++k) {
    trace[k].resize(line);
  }

  for (auto i{0}; i < col; ++i) {
    for (auto j{0}; j < line; ++j) {
      trace[i][j] = 0;
    }
  }

  // Inicialização da variavel para o tempo
  frameStart = Timer::elapsed();
}

void Pendulo::formulation() {
  // Inicialização da variavel para o tempo
  currentTime = Timer::elapsed();

  // Configura o tempo de execução
  accumulator += currentTime - frameStart;
  frameStart = currentTime;

  if (accumulator >= 1.0F / 30.0F) {
    accumulator = 1.0F / 30.0F;
  }

  while (accumulator > dt) {
    // Formula lagrangiana aplicada nos pendulos
    alpha1 = static_cast<float>(
        (-g * (2 * m1 + m2) * sin(O1) - g * m2 * sin(O1 - 2 * O2) -
         2 * m2 * sin(O1 - O2) * (w2 * w2 * l2 + w1 * w1 * l1 * cos(O1 - O2))) /
        (l1 * (2 * m1 + m2 - m2 * cos(2 * O1 - 2 * O2))));

    alpha2 =
        static_cast<float>((2 * sin(O1 - O2)) *
                           (w1 * w1 * l1 * (m1 + m2) + g * (m1 + m2) * cos(O1) +
                            w2 * w2 * l2 * m2 * cos(O1 - O2)) /
                           l2 / (2 * m1 + m2 - m2 * cos(2 * O1 - 2 * O2)));

    // O tempo esta com uma aceleração de 10 vezes por segundo para
    // melhorar o efeito
    w1 += 10 * dt * alpha1;
    w2 += 10 * dt * alpha2;
    O1 += 10 * dt * w1;
    O2 += 10 * dt * w2;

    accumulator -= dt;

    for (auto i{0}; i < col; ++i) {
      for (auto j{0}; j < line; ++j) {
        if (trace[i][j] > 0) {
          trace[i][j]--;
        }
      }
    }
  }
}

void Pendulo::draw() {
  formulation();

  for (auto i{0}; i < col; ++i) {
    for (auto j{0}; j < line; ++j) {
      if (canvas[i][j] == 48) {
        trace[i][j] = fps;
      }
      if (trace[i][j] >= 3 * static_cast<int>(fps / 4)) {
        canvas[i][j] = 58; // ascii code :
      } else if (trace[i][j] >= 2 * static_cast<int>(fps / 4)) {
        canvas[i][j] = 46; // ascii code .
      } else if (trace[i][j] >= static_cast<int>(fps / 4)) {
        (i + j) % 2 ? canvas[i][j] = 46 : canvas[i][j] = 32;
      } else {
        canvas[i][j] = 32; // ascii code space ' '
      }
    }
  }

  x1 = static_cast<int>((WIDTH / 2 + sin(O1) * l1 + dW * 0.5f) / dW);
  y1 = static_cast<int>((cos(O1) * l1 + dH * 0.5f) / dH + col / 2);

  x2 = static_cast<int>(x1 + (sin(O2) * l2 + dW * 0.5f) / dW);
  y2 = static_cast<int>(y1 + (cos(O2) * l2 + dH * 0.5f) / dH);

  Plot::drawLine(canvas, line / 2, col / 2, x1, y1, 35);
  Plot::drawLine(canvas, x1, y1, x2, y2, 35); // ascii code #

  Plot::drawPoint(canvas, line / 2, col / 2, 79); // ascii code O
  Plot::drawPoint(canvas, x1, y1, 48);            // ascii code 0
  Plot::drawPoint(canvas, x2, y2, 48);

  std::cout << canvas[0];
}
