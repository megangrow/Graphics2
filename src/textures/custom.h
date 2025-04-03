#pragma once
#include "texture.h"

class Custom : public Texture {
public:
    Custom(Color a, Color b);
    Color value(double u, double v) const;

private:
    Color a, b;
};