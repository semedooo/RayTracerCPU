#ifndef HITTABLE_H
#define HITTABLE_H
#include "Ray.h"
#include "Vec3.h"

class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, float t_min, float t_max, Vec3& hit_point) const = 0;
};

#endif // HITTABLE_H