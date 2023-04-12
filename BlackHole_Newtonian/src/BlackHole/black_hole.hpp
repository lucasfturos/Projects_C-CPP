#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

#include <Constante/constante.hpp>
#include <Photon/photon.hpp>

using namespace Constantes;

class BlackHole : public sf::Sprite {
  private:
    int point_count{1000};
    float err_show{0.009f};
    float half_width{}, half_height{};

    std::shared_ptr<Photon> photon;
    sf::RenderTexture texture;
    sf::CircleShape region1_atrator;
    sf::CircleShape region2_atrator;
    sf::CircleShape black_hole_radius;

  public:
    void setupObjectBlackHole();
    void setupObjectAtratorRegion();
    void render();

    BlackHole(float, float);
};
