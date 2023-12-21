QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    src/OpenGLWindow/openglwindow.cpp \
    src/main.cpp \
    src/Cubo/cubo.cpp

HEADERS += \
    src/Cubo/cubo.hpp \
    src/Cubo/setupCubo.hpp \
    src/OpenGLWindow/openglwindow.hpp

RESOURCES += \
    res/resources.qrc

QMAKE_CXXFLAGS += \
    -Wall -Wextra -Wpedantic -Werror -pedantic -g -O2

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
