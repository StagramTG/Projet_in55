#version 330

uniform mat4 MVPMatrix;

/*
in vec3 vertex;
in vec2 UV;
in vec3 normal;
in ivec4 ids;
in vec4 weight;
*/

layout(location=0) in vec3 vertex;
layout(location=1) in vec2 UV;
layout(location=2) in vec3 normal;
layout(location=4) in ivec4 ids;
layout(location=5) in vec4 weight;

const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];

out vec2 coords0;
//out vec4 we;
//out vec4 id;

void main ()
{

	mat4 BMatrix = gBones[ids[0]] * weight[0];
          BMatrix += gBones[ids[1]] * weight[1];
          BMatrix += gBones[ids[2]] * weight[2];
          BMatrix += gBones[ids[3]] * weight[3];
	
    gl_Position = MVPMatrix * (vec4(vertex,1.0));
	
	//we = weight;
    //id = ids;
 
    coords0 = UV;
}