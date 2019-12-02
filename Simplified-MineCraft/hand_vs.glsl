#version 400
uniform mat4 PVM;

layout (location = 0) in vec3 pos_attrib;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main(void){

	TexCoords = aTexCoords;
	gl_Position = PVM * vec4(pos_attrib, 1.0f);
}