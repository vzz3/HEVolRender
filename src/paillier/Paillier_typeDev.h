#pragma once

//#include <climits>
//#include <sys/types.h>


#define USE_FIX_WIDTH_INTEGER 			1
#define PAILLIER_MODULUS_BIT_LENGTH 	256 // GPU test: 64 // Paillier test: 256 


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
#define PAILLIER_INT_BIT_LENGTH 	(PAILLIER_MODULUS_BIT_LENGTH*4)
#define PAILLIER_INT_WORD_SIZE 		BIG_INT_BIT_TO_SIZE( PAILLIER_INT_BIT_LENGTH )

#define PAILLIER_INT_STORAGE_BIT_LENGTH 	(PAILLIER_MODULUS_BIT_LENGTH*2)
#define PAILLIER_INT_STORAGE_WORD_SIZE 		BIG_INT_BIT_TO_SIZE( PAILLIER_INT_STORAGE_BIT_LENGTH )

#ifdef USE_FIX_WIDTH_INTEGER
	#include "../math/SFixBigInt.hpp"
	typedef SFixBigInt<PAILLIER_INT_WORD_SIZE> PaillierInt;
#else
	#include "../math/SArbBigInt.hpp"
	typedef SArbBigInt PaillierInt;
#endif


#define GPU_INT_TEXTURE_FORMAT			VK_FORMAT_R32G32B32A32_UINT // VK_FORMAT_R32G32B32A32_UINT // VK_FORMAT_R8G8B8A8_UINT // VK_FORMAT_R8G8B8A8_UNORM 	// one channel must fit the current BIG_INT_WORD_TYPE
#define GPU_INT_TEXTURE_WORD_COUNT		4							// words per texture
#define GPU_INT_TEXTURE_SIZE			((PAILLIER_INT_STORAGE_WORD_SIZE + (GPU_INT_TEXTURE_WORD_COUNT-1)) / GPU_INT_TEXTURE_WORD_COUNT)	// = ciel(PAILLIER_INT_WORD_SIZE / GpuVolume::bigIntWordCount); the numbers of textures required for storing PAILLIER_INT_STORAGE_WORD_SIZE words
