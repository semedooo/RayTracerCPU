// Proteção contra inclusão múltipla
#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Ray.h"


class Camera {
public:
    Vec3 origin;
    float viewport_width;
    float viewport_height;
    float focal_length;

    Camera() : origin(0, 0, 0), viewport_width(16.0f), viewport_height(9.0f), focal_length(1.0f) {}

    Camera(const Vec3& origin, float viewport_width, float viewport_height, float focal_length)
        : origin(origin), viewport_width(viewport_width), viewport_height(viewport_height), focal_length(focal_length) {}


    void setViewport(float width, float height) {
        this->viewport_width = width;
        this->viewport_height = height;
    }

    void setFocalLength(float focal_length) {
        this->focal_length = focal_length;
    }

    void setOrigin(const Vec3& origin) {
        this->origin = origin;
    }

    Ray getRay(float u, float v) const {
        Vec3 horizontal(viewport_width, 0, 0);
        Vec3 vertical(0, viewport_height, 0);
        Vec3 lower_left_corner = origin - (horizontal / 2.0) - (vertical / 2.0) - Vec3(0, 0, focal_length);
        Vec3 direction = lower_left_corner + u * horizontal + v * vertical - origin;
        return Ray(origin, 0, direction.normalized());
    }

};

#endif // CAMERA_H