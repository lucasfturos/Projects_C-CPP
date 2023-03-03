#ifndef PENDULO_HPP
#define PENDULO_HPP

#include <cstdlib>
#include <iostream>
#include <vector>

#include "../plot/plot.hpp"
#include "../timer/timer.hpp"

class Pendulo : private Timer, Plot {
   private:
    static constexpr float pi{3.14159265358979323846F};
    static constexpr float fps{300.0F};
    static constexpr float dt{1.0F / fps};
    static constexpr float g{9.81F};// aceleração gravitacional

    float accumulator{0.0F};
    float frameStart{};
    float currentTime{};

    float 
        l1{120.0F}, l2{120.0F},    // tamanho da corda
        m1{10.0F}, m2{10.0F},      // massa da esfera na extremidade
        O1{2.0F * pi / 2.0F},      // thetas O1 e O2 do angulo
        O2{2.0F * pi / 3.0F}, 
        w1{0.0F}, w2{0.0F};        // velocidade angular

    std::vector<std::vector<int>> trace;
    char canvas[HEIGHT / dH][WIDTH / dW + 1];

    void formulaSetup();

   public:
    Pendulo();
    void draw();
};

#endif  // !PENDULO_HPP
