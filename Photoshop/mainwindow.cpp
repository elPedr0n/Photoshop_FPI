#include "config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(const QPixmap& imagem, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mudarImagem(imagem);
}

// Implementação do método para mudar a imagem
void MainWindow::mudarImagem(const QPixmap& novaImagem)
{
    // Acessa o QLabel e define a nova imagem
    ui->imagem_original->setPixmap(novaImagem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_copy_clicked()
{
    QPixmap tmp = ui->imagem_original->pixmap();

    if (!tmp.isNull()) {
        ui->imagem_copia->setPixmap(tmp);
    }

}


void MainWindow::on_load_image_clicked()
{
    QString name = PATH + ui->file_name->text() + ".jpg";

    QImage image(name);

    if (image.isNull()) {
        ui->msg_erro->setText("Não foi possível carregar a imagem");
    } else {
        ui->msg_erro->setText("");
        mudarImagem(QPixmap::fromImage(image));
    }

}

