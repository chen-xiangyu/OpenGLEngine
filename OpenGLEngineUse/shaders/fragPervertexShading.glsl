#version 330 core
// per vertex
in vec3 Color;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;
uniform vec3 ViewPos;
uniform vec3 LightColor;
uniform vec3 LightDir;

void main()
{
    vec3 NormalDir = normalize(Normal);
    vec3 LightDirNormalized = normalize(LightDir);
    vec3 DiffuseColor = max(dot(LightDirNormalized, NormalDir), 0.0f) * LightColor * Diffuse;

    vec3 ReflectDir = normalize(reflect(-LightDirNormalized, NormalDir));
    vec3 ViewDir = normalize(ViewPos - FragPos);
    vec3 SpecularColor = pow(max(dot(ViewDir, ReflectDir), 0.0f), Shininess) * LightColor * Specular;

    vec3 AmbientColor = Ambient * LightColor;

    vec3 FinalColor = (DiffuseColor + SpecularColor + AmbientColor) * vec3(0.3f, 0.3f, 0.3f);
    gl_FragColor = vec4(FinalColor, 1.0f);
}