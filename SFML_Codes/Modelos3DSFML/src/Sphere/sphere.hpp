#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "../point.hpp"

using std::shared_ptr;
using std::vector;

class Sphere {
  private:
    float radius;
    float vertex_quanty;
    shared_ptr<sf::RenderWindow> window;
    shared_ptr<sf::VideoMode> desktop;

  private:
    // Variáveis
    int num_vertex = 0;
    float rotation = 0;
    vector<Point> points;

    // SFML
    sf::Texture texture;
    vector<sf::Vector2f> tex_coords;

    // Funções auxiliares
    void init();
    void draw();
    void initTexture(float alpha, float beta);
    void applyTexture(float x, float y, int index);

  public:
    Sphere(float r, float vert);

    // Função principal
    void run();
};
