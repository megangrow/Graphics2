#pragma once
#include "object.h"
#include "point3d.h"
#include "triangle.h"

class Square : public Object {
public:
    Square(const Point3D& vertex0, const Vector3D& horizontal, const Vector3D& vertical, const Material* material);
    std::optional<double> intersect(const Ray& ray) const override;
    Hit construct_hit(const Ray& ray, double time) const override;
    std::pair<double, double> uv(const Hit& hit) const override;
private:
    Point3D vertex0, vertex1, vertex2, vertex3;
    Vector3D horizontal, vertical;
    Material* material;
    Triangle t1, t2;
};