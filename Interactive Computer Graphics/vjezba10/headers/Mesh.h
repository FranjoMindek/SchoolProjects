//
// Created by mindek on 30. 03. 2022..
//
#pragma once
// masksimalno se jednom koristi
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>

#include "Drawable.h"
#include "Shader.h"
#include "Material.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct MinMax{
    float x[2];
    float y[2];
    float z[2];
    glm::vec3 means;
    float maxMean;
};

class Mesh : public Drawable{
private:
    Material mMaterial;
    GLuint mVAO;
    GLuint mVBO;
    GLuint mEBO;

    std::vector<GLuint> mIndices;
    std::vector<Vertex> mVertices;


    void setupBuffers();

public:
    MinMax mMinMax;
    //default
    Mesh() {glGenVertexArrays(1, &mVAO);};
    ~Mesh() {
        glDeleteVertexArrays(1, &mVAO);
        glDeleteBuffers(1, &mVBO);
        glDeleteBuffers(1, &mEBO);
    };
    //custom
    Mesh(std::string const& dir, std::string const& name); //preko puta

    void Draw() override;
    glm::vec3 GetAmbient() override;
    glm::vec3 GetDiffuse() override;
    glm::vec3 GetSpecular() override;
};


