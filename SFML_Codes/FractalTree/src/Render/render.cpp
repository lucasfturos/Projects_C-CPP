#include "render.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>

using std::make_shared;

Render::Render()
    : depth(0), sliderValue(0), isDragging(false),
      window(make_shared<sf::RenderWindow>(
          sf::VideoMode(WIDTH, HEIGHT), "Fractal Tree",
          sf::Style::Titlebar | sf::Style::Close)),
      desktop(make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode())) {
    window->setPosition(
        sf::Vector2i(desktop->width / 2.f - window->getSize().x / 2.f,
                     desktop->height / 2.f - window->getSize().y / 2.f));
    initializeSlider();
}

void Render::initializeSlider() {
    sliderBar.setSize(sf::Vector2f(SLIDER_WIDTH, SLIDER_HEIGHT));
    sliderBar.setFillColor(sf::Color::White);
    sliderBar.setPosition(10, 10);

    sliderObject.setSize(sf::Vector2f(20, SLIDER_HEIGHT));
    sliderObject.setFillColor(sf::Color::Red);
    sliderObject.setPosition(10, 10);
}

void Render::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.key.code == sf::Keyboard::Q) {
            window->close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            sf::FloatRect sliderBounds = sliderObject.getGlobalBounds();
            if (sliderBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
                isDragging = true;
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            isDragging = false;
        }
    }
}

void Render::updateSliderPosition() {
    if (isDragging) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        float x = static_cast<float>(mousePos.x);
        x = std::max(10.f, std::min(10.f + SLIDER_WIDTH - 20, x));
        sliderObject.setPosition(x, 10);
        sliderValue =
            static_cast<int>((x - 10) / static_cast<float>(SLIDER_WIDTH - 20) *
                             SLIDER_MAX_VALUE);
    }
}

void Render::drawTree(int n, float x1, float y1, float x2, float y2,
                      float angle) {
    if (n <= 1)
        return;

    std::vector<sf::Vertex> line;
    line.push_back(sf::Vertex(sf::Vector2f(x1, y1)));
    line.push_back(sf::Vertex(sf::Vector2f(x2, y2)));
    window->draw(line.data(), line.size(), sf::LinesStrip);

    float midX = (x1 + x2) / 2;
    float midY = (y1 + y2) / 2;
    float newLength = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) * 0.7;

    float x3 = midX + newLength * cos(angle * pi / 180);
    float y3 = midY + newLength * sin(angle * pi / 180);

    float x4 = midX + newLength * cos(angle * pi / 180);
    float y4 = midY + newLength * sin(angle * pi / 180);

    drawTree(n - 1, midX, midY, x3, y3, angle + 45);
    drawTree(n - 1, midX, midY, x4, y4, angle - 45);
}

void Render::draw() {
    window->clear();
    window->draw(sliderBar);
    window->draw(sliderObject);
    float angle = -90;
    float trunkHeight = 400;
    drawTree(sliderValue, WIDTH / 2.f, HEIGHT, WIDTH / 2.f,
             HEIGHT - trunkHeight, angle);
    window->display();
}

void Render::run() {
    window->setFramerateLimit(60);
    while (window->isOpen()) {
        handleEvents();
        updateSliderPosition();
        draw();
    }
}
