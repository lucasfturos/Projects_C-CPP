#include "pendulo_duplo.hpp"

PenduloDuplo::PenduloDuplo(float l1, float l2, float m1, float m2, float O1,
                           float O2) {
    this->l1 = l1;
    this->l2 = l2;
    this->m1 = m1;
    this->m2 = m2;
    this->O1 = O1;
    this->O2 = O2;

    alpha1 = 0;
    alpha2 = 0;
    w1 = 0;
    w2 = 0;
}

auto PenduloDuplo::setupRenderObjects() -> void {
    texture.create(width, height);
    this->setTexture(texture.getTexture());

    ver_buffer.create(3);
    ver_buffer.setPrimitiveType(sf::LineStrip);

    length_vertices[0].position = sf::Vector2f(width / 2, height / 2.7);
    for (auto i{0}; i < 3; i++) {
        length_vertices[i].color = sf::Color::White;
    }

    base.setRadius(10);
    base.setOrigin(base.getRadius(), base.getRadius());
    base.setFillColor(sf::Color::White);

    mass1.setRadius(m1);
    mass1.setOrigin(mass1.getRadius(), mass1.getRadius());
    mass1.setFillColor(sf::Color::White);

    mass2.setRadius(m2);
    mass2.setOrigin(mass2.getRadius(), mass2.getRadius());
    mass2.setFillColor(sf::Color::White);
}

auto PenduloDuplo::update() -> void {
    alpha1 = static_cast<float>(
        (-g * (2 * m1 + m2) * sin(O1) - g * m2 * sin(O1 - 2 * O2) -
         2 * m2 * sin(O1 - O2) * (w2 * w2 * l2 + w1 * w1 * l1 * cos(O1 - O2))) /
        (l1 * (2 * m1 + m2 - m2 * cos(2 * O1 - 2 * O2))));
    alpha2 =
        static_cast<float>((2 * sin(O1 - O2)) *
                           (w1 * w1 * l1 * (m1 + m2) + g * (m1 + m2) * cos(O1) +
                            w2 * w2 * l2 * m2 * cos(O1 - O2)) /
                           l2 / (2 * m1 + m2 - m2 * cos(2 * O1 - 2 * O2)));

    w1 += alpha1 * dt * 2.5f;
    w2 += alpha2 * dt * 2.5f;
    O1 += w1 * dt * 2.5f;
    O2 += w2 * dt * 2.5f;

    updateXY();

    w1 *= 1.0f;
    w2 *= 1.0f;
}

auto PenduloDuplo::render() -> void {
    end_pos1 = sf::Vector2f(x1 * 100 + length_vertices[0].position.x,
                            y1 * 100 + length_vertices[0].position.y);
    end_pos2 = sf::Vector2f(x2 * 100 + length_vertices[0].position.x,
                            y2 * 100 + length_vertices[0].position.y);

    length_vertices[1].position = end_pos1;
    length_vertices[2].position = end_pos2;
    ver_buffer.update(length_vertices);

    base.setPosition(width / 2, height / 2.7);
    mass1.setPosition(end_pos1);
    mass2.setPosition(end_pos2);

    color_trace = sf::Color(255, 255, 255, rand() % 255);
    trace_s = traces.size();
    if (trace_s < trace_size) {
        traces.push_back(sf::Vertex(end_pos2, color_trace));
    } else {
        for (auto i{0}; i < trace_s - 1; ++i) {
            traces[i].position = traces[i + 1].position;
        }
        traces[trace_s - 1].position = end_pos2;
    }

    texture.clear(sf::Color::Black);
    if (show_length) {
        texture.draw(ver_buffer);
    }

    texture.draw(base);
    texture.draw(mass1);
    texture.draw(mass2);
    texture.draw(&traces[0], traces.size(), sf::LineStrip);
    texture.display();
}

auto PenduloDuplo::updateXY() -> void {
    x1 = l1 * sin(O1);
    y1 = l1 * cos(O1);

    x2 = x1 + l2 * sin(O2);
    y2 = y1 + l2 * cos(O2);
}
