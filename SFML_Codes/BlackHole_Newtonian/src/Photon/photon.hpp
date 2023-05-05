#pragma once

#include <Constante/constante.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>

using namespace Constantes;

class Photon : public sf::Sprite {
  private:
    sf::Vector2f pos, vel;
    sf::CircleShape photon_radius;

  public:
    void update();
    void render(sf::RenderTexture &);

    Photon(float, float, float, float);
};
