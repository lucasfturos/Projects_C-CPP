#include "PenduloDuplo/pendulo_duplo.hpp"
#include "Particles/particles.hpp"

int main(int argc, char *argv[]) {
    std::shared_ptr<sf::RenderWindow> window;
    auto desktop = sf::VideoMode::getDesktopMode();

    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(900, 900), "Pendulo Duplo em SFML");
    window->setFramerateLimit(60);

    window->setPosition(sf::Vector2i(desktop.width / 2 - window->getSize().x / 2,
                                     desktop.height / 2 - window->getSize().y / 2));

    PenduloDuplo pendulo(2, 2, 10, 10, 90 * pi / 180, 90 * pi / 180);
    pendulo.setupRenderObjects();

    while (window->isOpen()) {
        // Process events
        sf::Event event;
        while (window->pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window->close();
        }

        pendulo.update();
        pendulo.render();

        window->clear();
        window->draw(pendulo);
        window->display();
    }
}
