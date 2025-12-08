#version 450

layout (location = 0) in vec3 vPos; 
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

uniform mat4 uModel;
uniform mat4 uViewProjection;

uniform mat4 gBones[100];

out Surface 
{
	vec3 WorldPos;
	vec3 WorldNormal;
	vec2 TexCoord;
}vs_out;

void main()
{
	vs_out.WorldPos = vec3(uModel * vec4(vPos, 1.0));
	vs_out.WorldNormal = transpose(inverse(mat3(uModel))) * vNormal;
	vs_out.TexCoord = vTexCoord;

	mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0] + gBones[BoneIDs[1]] * Weights[1] +  gBones[BoneIDs[2]] * Weights[2] +  gBones[BoneIDs[3]] * Weights[3];

	vec4 pos = BoneTransform * vec4(vPos, 1.0);
	gl_Position = uViewProjection * uModel * pos;
}