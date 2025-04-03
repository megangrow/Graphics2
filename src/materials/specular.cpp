#include "specular.h"
#include "ray.h"
#include "hit.h"

Specular::Specular(const Texture *texture, bool emitting)
    :Material{texture, emitting} {}

Ray Specular::scatter(const Ray& ray, const Hit& hit) const {
    Vector3D reflected = reflect(ray.direction, hit.normal);
    return Ray{hit.position, reflected};
}

