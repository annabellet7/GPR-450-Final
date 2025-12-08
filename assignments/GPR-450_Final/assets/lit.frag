#version 450

out vec4 FragColor;

in Surface 
{
	vec3 WorldPos;
	vec3 WorldNormal;
	vec2 TexCoord;
	flat ivec4 BoneIDs;
	vec4 Weights;
}fs_in;

uniform sampler2D uMainTex;
uniform int gDisplayBoneIndex;

uniform vec3 uEyePos;
uniform vec3 uLightDir = vec3(0.0, -1.0, 0.0);
uniform vec3 uLightColor = vec3(1.0);
uniform vec3 uAmbientColor = vec3(0.3, 0.4, 0.46);

struct Material
{
	float Ka; //ambient coefficient
	float Kd; //diffuse coefficient
	float Ks; //specular coefficient
	float Shininess;
};
uniform Material uMaterial;

void main()
{
	vec3 norm = normalize(fs_in.WorldNormal);
	vec3 toLight = -uLightDir;
	float diffuseFactor = max(dot(norm, toLight), 0.0);

	vec3 toEye = normalize(uEyePos - fs_in.WorldPos);
	vec3 h = normalize(toLight + toEye);
	float specularFactor = pow(max(dot(norm,h),0.0),uMaterial.Shininess); 

	vec3 lightColor = (diffuseFactor * uMaterial.Kd + specularFactor * uMaterial.Ks) * uLightColor;
	lightColor += uAmbientColor * uMaterial.Ka;
	vec3 objColor = texture(uMainTex, fs_in.TexCoord).rgb;

	bool found = false;
	for (int i = 0 ; i < 4 ; i++) 
	{
        if (fs_in.BoneIDs[i] == gDisplayBoneIndex) 
		{
           if (fs_in.Weights[i] >= 0.7) 
		   {
               FragColor = vec4(1.0, 0.0, 0.0, 0.0) * fs_in.Weights[i];
           } 
		   else if (fs_in.Weights[i] >= 0.4 && fs_in.Weights[i] <= 0.6) 
		   {
               FragColor = vec4(0.0, 1.0, 0.0, 0.0) * fs_in.Weights[i];
           } 
		   else if (fs_in.Weights[i] >= 0.1) 
		   {
               FragColor = vec4(1.0, 1.0, 0.0, 0.0) * fs_in.Weights[i];
           }
           found = true;
           break;
        }
    }

    if (!found ) {
         FragColor = vec4(objColor * lightColor, 1.0);
    }



	//FragColor = vec4(objColor * lightColor, 1.0);
}