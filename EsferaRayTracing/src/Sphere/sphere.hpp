#pragma once

#include "../HitTable/hittable.hpp"
#include "../Vector3D/vec3.hpp"

class sphere : public hittable {
  public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r){};

    virtual bool hit(const ray &r, double t_min, double t_max,
                     hit_record &rec) const override;

  public:
    point3 center;
    double radius;
};
