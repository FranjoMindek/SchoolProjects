#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec2 aTex;

out vec3 lighting_color;
out vec3 base_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 ambientI;
uniform vec3 ambientK;
uniform vec3 diffuseI;
uniform vec3 diffuseK;
uniform vec3 specularI;
uniform vec3 specularK;
uniform vec3 eye;
uniform vec3 light_eye;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    vec3 mv_pos = vec3(model* vec4(aPos,1.0));
    vec3 mv_nor = vec3(model* vec4(aNor,0.0));

    vec3 l_vector = normalize(light_eye - mv_pos);
    vec3 v_vector = normalize(eye - mv_pos);
    vec3 r_vector = normalize(-reflect(l_vector, mv_nor));

    vec3 ambient = ambientI * ambientK;

    vec3 diffuse = diffuseI * diffuseK * max(dot(mv_nor, l_vector), 0.0);

    vec3 specular = specularI * specularK * pow(dot(v_vector, r_vector), 1);

    lighting_color = ambient + diffuse + specular;
    base_color = vec3(0.4,0.4,0.2);
}