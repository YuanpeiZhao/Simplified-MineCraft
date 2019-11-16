#version 400

out vec4 fragcolor;           
in vec3 TexCoords;

uniform float time_sec;

uniform samplerCube cubemap01;
uniform samplerCube cubemap02;
uniform samplerCube cubemap03;
uniform samplerCube cubemap04;
uniform samplerCube cubemap05;
uniform samplerCube cubemap06;
uniform samplerCube cubemap07;
uniform samplerCube cubemap08;
uniform samplerCube cubemap09;
uniform samplerCube cubemap10;
uniform samplerCube cubemap11;
uniform samplerCube cubemap12;
uniform samplerCube cubemap13;
uniform samplerCube cubemap14;
uniform samplerCube cubemap15;

uniform float cycle_time_sec;

float mode(float t, int m)
{
	return t - int(t / m) * m;
}
     
void main(void)
{   
   float t = mode(time_sec, int(cycle_time_sec)) / cycle_time_sec * 15.0f;

   if(t < 1.0f)
   {
		fragcolor = mix(texture(cubemap01, TexCoords), texture(cubemap02, TexCoords), t);
   }
   else if(t < 2.0f)
   {
		fragcolor = mix(texture(cubemap02, TexCoords), texture(cubemap03, TexCoords), t - 1.0f);
   }
   else if(t < 3.0f)
   {
		fragcolor = mix(texture(cubemap03, TexCoords), texture(cubemap04, TexCoords), t - 2.0f);
   }
   else if(t < 4.0f)
   {
		fragcolor = mix(texture(cubemap04, TexCoords), texture(cubemap05, TexCoords), t - 3.0f);
   }
   else if(t < 5.0f)
   {
		fragcolor = mix(texture(cubemap05, TexCoords), texture(cubemap06, TexCoords), t - 4.0f);
   }
      else if(t < 6.0f)
   {
		fragcolor = mix(texture(cubemap06, TexCoords), texture(cubemap07, TexCoords), t - 5.0f);
   }
      else if(t < 7.0f)
   {
		fragcolor = mix(texture(cubemap07, TexCoords), texture(cubemap08, TexCoords), t - 6.0f);
   }
      else if(t < 8.0f)
   {
		fragcolor = mix(texture(cubemap08, TexCoords), texture(cubemap09, TexCoords), t - 7.0f);
   }
      else if(t < 9.0f)
   {
		fragcolor = mix(texture(cubemap09, TexCoords), texture(cubemap10, TexCoords), t - 8.0f);
   }
      else if(t < 10.0f)
   {
		fragcolor = mix(texture(cubemap10, TexCoords), texture(cubemap11, TexCoords), t - 9.0f);
   }
      else if(t < 11.0f)
   {
		fragcolor = mix(texture(cubemap11, TexCoords), texture(cubemap12, TexCoords), t - 10.0f);
   }
      else if(t < 12.0f)
   {
		fragcolor = mix(texture(cubemap12, TexCoords), texture(cubemap13, TexCoords), t - 11.0f);
   }
      else if(t < 13.0f)
   {
		fragcolor = mix(texture(cubemap13, TexCoords), texture(cubemap14, TexCoords), t - 12.0f);
   }
      else if(t < 14.0f)
   {
		fragcolor = mix(texture(cubemap14, TexCoords), texture(cubemap15, TexCoords), t - 13.0f);
   }
      else
   {
		fragcolor = mix(texture(cubemap15, TexCoords), texture(cubemap01, TexCoords), t - 14.0f);
   }
}




















