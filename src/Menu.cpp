#include <iostream>
#include "Menu.h"

void printMenu() {
    std::cout << "=== RayTracerCPU - Interactive Tests ===" << std::endl;
    std::cout << "\n--- Basic Presets (Non-Reflective) ---" << std::endl;
    std::cout << "1. Render Centered Sphere" << std::endl;
    std::cout << "2. Render Ground Plane" << std::endl;
    std::cout << "3. Render Three Spheres" << std::endl;
    std::cout << "4. Render Sphere and Plane" << std::endl;
    std::cout << "5. Render Custom Scene" << std::endl;
    std::cout << "\n--- Reflection Showcase ---" << std::endl;
    std::cout << "6. Reflective Sphere (30%)" << std::endl;
    std::cout << "7. Reflective Sphere (80%)" << std::endl;
    std::cout << "8. Two Spheres Reflecting" << std::endl;
    std::cout << "\n0. Exit" << std::endl;
    std::cout << "Choose option: ";
}

void printLightMenu() {
    std::cout << "=== Light Position ===" << std::endl;
    std::cout << "1. Default" << std::endl;
    std::cout << "2. Top" << std::endl;
    std::cout << "3. Left" << std::endl;
    std::cout << "4. Right" << std::endl;
    std::cout << "5. Back" << std::endl;
    std::cout << "Choose option: ";
}

void printAddObjectsMenu() {
    std::cout << "=== Custom Scene Objects ===" << std::endl;
    std::cout << "1. Left Sphere" << std::endl;
    std::cout << "2. Close Sphere (near camera)" << std::endl;
    std::cout << "3. Right Sphere" << std::endl;
    std::cout << "4. Distant Sphere" << std::endl;
    std::cout << "5. Ground Plane" << std::endl;
    std::cout << "6. Inclined Plane" << std::endl;
    std::cout << "7. Background Plane" << std::endl;
    std::cout << "8. Left Vertical Plane" << std::endl;
    std::cout << "9. Add Sphere Manually" << std::endl;
    std::cout << "10. Add Plane Manually" << std::endl;
    std::cout << "0. Render Scene" << std::endl;
    std::cout << "Choose option: ";
}
