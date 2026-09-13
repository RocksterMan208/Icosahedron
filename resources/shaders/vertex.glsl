#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
    gl_Position = camMatrix * model * vec4(position, 1.0);
}