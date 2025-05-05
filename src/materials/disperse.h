#pragma once
#include "material.h"

class Disperse : public Material {
public:
    Disperse(const Texture *texture, bool emitting);

    Ray scatter(const Ray& ray, const Hit& hit) const override;
    Ray scatter_dispersely(const Ray& ray, const Hit& hit, char channel) const;

    const double ior_r = 1.50;
    const double ior_g = 1.52;
    const double ior_b = 1.55;
};