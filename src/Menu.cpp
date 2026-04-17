#include <iostream>
#include "Menu.h"

void printMenu() {
    std::cout << "=== RayTracerCPU - Interactive Tests ===" << std::endl;
    std::cout << "-- Vec3 Operations --" << std::endl;
    std::cout << "1. Vector Add (+)" << std::endl;
    std::cout << "2. Vector Subtract (-)" << std::endl;
    std::cout << "3. Vector Multiply (component-wise)" << std::endl;
    std::cout << "4. Vector Divide (component-wise)" << std::endl;
    std::cout << "5. Dot Product" << std::endl;
    std::cout << "6. Cross Product" << std::endl;
    std::cout << "7. Vector Length" << std::endl;
    std::cout << "8. Normalize Vector" << std::endl;
    std::cout << "-- Rendering --" << std::endl;
    std::cout << "9. Render Gradient Test (PPM)" << std::endl;
    std::cout << "10. Render Sky Color From Camera Rays" << std::endl;
    std::cout << "11. Render Sphere Intersection Test" << std::endl;
    std::cout << "12. Render Multiple Objects Test" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choose option: ";
}

void printObjectsMenu() {
    std::cout << "=== Multiple Objects Render Test ===" << std::endl;
    std::cout << "Choose an object to add to the scene:" << std::endl;
    std::cout << "1. Sphere" << std::endl;
    std::cout << "2. Plane" << std::endl;
    std::cout << "0. Finish and render" << std::endl;
    std::cout << "Choose option: ";
}
