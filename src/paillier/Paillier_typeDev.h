#pragma once

//#include <climits>
//#include <sys/types.h>


#define USE_FIX_WIDTH_INTEGER 					1
#define PAILLIER_MODULUS_BIT_LENGTH 			64 // GPU test: 64 // Paillier test: 256

/* ****************************************
 * *** Config. for different reder modi ***
 * ****************************************
 *
 */
#define GPU_MONTGOMERY_REDUCTION				1
#define GPU_TARGET_DOUBLE_WORD_LENGTH			1

// Why is the required integer bit length $ bitLengt(M) * 4 $ ?
// obfuscate(c) {
//		t1 = (r^M % M^2); 		=> bitLengt(M) * 2
//		t2 = t1 * c;			=> bitLengt(M) * 3
//		return t2 % M^2;		=> bitLengt(M) * 2
//}
// add(c1, c2) {
//		t1 = c1 * c2;	 		=> bitLengt(M) * 4
//		return t2 % M^2;		=> bitLengt(M) * 2
//}
#if !defined(GPU_MONTGOMERY_REDUCTION) && defined(BIG_INT_NO_MONTGOMERY_REDUCTION)
	#define PAILLIER_INT_BIT_LENGTH 			(PAILLIER_MODULUS_BIT_LENGTH*4)
#else
	#define PAILLIER_INT_BIT_LENGTH 			(PAILLIER_MODULUS_BIT_LENGTH*4)+18		// enshure that the reciprocal of the MontgomeryReducer can be calculated (modInverse ith one bit more then PAILLIER_MODULUS_BIT_LENGTH*2)
#endif
#define PAILLIER_INT_WORD_SIZE 					BIG_INT_BIT_TO_SIZE( PAILLIER_INT_BIT_LENGTH )

#define PAILLIER_INT_STORAGE_BIT_LENGTH 		(PAILLIER_MODULUS_BIT_LENGTH*2)
#define PAILLIER_INT_STORAGE_WORD_SIZE 			BIG_INT_BIT_TO_SIZE( PAILLIER_INT_STORAGE_BIT_LENGTH )

#ifdef USE_FIX_WIDTH_INTEGER
	#include "../math/SFixBigInt.hpp"
	typedef SFixBigInt<PAILLIER_INT_WORD_SIZE> PaillierInt;
#else
	#include "../math/SArbBigInt.hpp"
	typedef SArbBigInt PaillierInt;
#endif

// define Vulkan texture type that should be used as BigInteger storage format
#if _BIG_INT_WORD_LENGTH_PRESET_ == 8
	// 8bit
	#define GPU_INT_TEXTURE_FORMAT 				VK_FORMAT_R8G8B8A8_UINT
#elif _BIG_INT_WORD_LENGTH_PRESET_ == 16
	// 16bit
	#define GPU_INT_TEXTURE_FORMAT 				VK_FORMAT_R16G16B16A16_UINT
#elif _BIG_INT_WORD_LENGTH_PRESET_ == 32
	// 32bit
	#define GPU_INT_TEXTURE_FORMAT				VK_FORMAT_R32G32B32A32_UINT // VK_FORMAT_R32G32B32A32_UINT // VK_FORMAT_R8G8B8A8_UINT // VK_FORMAT_R8G8B8A8_UNORM 	// one channel must fit the current BIG_INT_WORD_TYPE
#elif _BIG_INT_WORD_LENGTH_PRESET_ == 64
	// 64bit
	#define GPU_INT_TEXTURE_FORMAT 				VK_FORMAT_R64G64B64A64_UINT
#else
	#error No Vulkan texture format is defined for a BigInteger word length preset of #_BIG_INT_WORD_LENGTH_PRESET_.
#endif

