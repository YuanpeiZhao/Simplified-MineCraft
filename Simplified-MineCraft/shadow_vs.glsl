#version 400            
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float type;

out vec2 TexCoords;
out float Type;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
	TexCoords = aTexCoords;
	Type = type;
    gl_Position = lightSpaceMatrix * model * vec4(position, 1.0f);
}