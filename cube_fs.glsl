#version 400

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
	if(dot(Normal, vec3(0.0, 1.0, 0.0)) > 0.5f)
	{
		FragColor = vec4(0.4f, 1.5 * texture(Texture1, TexCoords).g, 0.4f, 1.0f);
	}
	else if(dot(Normal, vec3(0.0, 1.0, 0.0)) < -0.5f)
	{
		FragColor = texture(Texture0, TexCoords);
	}
	else
	{
		FragColor = texture(Texture2, TexCoords);
	}
} 

















