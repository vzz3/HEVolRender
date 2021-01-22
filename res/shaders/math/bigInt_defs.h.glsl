//#include "../../../src/math/BigInt_wordDef.h"

/* *************************************
 * ***      BigInt  dependencies     ***
 * *************************************
 *
 * see src/math/BigInt_wordDef.h
 */

// BigInt
#define BIG_INT_WORD_COUNT_TYPE uint

// 8bit
#define BIG_INT_WORD_TYPE uint
#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xF)
#define BIG_INT_WORD_ALL_BIT_MASK BIG_INT_WORD_TYPE(0xFF)
#define BIG_INT_BITS_PER_WORD 8
#define BIG_INT_LESS_BITS_THEN_WORD_TYPE 1

// 16bit
//#define BIG_INT_WORD_TYPE uint16_t
//#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xFF)
//#define BIG_INT_LESS_BITS_THEN_WORD_TYPE 1

// 32bit
//#define BIG_INT_WORD_TYPE uint32_t
//#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xFFFF)



// Some importend values for a Word
#define BIG_INT_WORD_HIGH_BIT_MASK (BIG_INT_WORD_TYPE(~BIG_INT_WORD_LOW_BIT_MASK) & BIG_INT_WORD_ALL_BIT_MASK)
#define BIG_INT_WORD_MAX_VALUE ((BIG_INT_WORD_TYPE)(-1))	// works only for 32 bit variables (64bit leteral in c++: -1ll)
#define BIG_INT_WORD_HIGHEST_BIT ((BIG_INT_WORD_TYPE)(1u << (BIG_INT_BITS_PER_WORD - 1))) // works only for 32 bit variables (64bit leteral in c++: 1ull)


/**
 * Calculates the number of word required for storing a given number of bits
 * @param bit number of bits that should be stored
 * @return the required word count for storing [bit] bits
 */
#define BIG_INT_BIT_TO_SIZE(bit) BIG_INT_WORD_COUNT_TYPE( (bit + (BIG_INT_BITS_PER_WORD - 1)) / BIG_INT_BITS_PER_WORD )


/* *************************************
 * *** Paillier modulus dependencies ***
 * *************************************
 *
 * see src/paillier/Paillier_typeDev.h
 */
#define PAILLIER_MODULUS_BIT_LENGTH 		64


#define PAILLIER_INT_BIT_LENGTH 			(PAILLIER_MODULUS_BIT_LENGTH*4)
#define PAILLIER_INT_WORD_SIZE 				BIG_INT_BIT_TO_SIZE( PAILLIER_INT_BIT_LENGTH )

#define PAILLIER_INT_STORAGE_BIT_LENGTH 	(PAILLIER_MODULUS_BIT_LENGTH*2)
#define PAILLIER_INT_STORAGE_WORD_SIZE 		BIG_INT_BIT_TO_SIZE( PAILLIER_INT_STORAGE_BIT_LENGTH )


#define GPU_INT_TEXTURE_WORD_COUNT			4							// words per texture
#define GPU_INT_TEXTURE_SIZE				((PAILLIER_INT_STORAGE_WORD_SIZE + (GPU_INT_TEXTURE_WORD_COUNT-1)) / GPU_INT_TEXTURE_WORD_COUNT)	// = ciel(PAILLIER_INT_WORD_SIZE / GpuVolume::bigIntWordCount); the numbers of textures required for storing PAILLIER_INT_STORAGE_WORD_SIZE words


/* *************************************
 * ***     Storage Types for GLSL    ***
 * *************************************
 *
 */
#define FIX_BIG_INT_VALUE uint[PAILLIER_INT_WORD_SIZE]
