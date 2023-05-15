#include "render.hpp"

void Render::run() {
    // Color
    color_ptr = make_shared<Color>();

    // Camera
    // point3 lookfrom(26, 3, 6);
    // point3 lookfrom(13, 2, 3);
    point3 lookfrom(0, 0, 1); // visão de frente
    //  point3 lookfrom(3, 3, 2); // Visão da diagonal
    //  Visão do observador
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    color background(0, 0, 0);
    background = color(0.7, 0.7, 0.7);

    cam = make_shared<camera>(lookfrom, lookat, vup, vfov, aspect_ratio);

    // World
    // auto world{random_scene()};
    auto world{single_scene()};
    // auto world{solar_scene()};
    //  auto world{simple_light()};

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

void Render::run_term() {
    // Color
    color_ptr = make_shared<Color>();

    // Camera
    point3 lookfrom(0, 0, 1); // visão de frente
    point3 lookat(0, 0, 0);   //  Visão do observador
    vec3 vup(0, 1, 0);
    color background(0, 0, 0); // Background do céu
    background = color(0.7, 0.7, 0.7);

    cam = make_shared<camera>(lookfrom, lookat, vup, vfov, aspect_ratio);

    // World
   // auto world{random_scene()};
    auto world{single_scene()};
    // auto world{solar_scene()};
    //  auto world{simple_light()}; 

    // Renderização
    for (auto j{image_height - 1}; j >= 0; --j) {
        for (auto i{0}; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (auto s{0}; s < samples_per_pixel; ++s) {
                auto u{(i + random_double()) / (image_width - 1)};
                auto v{(j + random_double()) / (image_height - 1)};

                ray r{cam->get_ray(u, v)};
                pixel_color += ray_color(r, background, world, max_depth);
            }
            color_ptr->run_color(std::cout, pixel_color, samples_per_pixel);
        }
        std::cout << "\e[0m" << '\n';
    }
}
