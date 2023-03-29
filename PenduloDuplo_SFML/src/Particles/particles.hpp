#pragma once

#include <SFML/Graphics.hpp>

class Particles {
  public:
    struct Particle {
        sf::Vector2f velocity;
        int life_time{};
    };

    std::vector<Particle> store_particles;
    sf::VertexArray vertices;
    float size{}, x{}, y{};
    std::size_t count{};

    void resetParticles();
    void resetParticle(std::size_t, bool);
    void update();

    Particles(float, float);
};
