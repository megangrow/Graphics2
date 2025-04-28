#pragma once
#include "material.h"

class Isotropic : public Material {
public:
    Isotropic(const Texture* texture, bool emitting);
    Ray scatter(const Ray& ray, const Hit& hit) const override;
};