#pragma once

#include <cassert>
#include <cmath>
#include <limits>
#include <vector>

template <typename T> class Point {
  public:
    T x, y, z;

    Point();
    Point(T x_, T y_, T z_);

  public:
    Point operator-() const { return Point(-x, -y, -z); }

    T operator[](int i) const {
        assert(i >= 0 && i < 3);
        return (&x)[i];
    }

    T &operator[](int i) {
        assert(i >= 0 && i < 3);
        return (&x)[i];
    }

    Point &operator+=(const Point &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Point &operator*=(const T t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Point &operator/=(const T t) { return *this *= 1 / t; }

  public:
    void rotateX(T theta);
    void rotateY(T theta);
    void rotateZ(T theta);

    T getProjection(T distance, T xy, T offSet, T offSetZ);
};

template class Point<int>;
template class Point<double>;

using point3i = Point<int>;
using point3d = Point<double>;

struct ObjectSource {
    std::vector<int> indices;
    std::vector<point3d> vertices;
};

constexpr double eps = std::numeric_limits<double>::epsilon();
