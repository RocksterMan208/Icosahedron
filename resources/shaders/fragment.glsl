#version 330 core

in vec3 normalColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(normalColor, 1.0);
}