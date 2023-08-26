#pragma once

#include "../point.hpp"

class Sphere {
  protected:
    // Variáveis
    int num_vertex = 0;
    float rotation = 0;
    float radius;
    float vertex_quanty;
    vector<Point> points;

    // SFML
    sf::Texture texture;
    vector<sf::Vector2f> tex_coords;
    shared_ptr<sf::VideoMode> desktop;
    shared_ptr<sf::RenderWindow> window;

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
