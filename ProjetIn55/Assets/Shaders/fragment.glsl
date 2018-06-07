#version 400

uniform mat4 MMatrix;
uniform mat4 VPMatrix;

in vec2 coords0;

out vec4 fColor;

uniform sampler2D texUnit;

void main()
{
     vec4 texcolor = texture2D(texUnit,coords0);
 
     fColor = texcolor;
}