#version 330

uniform sampler2D texture;

in vec2 coords0;
in vec4 we;

out vec4 fColor;

void main ()
{ 	
	vec4 texcolor = texture2D(texture,coords0);
	//vec4 texcolor = vec4(we.xyz,1.0);
	
    fColor = texcolor;
}