#version 330 core

// In
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 vertex_color;

// Out
out vec3 Fragment_color;

// Uniform
uniform mat4 MVP;

void main()
{
    gl_Position    =  MVP * vec4(vertex, 1.0f);
    Fragment_color = vertex_color;
}
