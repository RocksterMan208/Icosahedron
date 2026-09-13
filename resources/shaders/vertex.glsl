#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 camMatrix;
uniform mat4 model;

out vec3 normalColor;

void main()
{
    gl_Position = camMatrix * model * vec4(position, 1.0);

    normalColor = normalize(position) * 0.5 + 0.5;
}