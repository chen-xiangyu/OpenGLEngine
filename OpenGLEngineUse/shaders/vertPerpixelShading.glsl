#version 330 core

layout(location = 0) in vec3 vPos;
//layout(location = 1) in vec3 vColor;
layout(location = 1) in vec3 vNormal;

out vec3 Color;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    FragPos = vec3(Model * vec4(vPos, 1.0f));
    gl_Position = Projection * View * vec4(FragPos, 1.0f);
    //Color = vColor;
    Color = vec3(0.5f, 0.5f, 0.3f);
    Normal = mat3(transpose(inverse(Model))) * vNormal;
}
