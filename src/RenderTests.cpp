#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "RenderTests.h"
#include "InputUtils.h"
#include "Image.h"
#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
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

Vec3 objectRayColor(const Hittable& obj, const Vec3& hit_point) {
    if (const Sphere* sphere = dynamic_cast<const Sphere*>(&obj)) {
        Vec3 normal = (hit_point - sphere->center).normalized();
        return 0.5 * (normal + Vec3(1.0, 1.0, 1.0));
    }

    if (const Plane* plane = dynamic_cast<const Plane*>(&obj)) {
        Vec3 normal = plane->normal.normalized();
        return 0.5 * (normal + Vec3(1.0, 1.0, 1.0));
    }

    return Vec3(1.0, 0.0, 1.0);
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

    int op = -1;
    std::vector<std::unique_ptr<Hittable>> scene_objects;

    while (op!=0) {
        printObjectsMenu();
        std::cin >> op;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: invalid input!" << std::endl;
            op = -1;
            continue;
        }

        switch (op) {
            case 1: {
                std::cout << "Adding Sphere to the scene..." << std::endl;
                Vec3 center = readVec("Sphere Center (x y z): ");
                float radius = readFloat("Sphere Radius: ");
                if (radius <= 0.0f) {
                    radius = 0.5f;
                }
                scene_objects.push_back(std::make_unique<Sphere>(center, radius));
                break;
            }
            case 2: {
                std::cout << "Adding Plane to the scene..." << std::endl;
                Vec3 point = readVec("Plane Point (x y z): ");
                Vec3 normal = readVec("Plane Normal (x y z): ");
                if (normal.length() == 0) {
                    normal = Vec3(0, 1, 0);
                }
                scene_objects.push_back(std::make_unique<Plane>(point, normal));
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

    if (scene_objects.empty()) {
        std::cout << "Scene is empty. Rendering sky only." << std::endl;
    }

    std::vector<Vec3> pixels(image_width * image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            double u = double(i) / (image_width - 1);
            double v = double(image_height - 1 - j) / (image_height - 1);

            Ray ray = camera.getRay(float(u), float(v));
            Vec3 color = rayColor(ray);

            double closest_so_far = std::numeric_limits<double>::infinity();
            bool has_hit = false;
            Vec3 closest_hit_point;
            const Hittable* closest_object = nullptr;

            for (const auto& obj : scene_objects) {
                Vec3 hit_point;
                if (obj->hit(ray, 0.001f, float(closest_so_far), hit_point)) {
                    double distance = (hit_point - ray.origin).length();
                    if (distance < closest_so_far) {
                        closest_so_far = distance;
                        closest_hit_point = hit_point;
                        closest_object = obj.get();
                        has_hit = true;
                    }
                }
            }

            if (has_hit && closest_object != nullptr) {
                color = objectRayColor(*closest_object, closest_hit_point);
            }

            pixels[j * image_width + i] = color;
        }
    }
    save_ppm("output/multiple_objects.ppm", image_width, image_height, pixels);
    std::cout << "Image saved to output/multiple_objects.ppm" << std::endl;

}
