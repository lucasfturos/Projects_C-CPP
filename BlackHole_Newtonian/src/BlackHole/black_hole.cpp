#include "black_hole.hpp"

BlackHole::BlackHole(float half_width, float half_height) {
    this->half_width = half_width;
    this->half_height = half_height;
}
auto BlackHole::setupObjectBlackHole() -> void {
    black_hole_radius.setRadius(radius * err_show);
    black_hole_radius.setOrigin(black_hole_radius.getRadius(),
                                black_hole_radius.getRadius());
    black_hole_radius.setFillColor(sf::Color::Black);
    black_hole_radius.setPosition(half_width, half_height);
    black_hole_radius.setPointCount(point_count);
}

auto BlackHole::setupObjectAtratorRegion() -> void {
    region1_atrator.setRadius((radius * err_show) * 3 + 32);
    region1_atrator.setOrigin(region1_atrator.getRadius(),
                              region1_atrator.getRadius());
    region1_atrator.setOutlineColor(sf::Color::Black);
    region1_atrator.setPosition(half_width, half_height);
    region1_atrator.setOutlineThickness(2.0f);
    region1_atrator.setPointCount(point_count);

    region2_atrator.setRadius((radius * err_show) * 3 + 16);
    region2_atrator.setOrigin(region2_atrator.getRadius(),
                              region2_atrator.getRadius());
    region2_atrator.setOutlineColor(sf::Color::Black);
    region2_atrator.setPosition(half_width, half_height);
    region2_atrator.setOutlineThickness(2.0f);
    region2_atrator.setPointCount(point_count);
}

auto BlackHole::render() -> void {
    texture.create(width, height);
    this->setTexture(texture.getTexture());

    setupObjectBlackHole();
    setupObjectAtratorRegion();

    texture.clear(sf::Color::White);
    texture.draw(region1_atrator);
    texture.draw(region2_atrator);
    texture.draw(black_hole_radius);
    texture.display();
}
