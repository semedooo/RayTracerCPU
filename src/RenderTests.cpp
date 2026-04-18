#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>
#include <cmath>
#include <string>
#include "RenderTests.h"
#include "InputUtils.h"
#include "Image.h"
#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Light.h"
#include "Material.h"
#include "Menu.h"

namespace {
Light sceneLight(Vec3(5, 5, -2), Vec3(1, 1, 1));

Camera makeDefaultCamera(float focal_length) {
    int image_width = 400;
    int image_height = 225;
    double aspect_ratio = double(image_width) / image_height;
    return Camera(Vec3(0, 0, 0), float(2.0 * aspect_ratio), 2.0f, focal_length);
}

Vec3 rayColor(const Ray& r) {
    Vec3 unit_direction = r.direction.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}

// Simple Phong shading for a hit point
Vec3 shadingRayColor(const Ray& ray, const HitRecord& record, const Light& light) {
    Vec3 ambient = record.material.ambient * light.intensity;

    Vec3 light_direction = (light.position - record.point).normalized();
    Vec3 view_direction = (ray.origin - record.point).normalized();
    Vec3 reflected_direction = (2.0f * record.normal.dot(light_direction) * record.normal - light_direction).normalized();

    float diffuse_factor = std::max(0.0f, static_cast<float>(record.normal.dot(light_direction)));
    float specular_factor = std::pow(std::max(0.0f, static_cast<float>(reflected_direction.dot(view_direction))), record.material.shininess);

    Vec3 diffuse = record.material.diffuse * diffuse_factor * light.intensity;
    Vec3 specular = record.material.specular * specular_factor * light.intensity;

    return ambient + diffuse + specular;
}

void renderSingleObjectTest(const Hittable& object, const std::string& output_file, float focal_length = 1.0f) {
    int image_width = 400;
    int image_height = 225;
    Camera camera = makeDefaultCamera(focal_length);
    std::vector<Vec3> pixels(image_width * image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            double u = double(i) / (image_width - 1);
            double v = double(image_height - 1 - j) / (image_height - 1);

            Ray ray = camera.getRay(float(u), float(v));
            HitRecord hit_record;
            pixels[j * image_width + i] = object.hit(ray, 0.001f, 1e30f, hit_record)
                ? shadingRayColor(ray, hit_record, sceneLight)
                : rayColor(ray);
        }
    }

    save_ppm(output_file, image_width, image_height, pixels);
    std::cout << "Image saved to " << output_file << std::endl;
}

void renderSceneTest(const Hittable& scene, const std::string& output_file, float focal_length = 1.0f) {
    int image_width = 400;
    int image_height = 225;
    Camera camera = makeDefaultCamera(focal_length);
    std::vector<Vec3> pixels(image_width * image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            double u = double(i) / (image_width - 1);
            double v = double(image_height - 1 - j) / (image_height - 1);

            Ray ray = camera.getRay(float(u), float(v));
            HitRecord hit_record;
            pixels[j * image_width + i] = scene.hit(ray, 0.001f, 1e30f, hit_record)
                ? shadingRayColor(ray, hit_record, sceneLight)
                : rayColor(ray);
        }
    }

    save_ppm(output_file, image_width, image_height, pixels);
    std::cout << "Image saved to " << output_file << std::endl;
}
/*
Camera readCameraParameters() {
    float width, height, focal_length;
    std::cout << "Enter viewport width: ";
    std::cin >> width;
    std::cout << "Enter viewport height: ";
    std::cin >> height;
    std::cout << "Enter focal length: ";
    std::cin >> focal_length;

    return Camera(Vec3(0, 0, 0), width, height, focal_length);
} */
} // namespace

void runCenteredSphereRenderTest() {
    Sphere sphere(Vec3(0, 0, -1), 0.5f);
    renderSingleObjectTest(sphere, "output/sphere_centered.ppm");
}

void runGroundPlaneRenderTest() {
    Plane plane(Vec3(0, -0.6f, 0), Vec3(0, 1, 0));
    renderSingleObjectTest(plane, "output/ground_plane.ppm");
}

void runThreeSpheresRenderTest() {
    HittableList scene;
    scene.add(std::make_unique<Sphere>(Vec3(-0.9f, -0.05f, -1.8f), 0.35f));
    scene.add(std::make_unique<Sphere>(Vec3(0.0f, -0.15f, -1.2f), 0.55f));
    scene.add(std::make_unique<Sphere>(Vec3(0.95f, 0.05f, -1.9f), 0.32f));

    renderSceneTest(scene, "output/three_spheres.ppm");
}

void runSphereAndPlaneRenderTest() {
    HittableList scene;
    scene.add(std::make_unique<Plane>(Vec3(0, -0.6f, 0), Vec3(0, 1, 0)));
    scene.add(std::make_unique<Sphere>(Vec3(0.0f, -0.05f, -1.1f), 0.45f));

    renderSceneTest(scene, "output/sphere_and_plane.ppm");
}

void runCustomSceneRenderTest() {
    float focal_length = readFloat("Focal Length (ex: 0.5, 1.0, 2.0): ");
    if (focal_length <= 0.0f) {
        focal_length = 1.0f;
    }

    int op = -1;
    HittableList scene_objects;

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
                scene_objects.add(std::make_unique<Sphere>(center, radius));
                break;
            }
            case 2: {
                std::cout << "Adding Plane to the scene..." << std::endl;
                Vec3 point = readVec("Plane Point (x y z): ");
                Vec3 normal = readVec("Plane Normal (x y z): ");
                if (normal.length() == 0) {
                    normal = Vec3(0, 1, 0);
                }
                scene_objects.add(std::make_unique<Plane>(point, normal));
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

    if (scene_objects.getObjects().empty()) {
        std::cout << "Scene is empty. Rendering sky only." << std::endl;
    }

    renderSceneTest(scene_objects, "output/multiple_objects.ppm", focal_length);

}
