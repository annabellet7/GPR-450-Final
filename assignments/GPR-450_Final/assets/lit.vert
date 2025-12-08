#version 450

layout (location = 0) in vec3 vPos; 
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in ivec4 vBoneIDs;
layout (location = 4) in vec4 vWeights;

uniform mat4 uModel;
uniform mat4 uViewProjection;

uniform mat4 gBones[100];

out Surface 
{
	vec3 WorldPos;
	vec3 WorldNormal;
	vec2 TexCoord;
	flat ivec4 BoneIDs;
	vec4 Weights;
}vs_out;

void main()
{
	vs_out.WorldPos = vec3(uModel * vec4(vPos, 1.0));
	vs_out.WorldNormal = transpose(inverse(mat3(uModel))) * vNormal;
	vs_out.TexCoord = vTexCoord;

	mat4 BoneTransform = gBones[vBoneIDs[0]] * vWeights[0] + gBones[vBoneIDs[1]] * vWeights[1] +  gBones[vBoneIDs[2]] * vWeights[2] +  gBones[vBoneIDs[3]] * vWeights[3];

//	vec4 pos = BoneTransform * vec4(vPos, 1.0);
//	gl_Position = uViewProjection * uModel * pos;
	gl_Position = uViewProjection * uModel * vec4(vPos, 1.0);
}