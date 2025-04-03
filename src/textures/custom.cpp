#include "custom.h"

Custom::Custom(Color a, Color b)
    :a{a}, b{b}{}

Color Custom::value(double u, double v) const {
    if (static_cast<int>(v / 0.1) % 2 == 0) {
        return a;
    }
    else {
        return b;
    }
}