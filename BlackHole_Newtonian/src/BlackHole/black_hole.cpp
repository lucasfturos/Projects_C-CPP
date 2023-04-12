#include "black_hole.hpp"

BlackHole::BlackHole(float half_width, float half_height) {
    this->half_width = half_width;
    this->half_height = half_height;
}

auto BlackHole::render() -> void {
    texture.create(width, height);
    this->setTexture(texture.getTexture());

    black_hole_radius.setRadius(radius * 0.005);
    black_hole_radius.setOrigin(black_hole_radius.getRadius(),
                                black_hole_radius.getRadius());
    black_hole_radius.setFillColor(sf::Color::Black);
    black_hole_radius.setPosition(half_width, half_height);

    texture.clear(sf::Color::White);
    texture.draw(black_hole_radius);
    texture.display();
}
