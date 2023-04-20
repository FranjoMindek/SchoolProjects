//
// Created by mindek on 01. 04. 2022..
//
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Transform.h"

//DEFAULTS


class Camera : public Transform{
private:
    float aspectRatio;
    float zoom;
    glm::mat4 Projection;
    const float ZOOM = 45.0f;
    float CAMERA_SENSITIVITY = 0.1f;
    float CAMERA_SPEED = 1.0f;
public:

    Camera(){
        aspectRatio = 1.0f;
        zoom = ZOOM;
    }
    Camera(float width, float height, float FOV){
        aspectRatio = width / height;
        zoom = FOV;
    }
    ~Camera()= default;

    void rotate(float xoff, float yoff, GLboolean lockPitch = true){
        Transform::rotate(CAMERA_SENSITIVITY*xoff, CAMERA_SENSITIVITY*yoff, lockPitch);
    }

    void move(Direction direction, float value){
        Transform::move(direction, CAMERA_SPEED*value);
    }

    glm::mat4 getProjectionMatrix(){
        Projection = glm::perspective(glm::radians(zoom), aspectRatio, 0.01f, 100.0f);
        return Projection;
    }

    void setAspectRatio(glm::vec2 screenSize){ //WIDTH PA HEIGHT !!!!
        aspectRatio = screenSize.x / screenSize.y;
        Projection = glm::perspective(glm::radians(zoom), aspectRatio, 0.01f, 100.0f);
    }

    void setAspectRatio(float w, float h){ //WIDTH PA HEIGHT !!!!
        aspectRatio = w / h;
        Projection = glm::perspective(glm::radians(zoom), aspectRatio, 0.01f, 100.0f);
    }
};

