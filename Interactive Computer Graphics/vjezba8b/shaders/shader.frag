#version 330 core

out vec4 FragColor;

in vec3 lighting_color;
in vec3 base_color;

void main()
{
    FragColor = vec4(base_color * lighting_color, 0);
}