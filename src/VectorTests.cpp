#include <iostream>
#include "VectorTests.h"
#include "InputUtils.h"
#include "Vec3.h"

void runVectorBinaryTest(int op) {
    Vec3 a = readVec("Vector A (x y z): ");
    Vec3 b = readVec("Vector B (x y z): ");

    if (op == 1) {
        printVec("A + B = ", a + b);
    } else if (op == 2) {
        printVec("A - B = ", a - b);
    } else if (op == 3) {
        printVec("A * B = ", a * b);
    } else if (op == 4) {
        if (b.x == 0 || b.y == 0 || b.z == 0) {
            std::cout << "Error: division by zero!" << std::endl;
        } else {
            printVec("A / B = ", a / b);
        }
    } else if (op == 5) {
        std::cout << "A . B = " << a.dot(b) << std::endl;
    } else if (op == 6) {
        printVec("A x B = ", a.cross(b));
    }
}

void runVectorUnaryTest(int op) {
    Vec3 v = readVec("Vector (x y z): ");

    if (op == 7) {
        std::cout << "Length = " << v.length() << std::endl;
    } else {
        printVec("Normalized = ", v.normalized());
    }
}
