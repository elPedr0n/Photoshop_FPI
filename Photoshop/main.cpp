#include "config.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);


    // Caminho da imagem (certifique-se de que a imagem está no mesmo diretório do seu executável)
    // ou use um caminho absoluto.
    // QString imagePath = "/Users/pedro/Documents/UFRGS/Semestre_4/FPI/Photoshop_FPI/images/mikudayo.jpg"; // Substitua pelo caminho real

    // Cria um objeto QImage e tenta carregar a imagem
    // QImage image(imagePath);

    // image = grayscale(image);

    // saveFile("saving", image);

    // Verifica se a imagem foi carregada com sucesso

    // // Exibe a janela

    MainWindow w;

    w.show();

    return a.exec();

    // return a.exec();
}
