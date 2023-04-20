#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices=3) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 eye;

void main(){
    vec3 c = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz)/3;
    vec3 e = eye - c;
    vec3 n = cross(gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz, gl_in[1].gl_Position.xyz - gl_in[2].gl_Position.xyz);
    if(e.x*n.x + e.y*n.y + e.z*n.z < 0){
        EndPrimitive();
        return;
    }
    gl_Position = projection * view * model * gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = projection * view * model * gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = projection * view * model * gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}