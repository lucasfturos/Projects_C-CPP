#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>

#include "../Constante/constante.hpp"
#include "../Photon/photon.hpp"

using namespace Constantes;

class BlackHole : public sf::Sprite {
  private:
    int point_count{1000};
    float half_width{}, half_height{};
    float elapsedSeconds{0.f};

    sf::Clock clock;
    sf::Time elapsed{clock.restart()};
    sf::RenderTexture texture;
    sf::CircleShape region1_atrator;
    sf::CircleShape region2_atrator;
    sf::CircleShape black_hole_radius;

    std::vector<std::shared_ptr<Photon>> photons;

  public:
    sf::Vector2f pos;

    void setupObjectBlackHole();
    void setupObjectAtratorRegion();
    void render();

    BlackHole(float, float);
};
