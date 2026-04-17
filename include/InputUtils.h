#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <string>
#include "Vec3.h"

Vec3 readVec(const std::string& prompt);
float readFloat(const std::string& prompt);
void printVec(const std::string& label, const Vec3& v);

#endif // INPUT_UTILS_H
