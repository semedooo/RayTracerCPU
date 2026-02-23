#include <iostream>
#include <string>
#include "Vec3.h"

using namespace std;

int main() {
    double x, y, z;
    cout << "Enter your vector components (x y z): ";
    cin >> x >> y >> z;
    cout << "Vector: (" << x << ", " << y << ", " << z << ")" << endl;

    Vec3 vec1(x, y, z);
    cout << "Length of the vector: " << vec1.length() << endl;
    Vec3 normalized = vec1.normalized();
    cout << "Normalized vector: (" << normalized.x << ", " << normalized.y << ", " << normalized.z << ")" << endl;
    return 0;
}