#ifndef HITTABLE_H
#define HITTABLE_H
#include "Ray.h"
#include "Vec3.h"
#include "Material.h"

struct HitRecord {
    Vec3 point;
    Vec3 normal;
    float t;
    Material material;
};

class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord &record) const = 0;
};

#endif // HITTABLE_H