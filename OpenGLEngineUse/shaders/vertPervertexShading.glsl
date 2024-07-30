#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;

out vec4 FragColor;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;
uniform vec3 ViewPos;
uniform vec3 LightColor;
uniform vec3 LightDir;

void main()
{
    vec3 FragPos = vec3(Model * vec4(vPos, 1.0f));
    gl_Position = Projection * View * vec4(FragPos, 1.0f);

    vec3 Color = vec3(0.5f, 0.3f, 0.3f);
    vec3 Normal = mat3(transpose(inverse(Model))) * vNormal;

    vec3 NormalDir = normalize(Normal);
    vec3 LightDirNormalized = normalize(LightDir);
    vec3 DiffuseColor = max(dot(LightDirNormalized, NormalDir), 0.0f) * LightColor * Diffuse;

    vec3 ReflectDir = normalize(reflect(-LightDirNormalized, NormalDir));
    vec3 ViewDir = normalize(ViewPos - FragPos);
    vec3 SpecularColor = pow(max(dot(ViewDir, ReflectDir), 0.0f), Shininess) * LightColor * Specular;

    vec3 AmbientColor = Ambient * LightColor;

    vec3 FinalColor = (DiffuseColor + SpecularColor + AmbientColor) * Color;
    FragColor = vec4(FinalColor, 1.0f);
}
