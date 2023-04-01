#include <PenduloDuplo/pendulo_duplo.hpp>

int main() {
    float window_x{}, window_y{};
    std::shared_ptr<sf::RenderWindow> window;
    auto desktop{sf::VideoMode::getDesktopMode()};

    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(width, height), "Pendulo Duplo em SFML",
        sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(fps);
    window_x = static_cast<float>(window->getSize().x / 2);
    window_y = static_cast<float>(window->getSize().y / 2);

    window->setPosition(sf::Vector2i(desktop.width / 2 - window_x,
                                     desktop.height / 2 - window_y));

    auto pendulo{std::make_shared<PenduloDuplo>(3, 3, 15, 15, 90 * pi / 180,
                                                90 * pi / 180)};
    pendulo->setupRenderObjects();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        pendulo->update();
        pendulo->render();

        window->clear(sf::Color::Black);
        window->draw(*pendulo);
        window->display();
    }
}
