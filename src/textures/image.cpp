#include "image.h"

Image::Image(const std::string &filename)
    :filename{filename}, pixels{filename} {}

Color Image::value(double u, double v) const {
    int x = static_cast<int>(u * (pixels.columns - 1));
    int y = static_cast<int>(v * (pixels.rows - 1));
    return pixels(y, x);
}