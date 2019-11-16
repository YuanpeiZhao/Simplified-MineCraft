#version 400

const int LEAF = 2;

uniform sampler2D tree_leaves_tex;

in vec2 TexCoords;
in float Type;

void main()
{  
	if(Type == LEAF)
	{
		vec4 texColor = texture(tree_leaves_tex, TexCoords);
		if(texColor.a < 0.1f)
			discard;
	}
}