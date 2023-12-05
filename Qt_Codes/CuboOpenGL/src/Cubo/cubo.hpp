#ifndef CUBO_HPP
#define CUBO_HPP

#include <QVector>
#include <src/OpenGLWindow/openglwindow.hpp>

class Cubo : public OpenGLWindow {
  public:
    using OpenGLWindow::OpenGLWindow;
    ~Cubo();

    void initialize() override;
    void render() override;

  private:
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    QOpenGLShaderProgram *m_program = nullptr;
    qfloat16 m_frame = 0.f;

  private:
    const char *vertexShaderSource = R"(
    attribute vec3 position;
    attribute vec3 color;
    varying vec3 fragColor;
    uniform mat4 matrix;

    void main() {
        gl_Position = matrix * vec4(position, 1.0);
        fragColor = color;
    }
    )";

    const char *fragmentShaderSource = R"(
    varying lowp vec3 fragColor;

    void main() {
        gl_FragColor = vec4(fragColor, 1.0);
    }
    )";

    const QVector<GLfloat> vertices = {
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

    const QVector<GLuint> indices = {// Top
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
};

#endif // CUBO_HPP
