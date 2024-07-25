#version 330 core
in vec3 Color;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;
uniform vec3 ViewPos;
uniform vec3 LightColor;

void main()
{
    vec3 LightDir = vec3(0.0f, 0.0f, 1.0f);
    vec3 NormalDir = normalize(Normal);
    vec3 DiffuseColor = max(dot(LightDir, NormalDir), 0.0f) * LightColor * Diffuse;

    vec3 ReflectDir = reflect(-LightDir, NormalDir);
    vec3 ViewDir = normalize(ViewPos - FragPos);
    vec3 SpecularColor = pow(max(dot(ViewDir, ReflectDir), 0.0f), Shininess) * LightColor * Specular;

    vec3 AmbientColor = Ambient * LightColor;

    vec3 FinalColor = (DiffuseColor + SpecularColor + AmbientColor) * Color;
    FragColor = vec4(FinalColor, 1.0f);
}