#include "render.hpp"

void Render::run() {
    //  Color
    color_ptr = make_shared<Color>();

    // Camera
    //  Visão da sala
    point3 lookfrom(139, 139, -400);
    //  Visão do observador
    point3 lookat(139, 139, 0);
    vec3 vup(0, 1, 0);
    color background(0, 0, 0);
    // background = color(0, 0, 0.1);

    cam = make_shared<camera>(lookfrom, lookat, vup, vfov, aspect_ratio);

    // World
    auto world{cornell_box()};
    // auto world{cornell_smoke()};

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
                pixel_color += ray_color(r, background, world, max_depth);
            }
            color_ptr->write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nTerminou" << '\n';
}

