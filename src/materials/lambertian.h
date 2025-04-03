#pragma once

#include "material.h"

class Lambertian : public Material {
public:
    Lambertian(const Texture *texture, bool emitting);

    Ray scatter(const Ray& ray, const Hit& hit) const override;

};
