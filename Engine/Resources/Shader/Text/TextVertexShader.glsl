#version 330 core

// In
layout(location = 0) in vec3 vertex;
layout(location = 2) in vec2 vertexUV;

uniform mat4 proj;
uniform mat4 model;

// Out
out vec2 UV;

void main()
{
	gl_Position = proj * (model * vec4(vertex, 1.0f));
	UV = vec2(vertexUV.x, vertexUV.y);
}