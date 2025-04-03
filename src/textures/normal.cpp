#include "normal.h"


Normal::Normal(){}

Color Normal::value(double u, double v) const {
    return Color{u, v, (u-v)};
}