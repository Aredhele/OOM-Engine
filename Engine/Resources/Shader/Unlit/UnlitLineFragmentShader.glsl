#version 330 core

// Out
out vec3 color;

// Uniform
uniform vec3 line_color;

void main()
{
    color = line_color;
}