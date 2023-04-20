#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec3 nor_vec[];
in vec3 pos_vec[];

out vec3 lighting_color;
out vec3 base_color;

uniform vec3 ambientI;
uniform vec3 ambientK;
uniform vec3 diffuseI;
uniform vec3 diffuseK;
uniform vec3 specularI;
uniform vec3 specularK;
uniform vec3 eye;
uniform vec3 light_eye;

void main(){
    vec3 mv_nor = normalize(nor_vec[0] + nor_vec[1] + nor_vec[2]);
    vec3 mv_pos = (pos_vec[0] + pos_vec[1] + pos_vec[2])/3;
    vec3 color = vec3(0.4, 0.4, 0.2);

    vec3 l_vector = normalize(light_eye - mv_pos);
    vec3 v_vector = normalize(eye - mv_pos);
    vec3 r_vector = normalize(-reflect(l_vector, mv_nor));

    vec3 ambient = ambientI * ambientK;

    vec3 diffuse = diffuseI * diffuseK * max(dot(mv_nor, l_vector), 0.0);

    vec3 specular = specularI * specularK * pow(dot(v_vector, r_vector), 1);

    vec3 all = ambient + diffuse + specular;

    gl_Position = gl_in[0].gl_Position;
    lighting_color = all;
    base_color = color;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    lighting_color = all;
    base_color = color;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    lighting_color = all;
    base_color = color;
    EmitVertex();

    EndPrimitive();
}
