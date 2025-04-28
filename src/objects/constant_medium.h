#pragma once

#include "object.h"

class ConstantMedium : public Object {
public:
    ConstantMedium(Object* boundary, double density, const Material* material);
    ~ConstantMedium() override;

    AABB bounding_box() const;
    std::optional<double> intersect(const Ray& ray) const;
    Hit construct_hit(const Ray& ray, double time) const;
    std::pair<double, double> uv(const Hit& hit) const;

    Object* boundary; // assume ownership
    double density;

};