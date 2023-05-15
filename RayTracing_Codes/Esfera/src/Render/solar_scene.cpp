#include "render.hpp"

hittable_list Render::solar_scene() {
    const char *filename = "earthmap.jpg";
    auto solar_texture{make_shared<image_texture>(filename)};
    auto solar_surface{make_shared<lambertian>(solar_texture)};
    auto globe{make_shared<sphere>(point3(0, 0, 0), 2, solar_surface)};
    return hittable_list(globe);
}
