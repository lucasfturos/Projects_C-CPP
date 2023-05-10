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
hittable_list Render::random_scene() {
    // World
    hittable_list world;

    material_lambertian = make_shared<lambertian>(color(.5, .5, .5));
    world.add(
        make_shared<sphere>(point3(0, -100, -1), 100, material_lambertian));

    for (int a = -2; a < 2; a++) {
        for (int b = -2; b < 2; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2,
                          b + 0.9 * random_double());

            if ((center - point3(4, .0, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    return world;
}

hittable_list Render::single_scene() {
    // Texture
    auto checker{make_shared<checker_texture>(color(0.2, 0.3, 0.1),
                                              color(0.9, 0.9, 0.9))};
    auto pertext{make_shared<noise_texture>(4)};

    // Material
    material_metal = make_shared<metal>(color(.8, .8, .8), .0);
    material_lambertian_checker = make_shared<lambertian>(checker);
    material_lambertian_pertext = make_shared<lambertian>(pertext);
    material_dieletric = make_shared<dielectric>(1.5);
    // World
    hittable_list world;
    // Chão
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100,
                                  material_lambertian_checker));
    // Objeto no centro
    world.add(make_shared<sphere>(point3(.0, .0, -1.0), .5,
                                  material_lambertian_pertext));
    // Objeto a esquerda
    world.add(make_shared<sphere>(point3(-1.0, .0, -1.0), .5, material_metal));
    // Objeto a direita
    // world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5,
    // material_metal));

    return world;
}

void Render::run() {
    // Camera
    // point3 lookfrom(13, 2, 3);
    point3 lookfrom(0, 0, 1); // visão de frente
    // point3 lookfrom(3, 3, 2); // Visão da diagonal
    // Visão do observador
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    // const double dist_to_focus{(lookfrom - lookat).length()};
    const double dist_to_focus{100.0};
    cam = make_shared<camera>(lookfrom, lookat, vup, vfov, aspect_ratio);

    // World
    // auto world{random_scene()};
    auto world{single_scene()};

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
