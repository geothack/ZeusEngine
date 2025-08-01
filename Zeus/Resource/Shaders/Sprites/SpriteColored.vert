#version 460 core
layout (location = 0) in vec4 vertex; 

//layout (std140, binding = 0) uniform Camera
//{
//    mat4 View;
//    mat4 Projection;
//};


uniform mat4 Model;
uniform mat4 Projection;

void main()
{
    gl_Position = Projection * Model * vec4(vertex.xy, 0.0, 1.0);
}