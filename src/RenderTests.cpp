#include <iostream>
#include <vector>
#include "RenderTests.h"
#include "InputUtils.h"
#include "Image.h"
#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include "Hittable.h"
#include "Menu.h"

namespace {
Vec3 rayColor(const Ray& r) {
    Vec3 unit_direction = r.direction.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}

Vec3 sphereRayColor(const Ray& r, const Sphere& sphere) {
    Vec3 hit_point;
    if (sphere.hit(r, 0.001f, 1e30f, hit_point)) {
        Vec3 normal = (hit_point - sphere.center).normalized();
        return 0.5 * (normal + Vec3(1.0, 1.0, 1.0));
    }
    return rayColor(r);
}

Camera readCameraParameters() {
    float width, height, focal_length;
    std::cout << "Enter viewport width: ";
    std::cin >> width;
    std::cout << "Enter viewport height: ";
    std::cin >> height;
    std::cout << "Enter focal length: ";
    std::cin >> focal_length;

    return Camera(Vec3(0, 0, 0), width, height, focal_length);
}
} // namespace

void runGradientRenderTest() {
    int width = 400;
    int height = 225;
    std::vector<Vec3> pixels(width * height);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            double r = double(i) / (width - 1);
            double g = double(height - 1 - j) / (height - 1);
            double b = 0.25;
            pixels[j * width + i] = Vec3(r, g, b);
        }
    }

    save_ppm("output/test.ppm", width, height, pixels);
    std::cout << "Image saved to output/test.ppm" << std::endl;
}

void runSkyRenderTest() {
    Camera camera = readCameraParameters();
    std::vector<Vec3> pixels(camera.viewport_width * camera.viewport_height);

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
    std::cout << "Image saved to output/raytracer.ppm" << std::endl;
}

void runSphereIntersectionRenderTest() {
    int image_width = 400;
    int image_height = 225;
    double aspect_ratio = double(image_width) / image_height;

    float focal_length = readFloat("Focal Length (ex: 0.5, 1.0, 2.0): ");
    if (focal_length <= 0.0f) {
        focal_length = 1.0f;
    }

    Camera camera(Vec3(0, 0, 0), float(2.0 * aspect_ratio), 2.0f, focal_length);

    Vec3 center = readVec("Sphere Center (x y z): ");
    float radius = readFloat("Sphere Radius: ");
    if (radius <= 0.0f) {
        radius = 0.5f;
    }

    Sphere sphere(center, radius);
    std::vector<Vec3> pixels(image_width * image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            double u = double(i) / (image_width - 1);
            double v = double(image_height - 1 - j) / (image_height - 1);

            Ray ray = camera.getRay(float(u), float(v));
            pixels[j * image_width + i] = sphereRayColor(ray, sphere);
        }
    }

    save_ppm("output/sphere.ppm", image_width, image_height, pixels);
    std::cout << "Image saved to output/sphere.ppm" << std::endl;
}

void runMultipleObjectsRenderTest() {

    int image_width = 400;
    int image_height = 225;
    double aspect_ratio = double(image_width) / image_height;

    float focal_length = readFloat("Focal Length (ex: 0.5, 1.0, 2.0): ");
    if (focal_length <= 0.0f) {
        focal_length = 1.0f;
    }

    Camera camera(Vec3(0, 0, 0), float(2.0 * aspect_ratio), 2.0f, focal_length);

    int op;
    op = -1;

    vector<Hittable*> scene_objects;

    while (op!=0) {
        printObjectsMenu();
        cin >> op;

        if (cin.fail()) {
            cout << "Error: invalid input!" << endl;
        }

        switch (op) {
            case 1: {
                std::cout << "Adding Sphere to the scene..." << std::endl;
                Vec3 center = readVec("Sphere Center (x y z): ");
                float radius = readFloat("Sphere Radius: ");
                if (radius <= 0.0f) {
                    radius = 0.5f;
                }
                Sphere sphere(center, radius);
                scene_objects.push_back(new Sphere(sphere));
                break;
            }
            case 2: {
                std::cout << "Adding Plane to the scene..." << std::endl;
                // Implement plane addition logic here
                break;
            }
            case 0:
                std::cout << "Finished adding objects to the scene." << std::endl;
                break;
            default:
                std::cout << "Error: invalid option!" << std::endl;
                break;
        }
    }

    std::vector<Vec3> pixels(image_width * image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            double u = double(i) / (image_width - 1);
            double v = double(image_height - 1 - j) / (image_height - 1);

            Ray ray = camera.getRay(float(u), float(v));
            Vec3 color(0, 0, 0);
            for (const auto& obj : scene_objects) {
                Vec3 hit_point;
                if (obj->hit(ray, 0.001f, 1e30f, hit_point)) {
                    color = Vec3(1, 0, 0); // Hit color (red)
                    break;
                }
            }
            pixels[j * image_width + i] = color;
        }
    }
    save_ppm("output/multiple_objects.ppm", image_width, image_height, pixels);
    std::cout << "Image saved to output/multiple_objects.ppm" << std::endl;

}
