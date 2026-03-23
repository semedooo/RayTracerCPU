#ifndef VEC3_H
#define VEC3_H

#include <cmath>

class  Vec3 {
public:
    double x, y, z;

    Vec3(): x(0), y(0), z(0) {}
    Vec3(double x, double y, double z): x(x), y(y), z(z) {}

    void set(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3 operator+(const Vec3& other) const {
        Vec3 result;
        result.x = this->x + other.x;
        result.y = this->y + other.y;
        result.z = this->z + other.z;
        return result;
    }

    Vec3 operator-(const Vec3& other) const {
        Vec3 result;
        result.x = this->x - other.x;
        result.y = this->y - other.y;
        result.z = this->z - other.z;
        return result;
    }

    Vec3 operator*(const Vec3& other) const {
        Vec3 result;
        result.x = this->x * other.x;
        result.y = this->y * other.y;
        result.z = this->z * other.z;
        return result;
    }

    Vec3 operator*(double scalar) const {
        Vec3 result;
        result.x = this->x * scalar;
        result.y = this->y * scalar;
        result.z = this->z * scalar;
        return result;
    }

    Vec3 operator/(const Vec3& other) const {
        Vec3 result;
        result.x = this->x / other.x;
        result.y = this->y / other.y;
        result.z = this->z / other.z;
        return result;
    }

    Vec3 cross(const Vec3& other) const {
        Vec3 result;
        result.x = this->y * other.z - this->z * other.y;
        result.y = this->z * other.x - this->x * other.z;
        result.z = this->x * other.y - this->y * other.x;
        return result;
    }

    double dot(const Vec3& other) const {
        double result;
        result = this->x * other.x +
                    this->y * other.y +
                    this->z * other.z;
        return result;
    }

    double length() const {
        double result;
        result = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        return result;
    }

    Vec3 normalized() const {
        Vec3 result;
        double len = this->length();
        if (len > 0) {
            result.x = this->x / len;
            result.y = this->y / len;
            result.z = this->z / len;
        } else {
            result.x = 0;
            result.y = 0;
            result.z = 0;
        }
        return result;
    }


};

inline Vec3 operator*(double t, const Vec3& v) {
    return v * t;
}

#endif // VEC3_H
