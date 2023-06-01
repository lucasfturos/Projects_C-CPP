#include "photon.hpp"

Photon::Photon(float pos_x, float pos_y, float vel_x, float vel_y) {
    pos.x = pos_x;
    pos.y = pos_y;
    vel.x = vel_x;
    vel.y = vel_y;

    initial_pos = pos;
    initial_vel = vel;
}

auto Photon::startCircleAnimation() -> void {
    animationState = AnimationState::CIRCLE;
    isAnimating = true;
}
auto Photon::startLinearAnimation() -> void {
    animationState = AnimationState::LINEAR;
    isAnimating = true;
}

auto Photon::resetPosition() -> void {
    pos = initial_pos;
    vel = initial_vel;
    isAnimating = false;
}

auto Photon::update() -> void {
    if (!isAnimating) {
        return;
    }
    elapsedSeconds += elapsed.asSeconds();

    float distance_x{pos.x - (width / 2)};
    float distance_y{pos.y - (height / 2)};
    float distance{
        std::sqrt(distance_x * distance_x + distance_y * distance_y)};
    if (animationState == AnimationState::CIRCLE) {
        if (distance < region_radius) {
            if (elapsedSeconds >= 2.0f) {
                pos.x -= width - 70.f;
                pos.y = 50.f;
                vel.x = 2.f;
                vel.y = 0;
            } else {
                float angle{std::atan2(distance_y, distance_x)};
                float target_radius{region_radius + 10.f};

                pos.x = (width / 2) + target_radius * std::cos(angle);
                pos.y = (height / 2) + target_radius * std::sin(angle);
            }
        } else {
            float inverse_distance{1.f / distance};

            float normalized_x{inverse_distance * distance_x};
            float normalized_y{inverse_distance * distance_y};

            float inverse_square_dropoff = inverse_distance * inverse_distance;

            float acceleration_x{normalized_x * 1000 * inverse_square_dropoff};
            float acceleration_y{normalized_y * 1000 * inverse_square_dropoff};

            vel.x += acceleration_x;
            vel.y += acceleration_y;

            pos.x += vel.x;
            pos.y += vel.y;
        }
    } else if (animationState == AnimationState::LINEAR) {
        //
    }
}

auto Photon::render(sf::RenderTexture &texture) -> void {
    if (isAnimating) {
        return;
    }

    photon_radius.setPosition(pos);
    photon_radius.setFillColor(sf::Color::Red);
    photon_radius.setRadius(2);
    update();
    texture.draw(photon_radius);
}
