#pragma once

#include "common.hpp"

class Point {
  public:
    float x, y, z;
    Point() {}
    Point(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    void rotateX(float theta);
    void rotateY(float theta);
    void rotateZ(float theta);
    float getProjection(float distance, float xy, float offSet, float offSetZ);
    sf::CircleShape drawCircle(float x_, float y_, float size, sf::Color color);
    sf::RectangleShape drawRect(float x_, float y_, float size,
                                sf::Color color);
};

inline void Point::rotateX(float theta) {
    float y_ = y;
    y = (y_ * cosf(theta)) + (z * sinf(theta) * -1.f);
    z = (y_ * sinf(theta)) + (z * cosf(theta));
}

inline void Point::rotateY(float theta) {
    float x_ = x;
    x = x_ * cosf(theta) + z * sinf(theta) * -1.f;
    z = x_ * sinf(theta) + z * cosf(theta);
}

inline void Point::rotateZ(float theta) {
    float x_ = x;
    x = (x_ * cosf(theta)) + (z * sinf(theta) * -1.f);
    y = (x_ * sinf(theta)) + (z * cosf(theta));
}

inline float Point::getProjection(float distance, float xy, float offSet,
                                  float offSetZ) {
    return (distance * xy) / (z - offSetZ) + offSet;
}

inline sf::CircleShape Point::drawCircle(float x_, float y_, float size,
                                         sf::Color color) {
    sf::CircleShape circle(size);
    circle.setFillColor(color);
    circle.setPosition(x_ - circle.getRadius(), y_ - circle.getRadius());
    return circle;
}

inline sf::RectangleShape Point::drawRect(float x_, float y_, float size,
                                          sf::Color color) {
    sf::RectangleShape rectangle(sf::Vector2f(size, size));
    rectangle.setFillColor(color);
    rectangle.setPosition(x_ - size / 2, y_ - size / 2);
    return rectangle;
}
