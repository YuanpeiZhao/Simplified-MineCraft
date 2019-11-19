#version 400
uniform mat4 PVM;

in vec3 pos_attrib;

void main(void){
	gl_Position = PVM * vec4(pos_attrib, 1.0f);
}