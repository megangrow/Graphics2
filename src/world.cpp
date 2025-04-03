#include "world.h"

#include "constants.h"
#include "object.h"

void World::add(std::unique_ptr<Object>&& object) {
    objects.push_back(std::move(object));
}

std::optional<Hit> World::find_nearest(const Ray& ray) const {
    double time = Constants::infinity;
    Object* nearest = nullptr;
    for (const auto& object : objects) {
        std::optional<double> t = object->intersect(ray);
        if (t.has_value() && t.value() < time) {
            nearest = object.get();
            time = t.value();
        }
    }
    if (nearest) {
        Hit hit = nearest->construct_hit(ray, time);
        return hit;
    }
    else {
        return {};
    }
}
