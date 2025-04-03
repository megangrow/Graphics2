#pragma once
#include "color.h"

class Texture {
public:
    virtual ~Texture() = default;
    virtual Color value(double u, double v) const = 0;

    Color color;
};