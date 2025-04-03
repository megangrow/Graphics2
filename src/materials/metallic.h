#pragma once

#include "material.h"
#include "color.h"

class Ray;
class Hit;

class Metallic : public Material {
public:
    Metallic(const Texture *texture, bool emitting, double fuzz);

    Ray scatter(const Ray& ray, const Hit& hit) const override;

private:
    double fuzz;
};
