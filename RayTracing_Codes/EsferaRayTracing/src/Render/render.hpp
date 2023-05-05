#pragma once

#include "../Color/color.hpp"
#include "../HitTable/hittable_list.hpp"
#include "../Sphere/sphere.hpp"
#include "../Utills/camera.hpp"
#include "../Utills/constante.hpp"
#include "../Utills/ray.hpp"
#include "../Utills/vec3.hpp"
#include "../Utills/material.hpp"

class Render {
  private:
    // Imagem
    const double aspect_ratio{16.0 / 9.0};
    const int image_width{400};
    const int image_height{static_cast<int>(image_width / aspect_ratio)};
    const int samples_per_pixel{100};
    const int max_depth{50};

    // World
    hittable_list world;

    // Camera
    camera cam;

  public:
    color ray_color(const ray &r, const hittable &world, int depth);
    Render();
};
