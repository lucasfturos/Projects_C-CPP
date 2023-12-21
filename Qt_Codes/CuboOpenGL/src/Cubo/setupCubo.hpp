#ifndef SETUPCUBO_HPP
#define SETUPCUBO_HPP

#include <QVector>
#include <QOpenGLWindow>

static const QVector<GLfloat> vertices = {
    // Top
    -1.0, 1.0, -1.0, 1.0, 0.0, 0.0, -1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0,
    1.0, 1.0, 0.0, 0.0, 1.0, 1.0, -1.0, 1.0, 0.0, 0.0,

    // Left
    -1.0, 1.0, 1.0, 0.0, 1.0, 0.0, -1.0, -1.0, 1.0, 0.0, 1.0, 0.0, -1.0,
    -1.0, -1.0, 0.0, 1.0, 0.0, -1.0, 1.0, -1.0, 0.0, 1.0, 0.0,

    // Right
    1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, -1.0, 1.0, 0.0, 0.0, 1.0, 1.0, -1.0,
    -1.0, 0.0, 0.0, 1.0, 1.0, 1.0, -1.0, 0.0, 0.0, 1.0,

    // Front
    1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, -1.0, 1.0, 0.0, 1.0, 0.0, -1.0, -1.0,
    1.0, 0.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,

    // Back
    1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, -1.0,
    -1.0, -1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, 1.0, 1.0, 1.0,

    // Bottom
    -1.0, -1.0, -1.0, 0.0, 0.5, 1.0, -1.0, -1.0, 1.0, 0.5, 0.5, 1.0, 1.0,
    -1.0, 1.0, 0.5, 0.5, 1.0, 1.0, -1.0, -1.0, 0.5, 0.5, 1.0};

static const QVector<GLuint> indices = {// Top
    0, 1, 2, 0, 2, 3,

    // Left
    5, 4, 6, 6, 4, 7,

    // Right
    8, 9, 10, 8, 10, 11,

    // Front
    13, 12, 14, 15, 14, 12,

    // Back
    16, 17, 18, 16, 18, 19,

    // Bottom
    21, 20, 22, 22, 20, 23};

#endif // SETUPCUBO_HPP
