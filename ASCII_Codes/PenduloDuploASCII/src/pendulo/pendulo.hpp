#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <plot/plot.hpp>
#include <timer/timer.hpp>

class Pendulo : public Timer, public Plot {
  private:
    static constexpr float pi{3.14159265358979323846F};
    static constexpr float fps{300.0F};
    static constexpr float dt{0.003333333F}; // dt = 1 / fps
    static constexpr float g{9.81F};         // aceleração gravitacional

    int x1{}, x2{};
    int y1{}, y2{};

    float accumulator{0.0F};
    float frameStart{0.0F};
    float currentTime{0.0F};

    float alpha1{0.0F}, alpha2{0.0F};
    float 
        l1{120.0F}, l2{120.0F},   // tamanho da corda
        m1{10.0F}, m2{10.0F},     // massa da esfera na extremidade
        w1{0.0F}, w2{0.0F},       // velocidade angular
        O1{2.0F * pi / 2.0F},     // theta O1 e O2 do angulo
        O2{2.0F * pi / 3.0F};

    std::vector<std::vector<int>> trace;
    char canvas[col][line + 1];

    void formulation();

  public:
    Pendulo();
    void draw();
};
