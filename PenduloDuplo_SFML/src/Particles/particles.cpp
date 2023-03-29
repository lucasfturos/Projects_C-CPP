#include "particles.hpp"

Particles::Particles(float x, float y) {
    count = 1024;
    size = 8;
    this->x = x;
    this->y = y;
    resetParticles();
}

auto Particles::resetParticles() -> void {
    store_particles = std::vector<Particle>(count);
    vertices = sf::VertexArray(sf::Quads, count * 4);

    for (size_t i{0}; i < store_particles.size(); ++i) {
        resetParticle(i, true);
    }
}

auto Particles::resetParticle(std::size_t index, bool start = false) -> void {
    vertices[4 * index + 0].position = sf::Vector2f(x, y);
    vertices[4 * index + 1].position = sf::Vector2f(x + size, y);
    vertices[4 * index + 2].position = sf::Vector2f(x + size, y + size);
    vertices[4 * index + 3].position = sf::Vector2f(x, y + size);

    color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);

    if (start) {
        color.a = 0;
    }

    for (std::size_t i{}; i < 4; ++i) {
        vertices[4 * index + i].color = color;
    }

    sf::Vector2f pos = {static_cast<float>(rand() / (float)RAND_MAX * 15 - 7.5f),
                        static_cast<float>(rand() / (float)RAND_MAX * 15 - 7.5f)};
    store_particles[index].velocity = pos;
    store_particles[index].life_time = 30 + rand() % 60;
}

auto Particles::update() -> void {
    for (std::size_t i{}; i < store_particles.size(); ++i) {
        if (store_particles[i].life_time == 0) {
            resetParticle(i, false);
        }
        vertices[4 * i + 0].position += store_particles[i].velocity;
        vertices[4 * i + 1].position += store_particles[i].velocity;
        vertices[4 * i + 2].position += store_particles[i].velocity;
        vertices[4 * i + 3].position += store_particles[i].velocity;
        --store_particles[i].life_time;
    }
}
