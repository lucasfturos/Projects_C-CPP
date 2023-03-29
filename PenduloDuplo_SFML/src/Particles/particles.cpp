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

auto Particles::resetParticle(std::size_t index, bool start = false) -> void {}

auto Particles::update() -> void {}
