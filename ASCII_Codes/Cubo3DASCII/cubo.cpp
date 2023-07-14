#include "cubo.hpp"

float Cubo::calculaX(float *v) {
    return v[1] * sinf(A) * sinf(B) * cosf(C) -
           v[2] * cosf(A) * sinf(B) * cosf(C) + v[1] * cosf(A) * sinf(C) +
           v[2] * sinf(A) * sinf(C) + v[0] * cosf(B) * cosf(C);
}

float Cubo::calculaY(float *v) {
    return v[1] * cosf(A) * cosf(C) + v[2] * sinf(A) * cosf(C) -
           v[1] * sinf(A) * sinf(B) * sinf(C) +
           v[2] * cosf(A) * sinf(B) * sinf(C) - v[0] * cosf(B) * sinf(C);
}

float Cubo::calculaZ(float *v) {
    return v[2] * cosf(A) * cosf(B) - v[1] * sinf(A) * cosf(B) + v[0] * sinf(B);
}

void Cubo::calculaSuperficie(std::array<float, 3> v, int ch) {
    x = calculaX(v.data());
    y = calculaY(v.data());
    z = calculaZ(v.data()) + distance;

    ooz = 1 / z;

    xp = static_cast<int>(w / 2 + horizontalOffSet + K1 * ooz * x * 2);
    yp = static_cast<int>(h / 2 + horizontalOffSet + K1 * ooz * y);

    idx = xp + yp * w;
    if (idx >= 0 && idx < w * h) {
        if (ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

void Cubo::draw() {
    std::cout << "\x1b[2J";
    while (1) {
        std::cout << "\033c";
        std::fill(buffer.begin(), buffer.end(),
                  32); // 32 code ASCII of space
        std::fill(zBuffer.begin(), zBuffer.end(),
                  0); // 0 code ASCII of Null

        cubeWidth = 20;
        horizontalOffSet *= cubeWidth;
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += speed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += speed) {
                calculaSuperficie({cubeX, cubeY, -cubeWidth},
                                  64); // 64 code ASCII of @
                calculaSuperficie({cubeWidth, cubeY, cubeX},
                                  38); // 38 code ASCII of &
                calculaSuperficie({-cubeWidth, cubeY, -cubeX}, 64);
                calculaSuperficie({-cubeX, cubeY, cubeWidth},
                                  35); // 35 code ASCII of #
                calculaSuperficie({cubeX, -cubeWidth, -cubeY}, 38);
                calculaSuperficie({cubeX, cubeWidth, cubeY}, 35);
            }
        }
        std::cout << "\x1b[H";
        for (int k = 0; k < w * h; k++) {
            std::putchar(k % w ? buffer[k] : 10);
        }

        A += 0.05;
        B += 0.05;
        C += 0.01;

        std::this_thread::sleep_for(std::chrono::microseconds(8000 * 2));
    }
}

int main() {
    Cubo cubo;
    cubo.draw();
}
