#include "rose.hpp"
#include "../common.hpp"

using std::make_shared;

Rose::Rose(float init_theta, float final_theta, float counter)
    : window(make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), "Rosa",
                                           sf::Style::Titlebar |
                                               sf::Style::Close)),
      desktop(make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode())),
      init_theta(init_theta), final_theta(final_theta), counter(counter) {}

float Rose::fx(float s) {
    float a = 1 - std::fmod((3.6f * s), (2 * pi)) / pi;
    float b = 1.25f * (a * a) - 0.25f;
    return 1 - 0.5f * (b * b);
}

float Rose::fy(float x, float phi) {
    float a = 1.2f * x - 1;
    return 2 * (x * x) * (a * a) * std::sin(phi);
}

void Rose::init() {
    points.reserve(static_cast<size_t>(counter));
    radius.reserve(static_cast<size_t>(counter));

    for (float x = 0.0f; x < 1.0f; x += 0.05) {
        for (float s = init_theta; s < final_theta;
             s += (final_theta - init_theta) / counter) {
            float phi = pi / 2 * std::exp(-s / (8 * pi));
            float X = fx(s);
            float Y = fy(x, phi);
            float r = X * (x * std::sin(phi) + Y * std::cos(phi));

            if (r > 0.0f) {
                float factor = 200.0f;
                r *= factor;
                X *= factor;

                points.emplace_back(r * std::cos(s),
                                    X * (x * std::cos(phi) - Y * std::sin(phi)),
                                    r * std::sin(s));
                radius.emplace_back(r);
                num_vertex++;
            }
        }
    }
}

sf::Color Rose::calculateColor(float radius, float r_min, float r_max) {
    float amplitude = 255.0f;
    float normalized_radius = (radius - r_min) / (r_max - r_min);
    sf::Uint16 value =
        34 + static_cast<sf::Uint16>(amplitude * normalized_radius);

    sf::Uint16 red =
        amplitude - static_cast<sf::Uint16>(amplitude * normalized_radius);
    value >>= 8;
    sf::Uint16 green = value & 0x1f;
    value >>= 8;
    sf::Uint16 blue = value & 0x0f;

    return sf::Color(red, green, blue);
}

void Rose::draw() {
    float x, y;
    auto p = make_shared<Point>();
    float r_min = *std::min_element(radius.begin(), radius.end());
    float r_max = *std::max_element(radius.begin(), radius.end());

    for (int i = 0; i < num_vertex; ++i) {
        *p = points[i];
        p->rotateY(rotation);
        float zoom = 900.0f;
        x = p->getProjection(distance + zoom, p->x, WIDTH / 2.f, zoom);
        y = p->getProjection(distance + zoom, p->y - 100, HEIGHT / 2.f, zoom);

        auto color = calculateColor(radius[i], r_min, r_max);
        auto circle = p->drawCircle(x, y, 5.f, color);
        window->draw(circle);
    }
}

void Rose::run() {
    window->setPosition(
        sf::Vector2i(desktop->width / 2.f - window->getSize().x / 2.f,
                     desktop->height / 2.f - window->getSize().y / 2.f));
    window->setFramerateLimit(60);

    init();
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Q:
                    window->close();
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
        window->clear();
        draw();
        rotation += 1.f / 60.f;
        window->display();
    }
}