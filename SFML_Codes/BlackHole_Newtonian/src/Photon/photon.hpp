#pragma once

#include "../Constante/constante.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <random>
#include <vector>

using namespace Constantes;

class Photon : public sf::Sprite {
  public:
    enum AnimationState { CIRCLE, LINEAR };

    void update();
    void render(sf::RenderTexture &);
    void startLinearAnimation();
    void startCircleAnimation();
    void resetPosition();

    Photon(float, float, float, float);

  private:
    sf::Clock clock;
    sf::CircleShape photon_radius;
    sf::Time elapsed{clock.restart()};
    sf::Vector2f pos, vel, initial_pos, initial_vel;

    float elapsedSeconds{0.f};
    float region_radius{40.f};
    bool isAnimating{false};
    AnimationState
        animationState; // Variável para controlar o estado da animação
};
