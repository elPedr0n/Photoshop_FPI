#include "config.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QLabel imageLabel;

    // Caminho da imagem (certifique-se de que a imagem está no mesmo diretório do seu executável)
    // ou use um caminho absoluto.
    QString imagePath = "/Users/pedro/Documents/UFRGS/Semestre_4/FPI/Photoshop_FPI/images/Gramado_72k.jpg"; // Substitua pelo caminho real

    // Cria um objeto QImage e tenta carregar a imagem
    QImage image(imagePath);

    image = grayscale(image);

    image = quantization(12, image);

    // Verifica se a imagem foi carregada com sucesso
    if (image.isNull()) {
        imageLabel.setText("Erro ao carregar a imagem.");
    } else {
        // Converte o QImage para um QPixmap para exibição no QLabel
        imageLabel.setPixmap(QPixmap::fromImage(image));
    }

    // Exibe a janela
    imageLabel.show();

    return a.exec();
    // MainWindow w;
    // w.show();
    // return a.exec();
}
