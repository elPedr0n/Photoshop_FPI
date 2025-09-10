#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "config.h"

QImage grayscale(QImage image);

QImage horizontal_flip(QImage image);

QImage vertical_flip(QImage image);

QImage quantization(int n, QImage image);

#endif // FUNCTIONS_H
