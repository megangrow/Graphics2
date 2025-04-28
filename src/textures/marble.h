#pragma once

#include "texture.h"

class Marble : public Texture {
public:
    Color value(double u, double v) const override;
};