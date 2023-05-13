#include "color.hpp"

void Color::write_color(std::ostream &out, color pixel_color,
                        int samples_per_pixel) {
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

color Color::ray_color(const ray &r, const color &background,
                       const hittable &world, int depth) {
    // Se exceder o limite do rebatimento dos pacotes de luz, não haverá mais
    // coleta de luz.
    if (depth <= 0) {
        return color(0, 0, 0);
    }

    // Se o raio não atingir nada, retorna a cor de fundo.
    if (!world.hit(r, .000001, infinity, rec)) {
        return background;
    }

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
        return emitted;
    }
    return emitted +
           attenuation * ray_color(scattered, background, world, depth - 1);
}
