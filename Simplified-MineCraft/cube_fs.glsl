#version 400

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
in float Type;

out vec4 FragColor;

uniform float time_sec;

uniform sampler2D dirt_tex;
uniform sampler2D grass_top_tex;
uniform sampler2D grass_side_tex;

uniform sampler2D tree_log_tex;
uniform sampler2D tree_log_top_tex;
uniform sampler2D tree_leaves_tex;

uniform sampler2D water_still_tex;

const int GRASS = 0;
const int TREE = 1;
const int LEAF = 2;

void renderGrassCube()
{
	if(dot(Normal, vec3(0.0, 1.0, 0.0)) > 0.5f)
	{
		FragColor = vec4(0.4f, 1.5 * texture(grass_top_tex, TexCoords).g, 0.4f, 1.0f);
	}
	else if(dot(Normal, vec3(0.0, 1.0, 0.0)) < -0.5f)
	{
		FragColor = texture(dirt_tex, TexCoords);
	}
	else
	{
		FragColor = texture(grass_side_tex, TexCoords);
	}
}

void renderLogCube()
{
	if(abs(dot(Normal, vec3(0.0, 1.0, 0.0))) > 0.5f)
	{
		FragColor = texture(tree_log_top_tex, TexCoords);
	}
	else
	{
		FragColor = texture(tree_log_tex, TexCoords);
	}
}

void renderLeafCube()
{
	vec4 texColor = texture(tree_leaves_tex, TexCoords);
	if(texColor.a < 0.1f)
		discard;
	FragColor = texColor * vec4(0.5f, 0.5f, 0.25f, 1.0f);
}

void renderStillWater()
{
	FragColor = texture(water_still_tex, vec2(TexCoords.x, TexCoords.y / 32 + time_sec / 100)) * vec4(0.0f, 0.8f, 1.0f, 0.5f);
}

void main()
{
	if(abs(Type - 0.0f) < 0.5f)
		renderGrassCube();
	else if(abs(Type - 1.0f) < 0.5f)
		renderLogCube();
	else if(abs(Type - 2.0f) < 0.5f)
		renderLeafCube();
	else if(abs(Type - 3.0f) < 0.5f)
		renderStillWater();
} 

















