#version 400
out vec4 fragcolor;

in vec2 TexCoords;
uniform sampler2D arm_tex;

void main(void){
	fragcolor = texture(arm_tex, vec2(TexCoords.x, TexCoords.y * 2.7));
	//fragcolor = vec4(0.5f);
}