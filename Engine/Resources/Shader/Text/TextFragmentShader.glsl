#version 330 core

// In
in vec2 UV;

// Out
out vec3 color;

// Uniforms
uniform vec3      textColor;
uniform sampler2D textureSampler;

void main()
{
	color = texture(textureSampler, UV).rgb;

    float threshold = 0.4f;
	if(color.x <= threshold && color.y <= threshold && color.z <= threshold)
	{
	    discard;
	}

	color = textColor;
}