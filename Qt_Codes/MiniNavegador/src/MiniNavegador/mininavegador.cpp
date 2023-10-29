#include "mininavegador.hpp"
#include "ui_mininavegador.h"

MiniNavegador::MiniNavegador(QWidget *parent)
    : QMainWindow(parent), ui(std::make_shared<Ui::MiniNavegador>()) {
    ui->setupUi(this);
    this->setWindowTitle("Mini Navegador");
    move(screen()->geometry().center() - frameGeometry().center());

    view = std::make_shared<QWebEngineView>();
    ui->textBrowser->close();
    ui->gridLayout->addWidget((view.get()));
}

void MiniNavegador::on_pushButton_clicked() {
    QString url = ui->lineEdit->text();
    view->load(QUrl("https://" + url));
}
