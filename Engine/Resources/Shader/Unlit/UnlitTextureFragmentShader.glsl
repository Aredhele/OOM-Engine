#version 330 core

// In
in vec2 UV;

// Out
out vec3 color;

// Uniform
uniform sampler2D texture_sampler;

void main()
{
    color = texture(texture_sampler, UV).rgb;
}