#include <cmath>
#include "Vec3.h"
#include "Point.h"

class Ray {
public:
    P3 origin; // Origin of the ray
    double t; // Time parameter
    Vec3 direction; // Direction of the ray

    Ray(): origin(0, 0, 0), t(0), direction() {}
    Ray(const P3& origin, double t, const Vec3& direction): origin(origin), t(t), direction(direction) {}

    void set(const P3& origin, double t, const Vec3& direction) {
        this->origin = origin;
        this->t = t;
        this->direction = direction;
    }

    P3 at(double t) const {
        return P3(
            origin.getX() + t * direction.x,
            origin.getY() + t * direction.y,
            origin.getZ() + t * direction.z
        );
    }

};