#pragma once

#include "../../../Engine/include/camera.hpp"
#include "../../../Engine/include/perlin.hpp"
#include "../../../Engine/src/BVH/bvh.hpp"
#include "../../../Engine/src/Box/box.hpp"
#include "../../../Engine/src/Color/color.hpp"
#include "../../../Engine/src/Constant_Medium/constant_medium.hpp"
#include "../../../Engine/src/HitTable/hittable_list.hpp"
#include "../../../Engine/src/Sphere/sphere.hpp"
#include "../../../Engine/src/Texture/texture.hpp"

class Render {
  private:
    // Imagem
    // const double aspect_ratio{3.0 / 2.0}; // Proporção 3:2
    const double aspect_ratio{1.0}; // Proporção 1:1
    const int image_width{40}; // Limite da função do run_term é 200 image_width
    const int image_height{static_cast<int>(image_width / aspect_ratio)};
    const int samples_per_pixel{100};
    const int max_depth{50};

    // Camera
    shared_ptr<camera> cam;
    const double aperture{2.0};
    const double vfov{40.0};

    // Color
    shared_ptr<Color> color_ptr;
    color ray_color(const ray &r, const color &background,
                    const hittable &world, int depth);

    // Material
    shared_ptr<hittable> box1;
    shared_ptr<hittable> box2;
    shared_ptr<metal> metal_tex;
    shared_ptr<lambertian> red;
    shared_ptr<lambertian> white;
    shared_ptr<lambertian> green;
    shared_ptr<diffuse_light> light;

    // Caixa de Cornell
    hittable_list cornell_box();
    hittable_list cornell_smoke();

  public:
    void run();
    void run_term();
};
