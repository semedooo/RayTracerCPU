#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
public:
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    float reflectivity;

    virtual ~Material() = default;

    Material() : ambient(0.1f), diffuse(0.7f), specular(0.2f), shininess(32.0f), reflectivity(0.0f) {}

    Material(float ambient, float diffuse, float specular, float shininess, float reflectivity)
        : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), reflectivity(reflectivity) {}

};

#endif // MATERIAL_H