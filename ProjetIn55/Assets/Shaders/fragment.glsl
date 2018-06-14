#version 330

uniform sampler2D texture;

in vec2 coords0;
//in vec4 we;
//in vec4 id;

out vec4 fColor;

void main ()
{ 	
	vec4 texcolor = texture2D(texture,coords0);
    fColor = texcolor;
}