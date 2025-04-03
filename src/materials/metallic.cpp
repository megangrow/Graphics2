#include "metallic.h"
#include "ray.h"
#include "hit.h"
#include "random.h"

Metallic::Metallic(const Texture *texture, bool emitting, double fuzz)
    :Material{texture, emitting}, fuzz{fuzz} {}

Ray Metallic::scatter(const Ray& ray, const Hit& hit) const {
    Vector3D scattered = unit(reflect(ray.direction, hit.normal) + fuzz*random_unit_vector());
    return Ray{hit.position, scattered};
}
