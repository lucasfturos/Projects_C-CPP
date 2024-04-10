#pragma once

#include <cassert>
#include <cmath>
#include <limits>
#include <vector>

template <typename T> class Vec3 {
  public:
    T x, y, z;

    Vec3();
    Vec3(T x_, T y_, T z_);

  public:
    Vec3 operator-() const { return Vec3(-x, -y, -z); }

    T operator[](int i) const {
        assert(i >= 0 && i < 3);
        return (&x)[i];
    }

    T &operator[](int i) {
        assert(i >= 0 && i < 3);
        return (&x)[i];
    }

    Vec3 &operator+=(const Vec3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3 &operator*=(const T t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec3 &operator/=(const T t) { return *this *= 1 / t; }

  public:
    void rotateX(T theta);
    void rotateY(T theta);
    void rotateZ(T theta);

    T getProjection(T distance, T xy, T offSet, T offSetZ);
};

template class Vec3<int>;
template class Vec3<double>;

using vec3i = Vec3<int>;
using vec3d = Vec3<double>;

using point3i = Vec3<int>;
using point3d = Vec3<double>;

struct ObjectSource {
    std::vector<int> indices;
    std::vector<vec3d> vertices;
};

constexpr double eps = std::numeric_limits<double>::epsilon();
