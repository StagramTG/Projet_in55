#version 400

in vec2 coords0;

out vec4 fColor;

uniform sampler2D texture;

void main()
{
     vec4 texcolor = texture2D(texture,coords0);
     fColor = texcolor;
}