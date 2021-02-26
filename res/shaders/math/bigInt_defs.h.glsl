//#include "../../../src/math/BigInt_wordDef.h"

/* *************************************
 * ***      BigInt  dependencies     ***
 * *************************************
 *
 * see src/math/BigInt_wordDef.h
 */

// BigInt
#define _BIG_INT_WORD_LENGTH_PRESET_ 			16

#define BIG_INT_WORD_COUNT_TYPE 				uint

#if _BIG_INT_WORD_LENGTH_PRESET_ == 8
// 8bit
	#define BIG_INT_WORD_TYPE 					uint
	#define BIG_INT_WORD_LOW_BIT_MASK 			BIG_INT_WORD_TYPE(0xFu)
	#define BIG_INT_WORD_ALL_BIT_MASK 			BIG_INT_WORD_TYPE(0xFFu)
	#define BIG_INT_BITS_PER_WORD 				8
	#define BIG_INT_LESS_BITS_THEN_WORD_TYPE 	1		// set this if the type in BIG_INT_WORD_TYPE has more bits then BIG_INT_BITS_PER_WORD
#elif _BIG_INT_WORD_LENGTH_PRESET_ == 16
	// 16bit
	#define BIG_INT_WORD_TYPE 					uint
	#define BIG_INT_WORD_LOW_BIT_MASK 			BIG_INT_WORD_TYPE(0xFF)
	#define BIG_INT_WORD_ALL_BIT_MASK 			BIG_INT_WORD_TYPE(0xFFFFu)
	#define BIG_INT_BITS_PER_WORD 				16
	#define BIG_INT_LESS_BITS_THEN_WORD_TYPE 	1
#elif _BIG_INT_WORD_LENGTH_PRESET_ == 32
	// 32bit
	#define BIG_INT_WORD_TYPE 					uint
	#define BIG_INT_WORD_LOW_BIT_MASK 			BIG_INT_WORD_TYPE(0xFFFFu)
	#define BIG_INT_WORD_ALL_BIT_MASK 			BIG_INT_WORD_TYPE(0xFFFFFFFFu)
	#define BIG_INT_BITS_PER_WORD 				32
#else
	#error A BigInteger word length preset of #_BIG_INT_WORD_LENGTH_PRESET_ is not supported.
#endif

// --- --- ---


// Some importend values for a Word
#define BIG_INT_WORD_HIGH_BIT_MASK 				(BIG_INT_WORD_TYPE(~BIG_INT_WORD_LOW_BIT_MASK) & BIG_INT_WORD_ALL_BIT_MASK)
#define BIG_INT_WORD_MAX_VALUE 					(BIG_INT_WORD_TYPE(-1))	// works only for 32 bit variables (64bit leteral in c++: -1ll)
#define BIG_INT_WORD_HIGHEST_BIT 				(BIG_INT_WORD_TYPE(1u << (BIG_INT_BITS_PER_WORD - 1))) // works only for 32 bit variables (64bit leteral in c++: 1ull)


/**
 * Calculates the number of word required for storing a given number of bits
 * @param bit number of bits that should be stored
 * @return the required word count for storing [bit] bits
 */
#define BIG_INT_BIT_TO_SIZE(bit) 				BIG_INT_WORD_COUNT_TYPE( (bit + (BIG_INT_BITS_PER_WORD - 1)) / BIG_INT_BITS_PER_WORD )


/* ****************************************
 * *** Config. for different reder modi ***
 * ****************************************
 *
 */
//#define BIG_INT_FORCE_SCHOOL					1		// if disable the GLSL extension "GL_EXT_shader_explicit_arithmetic_types_int64" is required
#define BIG_INT_REDUCE_BRANCHING 				1
#define BIG_INT_64BIT_WORD_ADD					1		// if enabled the GLSL extension "GL_EXT_shader_explicit_arithmetic_types_int64" is required
#define GPU_MONTGOMERY_REDUCTION				1
//#define BIG_INT_MONTGOMERY_FORCE_READABLE 	1
#define GPU_TARGET_DOUBLE_WORD_LENGTH			1		// if enabled and 32bit BigInt words are used the GLSL extension "GL_ARB_gpu_shader_int64" is required


