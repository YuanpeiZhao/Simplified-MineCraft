#version 400     

uniform mat4 armPVM;
uniform mat4 armM;
uniform mat4 PVM;
uniform mat4 M;
uniform mat4 lightSpaceMatrix;

layout (location = 0) in vec3 pos_attrib;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float type;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out float Type;
out vec4 FragPosLightSpace;

void main(void)
{
	if(abs(type - 7.0f) < 0.5f)
	{
		FragPos = vec3(armM * vec4(pos_attrib, 1.0));
		Normal = mat3(transpose(inverse(armM))) * aNormal;  
		TexCoords = aTexCoords;
		Type = type;
		FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

		//Compute clip-space vertex position
		gl_Position = armPVM*vec4(pos_attrib, 1.0);     //w = 1 becase this is a point
	}
	else
	{
		FragPos = vec3(M * vec4(pos_attrib, 1.0));
		Normal = mat3(transpose(inverse(M))) * aNormal;  
		TexCoords = aTexCoords;
		Type = type;
		FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

		//Compute clip-space vertex position
		gl_Position = PVM*vec4(pos_attrib, 1.0);     //w = 1 becase this is a point
	}
}
