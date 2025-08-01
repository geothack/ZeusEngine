#version 460 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec2 Tex;
layout (location = 2) in vec3 Norm;

out vec3 FragPos;
out vec2 TexPos;
out vec3 Normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * View * Model * vec4(Pos,1.0);
	FragPos = vec3(Model * vec4(Pos, 1.0));
	TexPos = Tex;
	Normal = mat3(transpose(inverse(Model))) * Norm;
}