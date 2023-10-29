#ifndef MININAVEGADOR_HPP
#define MININAVEGADOR_HPP

#include <QScreen>
#include <QMainWindow>
#include <QWebEngineView>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MiniNavegador;
}
QT_END_NAMESPACE

class MiniNavegador : public QMainWindow {
    Q_OBJECT

  public:
    MiniNavegador(QWidget *parent = nullptr);

  private slots:
    void on_pushButton_clicked();

  private:
    std::shared_ptr<QWebEngineView> view;
    std::shared_ptr<Ui::MiniNavegador> ui;
};

#endif // MININAVEGADOR_HPP
