#version 460 core

in vec2 Coord;

out vec4 OutColor;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
	vec4 diffColor = texture(diffuse0,Coord);
	vec4 specColor = texture(specular0,Coord);

	vec4 combine = mix(diffColor,specColor,0.5);
	
	OutColor = combine;
}