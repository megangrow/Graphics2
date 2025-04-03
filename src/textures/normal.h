#pragma once
#include "texture.h"
#include "../image/pixels.h"

class Normal : public Texture {
public:
    Normal();
    Color value(double u, double v) const;
};