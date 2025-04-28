// Axis-Aligned Bounding Boxes
#pragma once
#include "point3d.h"
class Ray;

class AABB {
public:
    AABB(const Point3D& minimum, const Point3D& maximum);
    bool intersect(const Ray& ray) const;
    Point3D minimum, maximum;
};

AABB surrounding_box(const AABB& box0, const AABB& box1);