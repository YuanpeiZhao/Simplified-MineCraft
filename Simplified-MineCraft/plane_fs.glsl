#version 400

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D dirt_tex;
uniform sampler2D depthMap;

void main()
{
	//FragColor = texture(dirt_tex, TexCoords);
	float depthValue = texture(depthMap, TexCoords).r;
	FragColor = vec4(vec3(depthValue), 1.0);
} 

















