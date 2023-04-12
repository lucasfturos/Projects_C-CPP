#pragma once

#include <Constante/constante.hpp>
#include <SFML/Graphics.hpp>

using namespace Constantes;

class Photon : public sf::Sprite {
  public:
    struct Particle {
        sf::Vector2f velocity;
        int life_time{};
    };

    sf::CircleShape photon_radius;
    sf::RenderTexture texture;
    sf::Color color;
    sf::Vector2f pos{};
    sf::VertexArray vertices;
    std::vector<Particle> store_particles;

    std::size_t count{};
    float size{}, x{}, y{};

    void resetParticles();
    void resetParticle(std::size_t, bool);
    void update();

    Photon();
};
