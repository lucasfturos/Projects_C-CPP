#pragma once

#include "../../../Engine/include/vec3.hpp"
#include "../../../Engine/src/HitTable/hittable.hpp"

class sphere : public hittable {
  public:
    sphere() {}
    sphere(point3 cen, double r, shared_ptr<material> m)
        : center(cen), radius(r), mat_ptr(m){};

    virtual bool hit(const ray &r, double t_min, double t_max,
                     hit_record &rec) const override;

  private:
    static void get_sphere_uv(const point3 &p, double &u, double &v) {
        // p: a given point on the sphere of radius one, centered at the origin.
        // u: returned value [0,1] of angle around the Y axis from X=-1.
        // v: returned value [0,1] of angle from Y=-1 to Y=+1.
        //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
        //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
        //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

        auto theta = acos(-p.y());
        auto phi = atan2(-p.z(), p.x()) + pi;

        u = phi / (2 * pi);
        v = theta / pi;
    }

  public:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;
};
