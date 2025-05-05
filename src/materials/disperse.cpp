#include "disperse.h"
#include "ray.h"
#include "hit.h"
#include "random.h"

Disperse::Disperse(const Texture *texture, bool emitting)
    : Material{texture, emitting} {}


Ray Disperse::scatter(const Ray &ray, const Hit &hit) const { }

Ray Disperse::scatter_dispersely(const Ray &ray, const Hit &hit, char channel) const {
    double n1 = 1.0; // ior of air
    double n2;
    if (channel == 'r') {
        n2 = ior_r;
    }
    else if (channel == 'g') {
        n2 = ior_g;
    }
    else {
        n2 = ior_b;
    }

    Vector3D normal = hit.normal;
    if (dot(ray.direction, hit.normal) > 0) {
        normal *= -1;
        std::swap(n1, n2);
    }

    double cos_theta = -dot(ray.direction, normal);
    double probability = schlick(cos_theta, n1/n2);

    if (random_double() < probability) { // [0, 1) < prob
        Vector3D reflected = reflect(ray.direction, normal);
        return Ray{hit.position, reflected};
    }
    else {
        Vector3D refracted = refract(ray.direction, normal, n1/n2);
        refracted += random_unit_vector() * 0.01;
        return Ray{hit.position, refracted};
    }

}