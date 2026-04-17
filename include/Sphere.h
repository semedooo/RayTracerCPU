
// Proteção contra inclusão múltipla
#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "Vec3.h"
#include "Ray.h"

class Sphere {
public:
    Vec3 center;
    float radius;

    Sphere() : center(0, 0, 0), radius(1.0f) {}

    Sphere(const Vec3& center, float radius) : center(center), radius(radius) {}

    float getRadius() const {
        return radius;
    }

    Vec3 getCenter() const {
        return center;
    }

    bool hit(const Ray& ray, float tmin, float tmax, Vec3& hit_point) const {
        Vec3 oc = ray.origin - center;
        double a = ray.direction.dot(ray.direction);
        double half_b = oc.dot(ray.direction);
        double c = oc.dot(oc) - radius * radius;
        double discriminant = half_b * half_b - a * c;

        if (discriminant < 0) {
            return false;
        }

        double sqrt_disc = std::sqrt(discriminant);
        double root = (-half_b - sqrt_disc) / a;
        if (root < tmin || root > tmax) {
            root = (-half_b + sqrt_disc) / a;
            if (root < tmin || root > tmax) {
                return false;
            }
        }

        hit_point = ray.at(root);
        return true;
    }

};

#endif // SPHERE_H