#ifndef PENDULO_HPP
#define PENDULO_HPP

#include <vector>
#include <cstdlib>
#include <iostream>

#include "../plot/plot.hpp"
#include "../timer/timer.hpp"

class Pendulo : public Plot, Timer {
   protected:
    static constexpr int WIDTH{Plot::WIDTH};
    static constexpr int HEIGHT{Plot::HEIGHT};
    static constexpr int dW{Plot::dW};
    static constexpr int dH{Plot::dH};

    static constexpr float pi{3.14159265358979323846f};
    static constexpr float fps{300.0f};
    static constexpr float dt{1.0f / fps};

    float accumulator{0.0f};
    float frameStart{Timer::elapsed()};
    float currentTime{Timer::elapsed()};

    float 
        l1{120.0f}, l2{120.0f},    // tamanho da corda
        m1{10.0f}, m2{10.0f},      // massa da esfera na extremidade
        O1{2.0f * pi / 2.0f},      // thetas O1 e O2 do angulo
        O2{2.0f * pi / 3.0f}, 
        w1{0.0f}, w2{0.0f},        // velocidade angular
        g{9.81f};                  // aceleração gravitacional

    std::vector<std::vector<int>> trace;
    char canvas[HEIGHT / dH][WIDTH / dW + 1];

    void tempoSetup();
    void formulaSetup();

   public:
    void canvasSetup();
    void traceSetup();
    void draw();
};

#endif  // !PENDULO_HPP
