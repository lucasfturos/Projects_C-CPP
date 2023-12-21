#ifndef CUBO_HPP
#define CUBO_HPP

#include <QDebug>
#include <QVector>
#include <src/Cubo/setupCubo.hpp>
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
};

#endif // CUBO_HPP
