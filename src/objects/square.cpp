#include <cmath>
#include "square.h"
#include "triangle.h"
#include "hit.h"
#include "ray.h"
#include "aabb.h"

Square::Square(const Point3D& vertex0, const Vector3D& horizontal,
               const Vector3D& vertical, const Material* material)
    : Object{material}, vertex0{vertex0}, vertex1{vertex0 + horizontal},
    vertex2{vertex0+horizontal+vertical}, vertex3{vertex0+vertical},
    horizontal{horizontal}, vertical{vertical},
    t1{vertex0, vertex2, vertex3, material},
    t2{vertex0, vertex2, vertex1, material} {}

std::optional<double> Square::intersect(const Ray &ray) const {
    auto first = t1.intersect(ray);
    auto second = t2.intersect(ray);
    if (first && second) {
        if (*first < *second) {
            return first;
        } else {
            return second;
        }
    }
    else if (first) {
        return first;
    }
    else {
        return second;
    }
}

Hit Square::construct_hit(const Ray &ray, double time) const {
    Point3D point = ray.at(time);
    Vector3D normal = unit(cross(horizontal, vertical));
    // ensure that the ray and surface normals are pointing in opposite directions
    bool negative = std::signbit(dot(ray.direction, normal));
    if (negative) {
        return Hit{time, point, normal, this};
    }
    else {
        return Hit{time, point, -normal, this};
    }
}

std::pair<double, double> Square::uv(const Hit &hit) const {
    Vector3D P = hit.position - vertex0;
    double u = dot(P, horizontal) / length(horizontal);
    double v = dot(P, vertical) / length(vertical);
    double magnitude = (u+v) / 2.0;
    return {u/magnitude, v/magnitude};
}

AABB Square::bounding_box() const {

}