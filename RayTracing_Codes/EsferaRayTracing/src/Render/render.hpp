#pragma once

#include "../Color/color.hpp"
#include "../HitTable/hittable_list.hpp"
#include "../Sphere/sphere.hpp"
#include "../Utills/camera.hpp"
#include "../Utills/constante.hpp"
#include "../Utills/material.hpp"
#include "../Utills/ray.hpp"
#include "../Utills/vec3.hpp"
#include <memory>

class Render {
  private:
    // Imagem
    const double aspect_ratio{3.0 / 2.0};
    const int image_width{400};
    const int image_height{static_cast<int>(image_width / aspect_ratio)};
    const int samples_per_pixel{100};
    const int max_depth{50};

    // Camera
    shared_ptr<camera> cam;
    const double aperture{2.0};
    const double vfov{20.0};

    // Color
    color ray_color(const ray &r, const hittable &world, int depth);

    // Material
    shared_ptr<metal> material_metal;
    shared_ptr<lambertian> material_lambertian;
    shared_ptr<dielectric> material_dieletric;

    // Esferas
    hittable_list random_scene();
    hittable_list single_scene();

  public:
    void run();
};
