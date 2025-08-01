#version 460 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec2 Tex;
layout (location = 2) in vec3 Norm;

out Vertex_DATA{
    vec2 tC;
    vec3 Normal;
    vec3 Position;
} vs_Out;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    vs_Out.Normal = mat3(transpose(inverse(Model))) * Norm;
    vs_Out.tC = Tex;
    vec3 v = vec3(Model * vec4(Pos,1.0));
    vs_Out.Position = v;

    gl_Position = Projection * View * Model * vec4(Pos, 1.0);
}  
