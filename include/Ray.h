// Proteção contra inclusão múltipla
#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
public:
    Vec3 origin; // Origin of the ray
    double t; // Time parameter
    Vec3 direction; // Direction of the ray

    Ray(): origin(0, 0, 0), t(0), direction() {}
    Ray(const Vec3& origin, double t, const Vec3& direction): origin(origin), t(t), direction(direction) {}

    void set(const Vec3& origin, double t, const Vec3& direction) {
        this->origin = origin;
        this->t = t;
        this->direction = direction;
    }

    Vec3 at(double t) const {
        return Vec3(
            origin.getX() + t * direction.x,
            origin.getY() + t * direction.y,
            origin.getZ() + t * direction.z
        );
    }

};

#endif // RAY_H