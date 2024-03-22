#include "pendulo_duplo.hpp"
#include <SFML/Graphics/Sprite.hpp>

PenduloDuplo::PenduloDuplo(float l1, float l2, float m1, float m2, float O1,
                           float O2)
    : m_l1(l1), m_l2(l2), m_m1(m1), m_m2(m2), m_O1(O1), m_O2(O2), alpha1(0),
      alpha2(0), w1(0), w2(0),
      frame_start(clock.getElapsedTime().asMilliseconds()), length_vertices(3) {

    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(width, height), "Pendulo Duplo em SFML",
        sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(fps);

    desktop = std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode());

    half_width = static_cast<float>(window->getSize().x / 2.0f);
    half_height = static_cast<float>(window->getSize().y / 2.0f);

    window->setPosition(sf::Vector2i(desktop->width / 2.0f - half_width,
                                     desktop->height / 2.0f - half_height));
}

auto PenduloDuplo::setupRenderObjects() -> void {
    vertex_buffer.create(3);
    vertex_buffer.setPrimitiveType(sf::LineStrip);

    length_vertices[0].position = sf::Vector2f(half_width, half_height * 0.7);
    for (auto i{0}; i < 3; i++) {
        length_vertices[i].color = sf::Color::White;
    }

    base.setRadius(m_m1);
    base.setOrigin(base.getRadius(), base.getRadius());
    base.setFillColor(sf::Color::White);

    mass1.setRadius(m_m1);
    mass1.setOrigin(mass1.getRadius(), mass1.getRadius());
    mass1.setFillColor(sf::Color::White);

    mass2.setRadius(m_m2);
    mass2.setOrigin(mass2.getRadius(), mass2.getRadius());
    mass2.setFillColor(sf::Color::White);
}

auto PenduloDuplo::update() -> void {
    current_time = clock.getElapsedTime().asMilliseconds();
    accumulator += current_time - frame_start;
    frame_start = current_time;

    if (accumulator >= 1.0F / 30.0F) {
        accumulator = 1.0F / 30.0F;
    }

    while (accumulator > dt) {
        float sinO1 = sinf(m_O1);
        float sinO2 = sinf(m_O2);
        float cosO1 = cosf(m_O1);
        float cosO2 = cosf(m_O2);

        float d1 = -g * (2 * m_m1 + m_m2) * sinO1 -
                   g * m_m2 * sinf(m_O1 - 2 * m_O2) -
                   2 * m_m2 * sinf(m_O1 - m_O2) *
                       (w2 * w2 * m_l2 + w1 * w1 * m_l1 * cosf(m_O1 - m_O2));
        float d2 = 2 * sinf(m_O1 - m_O2) *
                   (w1 * w1 * m_l1 * (m_m1 + m_m2) + g * (m_m1 + m_m2) * cosO1 +
                    w2 * w2 * m_l2 * m_m2 * cosf(m_O1 - m_O2));

        alpha1 =
            d1 / (m_l1 * (2 * m_m1 + m_m2 - m_m2 * cosf(2 * m_O1 - 2 * m_O2)));
        alpha2 =
            d2 / (m_l2 * (2 * m_m1 + m_m2 - m_m2 * cosf(2 * m_O1 - 2 * m_O2)));

        w1 += 0.1f * alpha1 * dt;
        w2 += 0.1f * alpha2 * dt;
        m_O1 += 2 * w1 * dt;
        m_O2 += 2 * w2 * dt;

        accumulator -= dt;
    }

    updateXY();
}

auto PenduloDuplo::render() -> void {
    end_pos1 = sf::Vector2f(x1 * 100 + length_vertices[0].position.x,
                            y1 * 100 + length_vertices[0].position.y);
    end_pos2 = sf::Vector2f(x2 * 100 + length_vertices[0].position.x,
                            y2 * 100 + length_vertices[0].position.y);

    length_vertices[1].position = end_pos1;
    length_vertices[2].position = end_pos2;
    vertex_buffer.update(length_vertices.data());

    base.setPosition(half_width, half_height * 0.7f);
    mass1.setPosition(end_pos1);
    mass2.setPosition(end_pos2);

    color_trace = sf::Color(255, 255, 255, rand() % 255);
    trace1_s = traces1.size();
    trace2_s = traces2.size();

    if (trace1_s < trace_size && trace2_s < trace_size) {
        traces1.push_back(sf::Vertex(end_pos1, color_trace));
        traces2.push_back(sf::Vertex(end_pos2, color_trace));
    } else {
        for (auto i{0}; i < trace1_s; ++i) {
            traces1[i].position = traces1[i + 1].position;
        }
        for (auto i{0}; i < trace2_s - 1; ++i) {
            traces2[i].position = traces2[i + 1].position;
        }
        traces1[trace1_s - 1].position = end_pos1;
        traces2[trace2_s - 1].position = end_pos2;
    }

    window->clear(sf::Color::Black);
    if (show_length) {
        window->draw(vertex_buffer);
    }

    window->draw(base);
    window->draw(mass1);
    window->draw(mass2);
    window->draw(&traces1[0], traces1.size(), sf::LineStrip);
    window->draw(&traces2[0], traces2.size(), sf::LineStrip);
    window->display();
}

auto PenduloDuplo::updateXY() -> void {
    x1 = m_l1 * sinf(m_O1);
    y1 = m_l1 * cosf(m_O1);

    x2 = x1 + m_l2 * sinf(m_O2);
    y2 = y1 + m_l2 * cosf(m_O2);
}

auto PenduloDuplo::run() -> void {
    setupRenderObjects();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.key.code == sf::Keyboard::Q)
                window->close();
        }
        window->clear(sf::Color::Black);

        update();
        render();
    }
}