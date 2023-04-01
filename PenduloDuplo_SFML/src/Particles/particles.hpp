#pragma once

#include <SFML/Graphics.hpp>

#include <PenduloDuplo/pendulo_duplo.hpp>

using namespace Constantes;

class Particles {
  public:
    struct Particle {
        sf::Vector2f velocity;
        int life_time{};
    };

    sf::Color color;
    sf::Vector2f pos{};
    sf::VertexArray vertices;
    std::vector<Particle> store_particles;

    std::size_t count{};
    float size{}, x{}, y{};

    void resetParticles();
    void resetParticle(std::size_t, bool);
    void update();

    Particles(float, float);
};
