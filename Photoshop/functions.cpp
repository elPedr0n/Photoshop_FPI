#include "config.h"


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

QImage quantization(int n, QImage image, int *tons) {

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
    if (n < tam_int && n < *tons) {

        int tam_tom = tam_int / n;

        for (int y = 0; y < altura; ++y) {
            for (int x = 0; x < largura; ++x) {

                int novo = floor(image.pixelColor(x, y).red() / (float)tam_tom) * tam_tom + 0.5;
                image.setPixelColor(x, y, qRgb(novo, novo, novo));

            }
        }

    }

    *tons = n;

    return image;
}

bool saveFile(QString name, QImage image) {

    QString path = "/Users/pedro/Documents/UFRGS/Semestre_4/FPI/Photoshop_FPI/images/" + name + ".jpg";

    bool success = image.save(path);

    return success;
}

QImage rotate90CW(QImage image) {

    int altura = image.height(), largura = image.width();
    QImage temp(altura, largura, QImage::Format_ARGB32_Premultiplied);

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {

            QColor t = image.pixelColor(x, y);
            temp.setPixelColor(altura - y - 1, x, t);

        }
    }


    return temp;
}

QImage rotate90CCW(QImage image) {

    int altura = image.height(), largura = image.width();
    QImage temp(altura, largura, QImage::Format_ARGB32_Premultiplied);

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {

            QColor t = image.pixelColor(x, y);
            temp.setPixelColor(y, largura - x - 1, t);

        }
    }

    return temp;
}


QImage negativo(QImage image) {

    int altura = image.height(), largura = image.width();

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {

            QColor t = image.pixelColor(x, y);
            image.setPixel(x, y, qRgb(255 - t.red(), 255 - t.green(), 255 - t.blue()));

        }
    }

    return image;
}

vector<float> monta_histograma_gray(QImage image) {

    vector<float> hist(256, 0);
    int altura = image.height(), largura = image.width();

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {

            QColor t = image.pixelColor(x, y);
            hist[t.red()]++;

        }
    }

    for (int i = 0; i < 256; i++) {
        hist[i] /= altura * largura;
    }

    return hist;

}

vector<vector<float>> monta_histograma_colorido(QImage image) {


    vector<vector<float>> hist(3, vector<float>(256));
    int altura = image.height(), largura = image.width();

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {

            QColor t = image.pixelColor(x, y);
            hist[0][t.red()]++;
            hist[1][t.green()]++;
            hist[2][t.blue()]++;

        }
    }

    for (int i = 0; i < 256; i++) {
        hist[0][i] /= altura * largura;
        hist[1][i] /= altura * largura;
        hist[2][i] /= altura * largura;
    }

    return hist;

}


QImage muda_brilho(QImage image, int n) {


    int altura = image.height(), largura = image.width();

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {

            int nr = 0, ng = 0, nb = 0;
            QColor t = image.pixelColor(x, y);
            nr = t.red() + n;
            ng = t.green() + n;
            nb = t.blue() + n;


            if (nr > 255) nr = 255;
            else if (nr < 0) nr = 0;

            if (ng > 255) ng = 255;
            else if (ng < 0) ng = 0;

            if (nb > 255) nb = 255;
            else if (nb < 0) nb = 0;

            image.setPixelColor(x, y, qRgb(nr, ng, nb));

        }
    }


    return image;
}


QImage muda_contraste(QImage image, float n) { //Falta testar isso aq

    int altura = image.height(), largura = image.width();

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {

            int nr = 0, ng = 0, nb = 0;
            QColor t = image.pixelColor(x, y);
            nr = (int) (t.red() * n);
            ng = (int) (t.green() * n);
            nb = (int) (t.blue() * n);


            if (nr > 255) nr = 255;
            else if (nr < 0) nr = 0;

            if (ng > 255) ng = 255;
            else if (ng < 0) ng = 0;

            if (nb > 255) nb = 255;
            else if (nb < 0) nb = 0;

            image.setPixelColor(x, y, qRgb(nr, ng, nb));

        }
    }


    return image;
}


QImage equalizacao_cinza(QImage image) {

    vector<float> hist(256), hist_cum(256);
    int altura = image.height(), largura = image.width();
    float alpha = 255.0 / (altura * largura);

    // Multiplicando isso aq pq to renormalizando o valor de cada indice

    hist = monta_histograma_gray(image);
    hist_cum[0] = alpha * (hist[0] * altura * largura);

    for (int i = 1; i < 256; i++) {
        hist_cum[i] = hist_cum[i-1] + alpha * (hist[i] * altura * largura);
        // cout << hist_cum[i] << ' ';
    }
    // cout << endl;

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {

            QColor t = image.pixelColor(x, y);
            int valor = hist_cum[t.red()];
            image.setPixelColor(x, y, qRgb(valor, valor, valor));

        }
    }



    return image;
}


QRgb faz_media2(QColor c1, QColor c2) {

    int r, g, b;
    r = (c1.red() + c2.red()) / 2;
    g = (c1.green() + c2.green()) / 2;
    b = (c1.blue() + c2.blue()) / 2;


    return qRgb(r, g, b);

}



QImage zoom_in(QImage image) {

    int altura = image.height(), largura = image.width();
    QImage temp(2 * largura, 2 * altura, QImage::Format_ARGB32_Premultiplied);


    // montando as linhas
    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < 2 * largura; ++x) {

            float src = x / 2.0;

            if (x % 2 == 0) {
                temp.setPixelColor(x, 2*y, image.pixelColor(floor(src), y));
            } else {
                if (ceil(src) >= largura)
                    temp.setPixelColor(x, 2*y, faz_media2(image.pixelColor(floor(src), y), image.pixelColor(largura - 1, y)));
                else
                    temp.setPixelColor(x, 2*y, faz_media2(image.pixelColor(floor(src), y), image.pixelColor(ceil(src), y)));
            }

        }
    }

    // montando as colunas

    for (int x = 0; x < 2 *  largura; ++x) {
        for (int y = 1; y < 2 * altura; y+=2) {

            temp.setPixelColor(x, y, faz_media2(temp.pixelColor(x, y-1), temp.pixelColor(x, min(y+1, 2*altura-1))));

        }
    }

    return temp;
}



