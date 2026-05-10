#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>
#include <cmath>
#include <string>
#include "RenderTests.h"
#include "InputUtils.h"
#include "Vec3.h"
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
#include "ShowPPM.h"

namespace {
Light sceneLight(Vec3(5, 5, -2), Vec3(1, 1, 1));

void printObjectAddedMessage(const std::string& object_name, const HittableList& scene) {
    std::cout << "\nGreat! " << object_name << " added to the scene." << std::endl;
    std::cout << "Scene now has " << scene.getObjects().size() << " object(s).\n" << std::endl;
}

Light getLightPreset(int option) {
    switch (option) {
        case 1: return Light(Vec3(5, 5, -2), Vec3(1, 1, 1));   // Default
        case 2: return Light(Vec3(0, 8, -1), Vec3(1, 1, 1));   // Top
        case 3: return Light(Vec3(-6, 4, -1), Vec3(1, 1, 1));  // Left
        case 4: return Light(Vec3(6, 4, -1), Vec3(1, 1, 1));   // Right
        case 5: return Light(Vec3(0, 4, 3), Vec3(1, 1, 1));    // Back
        default: return Light(Vec3(5, 5, -2), Vec3(1, 1, 1));  // Default
    }
}

Camera makeDefaultCamera(float focal_length) {
    int image_width = 400;
    int image_height = 225;
    double aspect_ratio = double(image_width) / image_height;
    return Camera(Vec3(0, 0, 0), float(2.0 * aspect_ratio), 2.0f, focal_length);
}

bool isInShadow(const Hittable& scene, const HitRecord& record, const Light& light) {
    Vec3 light_direction = (light.position - record.point).normalized();
    Vec3 shadow_origin = record.point + record.normal * (0.001f); // <- epsilon
    float distance_to_light = (light.position - shadow_origin).length();
    Ray shadow_ray(shadow_origin, 1.0, light_direction);
    HitRecord hit_record;
    return scene.hit(shadow_ray, 0.01f, distance_to_light, hit_record);
}

Vec3 reflect(const Vec3& incident, const Vec3& normal) {
    return incident - 2.0 * incident.dot(normal) * normal;
}

Vec3 rayColor(const Ray& r) {
    Vec3 unit_direction = r.direction.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}

// Simple Phong shading for a hit point
Vec3 shadingRayColor(const Ray& ray, const Hittable &scene, const HitRecord& record, const Light& light) { 

    Vec3 ambient = record.material.ambient * light.intensity;
    Vec3 diffuse;
    Vec3 specular;

    Vec3 light_direction = (light.position - record.point).normalized();
    Vec3 view_direction = (ray.origin - record.point).normalized();
    Vec3 reflected_direction = (2.0f * record.normal.dot(light_direction) * record.normal - light_direction).normalized();

    if (!isInShadow(scene, record, light)) {

        float diffuse_factor = std::max(0.0f, static_cast<float>(record.normal.dot(light_direction)));
        float specular_factor = std::pow(std::max(0.0f, static_cast<float>(reflected_direction.dot(view_direction))), record.material.shininess);

        diffuse = record.material.diffuse * diffuse_factor * light.intensity;
        specular = record.material.specular * specular_factor * light.intensity;

    }

    return ambient + diffuse + specular;
}

Vec3 traceRay(const Ray& ray, const Hittable& scene, const Light& light, int depth) {
    if (depth <= 0) {
        return Vec3(0, 0, 0);
    }

    HitRecord hit_record;
    if (!scene.hit(ray, 0.001f, 1e30f, hit_record)) {
        return rayColor(ray);
    }

    Vec3 local_color = shadingRayColor(ray, scene, hit_record, light);
    float reflectivity = std::clamp(hit_record.material.reflectivity, 0.0f, 1.0f);

    if (reflectivity <= 0.0f) {
        return local_color;
    }

    Vec3 reflected_direction = reflect(ray.direction.normalized(), hit_record.normal).normalized();
    Vec3 reflected_origin = hit_record.point + hit_record.normal * 0.001f;
    Ray reflected_ray(reflected_origin, 1.0, reflected_direction);
    Vec3 reflected_color = traceRay(reflected_ray, scene, light, depth - 1);

    return (1.0f - reflectivity) * local_color + reflectivity * reflected_color;
}

void renderObjectsTest(const Hittable& scene, const std::string& output_file, float focal_length = 1.0f, const Light& light = Light()) {
    int image_width = 400;
    int image_height = 225;
    constexpr int max_depth = 4;
    Camera camera = makeDefaultCamera(focal_length);
    std::vector<Vec3> pixels(image_width * image_height);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            double u = double(i) / (image_width - 1);
            double v = double(image_height - 1 - j) / (image_height - 1);

            Ray ray = camera.getRay(float(u), float(v));
            pixels[j * image_width + i] = traceRay(ray, scene, light, max_depth);
        }
    }

    save_ppm(output_file, image_width, image_height, pixels);
    std::cout << "Image saved to " << output_file << std::endl;
}
}

