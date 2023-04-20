#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices=3) out;


void main(){
    mat3 M = mat3(gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz);
    if(1 * determinant(M) < 0)
    {
        EndPrimitive();
        return;
    }

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}