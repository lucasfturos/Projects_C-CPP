#include "render.hpp"

hittable_list Render::cornell_box() {
    hittable_list objects;

    // Cores e luz
    red = make_shared<lambertian>(color(.65, .05, .05));
    white = make_shared<lambertian>(color(.73, .73, .73));
    green = make_shared<lambertian>(color(.12, .45, .15));
    light = make_shared<diffuse_light>(color(7, 7, 7));
    metal_tex = make_shared<metal>(color(.8, .8, .8), .0);

    // Paredes e lampada
    objects.add(make_shared<yz_rect>(0, 277.5, 0, 277.5, 277.5, green));
    objects.add(make_shared<yz_rect>(0, 277.5, 0, 277.5, 0, red));
    objects.add(make_shared<xz_rect>(56.5, 221.5, 63.5, 216, 277, light));
    objects.add(make_shared<xz_rect>(0, 277.5, 0, 277.5, 0, white));
    objects.add(make_shared<xz_rect>(0, 277.5, 0, 277.5, 277.5, white));
    objects.add(make_shared<xy_rect>(0, 277.5, 0, 277.5, 277.5, white));

    // Caixas
    box1 =
        make_shared<box>(point3(0, 0, 0), point3(82.5, 165, 82.5), metal_tex);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(132.5, 0, 147.5));
    objects.add(box1);

    box2 =
        make_shared<box>(point3(0, 0, 0), point3(82.5, 82.5, 82.5), metal_tex);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(65, 0, 32.5));
    objects.add(box2);

    return objects;
}
