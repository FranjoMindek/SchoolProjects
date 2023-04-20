#version 330 core

out vec4 FragColor;

uniform vec3 ambientI;
uniform vec3 ambientK;
uniform vec3 diffuseI;
uniform vec3 diffuseK;
uniform vec3 specularI;
uniform vec3 specularK;
uniform vec3 eye;
uniform vec3 light_eye;

uniform sampler2D shadowMap;

in VS_OUT {
    vec3 pos_vec;
    vec3 nor_vec;
    vec2 tex_cords;
    vec3 base_color;
    vec4 pos_light_space;
} fs_in;

float ShadowCalculation(vec4 pos_light_space){
    vec3 proj_cords = pos_light_space.xyz / pos_light_space.w;
    proj_cords = proj_cords * 0.5 + 0.5; // [0,1]
    float closest = texture(shadowMap, proj_cords.xy).r;
    float current = proj_cords.z;
    float bias = 0.005;
    float shadow = current - bias > closest ? 1.0 : 0.0;
    return shadow;
}

void main()
{
    vec3 mv_pos = fs_in.pos_vec;
    vec3 mv_nor = fs_in.nor_vec;

    vec3 l_vector = normalize(light_eye - mv_pos);
    vec3 v_vector = normalize(eye - mv_pos);
    vec3 r_vector = normalize((-l_vector, mv_nor));

    vec3 ambient = ambientI * ambientK;

    vec3 diffuse = diffuseI * diffuseK * max(dot(mv_nor, l_vector), 0.0);

    vec3 specular = specularI * specularK * pow(max(dot(v_vector, r_vector), 0.0), 1);

    float shadow = ShadowCalculation(fs_in.pos_light_space);

        if(shadow == 0.0)
        FragColor = vec4(1.0, 0.0, 0.0, 0.0);
        else
        FragColor = vec4(0.0, 1.0, 0.0, 0.0);
//    FragColor = vec4(fs_in.base_color * (ambient + ((diffuse + specular)*(1.0-shadow))), 0.0);
    //    FragColor = vec4(fs_in.base_color * (ambient + (diffuse + specular)), 0.0);
}