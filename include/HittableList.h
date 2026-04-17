#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>
#include "Hittable.h"

class HittableList : public Hittable {
public:
    void add(std::unique_ptr<Hittable> object) {
        objects.push_back(std::move(object));
    }

    bool hit(const Ray& r, float t_min, float t_max, Vec3& hit_point) const override {
        const Hittable* closest_object = nullptr;
        return hit(r, t_min, t_max, hit_point, closest_object);
    }

    bool hit(const Ray& r, float t_min, float t_max, Vec3& hit_point, const Hittable*& closest_object) const {
        bool has_hit = false;
        float closest_so_far = t_max;
        Vec3 current_hit_point;
        closest_object = nullptr;

        for (const auto& object : objects) {
            if (object->hit(r, t_min, closest_so_far, current_hit_point)) {
                has_hit = true;
                closest_so_far = (current_hit_point - r.origin).length();
                hit_point = current_hit_point;
                closest_object = object.get();
            }
        }

        return has_hit;
    }

    const std::vector<std::unique_ptr<Hittable>>& getObjects() const {
        return objects;
    }

private:
    std::vector<std::unique_ptr<Hittable>> objects;
};

#endif // HITTABLE_LIST_H