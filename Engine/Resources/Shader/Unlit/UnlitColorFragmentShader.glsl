#version 330 core

// In
in vec3 Fragment_color;

// Out
out vec3 color;

void main()
{
    color = Fragment_color;
}