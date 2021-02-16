#pragma once

#include <climits>
#include <cstdint>

/*
 * The Magnitude (value) of the BigInt Classes stores the Words as little-endian.
 * Therefore the least-significant word is stored at the smallest address (the word with index 0).
 */

#define _BIG_INT_WORD_LENGTH_PRESET_ 32

#define BIG_INT_WORD_COUNT_TYPE uint_fast32_t
//#include "BigInt_wordDev8bit.h"

// Definition of the variable type used for storing a BigInt Word.
// This also defines implicetly the radix of the BigInt.
#if _BIG_INT_WORD_LENGTH_PRESET_ == 8
	// 8bit
	#define BIG_INT_WORD_TYPE uint8_t
	#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xF) //15u	// 2^(sizeof(BIG_INT_WORD_TYPE)*8/2) - 1 		(BIG_INT_WORD_MAX_VALUE >> (BIG_INT_BITS_PER_WORD /2 ))
#elif _BIG_INT_WORD_LENGTH_PRESET_ == 16
	// 16bit
	#define BIG_INT_WORD_TYPE uint16_t
	#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xFF)
#elif _BIG_INT_WORD_LENGTH_PRESET_ == 32
	// 32bit
	#define BIG_INT_WORD_TYPE uint32_t
	#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xFFFF)
#elif _BIG_INT_WORD_LENGTH_PRESET_ == 64
	// 64bit
	#define BIG_INT_WORD_TYPE uint64_t
	#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xFFFFFFFF)
#else
	#error A BigInteger word length preset of #_BIG_INT_WORD_LENGTH_PRESET_ is not supported.
#endif

// Some importend values for a Word
#define BIG_INT_WORD_HIGH_BIT_MASK BIG_INT_WORD_TYPE(~BIG_INT_WORD_LOW_BIT_MASK)
#define BIG_INT_WORD_MAX_VALUE ((BIG_INT_WORD_TYPE)(-1ll))
#define BIG_INT_WORD_HIGHEST_BIT ((BIG_INT_WORD_TYPE)(1ull << (BIG_INT_BITS_PER_WORD - 1)))

// The length of a word in bit
#define BIG_INT_BITS_PER_WORD (sizeof(BIG_INT_WORD_TYPE) * CHAR_BIT)

/**
 * Calculates the number of word required for storing a given number of bits
 * @param bit number of bits that should be stored
 * @return the required word count for storing [bit] bits
 */
#define BIG_INT_BIT_TO_SIZE(bit) (BIG_INT_WORD_COUNT_TYPE)( (bit + (BIG_INT_BITS_PER_WORD - 1)) / BIG_INT_BITS_PER_WORD )
#define BIG_INT_REQUIRED_WORDS(sizeInBit) BIG_INT_BIT_TO_SIZE(sizeInBit)


// --- Prime numbers generation ---

// Minimum size in bits that the requested prime number has
// before we use the large prime number generating algorithms.
// The cutoff of 95 was chosen empirically for best performance.
#define BIG_INT_SMALL_PRIME_THRESHOLD 95

// Certainty required to meet the spec of probablePrime
#define BIG_INT_DEFAULT_PRIME_CERTAINTY 100

// --- Optimizations ---
//#define BIG_INT_REDUCE_BRANCHING 1
#define BIG_INT_NOASM 1
//#define BIG_INT_FORCE_SCHOOL 1
//#define BIG_INT_NO_MONTGOMERY_REDUCTION 1
#define BIG_INT_NO_MONTGOMERY_WINDOW 1
