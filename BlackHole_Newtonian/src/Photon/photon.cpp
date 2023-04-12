#include "photon.hpp"

Photon::Photon() {
    count = 1024;
    x = width / 2;
    y = height / 2.7f;
    resetParticles();
}

auto Photon::resetParticles() -> void {
    store_particles = std::vector<Particle>(count);
    vertices = sf::VertexArray(sf::LineStrip, count * 4);

    for (size_t i{0}; i < store_particles.size(); ++i) {
        resetParticle(i, true);
    }
}

auto Photon::resetParticle(std::size_t index, bool start = false) -> void {
    for (auto i{0UL}; i < 4; ++i) {
        vertices[4 * index + i].position = sf::Vector2f(x, y);
    }

    color = sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);

    if (start) {
        color.a = 0;
    }

    for (std::size_t i{}; i < 4; ++i) {
        vertices[4 * index + i].color = color;
    }

    pos = {static_cast<float>(rand() / (float)RAND_MAX * 8 - 4),
           static_cast<float>(rand() / (float)RAND_MAX * 8 - 4)};
    store_particles[index].velocity = pos;
    store_particles[index].life_time = 30 + rand() % 60;
}

auto Photon::update() -> void {
    for (std::size_t i{}; i < store_particles.size(); ++i) {
        if (store_particles[i].life_time == 0) {
            resetParticle(i, false);
        }
        for (auto j{0}; j < 4; ++j) {
            vertices[4 * i + j].position += store_particles[i].velocity;
        }
        --store_particles[i].life_time;
    }
}
