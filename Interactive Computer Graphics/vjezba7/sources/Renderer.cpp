//
// Created by mindek on 04. 04. 2022..
//
#include "Renderer.h"

void Renderer::render(Camera* camera){
    //std::cout << "Drawing " << mInstances.size() << " instances!" << std::endl;
    for(auto& meshInfo : mInstances){
        meshInfo->shader->use();
//        if(meshInfo->shader->needsEye()) {
//            meshInfo->shader->setUnifrom("eye",camera->getEye());
//        }
        meshInfo->shader->setUnifrom("model", meshInfo->transform->getModelMatrix());
        meshInfo->shader->setUnifrom("view", camera->getViewMatrix());
        meshInfo->shader->setUnifrom("projection", camera->getProjectionMatrix());
        meshInfo->drawable->Draw();
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