#define GPU_INT_TEXTURE_WORD_COUNT				4									// words per texture
#define GPU_INT_TEXTURE_SIZE					((PAILLIER_INT_STORAGE_WORD_SIZE + (GPU_INT_TEXTURE_WORD_COUNT-1)) / GPU_INT_TEXTURE_WORD_COUNT)	// = ciel(PAILLIER_INT_WORD_SIZE / GpuVolume::bigIntWordCount); the numbers of textures required for storing PAILLIER_INT_STORAGE_WORD_SIZE words

// define Vulkan FBO attachment texture type that should be used as BigInteger storage format
#define GPU_INT_ATTACHMENT_WORD_COUNT			GPU_INT_TEXTURE_WORD_COUNT		// words per FBO attachment texture

#ifndef GPU_TARGET_DOUBLE_WORD_LENGTH
	#define GPU_INT_ATTACHMENT_FORMAT			GPU_INT_TEXTURE_FORMAT
	#define GPU_INT_ATTACHMENT_SIZE				GPU_INT_TEXTURE_SIZE
	#define GPU_INT_ATTACHMENT_WORD_TYPE		BIG_INT_WORD_TYPE
#else
	#define GPU_INT_ATTACHMENT_SIZE				((PAILLIER_INT_STORAGE_WORD_SIZE/2 + (GPU_INT_TEXTURE_WORD_COUNT-1)) / GPU_INT_TEXTURE_WORD_COUNT)
	
	#if _BIG_INT_WORD_LENGTH_PRESET_ == 8
		#define GPU_INT_ATTACHMENT_FORMAT 		VK_FORMAT_R16G16B16A16_UINT
		#define GPU_INT_ATTACHMENT_WORD_TYPE	uint16_t
	#elif _BIG_INT_WORD_LENGTH_PRESET_ == 16
		#define GPU_INT_ATTACHMENT_FORMAT 		VK_FORMAT_R32G32B32A32_UINT
		#define GPU_INT_ATTACHMENT_WORD_TYPE	uint32_t
	#elif _BIG_INT_WORD_LENGTH_PRESET_ == 32
		#define GPU_INT_ATTACHMENT_FORMAT		VK_FORMAT_R64G64B64A64_UINT
		#define GPU_INT_ATTACHMENT_WORD_TYPE	uint64_t
	#else
		#error No Vulkan texture format is defined for GPU_TARGET_DOUBLE_WORD_LENGTH and a BigInteger word length preset of more then 32.
	#endif
#endif
	
	

// define Vulkan uvec4 types for big integer uniforms
#define GPU_INT_UVEC4_SIZE						((PAILLIER_INT_WORD_SIZE + (4-1)) / 4)
#define GPU_INT_UVEC4_STORAGE_SIZE				((PAILLIER_INT_STORAGE_WORD_SIZE + (4-1)) / 4)


// --- MACROS ---
#define PAILLIER_INT_TO_STORAGE_UVEC4(src, dst) { 									\
	for(uint texIndex = 0; texIndex < GPU_INT_UVEC4_STORAGE_SIZE; texIndex++) { 	\
		for(uint channelIndex = 0; channelIndex < 4 && (texIndex*4 + channelIndex) < PAILLIER_INT_STORAGE_WORD_SIZE; channelIndex++) { 	\
			assert( texIndex*4 + channelIndex < PAILLIER_INT_STORAGE_WORD_SIZE );	\
			dst[texIndex][channelIndex] = src[texIndex*4 + channelIndex]; 			\
		} 																			\
	} 																				\
}

#define PAILLIER_INT_TO_UVEC4(src, dst) { 											\
	for(uint texIndex = 0; texIndex < GPU_INT_UVEC4_SIZE; texIndex++) { 			\
		for(uint channelIndex = 0; channelIndex < 4 && (texIndex*4 + channelIndex) < PAILLIER_INT_WORD_SIZE; channelIndex++) { 	\
			assert( texIndex*4 + channelIndex < PAILLIER_INT_WORD_SIZE );			\
			dst[texIndex][channelIndex] = src[texIndex*4 + channelIndex]; 			\
		} 																			\
	} 																				\
}
