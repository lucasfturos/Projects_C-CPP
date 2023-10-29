#include "Cubo/cubo.hpp"
#include <QGuiApplication>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(60);

    Cubo window;
    window.setFormat(format);

    QScreen *screen = QGuiApplication::primaryScreen();
    int screenWidth = screen->geometry().width();
    int screenHeight = screen->geometry().height();

    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    window.setGeometry(x, y, windowWidth, windowHeight);
    window.show();
    window.setAnimating(true);

    return app.exec();
}
