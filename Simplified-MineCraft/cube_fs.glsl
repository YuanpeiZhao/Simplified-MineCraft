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

const float threshold = 0.1f;

vec3 lightColor = vec3(1.0f ,1.0f, 1.0f);
vec3 lightDir = vec3(1.0f ,1.0f, 1.0f);

float circle = 5.0f;

float mode(float t, int m)
{
	return t - int(t / m) * m;
}

vec4 renderGrassCube()
{
	if(dot(Normal, vec3(0.0, 1.0, 0.0)) > 0.5f)
	{
		return vec4(0.4f, 1.5 * texture(grass_top_tex, TexCoords).g, 0.4f, 1.0f);
	}
	else if(dot(Normal, vec3(0.0, 1.0, 0.0)) < -0.5f)
	{
		return texture(dirt_tex, TexCoords);
	}
	else
	{
		return texture(grass_side_tex, TexCoords);
	}
}

vec4 renderLogCube()
{
	if(abs(dot(Normal, vec3(0.0, 1.0, 0.0))) > 0.5f)
	{
		return texture(tree_log_top_tex, TexCoords);
	}
	else
	{
		return texture(tree_log_tex, TexCoords);
	}
}

vec4 renderLeafCube()
{
	vec4 texColor = texture(tree_leaves_tex, TexCoords);
	if(texColor.a < 0.1f)
		discard;
	return texColor * vec4(0.5f, 0.5f, 0.25f, 1.0f);
}

vec4 renderStillWater()
{
	return texture(water_still_tex, vec2(TexCoords.x, TexCoords.y / 32 + time_sec / 100)) * vec4(0.0f, 0.8f, 1.0f, 0.5f);
}

vec3 sunlight(vec3 objectColor)
{
	// ambient
    float ambientStrength = 0.2;
    vec3 ambient = vec3(ambientStrength);
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    lightDir = normalize(lightDir);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    return (ambient + diffuse) * objectColor;
}

void main()
{
	vec4 objColor;
	if(abs(Type - 0.0f) < 0.5f)
		objColor = renderGrassCube();
	else if(abs(Type - 1.0f) < 0.5f)
		objColor = renderLogCube();
	else if(abs(Type - 2.0f) < 0.5f)
		objColor = renderLeafCube();
	else if(abs(Type - 3.0f) < 0.5f)
		objColor = renderStillWater();

	float t = mode(time_sec, int(circle)) / circle;
	float angle = t * 3.1415926f;
	lightDir = vec3(cos(angle), sin(angle), 0.5f);
	if(t < threshold)
		lightColor = vec3(1.0f / threshold * t);
	if(t > 1.0f - threshold)
		lightColor = vec3(1.0f / threshold * (1.0f -t));

	FragColor = vec4(sunlight(objColor.xyz), objColor.w);
} 

















