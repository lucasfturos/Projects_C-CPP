#include "PenduloDuplo/pendulo_duplo.hpp"
#include <iostream>

int main() {
    try {
        auto pendulo = std::make_shared<PenduloDuplo>(
            3, 3, 15, 15, 90 * pi / 180, 90 * pi / 180);
        pendulo->run();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
