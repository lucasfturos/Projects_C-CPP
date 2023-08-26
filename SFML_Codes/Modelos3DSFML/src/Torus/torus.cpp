#include "torus.hpp"

Torus::Torus(float inner, float outter, float vert)
    : inner_radius(inner), outter_radius(outter), vertex_quanty(vert) {
    // Variáveis da janela inicializadas
    window = make_shared<sf::RenderWindow>(
        sf::VideoMode(WIDTH, HEIGHT), "Rosquinha :)",
        sf::Style::Titlebar | sf::Style::Close);

    desktop = make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode());

    if (!texture.loadFromFile("img/earthmap.jpg")) {
        throw std::invalid_argument("Erro ao carregar a textura!!!");
    }
}

void Torus::init() {
    float increment = pi / vertex_quanty;
    auto p = make_shared<Point>();

    points.resize(
        static_cast<size_t>(vertex_quanty * vertex_quanty * vertex_quanty));

    for (float alpha = increment; alpha <= 2 * pi; alpha += increment) {
        for (float beta = increment; beta <= 2 * pi; beta += increment) {
            p->x = (outter_radius + inner_radius * cosf(beta)) * cosf(alpha);
            p->y = (outter_radius + inner_radius * cosf(beta)) * sinf(alpha);
            p->z = inner_radius * sinf(beta);
            points[num_vertex] = *p;
            num_vertex++;
        }
    }
}

void Torus::initTexture(float alpha, float beta) {
    sf::Vector2f tex_coord;
    tex_coord.x = alpha / (2 * pi);
    tex_coord.y = beta / (2 * pi);
    tex_coords.emplace_back(tex_coord);
}

void Torus::applyTexture(float x, float y, int index) {
    auto p = make_shared<Point>();
    sf::Vector2f tex_coord = tex_coords[index];
    sf::CircleShape circle(p->drawCircle(x, y, 3.f, sf::Color::White));

    // circle.setTexture(&texture);
    // circle.setTextureRect(sf::IntRect(tex_coord.x * texture.getSize().x,
    //                                 tex_coord.y * texture.getSize().y, 2,
    //                                 2));
    // sf::RectangleShape rect(p->drawRect(x,
    // y, 50.f, sf::Color::White));
    // rect.setTexture(&texture);
    // rect.setTextureRect(sf::IntRect(tex_coord.x
    // * texture.getSize().x,
    //                                        tex_coord.y *
    //                                        texture.getSize().y, 2, 2));
    //  window->draw(rect);
    window->draw(circle);
}

void Torus::draw() {
    float x, y;
    auto p = make_shared<Point>();
    for (int i = 0; i < num_vertex; i++) {
        *p = points[i];
        p->rotateX(rotation);
        p->rotateY(rotation);
        x = p->getProjection(distance, p->x, WIDTH / 2.f, 100.f);
        y = p->getProjection(distance, p->y, HEIGHT / 2.f, 100.f);
        // applyTexture(x, y, i);
        //   window->draw(p->drawRect(x,
        //   y, 3.f, sf::Color::White));
        window->draw(p->drawCircle(x, y, 3.f, sf::Color::White));
    }
}

void Torus::run() {
    window->setPosition(
        sf::Vector2i(desktop->width / 2.f - window->getSize().x / 2.f,
                     desktop->height / 2.f - window->getSize().y / 2.f));
    window->setFramerateLimit(60);

    init();
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                event.key.code == sf::Keyboard::Q ? window->close() : (void(0));
            }
        }
        window->clear();
        draw();
        rotation += 1.f / 60.f;
        window->display();
    }
}
