#pragma once

#include "../../include/aabb.hpp"
#include "../../include/constante.hpp"
#include <memory>
#include <vector>

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    shared_ptr<material> mat_ptr;
    double u, v;

    inline void set_face_normal(const ray &r, const vec3 &outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
  public:
    virtual bool hit(const ray &r, double t_min, double t_max,
                     hit_record &rec) const = 0;

    virtual bool bounding_box(double time0, double time1,
                              aabb &output_box) const = 0;
};

class translate : public hittable {
  public:
    translate(shared_ptr<hittable> p, const vec3 &displacement)
        : ptr(p), offset(displacement) {}

    virtual bool hit(const ray &r, double t_min, double t_max,
                     hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1,
                              aabb &output_box) const override;

  public:
    shared_ptr<hittable> ptr;
    vec3 offset;
};

class rotate_y : public hittable {
  public:
    rotate_y(shared_ptr<hittable> p, double angle);

    virtual bool hit(const ray &r, double t_min, double t_max,
                     hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1,
                              aabb &output_box) const override {
        output_box = bbox;
        return hasbox;
    }

  public:
    shared_ptr<hittable> ptr;
    double sin_theta;
    double cos_theta;
    bool hasbox;
    aabb bbox;
};

inline rotate_y::rotate_y(shared_ptr<hittable> p, double angle) : ptr(p) {
    auto radians{degrees_to_radians(angle)};
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasbox = ptr->bounding_box(0, 1, bbox);

    point3 min(infinity, infinity, infinity);
    point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x{i * bbox.max().x() + (1 - i) * bbox.min().x()};
                auto y{j * bbox.max().y() + (1 - j) * bbox.min().y()};
                auto z{k * bbox.max().z() + (1 - k) * bbox.min().z()};

                auto newx{cos_theta * x + sin_theta * z};
                auto newz{-sin_theta * x + cos_theta * z};

                vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = aabb(min, max);
}
