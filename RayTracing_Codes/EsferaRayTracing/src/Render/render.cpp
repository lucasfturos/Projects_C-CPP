#include "render.hpp"

color Render::ray_color(const ray &r, const hittable &world, int depth) {
    hit_record rec;
    // Se exceder o limite do rebatimento dos pacotes de luz, não haverá mais
    // coleta de luz.
    if (depth <= 0) {
        return color(0, 0, 0);
    }

    if (world.hit(r, .000001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return color(0, 0, 0);
    }

    vec3 unit_direction{unit_vector(r.direction())};
    auto t{.5 * (unit_direction.y() + 1.0)};
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(.5, .7, 1.0);
}

void Render::run() {
    // Camera
    // visão de frente
    point3 lookfrom(0, 0, 0);

    // Visão da diagonal
    // point3 lookfrom(0, 2, 1);

    // Visão do observador
    point3 lookat(0, 0, -1);
    vec3 vup(0, 1, 0);
    cam = make_shared<camera>(lookfrom, lookat, vup, 90.0, aspect_ratio);

    // World
    auto material_metal{make_shared<metal>(color(.8, .8, .8), .0)};
    auto material_lambertian{make_shared<lambertian>(color(.8, .8, .8))};
    auto material_dieletric{make_shared<dielectric>(1.5)};

    // Chão
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_metal));
    // Objeto no centro
    world.add(make_shared<sphere>(point3(.0, .0, -1.0), 0.5, material_metal));
    // Objeto a esquerda
    // world.add(
    //    make_shared<sphere>(point3(-1.0, .0, -1.0), .5, material_dieletric));
    // Objeto a direita
    // world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5,
    // material_metal));

    // Renderização
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (auto j{image_height - 1}; j >= 0; --j) {
        std::cerr << "\rLinhas de varredura restantes: " << j << ' '
                  << std::flush;
        for (auto i{0}; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (auto s{0}; s < samples_per_pixel; ++s) {
                auto u{(i + random_double()) / (image_width - 1)};
                auto v{(j + random_double()) / (image_height - 1)};

                ray r{cam->get_ray(u, v)};
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nTerminou" << '\n';
}
