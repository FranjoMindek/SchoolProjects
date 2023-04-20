//
// Created by mindek on 16. 05. 2022..
//
#pragma once

#include <glm/glm.hpp>

class Drawable{
public:
    virtual void Draw()=0;
    virtual glm::vec3 GetAmbient()=0;
    virtual glm::vec3 GetDiffuse()=0;
    virtual glm::vec3 GetSpecular()=0;
};