#include "pendulo_duplo.hpp"

PenduloDuplo::PenduloDuplo(float l1, float l2, float m1, float m2, float O1,
                           float O2)
    : m_l1(l1), m_l2(l2), m_m1(m1), m_m2(m2), m_O1(O1), m_O2(O2), alpha1(0),
      alpha2(0), w1(0), w2(0), paused(false), show_length(true),
      length_vertices(3),
      window(std::make_shared<sf::RenderWindow>(
          sf::VideoMode(width, height), "Pendulo Duplo em SFML",
          sf::Style::Titlebar | sf::Style::Close)),
      desktop(
          std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode())) {

    window->setFramerateLimit(fps);

    half_width = static_cast<float>(window->getSize().x / 2.0f);
    half_height = static_cast<float>(window->getSize().y / 2.0f);

    window->setPosition(sf::Vector2i(desktop->width / 2.0f - half_width,
                                     desktop->height / 2.0f - half_height));

    frame_start = clock.getElapsedTime().asMilliseconds();
}

auto PenduloDuplo::setupRender() -> void {
    vertex_buffer.create(3);
    vertex_buffer.setPrimitiveType(sf::LineStrip);

    length_vertices[0].position = sf::Vector2f(half_width, half_height * 0.7f);
    for (std::size_t i = 0; i < length_vertices.size(); i++) {
        length_vertices[i].color = sf::Color(255, 255, 255, 180);
    }

    base.setRadius(m_m1);
    base.setOrigin(base.getRadius(), base.getRadius());
    base.setFillColor(sf::Color(8, 69, 150, 255));

    mass1.setRadius(m_m1);
    mass1.setOrigin(mass1.getRadius(), mass1.getRadius());
    mass1.setFillColor(sf::Color(8, 69, 150, 255));

    mass2.setRadius(m_m2);
    mass2.setOrigin(mass2.getRadius(), mass2.getRadius());
    mass2.setFillColor(sf::Color(8, 69, 150, 255));
}

auto PenduloDuplo::update() -> void {
    if (paused) {
        return;
    }

    current_time = clock.getElapsedTime().asMilliseconds();
    accumulator += current_time - frame_start;
    frame_start = current_time;

    if (accumulator >= 1.0F / 30.0F) {
        accumulator = 1.0F / 30.0F;
    }

    while (accumulator > dt) {
        float sinO1 = sinf(m_O1);
        float cosO1 = cosf(m_O1);

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

        w1 += 5 * alpha1 * dt;
        w2 += 5 * alpha2 * dt;
        m_O1 += 5 * w1 * dt;
        m_O2 += 5 * w2 * dt;

        accumulator -= dt;
    }

    updateXY();
}

auto PenduloDuplo::updateXY() -> void {
    x1 = m_l1 * sinf(m_O1);
    y1 = m_l1 * cosf(m_O1);

    x2 = x1 + m_l2 * sinf(m_O2);
    y2 = y1 + m_l2 * cosf(m_O2);
}

auto PenduloDuplo::render() -> void {
    end_pos1 = sf::Vector2f(x1 + length_vertices[0].position.x,
                            y1 + length_vertices[0].position.y);
    end_pos2 = sf::Vector2f(x2 + length_vertices[0].position.x,
                            y2 + length_vertices[0].position.y);

    length_vertices[1].position = end_pos1;
    length_vertices[2].position = end_pos2;
    vertex_buffer.update(length_vertices.data());

    base.setPosition(half_width, half_height * 0.7f);
    mass1.setPosition(end_pos1);
    mass2.setPosition(end_pos2);

    traces_size = traces.size();

    if (traces_size < trace_size) {
        traces.push_back(sf::Vertex(end_pos2, sf::Color(35, 108, 153, 255)));
    } else {
        for (std::size_t i = 0; i < traces_size - 1; ++i) {
            traces[i].position = traces[i + 1].position;
        }
        traces[traces_size - 1].position = end_pos2;
    }

    float wave_amplitude = 50.0f;
    sf::VertexArray oscilated_traces2(sf::LinesStrip, traces.size());
    for (std::size_t i = 0; i < traces.size(); ++i) {
        sf::Vector2f position = traces[i].position;
        position.y += wave_amplitude * sinf(i * w1 + current_time * w2);
        sf::Color vertex_color(
            static_cast<sf::Uint8>(start_color.r * (1 - current_time) +
                                   end_color.r * current_time),
            static_cast<sf::Uint8>(start_color.g * (1 - current_time) +
                                   end_color.g * current_time),
            static_cast<sf::Uint8>(start_color.b * (1 - current_time) +
                                   end_color.b * current_time));

        oscilated_traces2[i] = sf::Vertex(position, vertex_color);
    }

    window->clear(sf::Color::Black);
    if (show_length) {
        window->draw(vertex_buffer);
    }

    window->draw(base);
    window->draw(mass1);
    window->draw(mass2);
    window->draw(traces.data(), traces.size(), sf::LineStrip);
    window->draw(oscilated_traces2);
}

auto PenduloDuplo::togglePause() -> void { paused = !paused; }

auto PenduloDuplo::run() -> void {
    setupRender();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                case sf::Keyboard::Q:
                    window->close();
                    break;
                case sf::Keyboard::Space:
                    togglePause();
                    break;
                default:
                    break;
                }
            } 
            default:
                break;
            }
        }

        window->clear();
        update();
        render();
        window->display();
    }
}