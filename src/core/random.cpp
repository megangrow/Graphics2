#include "random.h"
#include <random>
#include "xorshiftrplus.h"

double random_double() {
    static thread_local std::random_device rd;
    static thread_local Xorshiftrplus xorshiftrplus{rd()};
    return xorshiftrplus.random_double();
}

double random_double(double min, double max) {
    return (max - min) * random_double() + min;
}
    
Vector3D random_unit_vector() {
    while (true) {
        double x = random_double(-1, 1);
        double y = random_double(-1, 1);
        double z = random_double(-1, 1);
        double length_squared = x*x + y*y + z*z;
        if (1e-160 < length_squared && length_squared <= 1) {
            Vector3D v{x, y, z};
            return v / std::sqrt(length_squared);
        }
    }
}


Vector3D random_hemisphere(const Vector3D& normal) {
    Vector3D v = random_unit_vector();
    if (dot(v, normal) > 0) {
        return v;
    }
    else {
        return -v;
    }
}
