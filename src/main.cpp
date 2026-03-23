#include <iostream>
#include <unistd.h>
#include <vector>
#include "Image.h"
#include "Vec3.h"
#include "Camera.h"

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

Camera readCameraParameters() {
    float width, height, focal_length;
    cout << "Enter viewport width: ";
    cin >> width;
    cout << "Enter viewport height: ";
    cin >> height;
    cout << "Enter focal length: ";
    cin >> focal_length;

    return Camera(P3(0, 0, 0), width, height, focal_length);
}

Vec3 rayColor(const Ray& r) {
    Vec3 unit_direction = r.direction.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    Vec3 color = (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
    return color;
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
    cout << "10. Ray Color (rayColor)" << endl;
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
            case 1: case 2: case 3: case 4: case 5: case 6:{
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
            case 10: {

                Camera camera = readCameraParameters();
                vector<Vec3> pixels(camera.viewport_width * camera.viewport_height);

                for (int i = 0; i < camera.viewport_height; i++) {
                    for (int j = 0; j < camera.viewport_width; j++) {
                        float u = float(j) / (camera.viewport_width - 1);
                        float v = float(i) / (camera.viewport_height - 1);

                        Ray ray = camera.getRay(u, v);
                        Vec3 color = rayColor(ray);
                        pixels[i * camera.viewport_width + j] = color;
                    }
                }
                save_ppm("output/raytracer.ppm", camera.viewport_width, camera.viewport_height, pixels);
                cout << "Image saved to output/raytracer.ppm" << endl;
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