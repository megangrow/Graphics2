#pragma once
#include "texture.h"
#include "../image/pixels.h"

class Image : public Texture {
public:
    Image(const std::string& filename);
    Color value(double u, double v) const override;
private:
    Pixels pixels;
    const std::string& filename;
};