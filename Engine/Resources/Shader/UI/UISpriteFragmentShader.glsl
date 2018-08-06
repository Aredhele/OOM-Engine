#version 330 core

// In
in vec2 UV;

// Out
out vec3 color;

// Uniforms
uniform sampler2D textureSampler;

void main()
{
	color = texture2D(textureSampler, UV).rgb;

    float threshold = 1.0f;
	if(color.x == threshold && color.y == threshold && color.z == threshold)
	{
	    discard;
	}
}