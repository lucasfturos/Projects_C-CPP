#pragma once

#include "../../../Engine/include/camera.hpp"
#include "../../../Engine/include/constante.hpp"
#include "../../../Engine/include/material.hpp"
#include "../../../Engine/include/perlin.hpp"
#include "../../../Engine/include/ray.hpp"
#include "../../../Engine/include/vec3.hpp"
#include "../../../Engine/src/Color/color.hpp"
#include "../../../Engine/src/HitTable/hittable_list.hpp"
#include "../../../Engine/src/Rect/rect.hpp"
#include "../../../Engine/src/Sphere/sphere.hpp"
#include "../../../Engine/src/Texture/texture.hpp"

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
    const double vfov{20.0};

    // Color
    color ray_color(const ray &r, const color &background,
                    const hittable &world, int depth);

    // Material
    shared_ptr<metal> material_metal;
    shared_ptr<lambertian> material_lambertian;
    shared_ptr<lambertian> material_lambertian_checker;
    shared_ptr<lambertian> material_lambertian_pertext;
    shared_ptr<dielectric> material_dieletric;

    // Esferas
    hittable_list random_scene();
    hittable_list single_scene();
    hittable_list solar_scene();
    hittable_list simple_light();

  public:
    void run();
};
