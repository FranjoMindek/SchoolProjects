#version 330 core

out vec4 FragColor;

in vec3 lighting_color;
in vec3 base_color;
in vec2 tex_cords;

uniform sampler2D our_tex;

void main()
{
    FragColor = texture(our_tex, tex_cords) * vec4(base_color * lighting_color, 1);
}
