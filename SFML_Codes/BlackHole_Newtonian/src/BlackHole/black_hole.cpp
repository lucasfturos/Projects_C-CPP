#include "black_hole.hpp"

BlackHole::BlackHole(float half_width, float half_height) {
    pos.x = half_width;
    pos.y = half_height;
}
auto BlackHole::setupObjectBlackHole() -> void {
    black_hole_radius.setRadius(radius * epsilon);
    black_hole_radius.setOrigin(black_hole_radius.getRadius(),
                                black_hole_radius.getRadius());
    black_hole_radius.setFillColor(sf::Color::Black);
    black_hole_radius.setPosition(pos.x, pos.y);
    black_hole_radius.setPointCount(point_count);
}

auto BlackHole::setupObjectAtratorRegion() -> void {
    region1_atrator.setRadius((radius * epsilon) * 3 + 32);
    region1_atrator.setOrigin(region1_atrator.getRadius(),
                              region1_atrator.getRadius());
    region1_atrator.setOutlineColor(sf::Color::Black);
    region1_atrator.setPosition(pos.x, pos.y);
    region1_atrator.setOutlineThickness(2.0f);
    region1_atrator.setPointCount(point_count);

    region2_atrator.setRadius((radius * epsilon) * 3 + 16);
    region2_atrator.setOrigin(region2_atrator.getRadius(),
                              region2_atrator.getRadius());
    region2_atrator.setOutlineColor(sf::Color::Black);
    region2_atrator.setPosition(pos.x, pos.y);
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

    elapsedSeconds += elapsed.asSeconds();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis_radius(0.f, 40.f);
    std::uniform_real_distribution<float> dis_angle(0.f, 2.f * M_PI);

    if (elapsedSeconds >= 2.0f) {
        for (const auto &photon : photons) {
            photon->resetPosition();
        }
    }

    for (const auto &photon : photons) {
        photon->startCircleAnimation();
    }
    for (int i{}; i < max_photons; i++) {
        float pos_x{};
        float pos_y{};
        float vel_x{4.f};
        float vel_y{0.f};

        float radius{dis_radius(gen)};
        float angle{dis_angle(gen)};
        pos_x = width - 70.f + radius * cosf(angle);
        pos_y = 50.f + radius * sinf(angle);

        auto photon{std::make_shared<Photon>(pos_x, pos_y, vel_x, vel_y)};
        photons.push_back(photon);

        if (elapsedSeconds >= 2.0f) {
            photon->startLinearAnimation();
        }

        photon->update();
        photon->render(texture);
    }

    texture.draw(black_hole_radius);
    texture.display();
}
