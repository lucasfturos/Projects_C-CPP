#include "render.hpp"

hittable_list Render::simple_light() {
    hittable_list objects;

    material_metal = make_shared<metal>(color(.8, .8, .8), .0);
    auto pertext{make_shared<noise_texture>(4)};
    objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000,
                                    make_shared<lambertian>(pertext)));
    objects.add(make_shared<sphere>(point3(0, 2, 0), 2,
                                    make_shared<lambertian>(pertext)));

    difflight = make_shared<diffuse_light>(color(4, 4, 4));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));

    return objects;
}

