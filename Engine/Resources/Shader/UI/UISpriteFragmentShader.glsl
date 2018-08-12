#version 330 core

// In
in vec2 textureUV;

// Out
out vec3 color;

// Uniform
uniform vec3	  spriteColor;
uniform sampler2D colorTexture;

void main(void)
{
   // Blending colors
   vec3 baseColor = texture(colorTexture, textureUV).rgb;

   float threshold = 0.94f;
   if(baseColor.x >= threshold && baseColor.y >= threshold && baseColor.z >= threshold)
   {
	   discard;
   }

   color = spriteColor * baseColor;
}