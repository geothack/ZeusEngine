#version 460 core

out vec4 FragColour;



in Vertex_DATA{
    vec2 tC;
    vec3 Normal;
    vec3 Position;
} vs_In;

uniform vec3 cameraPos;
uniform samplerCube skybox;
layout (binding = 1) uniform sampler2D diffuse;


void main()
{
    vec3 I = normalize(vs_In.Position + cameraPos);

    //calculate the reflection direction for the incident vector
    vec3 R = reflect(I, normalize(vs_In.Normal)); 
    

    vec4 Colour = vec4(texture(skybox, R).rgb, 1.0);
    //vec4 surface = vec4(texture(diffuse,vs_In.tC).rgb,1.0);

    //vec4 result = mix(surface,Colour,0.8);

    FragColour = Colour;

}