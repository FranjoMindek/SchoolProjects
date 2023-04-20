//
// Created by mindek on 04. 04. 2022..
//
#include "Renderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

void Renderer::render(Camera* camera){
    //std::cout << "Drawing " << mInstances.size() << " instances!" << std::endl;
    int i = 0;
    for(auto& meshInfo : mInstances){
        meshInfo->shader->use();
        std::cout << i << std::endl;
//        std::cout << glm::to_string(camera->getEye()) << std::endl;
        if (i == 1){
            meshInfo->shader->setUnifrom("ambientK", meshInfo->drawable->GetAmbient());
            meshInfo->shader->setUnifrom("diffuseK", glm::vec3(0.0, 0.0, 0.0));
            meshInfo->shader->setUnifrom("specularK", glm::vec3(0.0, 0.0, 0.0));
        } else if (i == 2){
            meshInfo->shader->setUnifrom("ambientK", glm::vec3(0.0, 0.0, 0.0));
            meshInfo->shader->setUnifrom("diffuseK", meshInfo->drawable->GetDiffuse());
            meshInfo->shader->setUnifrom("specularK", glm::vec3(0.0, 0.0, 0.0));
        } else if (i == 3) {
            meshInfo->shader->setUnifrom("ambientK", glm::vec3(0.0, 0.0, 0.0));
            meshInfo->shader->setUnifrom("diffuseK", glm::vec3(0.0, 0.0, 0.0));
            meshInfo->shader->setUnifrom("specularK", meshInfo->drawable->GetSpecular());
        } else if (i == 4) {
            meshInfo->shader->setUnifrom("ambientK", meshInfo->drawable->GetAmbient());
            meshInfo->shader->setUnifrom("diffuseK", meshInfo->drawable->GetDiffuse());
            meshInfo->shader->setUnifrom("specularK", meshInfo->drawable->GetSpecular());
        }
        meshInfo->shader->setUnifrom("eye", camera->getEye());
        meshInfo->shader->setUnifrom("model", meshInfo->transform->getModelMatrix());
        meshInfo->shader->setUnifrom("view", camera->getViewMatrix());
        meshInfo->shader->setUnifrom("projection", camera->getProjectionMatrix());

        meshInfo->shader->setUnifrom("ambientI", glm::vec3(1.0,1.0,1.0));
        meshInfo->shader->setUnifrom("diffuseI", glm::vec3(1.0,1.0,1.0));
        meshInfo->shader->setUnifrom("specularI", glm::vec3(1.0,1.0,1.0));
        meshInfo->shader->setUnifrom("light_eye", glm::vec3(0,0,1));

        meshInfo->drawable->Draw();
        i++;
    }
}

//Renderer::Renderer(Camera *camera){
//    mCurrentCamera = camera;
//}
Renderer::Renderer() = default;

Renderer::~Renderer() {
    for(auto& meshInfo: mInstances){
        delete meshInfo;
    }
}

bool Renderer::addInstance(std::string name, Drawable* drawable, Shader* shader, Transform* transfrom) {
    MeshInfo* meshInfo = new MeshInfo({drawable, shader, transfrom});
    mInstances.push_back(meshInfo);
    auto result = mMap.insert({name,transfrom});
    return result.second;
}
void Renderer::instanceSetModelMatrix(std::string name, glm::mat4 modelMatrix) {
    mMap.at(name)->setModelMatrix(modelMatrix);
}
glm::mat4 Renderer::instanceGetModelMatrix(std::string name) {
    return mMap.at(name)->getModelMatrix();
}

Transform* Renderer::getInstance(std::string name){
    return mMap.at(name);
}