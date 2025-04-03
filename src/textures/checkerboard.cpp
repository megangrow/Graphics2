#include "checkerboard.h"
#include "color.h"

Checkerboard::Checkerboard(Color a, Color b)
    :a{a}, b{b} {}

Color Checkerboard::value(double u, double v) const {
    if ((static_cast<int>(u*12)+static_cast<int>(v*6))%2 == 0) {
        return a;
    }
    else {
        return b;
    }

}