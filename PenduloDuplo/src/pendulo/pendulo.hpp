#ifndef PENDULO_HPP
#define PENDULO_HPP

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "../timer/timer.hpp"
#include "../draw/draw.hpp"

class Pendulo : public Draw, Timer {
   protected:
    static constexpr int WIDTH{Draw::WIDTH};
    static constexpr int HEIGHT{Draw::HEIGHT};
    static constexpr int dW{Draw::dW};
    static constexpr int dH{Draw::dH};

    static constexpr float pi{3.14159265358979323846f};
    static constexpr float fps{300.0f};
    static constexpr float dt{1.0f / fps};

    float accumulator{0.0f};
    float frameStart{Timer::elapsed()};
    float currentTime{Timer::elapsed()};

    float l1{150.0f}, l2{150.0f},  // tamanho da corda
        m1{10.0f}, m2{10.0f},      // massa da esfera na extremidade
        O1{2.0f * pi / 2.0f},      // thetas O1 e O2 do angulo
        O2{2.0f * pi / 3.0f}, 
        w1{0.0f}, w2{0.0f},        // velocidade angular
        g{9.81f};                  // aceleração gravitacional
    
    std::vector<std::vector<int>> trace;
    std::vector<std::vector<char>> plan;

    void planSetup();
    void traceSetup();
    void tempoSetup();
    void formulaSetup();
    void setupDrawing();

   public:
    void draw();
};

#endif // !PENDULO_HPP
