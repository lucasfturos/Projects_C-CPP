#include "PenduloDuplo/pendulo_duplo.hpp"
#include <iostream>

int main() {
    try {
        float mass = 20;
        float length = 280;
        auto pendulo = std::make_shared<PenduloDuplo>(length, length, mass,
                                                      mass, 3 * pi / 4, pi / 2);
        pendulo->run();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
