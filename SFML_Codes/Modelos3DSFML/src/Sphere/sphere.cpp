#include "sphere.hpp"

Sphere::Sphere(float r, float vert) : radius(r), vertex_quanty(vert) {
    // Variáveis da janela inicializadas
    window = make_shared<sf::RenderWindow>(
        sf::VideoMode(WIDTH, HEIGHT), "Bolinha :)",
        sf::Style::Titlebar | sf::Style::Close);

    desktop = make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode());

    if (!texture.loadFromFile("img/earthclouds.jpg")) {
        throw std::invalid_argument("Erro ao carregar a textura!!!");
    }
}

void Sphere::init() {
    float increment = pi / vertex_quanty;

    auto p = make_shared<Point>();

    points.resize(
        static_cast<size_t>(vertex_quanty * vertex_quanty * vertex_quanty));

    for (float alpha = increment; alpha <= 2 * pi; alpha += increment) {
        for (float beta = increment; beta <= pi; beta += increment) {
            sf::Vector2f tex_coord;
            tex_coord.x = alpha / (2 * pi);
            tex_coord.y = beta / (2 * pi);
            tex_coords.emplace_back(tex_coord);

            p->x = cos(alpha) * sin(beta) * radius;
            p->y = sin(alpha) * radius;
            p->z = cos(alpha) * cos(beta) * radius;
            points[num_vertex] = *p;
            num_vertex++;
        }
    }
}

void Sphere::draw() {
    float x, y;
    auto p = make_shared<Point>();

    for (int i = 0; i < num_vertex; i++) {
        *p = points[i];
        // p->rotateX(rotation);
        p->rotateY(rotation);
        x = p->getProjection(distance, p->x, WIDTH / 2.f, 100.f);
        y = p->getProjection(distance, p->y, HEIGHT / 2.f, 100.f);

        sf::CircleShape circle = p->drawCircle(x, y, 5.f, sf::Color::White);
        sf::Vector2f texCoord = tex_coords[i];

        circle.setTexture(&texture);
        circle.setTextureRect(sf::IntRect(texCoord.x * texture.getSize().x,
                                          texCoord.y * texture.getSize().y, 2,
                                          2));
        window->draw(circle);
    }
}

void Sphere::run() {
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
