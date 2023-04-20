#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec2 aTex;

out VS_OUT {
    vec3 pos_vec;
    vec3 nor_vec;
    vec2 tex_cords;
    vec3 base_color;
    vec4 pos_light_space;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vs_out.nor_vec = vec3(model* vec4(aNor, 0.0));
    vs_out.pos_vec = vec3(model* vec4(aPos, 1.0));
    vs_out.pos_light_space = lightSpaceMatrix * vec4(vs_out.pos_vec, 1.0);
    vs_out.tex_cords = aTex;
    vs_out.base_color = vec3(0.4,0.2,0.4);
}