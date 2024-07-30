#version 330 core
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 Ambient;
uniform float Shininess;
uniform vec3 ViewPos;
uniform vec3 LightColor;
uniform vec3 LightDir;

void main()
{
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    vec3 NormalDir = normalize(Normal);
    vec3 LightDirNormalized = normalize(LightDir);
    vec3 DiffuseColor = max(dot(LightDirNormalized, NormalDir), 0.0f) * LightColor * Diffuse;

    vec3 ReflectDir = normalize(reflect(-LightDirNormalized, NormalDir));
    vec3 ViewDir = normalize(ViewPos - FragPos);
    vec3 SpecularColor = pow(max(dot(ViewDir, ReflectDir), 0.0f), Shininess) * LightColor * Specular;

    vec3 AmbientColor = Ambient * LightColor;
    
    vec3 FinalColor = DiffuseColor + SpecularColor + AmbientColor;
    gl_FragColor = vec4(FinalColor, 1.0f);
}