void runCenteredSphereRenderTest() {
    Sphere sphere(Vec3(0, 0, -1), 0.5f);
    const char* outFile = "output/sphere_centered.ppm";
    renderObjectsTest(sphere, outFile);
    showPPMImage(outFile);
}

void runGroundPlaneRenderTest() {
    Plane plane(Vec3(0, -0.6f, 0), Vec3(0, 1, 0));
    const char* outFile = "output/ground_plane.ppm";
    renderObjectsTest(plane, outFile);
    showPPMImage(outFile);
}

void runThreeSpheresRenderTest() {
    HittableList scene;
    scene.add(std::make_unique<Sphere>(Vec3(-0.9f, -0.05f, -1.8f), 0.35f));
    scene.add(std::make_unique<Sphere>(Vec3(0.0f, -0.15f, -1.2f), 0.55f));
    scene.add(std::make_unique<Sphere>(Vec3(0.95f, 0.05f, -1.9f), 0.32f));
    const char* outFile = "output/three_spheres.ppm";
    renderObjectsTest(scene, outFile);
    showPPMImage(outFile);
}

void runSphereAndPlaneRenderTest() {
    Material matte_ground(0.12f, 0.75f, 0.08f, 8.0f, 0.1f);
    Material matte_sphere(0.1f, 0.7f, 0.2f, 32.0f, 0.0f);

    HittableList scene;
    scene.add(std::make_unique<Plane>(Vec3(0, -0.6f, 0), Vec3(0, 1, 0), matte_ground));
    scene.add(std::make_unique<Sphere>(Vec3(0.0f, 0.3f, -1.1f), 0.45f, matte_sphere));
    const char* outFile = "output/sphere_and_plane.ppm";
    renderObjectsTest(scene, outFile);
    showPPMImage(outFile);
}

void runReflectiveSphereLoRenderTest() {
    Material matte_ground(0.12f, 0.75f, 0.08f, 8.0f, 0.0f);
    Material reflective_sphere(0.08f, 0.4f, 0.6f, 64.0f, 0.3f);

    HittableList scene;
    scene.add(std::make_unique<Plane>(Vec3(0, -0.6f, 0), Vec3(0, 1, 0), matte_ground));
    scene.add(std::make_unique<Sphere>(Vec3(0.0f, 0.3f, -1.1f), 0.45f, reflective_sphere));
    const char* outFile = "output/reflective_sphere_lo.ppm";
    renderObjectsTest(scene, outFile);
    showPPMImage(outFile);
}

void runReflectiveSphereMediumRenderTest() {
    Material matte_ground(0.12f, 0.75f, 0.08f, 8.0f, 0.0f);
    Material reflective_sphere(0.05f, 0.25f, 0.85f, 128.0f, 0.8f);

    HittableList scene;
    scene.add(std::make_unique<Plane>(Vec3(0, -0.6f, 0), Vec3(0, 1, 0), matte_ground));
    scene.add(std::make_unique<Sphere>(Vec3(0.0f, 0.3f, -1.1f), 0.45f, reflective_sphere));
    const char* outFile = "output/reflective_sphere_med.ppm";
    renderObjectsTest(scene, outFile);
    showPPMImage(outFile);
}

void runTwoRefSphereRenderTest() {
    Material matte_ground(0.12f, 0.75f, 0.08f, 8.0f, 0.0f);
    Material reflective_sphere_1(0.06f, 0.3f, 0.7f, 96.0f, 0.5f);
    Material reflective_sphere_2(0.06f, 0.3f, 0.7f, 96.0f, 0.5f);

    HittableList scene;
    scene.add(std::make_unique<Plane>(Vec3(0, -0.6f, 0), Vec3(0, 1, 0), matte_ground));
    scene.add(std::make_unique<Sphere>(Vec3(-0.4f, 0.25f, -1.0f), 0.35f, reflective_sphere_1));
    scene.add(std::make_unique<Sphere>(Vec3(0.4f, 0.25f, -1.2f), 0.35f, reflective_sphere_2));
    const char* outFile = "output/two_reflective_spheres.ppm";
    renderObjectsTest(scene, outFile);
    showPPMImage(outFile);
}

