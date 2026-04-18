#ifndef PLANE_H
#define PLANE_H

#include <cmath>
#include "Hittable.h"

class Plane : public Hittable {
public:
    Vec3 point; // A point on the plane
    Vec3 normal; // Normal vector of the plane

    Plane() : point(0, 0, 0), normal(0, 1, 0) {}
    Plane(const Vec3& point, const Vec3& normal) : point(point), normal(normal.normalized()) {}

    bool hit(const Ray& ray, float t_min, float t_max, HitRecord &record) const override {
        float denom = normal.dot(ray.direction);
        if (std::abs(denom) > 1e-6) { // Avoid division by zero
            float t = (point - ray.origin).dot(normal) / denom;
            if (t >= t_min && t <= t_max) {
                record.point = ray.at(t);
                record.normal = normal;
                record.t = t;
                record.material = Material(); // Default material, can be customized
                return true;
            }
        }
        return false;
    }
};

#endif // PLANE_H