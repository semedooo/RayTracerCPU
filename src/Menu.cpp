#include <iostream>
#include "Menu.h"

void printMenu() {
    std::cout << "=== RayTracerCPU - Interactive Tests ===" << std::endl;
    std::cout << "1. Render Centered Sphere" << std::endl;
    std::cout << "2. Render Ground Plane" << std::endl;
    std::cout << "3. Render Three Spheres" << std::endl;
    std::cout << "4. Render Sphere and Plane" << std::endl;
    std::cout << "5. Render Custom Scene" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choose option: ";
}

void printObjectsMenu() {
    std::cout << "=== Custom Scene Setup ===" << std::endl;
    std::cout << "Choose an object to add to the scene:" << std::endl;
    std::cout << "1. Sphere" << std::endl;
    std::cout << "2. Plane" << std::endl;
    std::cout << "0. Finish and render" << std::endl;
    std::cout << "Choose option: ";
}
