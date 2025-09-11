#include "config.h"

int tons = 255;

QImage grayscale(QImage image) {

    int altura = image.height(), largura = image.width();

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {
            QColor pixel = image.pixelColor(x, y);
            int valor =  0.299 * pixel.red() + 0.587 * pixel.green() + 0.114 * pixel.blue();
            image.setPixelColor(x, y, qRgb(valor, valor, valor));
        }
    }

    return image;
}

QImage horizontal_flip(QImage image) {

    int altura = image.height(), largura = image.width();


    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < (largura / 2); ++x) {

            QColor first = image.pixelColor(x, y), second = image.pixelColor((largura - 1 - x), y);
            image.setPixel(largura - 1 - x, y, qRgb(first.red(), first.green(), first.blue()));
            image.setPixel(x, y, qRgb(second.red(), second.green(), second.blue()));
        }
    }

    return image;
}

QImage vertical_flip(QImage image) {

    int altura = image.height(), largura = image.width();


    for (int x = 0; x < largura; ++x) {
        for (int y = 0; y < (altura / 2); ++y) {

            QColor first = image.pixelColor(x, y), second = image.pixelColor(x, altura - 1 - y);
            image.setPixel(x,altura - 1 - y, qRgb(first.red(), first.green(), first.blue()));
            image.setPixel(x, y, qRgb(second.red(), second.green(), second.blue()));
        }
    }

    return image;
}

QImage quantization(int n, QImage image) {

    int altura = image.height(), largura = image.width();
    int min = 100000, max = -1;


    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {

            QColor valor = image.pixelColor(x, y);
            if (valor.red() < min) min = valor.red();
            else if (valor.red() > max) max = valor.red();
        }
    }

    int tam_int = max - 1 - min;
    if (n < tam_int && n < tons) {

        int tam_tom = tam_int / n;

        for (int y = 0; y < altura; ++y) {
            for (int x = 0; x < largura; ++x) {

                int novo = floor(image.pixelColor(x, y).red() / (float)tam_tom) * tam_tom + 0.5;
                image.setPixelColor(x, y, qRgb(novo, novo, novo));

            }
        }

    }

    tons = n;

    return image;
}

bool saveFile(QString name, QImage image) {

    QString path = "/Users/pedro/Documents/UFRGS/Semestre_4/FPI/Photoshop_FPI/images/" + name + ".jpg";

    bool success = image.save(path);

    return success;
}












