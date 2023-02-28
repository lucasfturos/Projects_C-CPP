#pragma once

#include <cstdlib>
#include <iostream>

#include "../draw/draw.hpp"
#include "../timer/timer.hpp"

class Pendulo : public Draw {
   protected:
    Timer tmr;

    static constexpr float pi{3.14159265358979323846f};
    static constexpr float fps{300.0f};
    static constexpr float dt{1.0f / fps};

    float accumulator{0.0f};
    float frameStart{tmr.elapsed()};
    float currentTime{tmr.elapsed()};

    float l1{150.0f}, l2{150.0f},  // tamanho da corda
        m1{10.0f}, m2{10.0f},      // massa da esfera na extremidade
        O1{2.0f * pi / 2.0f},      // thetas O1 e O2 do angulo
        O2{2.0f * pi / 3.0f}, 
        w1{0.0f}, w2{0.0f},        // velocidade angular
        g{9.81f};                  // aceleração gravitacional
    
    static constexpr int WIDTH{Draw::WIDTH};
    static constexpr int HEIGHT{Draw::HEIGHT};
    static constexpr int dW{Draw::dW};
    static constexpr int dH{Draw::dH};

    //std::array<std::array<int, HEIGHT / dH>, WIDTH / dW> trace;
    //std::array<std::array<char, HEIGHT / dH>, WIDTH / dW + 1> plan;
    int trace[HEIGHT / dH][WIDTH / dW];
    char plan[HEIGHT / dH][WIDTH / dW + 1];

    void planSetup();
    void traceSetup();
    void tempoSetup();
    void formulaSetup();
   public:
    void draw();
};
