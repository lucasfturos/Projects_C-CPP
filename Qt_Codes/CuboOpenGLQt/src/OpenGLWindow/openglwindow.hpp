#ifndef OPENGLWINDOW_HPP
#define OPENGLWINDOW_HPP

#include <QKeyEvent>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QOpenGLWindow>
#include <QPainter>
#include <QScreen>
#include <QWindow>

const int windowWidth = 800;
const int windowHeight = 600;

class OpenGLWindow : public QWindow, protected QOpenGLFunctions {
    Q_OBJECT
  public:
    explicit OpenGLWindow(QWindow *parent = nullptr);
    ~OpenGLWindow();

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

  public slots:
    void renderLater();
    void renderNow();

  protected:
    bool event(QEvent *event) override;

    void exposeEvent(QExposeEvent *event) override;

  private:
    bool m_animating = false;

    QOpenGLContext *m_context = nullptr;
    QOpenGLPaintDevice *m_device = nullptr;
};

#endif // OPENGLWINDOW_HPP
