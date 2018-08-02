#version 330 core

// In
in vec2 UV;

// Out
out vec3 color;

// Uniforms
uniform sampler2D texture_sampler;

void main()
{
    vec2 correct_uv = vec2(UV.x, 1.0 - UV.y);
    vec4 rgba       = texture(texture_sampler, correct_uv);

    if(rgba.a != 1.0f)
    {
        discard;
    }

    color = rgba.rgb;
}