#pragma once
#include "texture.h"
#include "../image/pixels.h"

class Gradient : public Texture {
public:
    Gradient(Color a, Color b);
    Color value(double u, double v) const;

private:
    Color a;
    Color b;
};