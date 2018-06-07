#version 400

uniform mat4 MVPMatrix;

layout(location=0) in vec3 position;
layout(location=1) in vec3 normals;
layout(location=2) in vec2 uvs;
layout(location=3) in vec4 weights;
layout(location=4) in vec4 ids;

out vec2 coords0;

const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];

void main ()
{ 
	mat4 BMatrix = gBones[ids[0]] * weights[0];
    BMatrix += gBones[ids[1]] * weights[1];
    BMatrix += gBones[ids[2]] * weights[2];
    BMatrix += gBones[ids[3]] * weights[3];
		  
    gl_Position = MVPMatrix * BMatrix * (vec4(position,1.0));
 
    coords0 = uvs;
}