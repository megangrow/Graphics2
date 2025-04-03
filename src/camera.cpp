#include "camera.h"
#include "constants.h"
#include <cmath>

Camera::Camera(Point3D position, Point3D target, Vector3D up, double fov, double aspect)
    : position{position} {
    const Vector3D w {unit(target - position)};
    const Vector3D u {unit(cross(w, up))};
    const Vector3D v {unit(cross(w, u))};

    const double theta = fov * (Constants::pi / 180.0);
    const double width = 2 * std::tan(theta / 2);
    const double height = width / aspect;

    horizontal = u * width; // Should I use 'this->horizontal' instead?
    vertical = v * height;
    upper_left_corner = position + w - (0.5 * (horizontal + vertical));
}

Ray Camera::compute_ray(double s, double t) const {
    Vector3D dir {upper_left_corner - position};
    dir += horizontal * s;
    dir += vertical * t;
    return {position, unit(dir)};
}
