#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

#include <Constante/constante.hpp>

using namespace Constantes;

class BlackHole : public sf::Sprite {
  private:
    float half_width{}, half_height{};

    sf::RenderTexture texture;
    sf::CircleShape black_hole_radius;
    sf::CircleShape region1_atrator;
    sf::CircleShape region2_atrator;

  public:
    void setupObjectBlackHole();
    void setupObjectAtratorRegion();
    void render();

    BlackHole(float, float);
};
