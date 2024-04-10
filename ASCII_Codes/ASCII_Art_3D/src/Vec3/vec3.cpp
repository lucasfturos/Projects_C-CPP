#include "vec3.hpp"

template <typename T> Vec3<T>::Vec3() : x(0), y(0), z(0) {}

template <typename T> Vec3<T>::Vec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

template <typename T> void Vec3<T>::rotateX(T theta) {
    T tempY = y;
    y = tempY * cos(theta) + z * sin(theta) * -1.0;
    z = tempY * sin(theta) + z * cos(theta);
}

template <typename T> void Vec3<T>::rotateY(T theta) {
    T tempX = x;
    x = tempX * cos(theta) + z * sin(theta) * -1.0;
    z = tempX * sin(theta) + z * cos(theta);
}

template <typename T> void Vec3<T>::rotateZ(T theta) {
    T tempX = x;
    x = tempX * cos(theta) + y * sin(theta) * -1.0;
    y = tempX * sin(theta) + y * cos(theta);
}

template <typename T>
T Vec3<T>::getProjection(T distance, T xy, T offSet, T offSetZ) {
    return (distance * xy) / (z - offSetZ) + offSet;
}