#ifndef CUBO_HPP
#define CUBO_HPP
#include <cmath>
#include <array>
#include <thread>
#include <cstring>
#include <iostream>

class Cubo {
    std::array<char, 160 * 44> buffer;
    std::array<float, 160 * 44> zBuffer;
    int
        w{ 80 }, h{ 40 },
        distance{ 100 },
        xp{}, yp{}, idx{};

    float
        A{}, B{}, C{}, K1{ 40.0f },
        cubeWidth{ 20.0f }, horizontalOffSet{},
        x{}, y{}, z{}, ooz{}, speed{ 0.6 };

protected:
    float calculaX(int i, int j, int k);

    float calculaY(int i, int j, int k);

    float calculaZ(int i, int j, int k);

    void calculaSuperficie(float cubeX, float cubeY, float cubeZ, int ch);

public:
    void draw();
};

#endif