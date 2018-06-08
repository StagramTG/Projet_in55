#version 400

uniform mat4 MVPMatrix;

layout(location=0) in vec3 position;
layout(location=1) in vec3 normals;
layout(location=2) in vec2 uvs;
layout(location=3) in vec4 weights;
layout(location=4) in ivec4 ids;

out vec2 coords0;

const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];

void main ()
{ 
	mat4 b0 = gBones[ids[0]];
	mat4 b1 = gBones[ids[1]];
	mat4 b2 = gBones[ids[2]];
	mat4 b3 = gBones[ids[3]];
	
	mat4 m0 = b0 * weights[0];
	mat4 m1 = b1 * weights[1];
	mat4 m2 = b2 * weights[2];
	mat4 m3 = b3 * weights[3];
	
	mat4 BMatrix = m0 + m1 + m2 + m3;
		  
    gl_Position = MVPMatrix * BMatrix * (vec4(position,1.0));
 
    coords0 = uvs;
}