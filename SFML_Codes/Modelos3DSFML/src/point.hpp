#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class Point {
  public:
    float x, y, z;
    Point() {}
    Point(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    ~Point() {}

    void rotateX(float theta) {
        float y_ = y;
        y = (y_ * cosf(theta)) + (z * sinf(theta) * -1.f);
        z = (y_ * sinf(theta)) + (z * cosf(theta));
    }

    void rotateY(float theta) {
        float x_ = x;
        x = x_ * cosf(theta) + z * sinf(theta) * -1.f;
        z = x_ * sinf(theta) + z * cosf(theta);
    }

    void rotateZ(float theta) {
        float x_ = x;
        x = (x_ * cosf(theta)) + (z * sinf(theta) * -1.f);
        y = (x_ * sinf(theta)) + (z * cosf(theta));
    }

    float getProjection(float distance, float xy, float offSet, float offSetZ) {
        return (distance * xy) / (z - offSetZ) + offSet;
    }

    sf::CircleShape drawCircle(float x_, float y_, float size,
                               sf::Color color) {
        sf::CircleShape circle(size);
        circle.setFillColor(color);
        circle.setPosition(x_ - circle.getRadius(), y_ - circle.getRadius());
        return circle;
    }

    sf::RectangleShape drawRect(float x_, float y_, float size,
                                sf::Color color) {
        sf::RectangleShape rectangle(sf::Vector2f(size, size));
        rectangle.setFillColor(color);
        rectangle.setPosition(x_ - size / 2, y_ - size / 2);
        return rectangle;
    }
};
