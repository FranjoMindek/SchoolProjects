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

#include <iostream>

void processInput(GLFWwindow *window, float delta);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera* camera;
Renderer* renderer;

bool firstCameraMovement = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

Shader* loadShader(char* path, const std::string& naziv, bool eye);
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-2);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.1, 0.2, 0.3, 1);

    glfwSwapInterval(0);
    fprintf(stderr, "%s\n", glGetString(GL_VERSION));

    FPSManager FPSManagerObject(window, 60, 1.0, "Zad 4");

    camera = new Camera((float)SCR_WIDTH, (float)SCR_HEIGHT, 45.0f);
    renderer = new Renderer();

    Shader* shader_scena = loadShader(argv[0], "shader", false);
    Shader* shader_projekcija = loadShader(argv[0], "shader2", true);
    Mesh* glava = loadMesh(argv[0], "glava");

//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(/*glava->mMinMax.x[0]-glava->mMinMax.x[1]*/1, 0, 0));
//    std::cout << glm::to_string(model) << std::endl;
//    std::cout << glm::to_string(glava->mMinMax.means) << std::endl;
    //model = glm::scale(model, glm::vec3(2.0f/kocka1->mMinMax.maxMean));
    //model = glm::inverse(model);

    renderer->addInstance("glava1", glava, shader_scena, new Transform());
    renderer->addInstance("glava2", glava, shader_projekcija, new Transform());
    renderer->instanceSetModelMatrix("glava1", model);

    while (glfwWindowShouldClose(window) == false){
        double delta = FPSManagerObject.enforceFPS(true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        glUseProgram(shader_scena->ID);

        renderer->render(camera);

        glfwSwapBuffers(window);
        glfwPollEvents();

        processInput(window, (float)delta);
    }

    delete shader_scena;
    delete shader_projekcija;
    delete glava;
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

Shader* loadShader(char* path, const std::string& naziv, bool eye) {
    std::string sPath(path);
    std::string pathVert;
    std::string pathFrag;
    std::string pathGeom;

    pathVert.append(path, sPath.find_last_of('/') + 1);
    pathVert.append("shaders/");
    pathVert.append(naziv);
    pathVert.append(".vert");

    pathFrag.append(path, sPath.find_last_of('/') + 1);
    pathFrag.append("shaders/");
    pathFrag.append(naziv);
    pathFrag.append(".frag");

    pathGeom.append(path, sPath.find_last_of('/') + 1);
    pathGeom.append("shaders/");
    pathGeom.append(naziv);
    pathGeom.append(".geom");
//    std::cout << pathFrag << std::endl << pathVert << std::endl << pathGeom << std::endl;
    return new Shader(pathVert.c_str(), pathFrag.c_str(), pathGeom.c_str(), eye);
}

Mesh* loadMesh(char* path, const std::string& naziv) {
    std::string sPath(path);
    std::string pathObj;

    pathObj.append(path, sPath.find_last_of('/') + 1);
    pathObj.append("resources/");
    pathObj.append(naziv + "/" + naziv + ".obj");
//    std::cout << pathObj << std::endl;
    return new Mesh(pathObj);
}
