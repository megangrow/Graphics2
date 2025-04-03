#include "material.h"

class Specular : public Material {
public:
    Specular(const Texture *texture, bool emitting);
    
    Ray scatter(const Ray& ray, const Hit& hit) const override;
};
