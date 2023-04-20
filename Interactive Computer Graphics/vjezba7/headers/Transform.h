//
// Created by mindek on 04. 04. 2022..
//
#pragma once

#include <glm/glm.hpp>

enum Direction{FORWARD, BACKWARD, LEFT, RIGHT};
class Transform{
private:
    void updateViewMatrix(){
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);
        right = glm::normalize(glm::cross(front, glm::vec3(0,1,0)));
        up = glm::normalize(glm::cross(right, front));
    }
protected:
    glm::vec3 eye;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::mat4 modelMatrix{};
    float pitch;
    float yaw;

public:
    Transform(){
        this->modelMatrix = glm::mat4(1);
    }
    Transform(glm::mat4 model){
        this->modelMatrix = model;
    }
    glm::vec3 getEye(){
        return this->eye;
    }
    glm::vec3 getInFront(){
        return this->eye + this->front;
    }
    glm::mat4 getModelMatrix(){
        return modelMatrix;
    }
    glm::mat4 getViewMatrix(){
        updateViewMatrix();
        return glm::lookAt(eye,eye+front, up);
    }
    void rotate(float xoff, float yoff, GLboolean lockPitch = true){
        yaw = glm::mod(yaw + xoff, 360.0f);//paziti da je unutar 0-360
        pitch += yoff;

        if (lockPitch){
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
        }
    }
    void move(Direction direction, float value){
        switch (direction){
            case FORWARD:
                eye += front*value;
                break;
            case BACKWARD:
                eye -= front*value;
                break;
            case LEFT:
                eye -= right*value;
                break;
            case RIGHT:
                eye += right*value;
                break;
        }
    }
    void setModelMatrix(glm::mat4 modelMatrix){
        this->modelMatrix = modelMatrix;
    }
    static glm::mat4 translate3D(glm::vec3 translateVector){
        return glm::translate(glm::mat4(1), translateVector);
    }
    static glm::mat4 scale3D(glm::vec3 scaleVector){
        return glm::scale(glm::mat4(1), scaleVector);
    }
    static glm::mat4 lookAtMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 viewUp){
        return glm::lookAt(eye, center, viewUp);
    }
    static glm::mat4 frustum(double l, double r, double b, double t, double n, double f){
        return glm::frustum(l, r, b, t, n, f);
    }
};