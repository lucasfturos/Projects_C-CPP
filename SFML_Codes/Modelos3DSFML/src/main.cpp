#include "Sphere/sphere.hpp"
#include "Torus/torus.hpp"

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            throw std::invalid_argument("Enter the model. Ex: Torus ou Sphere");
        }

        std::string input = argv[1];

        if (input == "Torus") {
            auto torus = make_shared<Torus>(10.f, 20.f, 30.f);
            torus->run();
        } else if (input == "Sphere") {
            auto sphere = make_shared<Sphere>(30.f, 30.f);
            sphere->run();
        } else {
            throw std::runtime_error(
                "Error: Enter the model name correctly!!!");
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
}
