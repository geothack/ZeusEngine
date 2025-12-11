#version 460 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec2 Tex;
layout (location = 2) in vec3 Norm;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;
layout (location = 5) in ivec4 boneIds; 
layout (location = 6) in vec4 weights;

layout (std140, binding = 0) uniform Camera
{
    mat4 View;
    mat4 Projection;
};

out vec3 FragPos;
out vec2 TexPos;
out vec3 Normal;

uniform mat4 Model;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

void main()
{
    vec4 totalPosition = vec4(Pos,1.0);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=MAX_BONES) 
        {
            totalPosition = vec4(Pos,1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(Pos,1.0f);
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * Norm;
    }

	gl_Position = Projection * View * Model * totalPosition;
	FragPos = vec3(Model * vec4(Pos, 1.0));
	TexPos = Tex;
	Normal = mat3(transpose(inverse(Model))) * Norm;
}