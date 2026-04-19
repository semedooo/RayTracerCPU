#include <iostream>
#include <string>

#include "ShowPPM.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " path/to/image.ppm" << std::endl;
        return 1;
    }

    const std::string filename = argv[1];
    if (!showPPMImage(filename)) {
        return 1;
    }

    return 0;
}
