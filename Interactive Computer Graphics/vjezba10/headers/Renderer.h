//
// Created by mindek on 04. 04. 2022..
//
#pragma once

#include <vector>
#include <map>

#include "Drawable.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"

struct MeshInfo{
   Drawable* drawable;
   Shader* shader;
   Transform* transform;
};

class Renderer{
private:
    std::map<std::string,Transform*> mMap;
    std::vector<MeshInfo*> mInstances;
    Shader* shadow_shader;
    int depthMapFBO;
    int depthMap;
//    Camera* mCurrentCamera;


public:
//    Renderer(Camera* camera);
    Renderer();
    ~Renderer();
    void setShadowShader(Shader* shader, int depthMapFBO, int depthMap);
    bool addInstance(std::string name, Drawable* drawable, Shader* shader, Transform* transfrom);
    void instanceSetModelMatrix(std::string name, glm::mat4 modelMatrix);
    glm::mat4 instanceGetModelMatrix(std::string name);
    Transform* getInstance(std::string name);
    void render(Camera* camera);
};