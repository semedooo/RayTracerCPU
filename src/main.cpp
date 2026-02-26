#include <iostream>
#include <unistd.h>
#include <vector>
#include "Image.h"

using namespace std;

void printVec(const string& label, const Vec3& v) {
    cout << label << "(" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
}

Vec3 readVec(const string& prompt) {
    double x, y, z;
    cout << prompt;
    cin >> x >> y >> z;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: invalid input!" << endl;
        return Vec3(0, 0, 0);
    }
    return Vec3(x, y, z);
}

void printMenu() {
    cout << "=== Ray Tracer CPU - Tests ===" << endl;
    cout << "1. Sum (+)" << endl;
    cout << "2. Subtraction (-)" << endl;
    cout << "3. Multiplication (*)" << endl;
    cout << "4. Division (/)" << endl;
    cout << "5. Dot Product (dot)" << endl;
    cout << "6. Cross Product (cross)" << endl;
    cout << "7. Length (length)" << endl;
    cout << "8. Normalize (normalized)" << endl;
    cout << "9. Generate test PPM image" << endl;
    cout << "0. Exit" << endl;
    cout << "Operation: ";
}

int main() {
    int op;
    op = -1;

    while (op!=0) {
        printMenu();
        cin >> op;

        if (cin.fail()) {
            cout << "Error: invalid input!" << endl;
            return 1;
        }

        switch (op) {
            case 1: case 2: case 3: case 4: case 5: case 6: {
                // Two vector operations
                Vec3 a = readVec("Vector A (x y z): ");
                Vec3 b = readVec("Vector B (x y z): ");

                if (op == 1) printVec("A + B = ", a + b);
                else if (op == 2) printVec("A - B = ", a - b);
                else if (op == 3) printVec("A * B = ", a * b);
                else if (op == 4) {
                    if (b.x == 0 || b.y == 0 || b.z == 0) {
                        cout << "Error: division by zero!" << endl;
                    } else {
                        printVec("A / B = ", a / b);
                    }
                }
                else if (op == 5) cout << "A . B = " << a.dot(b) << endl;
                else if (op == 6) printVec("A x B = ", a.cross(b));
                break;
            }
            case 7: case 8: {
                // One vector operations
                Vec3 v = readVec("Vector (x y z): ");

                if (op == 7) cout << "Length = " << v.length() << endl;
                else printVec("Normalized = ", v.normalized());
                break;
            }
            case 9: {
                // Generate test PPM image
                int width = 400, height = 225;
                vector<Vec3> pixels(width * height);

                for (int j = 0; j < height; j++) {
                    for (int i = 0; i < width; i++) {
                        double r = double(i) / (width - 1);
                        double g = double(height - 1 - j) / (height - 1);
                        double b = 0.25;
                        pixels[j * width + i] = Vec3(r, g, b);
                    }
                }

                save_ppm("output/test.ppm", width, height, pixels);
                cout << "Image saved to output/test.ppm" << endl;
                break;
            }
            case 0:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Error: invalid operation!" << endl;
                break;
        }
        if (op != 0) {
            sleep(1);
            cin.ignore(10000, '\n'); // limpa o \n residual do cin >> op
            cout << "Press Enter to continue...";
            cin.get();
            cout << endl;
        }
    }

    return 0;
}