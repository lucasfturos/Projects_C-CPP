#include "MiniNavegador/mininavegador.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
    auto a = std::make_shared<QApplication>(argc, argv);
    auto w = std::make_shared<MiniNavegador>();
    w->show();
    return a->exec();
}
