#version 460 core


in vec3 FragPos;
in vec2 TexPos;
in vec3 Normal;

out vec4 OutColor;


struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
//uniform vec3 Color;
uniform samplerCube skybox;
uniform sampler2D diffuse0;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 mapColor)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // combine results
    vec4 mDiff = vec4(texture(diffuse0, TexPos).rgb,1.0);
    vec4 result = mix(mDiff,mapColor,0.3);
    vec3 ambient = light.ambient * result.rgb;
    vec3 diffuse = light.diffuse * diff * result.rgb;
    vec3 specular = light.specular * spec * result.rgb;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 mapColor)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec4 mDiff = vec4(texture(diffuse0, TexPos).rgb,1.0);
    vec4 result = mix(mDiff,mapColor,0.3);
    vec3 ambient = light.ambient * result.rgb;
    vec3 diffuse = light.diffuse * diff * result.rgb;
    vec3 specular = light.specular * spec * result.rgb;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 mapColor)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec4 mDiff = vec4(texture(diffuse0, TexPos).rgb,1.0);
    vec4 result = mix(mDiff,mapColor,0.3);
    vec3 ambient = light.ambient * result.rgb;
    vec3 diffuse = light.diffuse * diff * result.rgb;
    vec3 specular = light.specular * spec * result.rgb;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main()
{
	vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 I = normalize(FragPos + viewPos);
    vec3 R = reflect(I, normalize(Normal)); 
    
    vec4 Colour = vec4(texture(skybox, R).rgb, 1.0);
    

    vec3 result = CalcDirLight(dirLight, norm, viewDir,Colour);

    result += CalcPointLight(pointLight, norm, FragPos, viewDir,Colour); 
        
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir,Colour);    
    
    OutColor = vec4(result, 1.0);
}