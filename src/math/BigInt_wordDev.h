#pragma once

#define BIG_INT_WORD_COUNT_TYPE uint_fast32_t
//#include "BigInt_wordDev8bit.h"

// 8bit
#define BIG_INT_WORD_TYPE uint8_t
#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xF) //15u	// 2^(sizeof(BIG_INT_WORD_TYPE)*8/2) - 1

// 16bit
//#define BIG_INT_WORD_TYPE uint16_t
//#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xFF)

// 32bit
//#define BIG_INT_WORD_TYPE uint32_t
//#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xFFFF)

// 64bit
//#define BIG_INT_WORD_TYPE uint64_t
//#define BIG_INT_WORD_LOW_BIT_MASK BIG_INT_WORD_TYPE(0xFFFFFFFF)

#define BIG_INT_WORD_HIGH_BIT_MASK BIG_INT_WORD_TYPE(~BIG_INT_WORD_LOW_BIT_MASK)
#define BIG_INT_WORD_MAX_VALUE ((BIG_INT_WORD_TYPE)(-1ll))
#define BIG_INT_BITS_PER_WORD (sizeof(BIG_INT_WORD_TYPE) * CHAR_BIT)
#define BIG_INT_WORD_HIGHEST_BIT ((BIG_INT_WORD_TYPE)(1ull << (BIG_INT_BITS_PER_WORD - 1)))

#define BIG_INT_BIT_TO_SIZE(bit) (BIG_INT_WORD_COUNT_TYPE)( (bit + (sizeof(BIG_INT_WORD_TYPE) * CHAR_BIT - 1)) / (sizeof(BIG_INT_WORD_TYPE) * CHAR_BIT) )

// --- Prime numbers generation ---

// Minimum size in bits that the requested prime number has
// before we use the large prime number generating algorithms.
// The cutoff of 95 was chosen empirically for best performance.
#define BIG_INT_SMALL_PRIME_THRESHOLD 95

// Certainty required to meet the spec of probablePrime
#define BIG_INT_DEFAULT_PRIME_CERTAINTY 100
