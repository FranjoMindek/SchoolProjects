//
// Created by mindek on 30. 05. 2022..
//
#pragma once

#include <string>
#include <vector>
#include <map>

#include <glm/glm.hpp>

struct MaterialInfo {
    const char* name;
    const char* dir;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class Material{
public:
    Material();
    ~Material();

    bool HasMaterial();
    void AddMaterial(const char* name, const char* dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    glm::vec3 GetAmbient();
    glm::vec3 GetDiffuse();
    glm::vec3 GetSpecular();

private:
    bool has_material_;
    MaterialInfo info_;
};
