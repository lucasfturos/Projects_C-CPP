#pragma once

#include <SFML/Graphics.hpp>

class Particles {
  public:
    struct Particle {
        sf::Vector2f velocity;
        int life_time{};
    };

    sf::Color color;
    sf::VertexArray vertices;
    std::vector<Particle> store_particles;

    std::size_t count{};
    float size{}, x{}, y{};

    void resetParticles();
    void resetParticle(std::size_t, bool);
    void update();

    Particles(float, float);
};
