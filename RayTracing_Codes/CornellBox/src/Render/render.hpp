#pragma once

#include "../../../Engine/include/camera.hpp"
#include "../../../Engine/include/constante.hpp"
#include "../../../Engine/include/material.hpp"
#include "../../../Engine/include/perlin.hpp"
#include "../../../Engine/include/ray.hpp"
#include "../../../Engine/include/texture.hpp"
#include "../../../Engine/include/vec3.hpp"
#include "../../../Engine/src/Color/color.hpp"
#include "../../../Engine/src/HitTable/hittable_list.hpp"
#include "../../../Engine/src/Rect/rect.hpp"
#include "../../../Engine/src/Sphere/sphere.hpp"

class Render {
  private:
    // Imagem
    // const double aspect_ratio{3.0 / 2.0}; // Proporção 3:2
    const double aspect_ratio{16.0 / 9.0}; // Proporção 16:9
    const int image_width{400};
    const int image_height{static_cast<int>(image_width / aspect_ratio)};
    const int samples_per_pixel{100};
    const int max_depth{50};

    // Camera
    shared_ptr<camera> cam;
    const double aperture{2.0};
    const double vfov{10.0};

    // Color
    color ray_color(const ray &r, const color &background,
                    const hittable &world, int depth);

    // Material
    shared_ptr<lambertian> red;
    shared_ptr<lambertian> white;
    shared_ptr<lambertian> green;
    shared_ptr<diffuse_light> light;

    // Caixa de Cornell
    hittable_list cornell_box();

  public:
    void run();
};
