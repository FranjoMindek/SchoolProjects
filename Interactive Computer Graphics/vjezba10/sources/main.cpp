//
// Created by mindek on 31. 03. 2022..
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "FPSManager.h"
#include "Camera.h"
#include "Renderer.h"
#include "DirectionalLight.h"

#include <iostream>

void processInput(GLFWwindow *window, float delta);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void space_callback(GLFWwindow*, int key, int scancode, int action, int mods);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera* camera;
Renderer* renderer;

bool firstCameraMovement = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

Shader* loadShader(char* path, const std::string& naziv, bool geom = false);
Mesh* loadMesh(char* path, const std::string& naziv);

int main(int, char* argv[]) {

    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Zad 4", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        exit(-1);
    }


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, space_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-2);
    }

    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );




    glfwSwapInterval(0);
    fprintf(stderr, "%s\n", glGetString(GL_VERSION));

    FPSManager FPSManagerObject(window, 60, 1.0, "Zad 4");

    camera = new Camera((float)SCR_WIDTH, (float)SCR_HEIGHT, 45.0f);
    renderer = new Renderer();

    Shader* shader = loadShader(argv[0], "shader");
    Shader* lightcube = loadShader(argv[0], "lightcube");
    Shader* light = loadShader(argv[0], "light");

    Mesh* glava = loadMesh(argv[0], "glava");
    Mesh* kocka = loadMesh(argv[0], "kocka");

    renderer->addInstance("kocka2", kocka, shader, new Transform());
    for(int i=0; i<64; i++){
        renderer->addInstance("glava"+std::to_string(i), glava, shader, new Transform());
    }

    glm::mat4 one = glm::mat4(1.0f);
    glm::mat4 floor = glm::translate(one, glm::vec3(0.0f,-1.0f, 0.0f));
    floor = glm::scale(floor, glm::vec3(15.0f, 0.001f, 15.0f));
    floor = glm::translate(floor, glm::vec3(-0.5f, 0.0f, -0.5f));

    renderer->instanceSetModelMatrix("kocka2", floor);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++) {
            for (int k=0; k <4; k++) {
                glm::mat4 trans = glm::translate(one, glm::vec3(j, k, i));
                renderer->instanceSetModelMatrix("glava"+std::to_string(i*16 + j*4 + k), trans);
            }
        }
    }

    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    const unsigned int SHADOW_WIDTH = 800, SHADOW_HEIGHT = 600;

    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    std::cout << depthMap << std::endl;

    renderer->setShadowShader(light, depthMapFBO, depthMap);

    while (glfwWindowShouldClose(window) == false){
        glClearColor(0.2, 0.4, 0.6, 1);
        double delta = FPSManagerObject.enforceFPS(true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer->render(camera);

        glfwSwapBuffers(window);
        glfwPollEvents();

        processInput(window, (float)delta);
    }

    delete shader;
    delete lightcube;
    delete light;
    delete glava;
    delete kocka;
    delete renderer;
    delete camera;
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* , int width, int height)
{
    std::cout << "Changing window size to: " << width << " " << height << std::endl;
    glViewport(0, 0, width, height);
    camera->setAspectRatio((float)width,(float)height);
}

void space_callback(GLFWwindow*, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){

    }
}


void mouse_callback(GLFWwindow* , double xposIn, double yposIn)
{
    auto xpos = static_cast<float>(xposIn);
    auto ypos = static_cast<float>(yposIn);
    if (firstCameraMovement)
    {
        lastX = xpos;
        lastY = ypos;
        firstCameraMovement = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
    camera->rotate(xoffset, yoffset);
}

void processInput(GLFWwindow *window, float delta) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->move(FORWARD, delta);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->move(FORWARD, delta);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->move(BACKWARD, delta);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->move(LEFT, delta);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->move(RIGHT, delta);
}

Shader* loadShader(char* path, const std::string& naziv, bool geom) {
    std::string sPath(path);
    std::string pathVert;
    std::string pathFrag;
//    std::string pathGeom;

    pathVert.append(path, sPath.find_last_of('/') + 1);
    pathVert.append("shaders/");
    pathVert.append(naziv);
    pathVert.append(".vert");

    pathFrag.append(path, sPath.find_last_of('/') + 1);
    pathFrag.append("shaders/");
    pathFrag.append(naziv);
    pathFrag.append(".frag");

    if(geom){
        std::string pathGeom;
        pathGeom.append(path, sPath.find_last_of('/') +1);
        pathGeom.append("shaders/");
        pathGeom.append(naziv);
        pathGeom.append(".geom");
        return new Shader(pathVert.c_str(), pathFrag.c_str(), pathGeom.c_str());
    }
    return new Shader(pathVert.c_str(), pathFrag.c_str());
}

Mesh* loadMesh(char* path, const std::string& naziv) {
    std::string sPath(path);
    std::string pathObj;

    pathObj.append(path, sPath.find_last_of('/') + 1);
    pathObj.append("resources/");
    pathObj.append(naziv + "/");
//    std::cout << pathObj << std::endl;
    return new Mesh(pathObj, naziv);
}
