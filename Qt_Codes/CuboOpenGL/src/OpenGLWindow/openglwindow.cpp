#include "openglwindow.hpp"

OpenGLWindow::OpenGLWindow(QWindow *parent) : QWindow(parent) {
    setSurfaceType(QWindow::OpenGLSurface);
}

OpenGLWindow::~OpenGLWindow() {
    if (m_device) {
        delete m_device;
        m_device = nullptr;
    }
}

void OpenGLWindow::render(QPainter *painter) { Q_UNUSED(painter); }

void OpenGLWindow::initialize() {}

void OpenGLWindow::render() {    
    if (!m_device) {
        m_device = new QOpenGLPaintDevice;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size() * devicePixelRatio());
    m_device->setDevicePixelRatio(devicePixelRatio());

    QPainter painter(m_device);
    render(&painter);
}

void OpenGLWindow::renderLater() { requestUpdate(); }

bool OpenGLWindow::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    case QEvent::KeyPress: {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        keyEvent->key() == Qt::Key_Q ? QWindow::close() : 0;
        return true;
    }
    default:
        return QWindow::event(event);
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent *event) {
    Q_UNUSED(event);
    isExposed() ? renderNow() : (void(0));
}

void OpenGLWindow::renderNow() {
    if (!isExposed()) {
        return;
    }

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    m_animating ? renderLater() : (void(0));
}

void OpenGLWindow::setAnimating(bool animating) {
    m_animating = animating;

    animating ? renderLater() : (void(0));
}
