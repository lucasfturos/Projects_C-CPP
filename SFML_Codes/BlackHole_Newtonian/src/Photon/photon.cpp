#include "photon.hpp"

Photon::Photon(float pos_x, float pos_y, float vel_x, float vel_y) {
    pos.x = pos_x;
    pos.y = pos_y;
    vel.x = vel_x;
    vel.y = vel_y;
}

auto Photon::update() -> void {
    float distance_x = width / 2 - (radius) + pos.x;
    float distance_y = height / 2 - (radius) + pos.y;

    float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

    float inverse_distance = 1.f / distance;

    float normalized_x = inverse_distance * distance_x;
    float normalized_y = inverse_distance * distance_y;

    float inverse_square_dropoff = inverse_distance * inverse_distance;

    float acceleration_x = normalized_x * 1000 * inverse_square_dropoff;
    float acceleration_y = normalized_y * 1000 * inverse_square_dropoff;

    vel.x += acceleration_x;
    vel.y += acceleration_y;

    pos.x += vel.x;
    pos.y += vel.y;
}

auto Photon::render(sf::RenderTexture &texture) -> void {
    photon_radius.setPosition(pos);
    photon_radius.setFillColor(sf::Color::Red);
    photon_radius.setRadius(8);
    update();
    texture.draw(photon_radius);
}
