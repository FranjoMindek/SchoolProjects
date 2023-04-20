//
// Created by mindek on 27. 05. 2022..
//
#pragma once

#include "Transform.h"
#include <glm/glm.hpp>

class DirectionalLight : public Transform{
public:
    DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular){
        this->ambient_ = ambient;
        this->diffuse_ = diffuse;
        this->specular_ = specular;
    }
    glm::vec3 GetAmbient(){
        return this->ambient_;
    }
    glm::vec3 GetDiffuse(){
        return this->diffuse_;
    }
    glm::vec3 GetSpecular(){
        return this->specular_;
    }
    ~DirectionalLight()= default;

    glm::mat4 getProjectionMatrix(){
        return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.0f);
    }
    glm::mat4 lookAtMatrix(){
        return Transform::lookAtMatrix(glm::vec3(-2.0f, 4.0f, -1.0f),
                                       glm::vec3( 0.0f, 0.0f,  0.0f),
                                      glm::vec3( 0.0f, 1.0f,  0.0f));
    }
private:
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;
};