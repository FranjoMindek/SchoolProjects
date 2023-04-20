//
// Created by mindek on 16. 05. 2022..
//
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <iostream>
#include <set>

#include "Drawable.h"
#include "Shader.h"

class Curve : public Drawable{
private:
    Shader* shader_;
    GLuint VBO_[3];
    GLuint VAO_[3];
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> approximation_vertices_;
    std::vector<glm::vec3> interpolation_vertices_vectors_;
    std::vector<glm::vec3> interpolation_vertices_;
    int BinomialCoefficient(const int n, const int k);
    glm::mat4 inversion_matrix_4_;


public:
    Curve(Shader* shader);
    ~Curve();
    void Draw() override;
    void AddVertex(glm::vec3 vertex);

};
