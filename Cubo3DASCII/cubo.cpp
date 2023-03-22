#include "cubo.hpp"

float Cubo::calculaX(int i, int j, int k) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
           j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float Cubo::calculaY(int i, int j, int k) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
           j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
           i * cos(B) * sin(C);
}

float Cubo::calculaZ(int i, int j, int k) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void Cubo::calculaSuperficie(float cubeX, float cubeY, float cubeZ, int ch) {
    x = calculaX(cubeX, cubeY, cubeZ);
    y = calculaY(cubeX, cubeY, cubeZ);
    z = calculaZ(cubeX, cubeY, cubeZ) + distance;

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
        memset(buffer.data(), 32, (w * h));   // 32 code ASCII of space
        memset(zBuffer.data(), 0, w * h * 4); // 0 code ASCII of Null

        cubeWidth = 20;
        horizontalOffSet *= cubeWidth;
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += speed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += speed) {
                calculaSuperficie(cubeX, cubeY, -cubeWidth,
                                  64); // 64 code ASCII of @
                calculaSuperficie(cubeWidth, cubeY, cubeX,
                                  47); // 47 code ASCII of /
                calculaSuperficie(-cubeWidth, cubeY, -cubeX, 64);
                calculaSuperficie(-cubeX, cubeY, cubeWidth,
                                  35); // 35 code ASCII of #
                calculaSuperficie(cubeX, -cubeWidth, -cubeY, 47);
                calculaSuperficie(cubeX, cubeWidth, cubeY, 35);
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
