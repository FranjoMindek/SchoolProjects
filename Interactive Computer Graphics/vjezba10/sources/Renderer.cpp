//
// Created by mindek on 04. 04. 2022..
//
#include "Renderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

void Renderer::render(Camera* camera){

    auto proj =  glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 10.0f);
    auto view = Transform::lookAtMatrix(glm::vec3(-2.0f, 4.0f, -1.0f),
                                        glm::vec3( 0.0f, 0.0f,  0.0f),
                                        glm::vec3( 0.0f, 1.0f,  0.0f));
    auto lsm = proj*view;

    int i = 0;
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    for(auto& meshInfo : mInstances){
        this->shadow_shader->use();

        meshInfo->shader->setUnifrom("lightSpaceMatrix", lsm);
        meshInfo->shader->setUnifrom("model", meshInfo->transform->getModelMatrix());
        meshInfo->drawable->Draw();

        i++;
    }
    i = 0;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    for(auto& meshInfo : mInstances){
        std::cout << glm::to_string(camera->getEye()) << std::endl;
        meshInfo->shader->use();

        meshInfo->shader->setUnifrom("ambientK", meshInfo->drawable->GetAmbient());
        meshInfo->shader->setUnifrom("diffuseK", meshInfo->drawable->GetDiffuse());
        meshInfo->shader->setUnifrom("specularK", meshInfo->drawable->GetSpecular());

        meshInfo->shader->setUnifrom("lightSpaceMatrix", lsm);

        glUniform1i(glGetUniformLocation(meshInfo->shader->ID, "depthMap"), 1);
        meshInfo->shader->setUnifrom("eye", camera->getEye());
        meshInfo->shader->setUnifrom("model", meshInfo->transform->getModelMatrix());
        meshInfo->shader->setUnifrom("view", camera->getViewMatrix());
        meshInfo->shader->setUnifrom("projection", camera->getProjectionMatrix());

        meshInfo->shader->setUnifrom("ambientI", glm::vec3(0.7,0.7,0.7));
        meshInfo->shader->setUnifrom("diffuseI", glm::vec3(0.7,0.7,0.7));
        meshInfo->shader->setUnifrom("specularI", glm::vec3(0.5,0.5,0.5));
        meshInfo->shader->setUnifrom("light_eye", glm::vec3(3.0f, 5.0f, 1.0f));

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

void Renderer::setShadowShader(Shader *shader, int depthMapFBO, int depthMap) {
    this->shadow_shader = shader;
    this->depthMapFBO = depthMapFBO;
    this->depthMap = depthMap;
}
