#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "../point.hpp"

using std::shared_ptr;
using std::vector;

class Rose {
  private:
    shared_ptr<sf::RenderWindow> window;
    shared_ptr<sf::VideoMode> desktop;
    float init_theta;
    float final_theta;
    float counter;

  private:
    // Variáveis
    int num_vertex = 0;
    float rotation = 0;
    vector<Point> points;
    vector<float> radius;

    // Funções auxiliares
    void init();
    void draw();
    float fx(float s);
    float fy(float x, float phi);
    sf::Color calculateColor(float radius, float r_min, float r_max);

  public:
    Rose(float init_theta, float final_theta, float counter);

    // Função principal
    void run();
};
