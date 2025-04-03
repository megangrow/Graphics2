#pragma once
#include "texture.h"
#include "../image/pixels.h"

class Solid : public Texture {
public:
    Solid(Color color);
    Color value(double u, double v) const;

private:
    Color color;
};