#version 400
out vec4 fragcolor;
in vec2 TexCoord;
in float Type;

uniform sampler2D  ui_tex;
uniform sampler2D select_tex;
void main(void){
	if(Type == 0.0f)
		fragcolor = texture2D( ui_tex, TexCoord);
	else{
		fragcolor = texture2D(select_tex, TexCoord);
	}

}