#version 460 core

layout (location = 0) in vec3 Pos;

out vec3 TexPos;

uniform mat4 Projection;
uniform mat4 View;


void main()
{
    TexPos = Pos;
    vec4 position = Projection * View * vec4(Pos, 1.0);
    gl_Position = position.xyww;
}  