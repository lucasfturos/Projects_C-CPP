#include "Rose/rose.hpp"
#include "Sphere/sphere.hpp"
#include "Torus/torus.hpp"
#include "common.hpp"

#include <stdexcept>
#include <unordered_map>

using std::make_shared;

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            throw std::runtime_error("Enter the model. Ex: ./Models Torus");
        }

        std::string input = argv[1];
        std::unordered_map<std::string, int> options{
            {"Torus", 1}, {"Sphere", 2}, {"Rose", 3}};

        auto it = options.find(input);
        if (it == options.end()) {
            throw std::invalid_argument(
                "Error: Enter the model name correctly!!!");
        }

        switch (it->second) {
        case 1: {
            auto torus = make_shared<Torus>(10.0f, 20.0f, 30.0f);
            torus->run();
            break;
        }
        case 2: {
            auto sphere = make_shared<Sphere>(30.0f, 30.0f);
            sphere->run();
            break;
        }
        case 3: {
            auto rose = make_shared<Rose>(-2.0f * pi, 15.0f * pi, 900.0f);
            rose->run();
            break;
        }
        default:
            break;
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
