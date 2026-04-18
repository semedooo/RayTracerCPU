#ifndef LIGHT_H
#define LIGHT_H

#include "Vec3.h"


class Light {
public:
    Vec3 position;
    Vec3 intensity;

    Light() : position(5, 5, -2), intensity(1, 1, 1) {}
    Light(const Vec3& position, const Vec3& intensity) : position(position), intensity(intensity) {}
};

#endif // LIGHT_H