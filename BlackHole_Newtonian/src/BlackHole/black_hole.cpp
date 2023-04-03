#include "black_hole.hpp"


auto BlackHole::setupRenderObjectBlackHole() -> void {
    texture.create(width, height);
    this->setTexture(texture.getTexture());

    black_hole_radius.setRadius(radius);
    black_hole_radius.setOrigin(black_hole_radius.getRadius(),
                                black_hole_radius.getRadius());
    black_hole_radius.setFillColor(sf::Color::Black);
}

auto BlackHole::render() -> void {
    black_hole_radius.setPosition(width / 2, height / 2);
    texture.clear(sf::Color::White);
    texture.draw(black_hole_radius);
    texture.display();
}
