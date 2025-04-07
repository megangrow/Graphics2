#include "aabb.h"
#include "constants.h"
#include "ray.h"

AABB::AABB(const Point3D &minimum, const Point3D &maximum)
    :minimum{minimum}, maximum{maximum} {
    // increase the box size by an Epsilon
    this->minimum.x -= Constants::epsilon;
    this->minimum.y -= Constants::epsilon;
    this->minimum.z -= Constants::epsilon;

    this->maximum.x += Constants::epsilon;
    this->maximum.y += Constants::epsilon;
    this->maximum.z += Constants::epsilon;
}

bool AABB::intersect(const Ray& ray) const {
    double d = 1.0 / ray.direction.x;
    double tmin = (minimum.x - ray.origin.x) * d;
    double tmax = (maximum.x - ray.origin.x) * d;
    if (d < 0.0) {
        std::swap(tmin, tmax);
    }
    d = 1.0 / ray.direction.y;
    double t0 = (minimum.y - ray.origin.y) * d;
    double t1 = (maximum.y - ray.origin.y) * d;
    if (d < 0.0) {
        std::swap(t0, t1);
    }
    // reduce overlap range
    tmin = t0 > tmin ? t0 : tmin;
    tmax = t1 < tmax ? t1 : tmax;
    if (tmax <= tmin) {
        return false;
    }

    d = 1.0 / ray.direction.z;
    t0 = (minimum.z - ray.origin.z) * d;
    t1 = (maximum.z - ray.origin.z) * d;
    if (d < 0.0) {
        std::swap(t0, t1);
    }
    tmin = t0 > tmin ? t0 : tmin;
    tmax = t1 < tmax ? t1 : tmax;
    if (tmax <= tmin) {
        return false;
    }
    return true;
}

AABB AABB::surrounding_box(const AABB &box0, const AABB &box1) {
    Point3D small{std::min(box0.minimum.x, box1.minimum.x),
                  std::min(box0.minimum.y, box1.minimum.y),
                  std::min(box0.minimum.z, box1.minimum.z)};
    Point3D big{std::max(box0.maximum.x, box1.maximum.x),
                  std::max(box0.maximum.y, box1.maximum.y),
                  std::max(box0.maximum.z, box1.maximum.z)};
    return AABB{small, big}; // applies the epsilon
}