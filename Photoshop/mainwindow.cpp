#include "config.h"

bool copia = false, carregou = false;

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
    ui->msg_erro->setText("");
    QPixmap tmp = ui->imagem_original->pixmap();

    if (!tmp.isNull()) {
        ui->imagem_copia->setPixmap(tmp);
        copia = true;
        ui->imagem_copia->setStyleSheet("border: 2px solid #FFFF00;");
        ui->imagem_original->setStyleSheet("");
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
        carregou = true;
        copia = false;
        ui->imagem_original->setStyleSheet("border: 2px solid #FFFF00;");
        ui->imagem_copia->setStyleSheet("");

    }

}


void MainWindow::on_grayscale_clicked()
{
    ui->msg_erro->setText("");
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(grayscale(image)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(grayscale(image)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_h_flip_clicked()
{
    ui->msg_erro->setText("");
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(horizontal_flip(image)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(horizontal_flip(image)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_v_flip_clicked()
{
    ui->msg_erro->setText("");
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(vertical_flip(image)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(vertical_flip(image)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_quantize_clicked()
{
    ui->msg_erro->setText("");
    int n = ui->shades->value();
    if (!n) {
        ui->msg_erro->setText("Não é possível quantizar com 0 tons!!");
        return;
    }
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        image = grayscale(image);
        ui->imagem_original->setPixmap(QPixmap::fromImage(quantization(n, image)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        image = grayscale(image);
        ui->imagem_copia->setPixmap(QPixmap::fromImage(quantization(n, image)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_save_image_clicked()
{
    ui->msg_erro->setText("");
    QString name = ui->save_name->text();
    QImage image;
    bool succ;

    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        image = tmp.toImage();
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        image = tmp.toImage();
    } else {
        ui->msg_erro->setText("Não foi possível salvar pois não temos uma imagem aberta");
        return;
    }

    if (name.length() == 0) {
        name = "image";
        succ = saveFile(name, image);

        if (!succ) {
            ui->msg_erro->setText("Não foi possível salvar!");
        } else {
            ui->msg_erro->setText("Imagem image.jpg salva com sucesso!");
        }
    } else {
        succ = saveFile(name, image);

        if (!succ) {
            ui->msg_erro->setText("Não foi possível salvar!");
        } else {
            ui->msg_erro->setText("Imagem salva com sucesso!");
        }
    }
}

