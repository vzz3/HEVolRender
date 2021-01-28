#version 450

// DO NOT FORGET:
//	cd /Users/sebastian/Documents/_Eigene_Dokumente/TU/CsProject/prototypeVulkan/build
//	glslc -o shaders/encryptedXRay.frag.spv ../res/shaders/encryptedXRay.frag
//	MoltenVKShaderConverter -si shaders/encryptedXRay.frag.spv -mo shaders/encryptedXRay.frag.msl -l

#include "math/bigInt_defs.h.glsl"
#include "math/BigIntUtil.glsl"
#include "math/UFixBigInt.glsl"
#include "lib/EncryptedVolumeUniformBufferObject.glsl"

layout(binding = 1) uniform uboEncVolume {
	EncryptedVolumeUniformBufferObject volumeInfo;
};

layout (binding = 2) uniform sampler samplerCubePos;
layout (binding = 3) uniform texture2D texturesCubePos[2];
// http://kylehalladay.com/blog/tutorial/vulkan/2018/01/28/Textue-Arrays-Vulkan.html
//layout (binding = 2) uniform sampler3D samplerVolume;
layout (binding = 4) uniform sampler samplerVolumes;
layout (binding = 5) uniform utexture3D texturesVolumes[GPU_INT_TEXTURE_SIZE];

layout (location = 0) in vec2 inUV;

//layout (location = 0) out vec4 outFragColor;
layout (location = 0) out uvec4 outFragColor[GPU_INT_TEXTURE_SIZE];

void main()
{
	uvec4[GPU_INT_UVEC4_STORAGE_SIZE] pkM2fromUniform = volumeInfo.modulusSquared;
	FIX_BIG_INT_VALUE pkM2 = UFixBigInt_fromUniform(pkM2fromUniform);

	//outFragColor = texture(samplerColor, inUV);

  	vec3 inPos  = texture(sampler2D(texturesCubePos[0], samplerCubePos), inUV).xyz;
	vec3 outPos = texture(sampler2D(texturesCubePos[1], samplerCubePos), inUV).xyz;

	//outFragColor = vec4(outPos, 1.0f);

	float raySamplerDist = (1.0/volumeInfo.volumeDepth);

	float d = 0.0;
	vec3 samplePos;
	vec3 direction =  outPos - inPos;
	float rayLength = length(direction);
	direction = normalize(direction);
	//float sum = 0.0;
	FIX_BIG_INT_VALUE sum; UFixBigInt_setOne(sum); // Paillier encrypt(): {modulus * plaintext + PaillierInt(1)) % _modulusSquared} => 1 is a valide encryption of 0
	//float sampleCount = 0.0;
	while (d < rayLength) {
		samplePos = inPos + (direction * d);
		//float density = texture(samplerVolume, samplePos).x;
		FIX_BIG_INT_VALUE density = UFixBigInt_fromVolume(samplerVolumes, texturesVolumes, samplePos);
		//FIX_BIG_INT_VALUE density = UFixBigInt_fromVolume(samplerVolumes, texturesVolumes, ivec3(gl_FragCoord.x, gl_FragCoord.y, 10));

		//sum += density;
		FIX_BIG_INT_VALUE heProduct = UFixBigInt_mul(sum, density);
		FIX_BIG_INT_VALUE heM = pkM2;
		sum = UFixBigInt_mod(heProduct, heM); // Paillier add(): {ciphertext1 * ciphertext2 % _modulusSquared}
		//sum[0] = 127;

		//sampleCount++;
		d += raySamplerDist;
	}

	//sum = UFixBigInt_add(sum, pkM2);

	//sum[0] = 127;
	//float avg = sum / volumeInfo.volumeDepth * 2.0 ;//sampleCount;
	//outFragColor = vec4(avg,avg,avg,1);
	outFragColor = UFixBigInt_toColorOut(sum);
}
