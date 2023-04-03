#include <BlackHole/black_hole.hpp>

auto main() -> int {
    std::shared_ptr<sf::RenderWindow> window;
    auto desktop{sf::VideoMode::getDesktopMode()};

    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(width, height), "Black Hole Newtonian - SFML",
        sf::Style::Titlebar | sf::Style::Close);

    window->setFramerateLimit(fps);

    window->setPosition(sf::Vector2i(desktop.width / 2 - width / 2,
                                     desktop.height / 2 - height / 2));
    auto black_hole{std::make_shared<BlackHole>()};

    black_hole->setupRenderObjectBlackHole();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        black_hole->render();
        window->clear(sf::Color::White);
        window->draw(*black_hole);
        window->display();
    }
}
