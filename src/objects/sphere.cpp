#include "sphere.h"
#include "ray.h"
#include "constants.h"
#include "aabb.h"
#include <cmath>

Sphere::Sphere(const Point3D& center, double radius, const Material* material)
    :Object{material}, center{center}, radius{radius} {}

AABB Sphere::bounding_box() const {
    Point3D R{radius, radius, radius};
    return AABB{center - R, center + R};
}

std::optional<double> Sphere::intersect(const Ray& ray) const {
    Vector3D OC = center - ray.origin;
    double R = dot(ray.direction, OC);
    double h2 = radius*radius - dot(OC, OC) + R*R;
    if (h2 < 0) {
	return {};
    }

    double h = std::sqrt(h2);

    // time = R +/- h
    if ((R-h) > Constants::epsilon) {
	// ray intersects from outside sphere -> R-h is closer to ray origin
	// if time is positive and futher away than Epsilon
	return R-h;
    }
    else if ((R+h) > Constants::epsilon) {
	// ray intersections from inside sphere -> R+h is in the direction of the ray
	// time is positive and further away than Epsilon
	return R+h;
    }
    else {
	return {};
    }
}

std::optional<double> Sphere::intersect2(const Ray& ray) const {
    Vector3D OC = center - ray.origin;
    double R = dot(ray.direction, OC);
    double q2 = dot(OC, OC) - R*R;
    double q = std::sqrt(q2);
    if (q - Constants::epsilon > radius) { // outside sphere = miss
        return {};
    }

    if (std::abs(q - radius) < Constants::epsilon) { // on sphere boundary = one hit
        return R;
    }

    double h = std::sqrt(radius*radius - q2);    

    // time = R +/- h
    if ((R-h) > Constants::epsilon) {
        // ray intersects from outside sphere -> R-h is closer to ray origin
        // if time is positive and futher away than Epsilon
        return R-h;
    }
    else if ((R+h) > Constants::epsilon) {
        // ray intersections from inside sphere -> R+h is in the direction of the ray
        // time is positive and further away than Epsilon
        return R+h;
    }
    else {
        return {};
    }
}

std::optional<double> Sphere::intersect_algebraic(const Ray& ray) const {
    Vector3D oc = center - ray.origin;
    double a = dot(ray.direction, ray.direction);
    double b = -2*dot(ray.direction, oc);
    double c = dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant < -Constants::epsilon) {
        return {}; // no hit
    }
    else if (discriminant < Constants::epsilon) { // one hit := -eps <= discriminant < eps
        double time = -b / (2*a); // round discriminant to zero
        return time;
    }
    else { // two hits := discriminant >= eps
        double time = (-b - std::sqrt(discriminant)) / (2*a);
        return time;
    }
}

Hit Sphere::construct_hit(const Ray& ray, double time) const {
    // calculate surface normal
    Point3D point = ray.at(time);
    Vector3D normal = (point - center) / radius;
    return Hit{time, point, normal, this};
}

std::pair<double, double> Sphere::uv(const Hit& hit) const {
    double theta = std::acos(hit.normal.z); // [0, pi]
    double phi = std::atan2(hit.normal.y, hit.normal.x); // [-pi, pi]
    double u = 0.5 + phi / (2 * Constants::pi); // [0, 1]
    double v = theta / Constants::pi; // [0, 1]
    return {u, v};
}