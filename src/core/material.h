#pragma once

#include "texture.h"

class Hit;
class Ray;

class Material {
public:
    Material(const Texture *texture, bool emitting);

    virtual Ray scatter(const Ray& ray, const Hit& hit) const = 0;
    virtual ~Material() = default;
    
    const Texture* texture;
    bool emitting;
};

Vector3D reflect(const Vector3D& v, const Vector3D& normal);
Vector3D refract(const Vector3D& v, const Vector3D& normal, double index_ratio);
double schlick(double cos_theta, double index_ratio);
