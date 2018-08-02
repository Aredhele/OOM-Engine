#version 330 core

// In
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 vertex_uv;

// Out
out vec2 UV;

// Uniform
uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vertex, 1.0f);
    UV          = vertex_uv;
}