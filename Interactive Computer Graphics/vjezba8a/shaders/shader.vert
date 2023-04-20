#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec2 aTex;

out vec3 nor_vec;
out vec3 pos_vec;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    nor_vec = vec3(model* vec4(aNor,0.0));
    pos_vec = vec3(model* vec4(aPos,1.0));
}