#pragma once

#include "vector3d.h"
#include "point3d.h"

class Object;

class Hit {
public:
    Hit(double time, const Point3D& position, const Vector3D& normal,
        const Object* object);
    
    double time;
    Point3D position; 
    Vector3D normal;

    const Object* object;
};

// operator<<
