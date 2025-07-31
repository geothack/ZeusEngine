#version 460 core
in vec2 TexCoords;
out vec4 color;

layout (location = 0) uniform sampler2D Image;

void main()
{    
    color = texture(Image, TexCoords);
}  