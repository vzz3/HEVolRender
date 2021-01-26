#version 450
#extension GL_GOOGLE_include_directive : require

// DO NOT FORGET:
//	cd /Users/sebastian/Documents/_Eigene_Dokumente/TU/CsProject/prototypeVulkan/build
//	glslc -o shaders/bigIntTest.frag.spv ../res/shaders/bigIntTest.frag
//	MoltenVKShaderConverter -si shaders/bigIntTest.frag.spv -mo shaders/bigIntTest.frag.msl -l


//#include "lib/VolumeUniformBufferObject.glsl"
#include "math/bigInt_defs.h.glsl"
#include "math/BigIntUtil.glsl"
#include "math/UFixBigInt.glsl"
#include "../../src/rendering/test/BigIntGpuTestOperation_types.hpp"

layout(binding = 1) uniform uboBigIntTest {
	uint testOperationType;
};

// http://kylehalladay.com/blog/tutorial/vulkan/2018/01/28/Textue-Arrays-Vulkan.html
//layout (binding = 2) uniform sampler3D samplerVolume;


layout (binding = 3) uniform sampler samplerVolumes;
//layout (binding = 4) uniform utexture3D texturesVolumes[BIG_INT_BIT_TO_SIZE( (64*2) )];
layout (binding = 4) uniform utexture3D texturesVolumes[GPU_INT_TEXTURE_SIZE];


layout (location = 0) in vec2 inUV;

layout (location = 0) out uvec4 outFragColor[GPU_INT_TEXTURE_SIZE];

void main() {
	// inizialize all output variables
	//for(uint i=0; i<4; i++) {
	//	outFragColor[i] = uvec4(0,0,0,0);
	//}

	// working texture() example (pos coordinates are normalized floats)
	//outFragColor[0] = texture(usampler3D(texturesVolumes[0], samplerVolumes), vec3(inUV, 0.5f));

	// working texelFetch() example (pos coordinates are absolute integers)
	//outFragColor[0] = texelFetch(usampler3D(texturesVolumes[0], samplerVolumes), ivec3(gl_FragCoord.xy, 0), 0);

	// simple copy
	//for(uint i=0; i<GPU_INT_TEXTURE_SIZE; i++) {
	//	outFragColor[i] = texelFetch(usampler3D(texturesVolumes[i], samplerVolumes), ivec3(gl_FragCoord.xy, 0), 0);
	//}


	FIX_BIG_INT_VALUE ufBigIntRes;
	FIX_BIG_INT_VALUE ufBigIntA = UFixBigInt_fromVolume(samplerVolumes, texturesVolumes, ivec3(0, gl_FragCoord.y, 0));
	FIX_BIG_INT_VALUE ufBigIntB = UFixBigInt_fromVolume(samplerVolumes, texturesVolumes, ivec3(1, gl_FragCoord.y, 0));

	switch (testOperationType) {
		/* ---------- comparisons ---------- */
		case BIG_INT_GPU_TEST_OPERATION_lessThan: // <
			UFixBigInt_lessThan(ufBigIntA, ufBigIntB) ? UFixBigInt_setOne(ufBigIntRes) : UFixBigInt_setZero(ufBigIntRes);
			break;
		case BIG_INT_GPU_TEST_OPERATION_lessThanOrEqualTo: // <=
			UFixBigInt_lessThanOrEqualTo(ufBigIntA, ufBigIntB) ? UFixBigInt_setOne(ufBigIntRes) : UFixBigInt_setZero(ufBigIntRes);
			break;
		case BIG_INT_GPU_TEST_OPERATION_greaterThan: // >
			UFixBigInt_greaterThan(ufBigIntA, ufBigIntB) ? UFixBigInt_setOne(ufBigIntRes) : UFixBigInt_setZero(ufBigIntRes);
			break;
		case BIG_INT_GPU_TEST_OPERATION_greaterThanOrEqualTo: // >=
			UFixBigInt_greaterThanOrEqualTo(ufBigIntA, ufBigIntB) ? UFixBigInt_setOne(ufBigIntRes) : UFixBigInt_setZero(ufBigIntRes);
			break;
		case BIG_INT_GPU_TEST_OPERATION_equalTo: // ==
			UFixBigInt_equalTo(ufBigIntA, ufBigIntB) ? UFixBigInt_setOne(ufBigIntRes) : UFixBigInt_setZero(ufBigIntRes);
			break;
		case BIG_INT_GPU_TEST_OPERATION_notEqualTo: // !=
			UFixBigInt_notEqualTo(ufBigIntA, ufBigIntB) ? UFixBigInt_setOne(ufBigIntRes) : UFixBigInt_setZero(ufBigIntRes);
			break;

		case BIG_INT_GPU_TEST_OPERATION_shiftLeft:
			ufBigIntRes = UFixBigInt_rcl(ufBigIntA, ufBigIntB[0]);
			break;
		case BIG_INT_GPU_TEST_OPERATION_shiftRight:
			ufBigIntRes = UFixBigInt_rcr(ufBigIntA, ufBigIntB[0]);
			break;

		case BIG_INT_GPU_TEST_OPERATION_add:
			ufBigIntRes = UFixBigInt_add(ufBigIntA, ufBigIntB);
			break;
		case BIG_INT_GPU_TEST_OPERATION_sub:
			ufBigIntRes = UFixBigInt_sub(ufBigIntA, ufBigIntB);
			break;
		case BIG_INT_GPU_TEST_OPERATION_mul:
			ufBigIntRes = UFixBigInt_mul(ufBigIntA, ufBigIntB);
			break;
		case BIG_INT_GPU_TEST_OPERATION_div:
			ufBigIntRes = UFixBigInt_div(ufBigIntA, ufBigIntB);
			break;
		case BIG_INT_GPU_TEST_OPERATION_mod:
			ufBigIntRes = UFixBigInt_mod(ufBigIntA, ufBigIntB);
			break;

		case BIG_INT_GPU_TEST_OPERATION_copy:
		    //result = cubicOut();
			ufBigIntRes = ufBigIntA;
		    break;
		default:
			ufBigIntRes = ufBigIntA; //UFixBigInt_fromVolume(samplerVolumes, texturesVolumes, ivec3(gl_FragCoord.xy, 0));
	}

	outFragColor = UFixBigInt_toColorOut(ufBigIntRes);
}
