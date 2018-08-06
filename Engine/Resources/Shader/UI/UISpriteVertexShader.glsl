#version 330 core

// In
layout(location = 0) in vec3 vertex;
layout(location = 2) in vec2 vertexUV;

// Uniform
uniform mat4 M;

// Out
out vec2 UV;

void main()
{
	vec2 vertexPosition_homoneneousspace  = vec2(vertex.x, vertex.y) - vec2(900, 450);
    	 vertexPosition_homoneneousspace /= vec2(900, 450);

	gl_Position =  vec4(vertexPosition_homoneneousspace, 0.0f, 1.0f);
	UV          = vec2(vertexUV.x, vertexUV.y);
}

