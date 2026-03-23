// Proteção contra inclusão múltipla
#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include "Vec3.h"
#include <fstream>
using namespace std;

void save_ppm(const string& filename, int width, int height, const vector<Vec3>& pixels) {
    ofstream ofs(filename, ios::out | ios::binary);
    ofs << "P3\n" << width << " " << height << "\n255\n";
    for (const auto& pixel : pixels) {
        int r = (int)(255.99 * pixel.x);
        int g = (int)(255.99 * pixel.y);
        int b = (int)(255.99 * pixel.z);
        ofs << r << " " << g << " " << b << "\n";
    }
}

#endif // IMAGE_H