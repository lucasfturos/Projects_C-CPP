#include "render.hpp"

Render::Render()
    : camp(HEIGHT, std::vector<std::string>(WIDTH)),
      p(std::make_shared<point3d>()),
      torus(std::make_shared<Torus>(0.8, 2.0, 30)), sources(torus->Sources()),
      distance(400), alpha(0), beta(0), theta(0) {}

// Render::Render()
//     : camp(HEIGHT, std::vector<std::string>(WIDTH)),
//       p(std::make_shared<point3d>()),
//       read_object(std::make_shared<ReadObjectFile>("./obj/teapot.obj")),
//       sources(read_object->Sources()), distance(700), alpha(0), beta(0),
//       theta(0) {}

void Render::update() {
    alpha += 0.05;
    beta += 0.03;
    theta += 0.02;
}

void Render::clear() {
    auto vertices = sources.vertices;

    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            if (row == 0 || row == HEIGHT - 1 || col == 0 || col == WIDTH - 1) {
                camp[row][col] = '#';
            } else {
                camp[row][col] = ' ';
            }
        }
    }

    for (const auto &indice : sources.indices) {
        p->x = vertices[indice].x;
        p->y = vertices[indice].y;
        p->z = vertices[indice].z;

        p->rotateX(alpha);
        p->rotateY(beta);
        p->rotateZ(theta);

        double projectedX = p->getProjection(distance, p->x, WIDTH / 2.0, 90);
        double projectedY = p->getProjection(distance, p->y, HEIGHT / 2.0, 90);

        int screenX = static_cast<int>(projectedX);
        int screenY = static_cast<int>(projectedY);

        camp[screenY][screenX] = ':';

        int shadowX = screenX + 1;
        int shadowY = screenY + 1;
        if (shadowX < WIDTH - 1 && shadowY < HEIGHT - 1) {
            camp[shadowY][shadowX] = '.';
        }
    }
}

void Render::draw() {
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            std::cout << camp[row][col].c_str();
        }
        std::cout << '\n';
    }
}

void Render::run() {
    while (true) {
        std::cout << "\033c";
        clear();
        update();
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
