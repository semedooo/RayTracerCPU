#include <iostream>
#include <limits>
#include <string>
#include "InputUtils.h"

Vec3 readVec(const std::string& prompt) {
    double x, y, z;
    std::cout << prompt;
    std::cin >> x >> y >> z;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Error: invalid input!" << std::endl;
        return Vec3(0, 0, 0);
    }

    return Vec3(x, y, z);
}

float readFloat(const std::string& prompt) {
    float value;
    std::cout << prompt;
    std::cin >> value;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Error: invalid input!" << std::endl;
        return 0.0f;
    }

    return value;
}

void printVec(const std::string& label, const Vec3& v) {
    std::cout << label << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}
