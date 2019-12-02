#version 400

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
in float Type;
in vec4 FragPosLightSpace;

out vec4 FragColor;

uniform float time_sec;

uniform sampler2D dirt_tex;
uniform sampler2D grass_top_tex;
uniform sampler2D grass_side_tex;

uniform sampler2D tree_log_tex;
uniform sampler2D tree_log_top_tex;
uniform sampler2D tree_leaves_tex;

uniform sampler2D water_still_tex;
uniform sampler2D brick_tex;

uniform sampler2D shadowMap;

uniform sampler2D arm_tex;

const float GRASS = 0.0f;
const float TREE = 1.0f;
const float LEAF = 2.0f;
const float WATER = 3.0f;
const float SAND = 4.0f;
const float BRICK = 5.0f;
const float LIGHT = 6.0f;
const float ARM = 7.0f;

const float threshold = 0.1f;

vec3 lightColor = vec3(1.0f ,1.0f, 1.0f);
vec3 lightDir = vec3(1.0f ,1.0f, 1.0f);

uniform float cycle_time_sec;

float mode(float t, int m)
{
	return t - int(t / m) * m;
}

vec4 renderGrassCube()
{
	if(dot(Normal, vec3(0.0, 1.0, 0.0)) > 0.5f)
	{
		//return texture(shadowMap, TexCoords);
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

vec4 renderSandPlane()
{
	return texture(dirt_tex, TexCoords);
}

vec4 renderBrick()
{
	return texture(brick_tex, TexCoords);
}

vec4 renderLight()
{
	return vec4(1.0f, 1.0f, 0.7f, 1.0f);
}

vec4 renderArm()
{
	return texture(arm_tex, vec2(TexCoords.x, TexCoords.y * 2.7f));
}

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal)
{
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;

	if(projCoords.z > 1.0)
        return 0.0f;

	float bias = max(0.004 * (1.0 - dot(normal, lightDir)), 0.0004);
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 9.0;
	
	return shadow;
}

vec3 sunlight(vec3 objectColor)
{
	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = vec3(ambientStrength);
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    lightDir = normalize(lightDir);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
	float shadow = ShadowCalculation(FragPosLightSpace, norm);
    return (ambient + (1.0f - shadow) * diffuse) * objectColor;
}

vec3 CalcPointLight(vec3 lightPos)
{
    vec3 pointLightDir = normalize(lightPos - FragPos);
    float diff = max(dot(Normal, pointLightDir), 0.0);

    float dis = length(lightPos - FragPos);
    float attenuation = 0.7f / (0.0f + 0.1f * dis + 
                 0.7f * (dis * dis));    

    vec3 ambient  = vec3(1.0f, 1.0f, 0.7f)  * 0.4f;
    vec3 diffuse  = vec3(1.0f, 1.0f, 0.7f)  * diff * 0.2f;

    ambient  *= attenuation;
    diffuse  *= attenuation;

    return (ambient + diffuse);
}

void main()
{
	vec4 objColor;
	if(abs(Type - GRASS) < 0.5f)
		objColor = renderGrassCube();
	else if(abs(Type - TREE) < 0.5f)
		objColor = renderLogCube();
	else if(abs(Type - LEAF) < 0.5f)
		objColor = renderLeafCube();
	else if(abs(Type - WATER) < 0.5f)
		objColor = renderStillWater();
	else if(abs(Type - SAND) < 0.5f)
		objColor = renderSandPlane();
	else if(abs(Type - BRICK) < 0.5f)
		objColor = renderBrick();
	else if(abs(Type - LIGHT) < 0.5f)
		objColor = renderLight();
	else if(abs(Type - ARM) < 0.5f)
		objColor = renderArm();

	if(abs(Type - LIGHT) < 0.5f)
	{
		FragColor = objColor;
	}
	else
	{
		float t = mode(time_sec, int(cycle_time_sec)) / cycle_time_sec;
		float angle = t * 3.1415926f;
		lightDir = vec3(cos(angle), sin(angle), 0.5f);
		if(t < threshold)
			lightColor = vec3(1.0f / threshold * t);
		if(t > 1.0f - threshold)
			lightColor = vec3(1.0f / threshold * (1.0f -t));

		FragColor = vec4(sunlight(objColor.xyz), objColor.w);

		FragColor += vec4(CalcPointLight(vec3(0.0f, 2.0f, 4.0f)), 0.0f);
		FragColor += vec4(CalcPointLight(vec3(0.0f, 2.0f, 0.0f)), 0.0f);
		FragColor += vec4(CalcPointLight(vec3(0.0f, 2.0f, -4.0f)), 0.0f);
		FragColor += vec4(CalcPointLight(vec3(4.0f, 2.0f, 0.0f)), 0.0f);
		FragColor += vec4(CalcPointLight(vec3(4.0f, 2.0f, 4.0f)), 0.0f);
		FragColor += vec4(CalcPointLight(vec3(4.0f, 2.0f, -4.0f)), 0.0f);
		FragColor += vec4(CalcPointLight(vec3(0.0f, 2.0f, 8.0f)), 0.0f);
		FragColor += vec4(CalcPointLight(vec3(0.0f, 2.0f, -8.0f)), 0.0f);
		FragColor += vec4(CalcPointLight(vec3(4.0f, 2.0f, 8.0f)), 0.0f);
		FragColor += vec4(CalcPointLight(vec3(4.0f, 2.0f, -8.0f)), 0.0f);
	}
} 

















