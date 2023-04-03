#include "black_hole.hpp"

BlackHole::BlackHole(float half_witdh, float half_height) {
    this->half_witdh = half_witdh;
    this->half_height = half_height;
}

auto BlackHole::render() -> void {
    texture.create(width, height);
    this->setTexture(texture.getTexture());

    black_hole_radius.setRadius(radius);
    black_hole_radius.setOrigin(black_hole_radius.getRadius(),
                                black_hole_radius.getRadius());
    black_hole_radius.setFillColor(sf::Color::Black);
    black_hole_radius.setPosition(half_witdh, half_height);

    texture.clear(sf::Color::White);
    texture.draw(black_hole_radius);
    texture.display();
}
