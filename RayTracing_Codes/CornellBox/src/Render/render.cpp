#include "render.hpp"

color Render::ray_color(const ray &r, const color &background,
                        const hittable &world, int depth) {
    hit_record rec;
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

hittable_list Render::cornell_box() {
    hittable_list objects;

    red = make_shared<lambertian>(color(.65, .05, .05));
    white = make_shared<lambertian>(color(.73, .73, .73));
    green = make_shared<lambertian>(color(.12, .45, .15));
    light = make_shared<diffuse_light>(color(15, 15, 15));

    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    objects.add(
        make_shared<box>(point3(130, 0, 65), point3(295, 165, 230), white));
    objects.add(
        make_shared<box>(point3(265, 0, 295), point3(430, 330, 460), white));
    return objects;
}

void Render::run() {
    // Camera
    //  Visão da sala
    point3 lookfrom(278, 278, -800);
    //  Visão do observador
    point3 lookat(278, 278, 0);
    vec3 vup(0, 1, 0);
    color background(0, 0, 0);
    background = color(0, 0, 0.1);

    // const double dist_to_focus{(lookfrom - lookat).length()};
    const double dist_to_focus{100.0};
    cam = make_shared<camera>(lookfrom, lookat, vup, vfov, aspect_ratio);

    // World
    auto world{cornell_box()};

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
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nTerminou" << '\n';
}