/* *************************************
 * *** Paillier modulus dependencies ***
 * *************************************
 *
 * see src/paillier/Paillier_typeDev.h
 */
#define PAILLIER_MODULUS_BIT_LENGTH 			64

#ifndef GPU_MONTGOMERY_REDUCTION
	#define PAILLIER_INT_BIT_LENGTH 			(PAILLIER_MODULUS_BIT_LENGTH*4)
#else
	#define PAILLIER_INT_BIT_LENGTH 			(PAILLIER_MODULUS_BIT_LENGTH*4)+18 		// enshure that the reciprocal of the MontgomeryReducer can be calculated (modInverse ith one bit more then PAILLIER_MODULUS_BIT_LENGTH*2)
#endif
#define PAILLIER_INT_WORD_SIZE 					BIG_INT_BIT_TO_SIZE( PAILLIER_INT_BIT_LENGTH )

#define PAILLIER_INT_STORAGE_BIT_LENGTH 		(PAILLIER_MODULUS_BIT_LENGTH*2)
#define PAILLIER_INT_STORAGE_WORD_SIZE 			BIG_INT_BIT_TO_SIZE( PAILLIER_INT_STORAGE_BIT_LENGTH )

// define Vulkan texture type that should be used as BigInteger storage format
#define GPU_INT_TEXTURE_WORD_COUNT				4							// words per texture
#define GPU_INT_TEXTURE_SIZE					((PAILLIER_INT_STORAGE_WORD_SIZE + (GPU_INT_TEXTURE_WORD_COUNT-1)) / GPU_INT_TEXTURE_WORD_COUNT)	// = ciel(PAILLIER_INT_WORD_SIZE / GpuVolume::bigIntWordCount); the numbers of textures required for storing PAILLIER_INT_STORAGE_WORD_SIZE words

// define Vulkan FBO attachment texture type that should be used as BigInteger storage format
#define GPU_INT_ATTACHMENT_WORD_COUNT			GPU_INT_TEXTURE_WORD_COUNT		// words per FBO attachment texture

#ifndef GPU_TARGET_DOUBLE_WORD_LENGTH
	#define GPU_INT_ATTACHMENT_SIZE				GPU_INT_TEXTURE_SIZE
	#define GPU_INT_ATTACHMENT_WORD_TYPE		BIG_INT_WORD_TYPE
	#define GPU_INT_ATTACHMENT_FORMAT			uvec4
#else
	#define GPU_INT_ATTACHMENT_SIZE				((PAILLIER_INT_STORAGE_WORD_SIZE/2 + (GPU_INT_TEXTURE_WORD_COUNT-1)) / GPU_INT_TEXTURE_WORD_COUNT)

	#if _BIG_INT_WORD_LENGTH_PRESET_ == 8
		#define GPU_INT_ATTACHMENT_WORD_TYPE	uint		//uint16_t
		#define GPU_INT_ATTACHMENT_FORMAT		uvec4 		//u16vec4
	#elif _BIG_INT_WORD_LENGTH_PRESET_ == 16
		#define GPU_INT_ATTACHMENT_WORD_TYPE	uint		//uint32_t
		#define GPU_INT_ATTACHMENT_FORMAT		uvec4		//u32vec4
	#elif _BIG_INT_WORD_LENGTH_PRESET_ == 32
		#define GPU_INT_ATTACHMENT_WORD_TYPE	uint64_t
		#define GPU_INT_ATTACHMENT_FORMAT		u64vec4
	#else
		#error No Vulkan texture format is defined for GPU_TARGET_DOUBLE_WORD_LENGTH and a BigInteger word length preset of more then 32.
	#endif
#endif

// define Vulkan uvec4 types for big integer uniforms
#define GPU_INT_UVEC4_SIZE						((PAILLIER_INT_WORD_SIZE + (4-1)) / 4)
#define GPU_INT_UVEC4_STORAGE_SIZE				((PAILLIER_INT_STORAGE_WORD_SIZE + (4-1)) / 4)




/* *************************************
 * ***     Storage Types for GLSL    ***
 * *************************************
 *
 */
#define FIX_BIG_INT_VALUE 						BIG_INT_WORD_TYPE[PAILLIER_INT_WORD_SIZE]
