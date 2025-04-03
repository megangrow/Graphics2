#pragma once
#include "texture.h"
#include "../image/pixels.h"

class Checkerboard : public Texture {
public:
    Checkerboard(Color a, Color b);
    Color value(double u, double v) const;

private:
    Color a;
    Color b;
};