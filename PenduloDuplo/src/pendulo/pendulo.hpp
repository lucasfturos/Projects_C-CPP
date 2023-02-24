#pragma once
//#include <ncurses.h>

#include <array>
#include <iostream>

#include "../draw/draw.hpp"
#include "../timer/timer.hpp"

class Pendulo {
   protected:
    Draw d;
    Timer tmr;

    static constexpr float pi{3.14159265358979323846f};
    static constexpr float fps{300.0f};
    static constexpr float dt{1.0f / fps};

    float accumulator{0.0f};
    float frameStart{tmr.elapsed()};
    float currentTime{tmr.elapsed()};

    float l1{150.0f}, l2{150.0f},  // tamanho da corda
        m1{10.0f}, m2{10.0f},      // massa da esfera na extremidade
        O1{2.0f * M_PI / 2.0f},    // thetas O1 e O2 do angulo
        O2{2.0f * M_PI / 3.0f}, w1{0.0f}, w2{0.0f},  // velocidade angular
        g{9.81f};  // aceleração gravitacional

   public:
    void draw();
};
