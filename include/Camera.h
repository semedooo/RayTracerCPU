#include "Vec3.h"
#include "Point.h"
#include "Ray.h"
#include "Image.h"
#include <iostream>


class Camera {
public:
    P3 origin;
    float viewport_width;
    float viewport_height;
    float focal_length;

    Camera() : origin(0, 0, 0), viewport_width(16.0f), viewport_height(9.0f), focal_length(1.0f) {}

    Camera(const P3& origin, float viewport_width, float viewport_height, float focal_length)
        : origin(origin), viewport_width(viewport_width), viewport_height(viewport_height), focal_length(focal_length) {}


    void setViewport(float width, float height) {
        this->viewport_width = width;
        this->viewport_height = height;
    }

    void setFocalLength(float focal_length) {
        this->focal_length = focal_length;
    }

    void setOrigin(const P3& origin) {
        this->origin = origin;
    }

    Ray getRay(float u, float v) const {
        Vec3 direction = Vec3(u, v, -focal_length) - Vec3(origin.getX(), origin.getY(), origin.getZ());
        return Ray(origin, 0, direction.normalized());
    }

};