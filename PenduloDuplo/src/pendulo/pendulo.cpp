#include "pendulo.hpp"

Pendulo::Pendulo() {
  // Inicializa a area
  for (std::size_t i{}; i < HEIGHT / dH - 1; ++i) {
    canvas[i][WIDTH / dW] = '\n';
  }

  canvas[HEIGHT / dH - 1][WIDTH / dW] = '\0';

  for (std::size_t i{}; i < HEIGHT / dH; ++i) {
    for (std::size_t j{}; j < WIDTH / dW; ++j) {
      canvas[i][j] = ' ';
    }
  }

  // Inicializa a área do traço
  trace.resize(HEIGHT / dH);
  for (std::size_t k{}; k < trace.size(); ++k) {
    trace[k].resize(WIDTH / dW);
  }

  for (std::size_t i{}; i < HEIGHT / dH; ++i) {
    for (std::size_t j{}; j < WIDTH / dW; ++j) {
      trace[i][j] = 0;
    }
  }

  // Inicialização das variaveis para o tempo
  frameStart = Timer::elapsed();
  currentTime = Timer::elapsed();

  // Configura o tempo de execução
  accumulator += currentTime - frameStart;
  frameStart = currentTime;

  if (accumulator >= 1.0F / 30.0F) {
    accumulator = 1.0F / 30.0F;
  }

  while (accumulator > dt) {
    // Formula lagrangiana aplicada nos dois pendulos
    float alpha1{static_cast<float>(
        (-g * (2 * m1 + m2) * sin(O1) - g * m2 * sin(O1 - 2 * O2) -
         2 * m2 * sin(O1 - O2) * (w2 * w2 * l2 + w1 * w1 * l1 * cos(O1 - O2))) /
        (l1 * (2 * m1 + m2 - m2 * cos(2 * O1 - 2 * O2))))};

    float alpha2{
        static_cast<float>((2 * sin(O1 - O2)) *
                           (w1 * w1 * l1 * (m1 + m2) + g * (m1 + m2) * cos(O1) +
                            w2 * w2 * l2 * m2 * cos(O1 - O2)) /
                           l2 / (2 * m1 + m2 - m2 * cos(2 * O1 - 2 * O2)))};

    // O tempo esta com uma aceleração de 10 vezes por segundo para
    // melhorar o efeito
    w1 += 10 * dt * alpha1;
    w2 += 10 * dt * alpha2;
    O1 += 10 * dt * w1;
    O2 += 10 * dt * w2;

    accumulator -= dt;

    for (std::size_t i{}; i < HEIGHT / dH; ++i) {
      for (std::size_t j{}; j < WIDTH / dW; ++j) {
        if (trace[i][j] > 0) {
          trace[i][j]--;
        }
      }
    }
  }
}

void Pendulo::draw() {
  system("clear");
  // drawing
  for (std::size_t i{}; i < HEIGHT / dH; ++i) {
    for (std::size_t j{}; j < WIDTH / dW; ++j) {
      if (canvas[i][j] == '0') {
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

  int x1{}, x2{}, y1{}, y2{};

  x1 = static_cast<int>((WIDTH / 2 + sin(O1) * l1 + dW * 0.5f) / dW);
  y1 = static_cast<int>((cos(O1) * l1 + dH * 0.5f) / dH + HEIGHT / dH / 2);

  x2 = static_cast<int>(x1 + (sin(O2) * l2 + dW * 0.5f) / dW);
  y2 = static_cast<int>(y1 + (cos(O2) * l2 + dH * 0.5f) / dH);

  Plot::drawLine(canvas, static_cast<int>(WIDTH / dW / 2),
                 static_cast<int>(HEIGHT / dH / 2), x1, y1, '#');
  Plot::drawLine(canvas, x1, y1, x2, y2, '#');

  Plot::drawPoint(canvas, static_cast<int>(WIDTH / dW / 2),
                  static_cast<int>(HEIGHT / dH / 2), 'O');
  Plot::drawPoint(canvas, x1, y1, '0');
  Plot::drawPoint(canvas, x2, y2, '0');

  puts(canvas[0]);
  std::getchar();
}
