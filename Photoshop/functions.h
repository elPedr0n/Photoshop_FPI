#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "config.h"

QImage grayscale(QImage image);

QImage horizontal_flip(QImage image);

QImage vertical_flip(QImage image);

QImage quantization(int n, QImage image, int *tons);

bool saveFile(QString name, QImage image);

QImage rotate90CW(QImage image);

QImage rotate90CCW(QImage image);

QImage negativo(QImage image);

vector<float> monta_histograma_gray(QImage image);

vector<vector<float>> monta_histograma_colorido(QImage image);

QImage muda_brilho(QImage image, int n);

QImage equalizacao_cinza(QImage image);

#endif // FUNCTIONS_H
