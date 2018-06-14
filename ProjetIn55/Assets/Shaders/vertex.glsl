#version 330

uniform mat4 MVPMatrix;

layout(location=0) in vec3 vertex;
layout(location=1) in vec2 UV;
layout(location=2) in vec4 weight;
layout(location=3) in ivec4 ids;

const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];

out vec2 coords0;
out vec4 we;

void main ()
{

	mat4 BMatrix = gBones[ids[0]] * weight[0];
          BMatrix += gBones[ids[1]] * weight[1];
          BMatrix += gBones[ids[2]] * weight[2];
          BMatrix += gBones[ids[3]] * weight[3];
	
    gl_Position = MVPMatrix * BMatrix * (vec4(vertex,1.0));
	
	we = weight;
 
    coords0 = UV;
}