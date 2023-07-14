#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <thread>

class Cubo {
    std::array<float, 3> vec;
    std::array<char, 160 * 44> buffer;
    std::array<float, 160 * 44> zBuffer;
    int w{80}, h{40}, distance{100}, xp{}, yp{}, idx{};

    float A{}, B{}, C{}, K1{40.0f}, cubeWidth{20.0f}, horizontalOffSet{}, x{},
        y{}, z{}, ooz{}, speed{0.6};

  protected:
    float calculaX(float *v);

    float calculaY(float *v);

    float calculaZ(float *v);

    void calculaSuperficie(std::array<float, 3> v, int ch);

  public:
    void draw();
};
