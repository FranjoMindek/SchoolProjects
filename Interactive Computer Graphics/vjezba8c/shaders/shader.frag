#version 330 core

out vec4 FragColor;

in vec3 base_color;
in vec3 nor_vec;
in vec3 pos_vec;

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
    vec3 mv_pos = pos_vec;
    vec3 mv_nor = nor_vec;

    vec3 l_vector = normalize(light_eye - mv_pos);
    vec3 v_vector = normalize(eye - mv_pos);
    vec3 r_vector = normalize(-reflect(l_vector, mv_nor));

    vec3 ambient = ambientI * ambientK;

    vec3 diffuse = diffuseI * diffuseK * max(dot(mv_nor, l_vector), 0.0);

    vec3 specular = specularI * specularK * pow(dot(v_vector, r_vector), 1);

    FragColor = vec4(base_color * (ambient + diffuse + specular), 0);
}