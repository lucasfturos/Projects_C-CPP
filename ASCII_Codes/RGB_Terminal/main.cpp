#include "color.hpp"

int main(int argc, char *argv[]) {
    auto color{std::make_shared<Color>()};
    // color->run_color();
    color->run_image(argc, argv);
}
