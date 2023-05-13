#pragma once

#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>

// Constants
const double infinity{std::numeric_limits<double>::infinity()};
const double pi{3.1415926535897932385};

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double clamp(double x, double min, double max) {
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}

// Using
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Header

#include "ray.hpp"
#include "vec3.hpp"
