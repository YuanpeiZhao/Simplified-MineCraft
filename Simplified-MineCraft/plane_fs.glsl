#version 400

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D dirt_tex;

void main()
{
	FragColor = texture(dirt_tex, TexCoords);
} 

















