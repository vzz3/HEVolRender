#version 450
#extension GL_GOOGLE_include_directive : require
#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require
#extension GL_ARB_gpu_shader_int64 : require

// DO NOT FORGET:
//	cd /Users/sebastian/Documents/_Eigene_Dokumente/TU/CsProject/prototypeVulkan/build
//	glslc -o shaders/encryptedXRay.frag.spv ../res/shaders/encryptedXRay.frag
//	MoltenVKShaderConverter -si shaders/encryptedXRay.frag.spv -mo shaders/encryptedXRay.frag.msl -l

#include "math/bigInt_defs.h.glsl"
#include "math/BigIntUtil.glsl"
#include "math/UFixBigInt.glsl"
#include "lib/EncryptedVolumeUniformBufferObject.glsl"
#ifdef GPU_MONTGOMERY_REDUCTION
	#include "math/MontgomeryReducer.glsl"
#endif

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
layout (location = 0) out GPU_INT_ATTACHMENT_FORMAT outFragColor[GPU_INT_ATTACHMENT_SIZE];

void main()
{
	uvec4[GPU_INT_UVEC4_STORAGE_SIZE] pkM2FromUniform = volumeInfo.modulusSquared;
	FIX_BIG_INT_VALUE pkM2 = UFixBigInt_fromUniform(pkM2FromUniform);

	#ifdef GPU_MONTGOMERY_REDUCTION
		uint montReducerBitsFromUniform = volumeInfo.montReducerBits;
		uvec4[GPU_INT_UVEC4_SIZE] montMaskFromUniform = volumeInfo.montMask;
		uvec4[GPU_INT_UVEC4_SIZE] montFactorFromUniform = volumeInfo.montFactor;

		MontgomeryReducer_Data montData;
		montData.reducerBits = montReducerBitsFromUniform;
		montData.modulus = pkM2;
		montData.mask = UFixBigInt_fromUniform(montMaskFromUniform);
		montData.factor = UFixBigInt_fromUniform(montFactorFromUniform);
		montData.reducerWords = BIG_INT_BIT_TO_SIZE(montData.reducerBits);
	#endif

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
	FIX_BIG_INT_VALUE sum;
	#ifdef GPU_MONTGOMERY_REDUCTION
		uvec4[GPU_INT_UVEC4_STORAGE_SIZE] montConvertedEncZeroFromUniform = volumeInfo.montConvertedEncZero;
		sum = UFixBigInt_fromUniform(montConvertedEncZeroFromUniform);
	#else
		UFixBigInt_setOne(sum); // Paillier encrypt(): {modulus * plaintext + PaillierInt(1)) % _modulusSquared} => 1 is a valide encryption of 0
	#endif
	//float sampleCount = 0.0;
	while (d < rayLength) {
		samplePos = inPos + (direction * d);
		//float density = texture(samplerVolume, samplePos).x;
		FIX_BIG_INT_VALUE density = UFixBigInt_fromVolume(samplerVolumes, texturesVolumes, samplePos);
		//FIX_BIG_INT_VALUE density = UFixBigInt_fromVolume(samplerVolumes, texturesVolumes, ivec3(gl_FragCoord.x, gl_FragCoord.y, 10));

		#ifdef GPU_MONTGOMERY_REDUCTION
			sum = MontgomeryReducer_multiply(montData, sum, density);
		#else
			//sum += density;
			FIX_BIG_INT_VALUE heProduct = UFixBigInt_mul(sum, density);
			FIX_BIG_INT_VALUE heM2 = pkM2;
			sum = UFixBigInt_mod(heProduct, heM2); // Paillier add(): {ciphertext1 * ciphertext2 % _modulusSquared}
			//sum[0] = 127;
		#endif

		//sampleCount++;
		d += raySamplerDist;
	}

	//sum = UFixBigInt_add(sum, pkM2);

	//sum[0] = 127;
	//float avg = sum / volumeInfo.volumeDepth * 2.0 ;//sampleCount;
	//outFragColor = vec4(avg,avg,avg,1);
	outFragColor = UFixBigInt_toColorOut(sum);
}
