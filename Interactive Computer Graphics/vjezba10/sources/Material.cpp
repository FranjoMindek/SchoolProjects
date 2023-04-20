//
// Created by mindek on 30. 05. 2022..
//
#include "Material.h"

void Material::AddMaterial(const char* name, const char* dir, glm::vec3 ambient, glm::vec3 diffuse,
                           glm::vec3 specular) {
    this->info_.name = name;
    this->info_.dir = dir;
    this->info_.specular = specular;
    this->info_.diffuse = diffuse;
    this->info_.ambient = ambient;
    this->has_material_ = true;
}

Material::Material() {
    this->has_material_ = false;
}

bool Material::HasMaterial() {
    return this->has_material_;
}

glm::vec3 Material::GetAmbient() {
    return this->info_.ambient;
}

glm::vec3 Material::GetDiffuse() {
    return this->info_.diffuse;
}

glm::vec3 Material::GetSpecular() {
    return this->info_.specular;
}

Material::~Material() = default;
