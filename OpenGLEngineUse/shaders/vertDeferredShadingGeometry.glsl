#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    vec4 WorldPos = Model * vec4(vPos, 1.0f);
    FragPos = WorldPos.xyz;
    gl_Position = Projection * View * WorldPos;

    Normal = mat3(transpose(inverse(Model))) * vNormal;
}