void runCustomSceneRenderTest() {
    // Step 1: Choose light
    int light_op = -1;
    Light selected_light = Light();
    while (light_op < 1 || light_op > 5) {
        printLightMenu();
        std::cin >> light_op;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: invalid input!" << std::endl;
            light_op = -1;
            continue;
        }
        if (light_op >= 1 && light_op <= 5) {
            selected_light = getLightPreset(light_op);
        }
    }

    // Step 2: Focal length
    float focal_length = readFloat("Focal Length (ex: 0.5, 1.0, 2.0): ");
    if (focal_length <= 0.0f) {
        focal_length = 1.0f;
    }

    // Step 3: Add objects (default + manual)
    int default_op = -1;
    HittableList scene_objects;
    bool render_scene = false;
    while (!render_scene) {
        printAddObjectsMenu();
        std::cin >> default_op;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: invalid input!" << std::endl;
            continue;
        }

        switch (default_op) {
            case 1:
                scene_objects.add(std::make_unique<Sphere>(Vec3(-0.8f, 0, -1.2f), 0.4f));
                printObjectAddedMessage("Left Sphere", scene_objects);
                break;
            case 2:
                scene_objects.add(std::make_unique<Sphere>(Vec3(0, 0.1f, -0.8f), 0.3f));
                printObjectAddedMessage("Close Sphere", scene_objects);
                break;
            case 3:
                scene_objects.add(std::make_unique<Sphere>(Vec3(0.7f, 0, -1.2f), 0.35f));
                printObjectAddedMessage("Right Sphere", scene_objects);
                break;
            case 4:
                scene_objects.add(std::make_unique<Sphere>(Vec3(0, 0, -2), 0.5f));
                printObjectAddedMessage("Distant Sphere", scene_objects);
                break;
            case 5:
                scene_objects.add(std::make_unique<Plane>(Vec3(0, -0.6f, 0), Vec3(0, 1, 0)));
                printObjectAddedMessage("Ground Plane", scene_objects);
                break;
            case 6:
                scene_objects.add(std::make_unique<Plane>(Vec3(0, -0.5f, -1), Vec3(0.2f, 1, 0).normalized()));
                printObjectAddedMessage("Inclined Plane", scene_objects);
                break;
            case 7:
                scene_objects.add(std::make_unique<Plane>(Vec3(0, 0, -3), Vec3(0, 0, 1)));
                printObjectAddedMessage("Background Plane", scene_objects);
                break;
            case 8:
                scene_objects.add(std::make_unique<Plane>(Vec3(-1.0f, 0, 0), Vec3(1, 0, 0)));
                printObjectAddedMessage("Left Vertical Plane", scene_objects);
                break;
            case 9:
            {
                Vec3 center = readVec("Sphere Center (x y z): ");
                float radius = readFloat("Sphere Radius: ");
                if (radius <= 0.0f) {
                    radius = 0.5f;
                }
                scene_objects.add(std::make_unique<Sphere>(center, radius));
                printObjectAddedMessage("Manual Sphere", scene_objects);
                break;
            }
            case 10: {
                Vec3 point = readVec("Plane Point (x y z): ");
                Vec3 normal = readVec("Plane Normal (x y z): ");
                if (normal.length() == 0) {
                    normal = Vec3(0, 1, 0);
                }
                scene_objects.add(std::make_unique<Plane>(point, normal));
                printObjectAddedMessage("Manual Plane", scene_objects);
                break;
            }
            case 0:
                std::cout << "\nAwesome! Rendering scene now...\n" << std::endl;
                render_scene = true;
                break;
            default:
                std::cout << "Error: invalid option!" << std::endl;
                break;
        }
    }

    if (scene_objects.getObjects().empty()) {
        std::cout << "Scene is empty. Rendering sky only." << std::endl;
    }

    const char* outFile = "output/multiple_objects.ppm";
    renderObjectsTest(scene_objects, outFile, focal_length, selected_light);
    showPPMImage(outFile);

}
