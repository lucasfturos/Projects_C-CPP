#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 800;
const int HALF_WIDTH = WIDTH / 2;
const int HALF_HEIGHT = HEIGHT / 2;
const int MAX = 50;
const int MAX_ITERATIONS = 600;
const float pi = M_PI;

int main() {
    auto window =
        std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), "Orb");
    auto desktop =
        std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode());
    window->setPosition(
        sf::Vector2i(desktop->width / 2.f - window->getSize().x / 2.f,
                     desktop->height / 2.f - window->getSize().y / 2.f));
    window->setFramerateLimit(60);

    std::vector<sf::Vector3f> points;
    std::vector<sf::VertexArray> lines;
    std::vector<sf::Color> orbitColors;

    float tim = 0;
    int count = 0;
    int iterationCount = 0;
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            event.type == sf::Event::Closed ? window->close() : (void(0));
            event.key.code == sf::Keyboard::Q ? window->close() : (void(0));
        }

        window->clear();

        if (iterationCount >= MAX_ITERATIONS) {
            lines.clear();
            points.clear();
            orbitColors.clear();
            count = 0;
            iterationCount = 0;
        }
        points.clear();

        float r = 0.0f;
        for (size_t a = 0; a < MAX; ++a) {
            points.push_back({cosf(r), sinf(r), 0});
            r += (pi * 2) / MAX;
        }

        for (size_t a = 0; a < MAX; ++a) {
            points.push_back({0, points[a].x, points[a].y});
        }

        for (size_t a = 0; a < MAX; ++a) {
            points.push_back({points[a].y, 0, points[a].x});
        }
        for (int i = 0; i < 256; ++i) {
            float hue = (static_cast<float>(i) / MAX) * 360.f;
            orbitColors.emplace_back(hue * 0.7f, hue, hue, 100.f);
        }

        tim = count / 5.0f;
        for (int e = 0; e < 3; ++e) {
            tim *= 1.7f;
            float s = 1 - e / 3.0f;
            float a = tim / 59.0f;
            float yp = cosf(a);
            float yp2 = sinf(a);
            a = tim / 23.0f;
            float xp = cosf(a);
            float xp2 = sinf(a);

            std::vector<sf::Vector3f> p2;

            for (int a = 0; a < points.size(); a++) {
                float x = points[a].x;
                float y = points[a].y;
                float z = points[a].z;

                float y1 = y * yp + z * yp2;
                float z1 = y * yp2 - z * yp;
                float x1 = x * xp + z1 * xp2;

                z = x * xp2 - z1 * xp;
                z1 = powf(2, z * s);
                x = x1 * z1;
                y = y1 * z1;
                p2.push_back({x, y, z});
            }

            s *= 200.0f;

            for (size_t a = 0; a < MAX; ++a) {
                sf::Vector3f b = p2[a];
                sf::Vector3f c = p2[(a + 1) % MAX];

                sf::VertexArray line(sf::LinesStrip, 2);
                line[0].position =
                    sf::Vector2f(b.x * s + HALF_WIDTH, b.y * s + HALF_HEIGHT);
                line[1].position =
                    sf::Vector2f(c.x * s + HALF_WIDTH, c.y * s + HALF_HEIGHT);

                sf::Color color(orbitColors[a].r, orbitColors[a].g,
                                orbitColors[a].b, orbitColors[a].a);

                line[0].color = orbitColors[a];
                line[1].color = orbitColors[a];
                line[0].color.a = 100;
                line[1].color.a = 100;

                lines.emplace_back(line);
            }
        }
        count++;
        iterationCount++;

        for (const auto &line : lines) {
            window->draw(line);
        }
        window->display();
    }

    return 0;
}
