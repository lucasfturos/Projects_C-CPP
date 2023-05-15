#include "render.hpp"

hittable_list Render::single_scene() {
    hittable_list world;
    // Texture
    auto checker{make_shared<checker_texture>(color(0.2, 0.3, 0.1),
                                              color(0.9, 0.9, 0.9))};
    auto pertext{make_shared<noise_texture>(4)};

    // Material
    difflight = make_shared<diffuse_light>(color(4, 4, 4));
    material_metal = make_shared<metal>(color(.8, .8, .8), .0);
    material_lambertian = make_shared<lambertian>(color(1.0, .0, .0));
    material_lambertian_checker = make_shared<lambertian>(checker);
    material_lambertian_pertext = make_shared<lambertian>(pertext);
    material_dieletric = make_shared<dielectric>(1.5);

    // Chão
    world.add(
        make_shared<sphere>(point3(0, -100.5, -1), 100, material_lambertian));
    // Objeto no centro
    world.add(make_shared<sphere>(point3(.0, .0, -1), .5, material_metal));
    // Objeto a esquerda
    // world.add(make_shared<sphere>(point3(-1.0, .0, -1.0), .5, difflight));
    // Objeto a direita
    // world.add(make_shared<sphere>(point3(1.0, .0, -1.0), .5, difflight));
    // Objeto em cima do centro
    world.add(make_shared<sphere>(point3(.0, 1.2, -1), .5, difflight));

    return world;
}
