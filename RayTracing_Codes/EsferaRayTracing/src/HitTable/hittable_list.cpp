#include "hittable_list.hpp"

bool hittable_list::hit(const ray &r, double t_min, double t_max,
                        hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything{false};
    auto closet_so_far{t_max};

    for (const auto &object : objects) {
        if (object->hit(r, t_min, closet_so_far, temp_rec)) {
            hit_anything = true;
            closet_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
