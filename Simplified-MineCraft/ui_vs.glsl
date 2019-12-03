#version 400
uniform mat4 T;
uniform mat4 S;
layout(location = 0) in vec3 pos_attrib;
layout(location = 1) in vec2 tex_coord;
layout(location = 2) in float type;

out float Type;
out vec2 TexCoord;

void main(void){
	
	Type = type;
	TexCoord = tex_coord;
	
	if(type == 0.0f){
		gl_Position = S * vec4(pos_attrib, 1.0f);
	}
	else{
		gl_Position = T * S * vec4(pos_attrib, 1.0f);
	}
}