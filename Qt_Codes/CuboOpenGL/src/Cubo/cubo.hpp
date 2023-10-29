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
        -1.0f, -1.0f, -1.0f, 1.0f, 0.0f,  0.0f,  1.0f, -1.0f, -1.0f, 0.0f,
        1.0f,  0.0f,  1.0f,  1.0f, -1.0f, 0.0f,  0.0f, 1.0f,  -1.0f, 1.0f,
        -1.0f, 1.0f,  1.0f,  0.0f, -1.0f, -1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
        1.0f,  -1.0f, 1.0f,  0.0f, 1.0f,  0.0f,  1.0f, 1.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  -1.0f, 1.0f, 1.0f,  1.0f,  1.0f, 0.0f,
    };

    const QVector<GLuint> indices = {
        0, 1, 2, 0, 2, 3, // Face frontal
        4, 5, 6, 4, 6, 7, // Face traseira
        0, 3, 7, 0, 7, 4, // Lado esquerdo
        1, 2, 6, 1, 6, 5, // Lado direito
        3, 2, 6, 3, 6, 7, // Topo
        0, 1, 5, 0, 5, 4  // Base
    };
};

#endif // CUBO_HPP
