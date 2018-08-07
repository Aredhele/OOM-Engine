#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform sampler2D colorTexture;

void main(void)
{
   color = texture2D(colorTexture, textureUV).rgb;

   float threshold = 0.99f;
   if(color.x >= threshold && color.y >= threshold && color.z >= threshold)
   {
	   discard;
   }
}