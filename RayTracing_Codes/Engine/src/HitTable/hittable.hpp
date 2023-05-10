#pragma once

#include "../../include/aabb.hpp"
#include "../../include/ray.hpp"
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

inline bool translate::hit(const ray &r, double t_min, double t_max,
                           hit_record &rec) const {
    ray moved_r(r.origin() - offset, r.direction(), r.time());
    if (!ptr->hit(moved_r, t_min, t_max, rec))
        return false;

    rec.p += offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}

inline bool translate::bounding_box(double time0, double time1,
                             aabb &output_box) const {
    if (!ptr->bounding_box(time0, time1, output_box))
        return false;

    output_box = aabb(output_box.min() + offset, output_box.max() + offset);

    return true;
}
