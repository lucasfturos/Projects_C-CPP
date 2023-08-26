#pragma once

#include "../point.hpp"

class Torus {
  protected:
    // Variáveis
    int num_vertex = 0;
    float rotation = 0;
    float inner_radius;
    float outter_radius;
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
    Torus(float inner, float outter, float vert);
        
    // Função principal
    void run();
};
