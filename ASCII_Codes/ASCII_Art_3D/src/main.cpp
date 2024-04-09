#include "Render/render.hpp"

int main() {
    try {
        auto render = std::make_shared<Render>();
        render->run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
