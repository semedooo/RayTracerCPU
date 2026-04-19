// Proteção contra inclusão múltipla
#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include "Vec3.h"
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

void save_ppm(const string& filename, int width, int height, const vector<Vec3>& pixels) {
    ofstream ofs(filename, ios::out | ios::binary);
    ofs << "P3\n" << width << " " << height << "\n255\n";
    for (const auto& pixel : pixels) {
        double rx = std::clamp(pixel.x, 0.0, 1.0);
        double gx = std::clamp(pixel.y, 0.0, 1.0);
        double bx = std::clamp(pixel.z, 0.0, 1.0);

        // Basic gamma correction (gamma = 2.0) keeps gradients and 3D shading perceptually correct.
        rx = std::sqrt(rx);
        gx = std::sqrt(gx);
        bx = std::sqrt(bx);

        int r = static_cast<int>(255.99 * std::clamp(rx, 0.0, 0.999));
        int g = static_cast<int>(255.99 * std::clamp(gx, 0.0, 0.999));
        int b = static_cast<int>(255.99 * std::clamp(bx, 0.0, 0.999));
        ofs << r << " " << g << " " << b << "\n";
    }
}

#endif // IMAGE_H