#include "color.hpp"

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r{pixel_color.x()};
    auto g{pixel_color.y()};
    auto b{pixel_color.z()};
    // Divide a cor pelo número de amostras.
    auto scale{1.0 / samples_per_pixel};
    r *= scale;
    g *= scale;
    b *= scale;
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255 * clamp(b, 0.0, 0.999)) << '\n';
}
