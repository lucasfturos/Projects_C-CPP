#include "Render/render.hpp"

int main() {
    try {
        auto render = make_shared<Render>();
        render->run();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        std::exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
