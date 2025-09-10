#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QPixmap& imagem, QWidget *parent = nullptr);

    void mudarImagem(const QPixmap& novaImagem);

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_copy_clicked();

    void on_load_image_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
