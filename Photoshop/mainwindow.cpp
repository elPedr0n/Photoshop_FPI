#include "config.h"

bool copia = false, carregou = false;
int tons_original = 255, tons_copia = 255;
vector<vector<double>> filter(3, vector<double>(3, 0));

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
        tons_copia = 255;
        ui->imagem_copia->setStyleSheet("border: 2px solid #FFFF00;");
        ui->imagem_original->setStyleSheet("");
        ui->imagem_copia->setAlignment(Qt::AlignCenter);
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
        tons_original = 255;
        ui->imagem_original->setStyleSheet("border: 2px solid #FFFF00;");
        ui->imagem_copia->setStyleSheet("");
        ui->imagem_original->setAlignment(Qt::AlignCenter);

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
        // image = grayscale(image);
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
        ui->imagem_original->setPixmap(QPixmap::fromImage(quantization(n, image, &tons_original)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        image = grayscale(image);
        ui->imagem_copia->setPixmap(QPixmap::fromImage(quantization(n, image, &tons_copia)));
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


void MainWindow::on_negativo_clicked()
{
    ui->msg_erro->setText("");
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(negativo(image)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(negativo(image)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_zoom_in_clicked()
{
    ui->msg_erro->setText("");
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(zoom_in(image)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(zoom_in(image)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_RCCW_clicked()
{
    ui->msg_erro->setText("");
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(rotate90CCW(image)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(rotate90CCW(image)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_RCW_clicked()
{
    ui->msg_erro->setText("");
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(rotate90CW(image)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(rotate90CW(image)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_mudar_brilho_clicked()
{
    ui->msg_erro->setText("");
    int n = ui->n_brilho->value();
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(muda_brilho(image, n)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(muda_brilho(image, n)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_mudar_contraste_clicked()
{
    ui->msg_erro->setText("");
    double n = ui->n_contraste->value();
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(muda_contraste(image, n)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(muda_contraste(image, n)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_equaliza_hist_clicked()
{
    ui->msg_erro->setText("");
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(equalizacao_colorida(image)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(equalizacao_colorida(image)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}


void MainWindow::on_hist_matching_clicked()
{
    ui->msg_erro->setText("");
    QPixmap tmp = ui->imagem_original->pixmap();
    QImage image1 = tmp.toImage();
    tmp = ui->imagem_copia->pixmap();
    QImage image2 = tmp.toImage();
    ui->imagem_original->setPixmap(QPixmap::fromImage(matching_histograma(grayscale(image1), grayscale(image2))));

}


void MainWindow::on_zoom_out_clicked()
{
    ui->msg_erro->setText("");
    int sy = ui->Sy->value(), sx = ui->Sx->value();
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(zoom_out(image, sx, sy)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(equalizacao_colorida(image)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }
}





void MainWindow::on_convoluir_clicked()
{
    if (!copia && carregou) {
        QPixmap tmp = ui->imagem_original->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_original->setPixmap(QPixmap::fromImage(convolution(image, filter, false)));
    } else if (carregou) {
        QPixmap tmp = ui->imagem_copia->pixmap();
        QImage image = tmp.toImage();
        ui->imagem_copia->setPixmap(QPixmap::fromImage(convolution(image, filter, false)));
    } else {
        ui->msg_erro->setText("Nenhuma imagem foi carregada!!");
    }


}


void MainWindow::on_gauss_clicked()
{
    filter[0][0] = 0.0625;
    filter[0][1] = 0.125;
    filter[0][2] = 0.0625;
    filter[1][0] = 0.125;
    filter[1][1] = 0.25;
    filter[1][2] = 0.125;
    filter[2][0] = 0.0625;
    filter[2][1] = 0.125;
    filter[2][2] = 0.0625;

    ui->a00->setValue(0.0625);
    ui->a01->setValue(0.125);
    ui->a02->setValue(0.0625);
    ui->a10->setValue(0.125);
    ui->a11->setValue(0.25);
    ui->a12->setValue(0.125);
    ui->a20->setValue(0.0625);
    ui->a21->setValue(0.125);
    ui->a22->setValue(0.0625);
}


void MainWindow::on_Laplace_clicked()
{
    filter[0][0] = 0;
    filter[0][1] = -1;
    filter[0][2] = 0;
    filter[1][0] = -1;
    filter[1][1] = 4;
    filter[1][2] = -1;
    filter[2][0] = 0;
    filter[2][1] = -1;
    filter[2][2] = 0;

    ui->a00->setValue(0.0);
    ui->a01->setValue(-1);
    ui->a02->setValue(0.0);
    ui->a10->setValue(-1);
    ui->a11->setValue(4);
    ui->a12->setValue(-1);
    ui->a20->setValue(0.0);
    ui->a21->setValue(-1);
    ui->a22->setValue(0.0);
}


void MainWindow::on_PAG_clicked()
{
    filter[0][0] = -1;
    filter[0][1] = -1;
    filter[0][2] = -1;
    filter[1][0] = -1;
    filter[1][1] = 8;
    filter[1][2] = -1;
    filter[2][0] = -1;
    filter[2][1] = -1;
    filter[2][2] = -1;

    ui->a00->setValue(-1);
    ui->a01->setValue(-1);
    ui->a02->setValue(-1);
    ui->a10->setValue(-1);
    ui->a11->setValue(8);
    ui->a12->setValue(-1);
    ui->a20->setValue(-1);
    ui->a21->setValue(-1);
    ui->a22->setValue(-1);
}


void MainWindow::on_PHx_clicked()
{
    filter[0][0] = -1;
    filter[0][1] = 0;
    filter[0][2] = 1;
    filter[1][0] = -1;
    filter[1][1] = 0;
    filter[1][2] = 1;
    filter[2][0] = -1;
    filter[2][1] = 0;
    filter[2][2] = 1;

    ui->a00->setValue(-1);
    ui->a01->setValue(0);
    ui->a02->setValue(1);
    ui->a10->setValue(-1);
    ui->a11->setValue(0);
    ui->a12->setValue(1);
    ui->a20->setValue(-1);
    ui->a21->setValue(0);
    ui->a22->setValue(1);
}


void MainWindow::on_PHy_clicked()
{
    filter[0][0] = -1;
    filter[0][1] = -1;
    filter[0][2] = -1;
    filter[1][0] = 0;
    filter[1][1] = 0;
    filter[1][2] = 0;
    filter[2][0] = 1;
    filter[2][1] = 1;
    filter[2][2] = 1;

    ui->a00->setValue(-1);
    ui->a01->setValue(-1);
    ui->a02->setValue(-1);
    ui->a10->setValue(0);
    ui->a11->setValue(0);
    ui->a12->setValue(0);
    ui->a20->setValue(1);
    ui->a21->setValue(1);
    ui->a22->setValue(1);
}


void MainWindow::on_SHx_clicked()
{
    filter[0][0] = -1;
    filter[0][1] = 0;
    filter[0][2] = 1;
    filter[1][0] = -2;
    filter[1][1] = 0;
    filter[1][2] = 2;
    filter[2][0] = -1;
    filter[2][1] = 0;
    filter[2][2] = 1;

    ui->a00->setValue(-1);
    ui->a01->setValue(0);
    ui->a02->setValue(1);
    ui->a10->setValue(-2);
    ui->a11->setValue(0);
    ui->a12->setValue(2);
    ui->a20->setValue(-1);
    ui->a21->setValue(0);
    ui->a22->setValue(1);
}


void MainWindow::on_XHy_clicked()
{
    filter[0][0] = -1;
    filter[0][1] = -2;
    filter[0][2] = -1;
    filter[1][0] = 0;
    filter[1][1] = 0;
    filter[1][2] = 0;
    filter[2][0] = 1;
    filter[2][1] = 2;
    filter[2][2] = 1;

    ui->a00->setValue(-1);
    ui->a01->setValue(-1);
    ui->a02->setValue(-1);
    ui->a10->setValue(0);
    ui->a11->setValue(0);
    ui->a12->setValue(0);
    ui->a20->setValue(1);
    ui->a21->setValue(1);
    ui->a22->setValue(1);
}

