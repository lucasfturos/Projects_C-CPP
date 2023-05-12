#include "hittable.hpp"

bool translate::hit(const ray &r, double t_min, double t_max,
                    hit_record &rec) const {
    ray moved_r(r.origin() - offset, r.direction(), r.time());
    if (!ptr->hit(moved_r, t_min, t_max, rec))
        return false;

    rec.p += offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}

bool translate::bounding_box(double time0, double time1,
                             aabb &output_box) const {
    if (!ptr->bounding_box(time0, time1, output_box)) {
        return false;
    }

    output_box = aabb(output_box.min() + offset, output_box.max() + offset);

    return true;
}

bool rotate_y::hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const {
    auto origin{r.origin()};
    auto direction{r.direction()};

    origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
    origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

    direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
    direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

    ray rotated_r(origin, direction, r.time());

    if (!ptr->hit(rotated_r, t_min, t_max, rec)) {
        return false;
    }

    auto p{rec.p};
    auto normal{rec.normal};

    p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
    p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

    normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.p = p;
    rec.set_face_normal(rotated_r, normal);

    return true;
}
