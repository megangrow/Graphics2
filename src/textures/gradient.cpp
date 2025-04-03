#include "gradient.h"

Gradient::Gradient(Color a, Color b)
    :a{a}, b{b} {}

Color Gradient::value(double u, double v) const {
    double c = (u + v) / 2.0;
    return a * (1.0 - c) + b * c;
}