#pragma once
#include <string>
#include <memory>

#include "BigInt_wordDef.h"

#include "Random.hpp"

/*
 UFixBigInt:		Unsigned Fixed     width Big Integer (only stack memory)
 SFixBigInt:		Signed   Fixed     width Big Integer (only stack memory)
 UArbBigInt:		Unsigned Arbitrary width Big Integer (required heap memory)
 SArbBigInt:		Signed   Arbitrary width Big Integer (required heap memory)
 */


// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)

namespace ppvr {
	namespace math {
		class BigIntUtil {

		public:
			static uint addTwoIntsCounter;
			
		// ----- bit utilities -----
			
			/**
			 * this method returns the number of the highest set bit in word
			 * if the 'word' is zero this method returns '-1'
			 */
			static int findHighestSetBitInWord(BIG_INT_WORD_TYPE word);
			
			/**
			 * this method returns the number of the lowest set bit in word
			 * if the 'word' is zero this method returns '-1'
			 */
			static int findLowestSetBitInWord(BIG_INT_WORD_TYPE word);
			
			/**
			 * Replace target.low with src.low bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		hhhhLLLL
			 */
			static inline BIG_INT_WORD_TYPE setLowFromLowBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) {
				BIG_INT_WORD_TYPE res =
				// set low bits to 0 and keep the high bits
				BigIntUtil::getHighAsHighBits(target)
				|
				// set high bits to 0 and keep the low bits
				BigIntUtil::getLowAsLowBits(src)
				;
				
				return res;
			}
			
			/**
			 * Replace target.low with src.high bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		hhhhHHHH
			 */
			static inline BIG_INT_WORD_TYPE setLowFromHighBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) {
				BIG_INT_WORD_TYPE res =
				// set low bits to 0 and keep the high bits
				//(target & BIG_INT_WORD_HIGH_BIT_MASK)
				BigIntUtil::getHighAsHighBits(target)
				|
				// move the high bits of src to the low bits
				//(src >> (BIG_INT_BITS_PER_WORD/2))
				BigIntUtil::getHighAsLowBits(src)
				;
				
				return res;
			}
			
			/**
			 * Replace target.high with src.high bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		HHHHllll
			 */
			static inline BIG_INT_WORD_TYPE setHighFromHighBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) {
				BIG_INT_WORD_TYPE res =
				// set high bits to 0 and keep the low bits
				BigIntUtil::getLowAsLowBits(target)
				|
				// set low bits to 0 and keep the high bits
				BigIntUtil::getHighAsHighBits(src)
				;
				
				return res;
			}
			
			/**
			 * Replace target.high with src.low bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		LLLLllll
			 */
			static inline BIG_INT_WORD_TYPE setHighFromLowBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) {
				BIG_INT_WORD_TYPE res =
				// set high bits to 0 and keep the low bits
				//(target & BIG_INT_WORD_LOW_BIT_MASK)
				BigIntUtil::getLowAsLowBits(target)
				|
				// move the low bits of src to the high bits
				//(src << (BIG_INT_BITS_PER_WORD/2))
				BigIntUtil::getLowAsHighBits(src)
				;
				
				return res;
			}
			
			/**
			 * Set low bit to 0 and keep the high bits.
			 *
			 * src:	HHHHLLLL
			 * res:	HHHH0000
			 */
			static inline BIG_INT_WORD_TYPE getHighAsHighBits(const BIG_INT_WORD_TYPE src) {
				BIG_INT_WORD_TYPE res = (src & BIG_INT_WORD_HIGH_BIT_MASK);
				return res;
			}
			
			/**
			 * Move the high bits of src to the low bits. The high bits will be 0.
			 *
			 * src:	HHHHLLLL
			 * res:	0000HHHH
			 */
			static inline BIG_INT_WORD_TYPE getHighAsLowBits(const BIG_INT_WORD_TYPE src) {
				BIG_INT_WORD_TYPE res = (src >> (BIG_INT_BITS_PER_WORD/2));
				return res;
			}
			
			/**
			 * Set high bit to 0 and keep the low bits.
			 *
			 * src:	HHHHLLLL
			 * res:	0000LLLL
			 */
			static inline BIG_INT_WORD_TYPE getLowAsLowBits(const BIG_INT_WORD_TYPE src) {
				BIG_INT_WORD_TYPE res = (src & BIG_INT_WORD_LOW_BIT_MASK);
				return res;
			}
			
			/**
			 * Move the low bits of src to the high bits. The low bits will be 0.
			 *
			 * src:	HHHHLLLL
			 * res:	LLLL0000
			 */
			static inline BIG_INT_WORD_TYPE getLowAsHighBits(const BIG_INT_WORD_TYPE src) {
				BIG_INT_WORD_TYPE res = (src << (BIG_INT_BITS_PER_WORD/2));
				return res;
			}
		
		// ----- addition -----
			/**
			 * this method adds two words together
			 * returns carry
			 */
			static inline BIG_INT_WORD_TYPE addTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE* result) {
				#if _BIG_INT_WORD_LENGTH_PRESET_ > 32 || !defined(BIG_INT_64BIT_WORD_ADD)
					BIG_INT_WORD_TYPE temp;
					if( carry == 0 ) {
						temp = a + b;
						if( temp < a ) {
							carry = 1;
						}
					} else {
						carry = 1;
						temp  = a + b + carry;
						if( temp > a ) { // !(temp<=a)
							carry = 0;
						}
					}
					*result = temp;
					return carry;
				#else
					uint64_t temp = (uint64_t)a + (uint64_t)b + (uint64_t)carry;
					*result = (BIG_INT_WORD_TYPE)temp;
					return BIG_INT_WORD_TYPE(temp >> uint64_t(BIG_INT_BITS_PER_WORD));
				#endif
			}
			
			/**
			 * this method adds only two unsigned words to the existing value
			 * and these words begin on the 'index' position
			 *
			 * index should be equal or smaller than value_size-2 (index <= value_size-2)
			 * x1 - lower word, x2 - higher word
			 *
			 * for example if we've got value_size equal 4 and:
			 *
			 * value[0] = 3
			 * value[1] = 4
			 * value[2] = 5
			 * value[3] = 6
			 *
			 * then let
			 *
			 * x1 = 10
			 * x2 = 20
			 *
			 * and
			 *
			 * index = 1
			 *
			 * the result of this method will be:
			 *
			 * value[0] = 3
			 * value[1] = 4 + x1 = 14
			 * value[2] = 5 + x2 = 25
			 * value[3] = 6
			 *
			 * and no carry at the end of value[3]
			 *
			 * (of course if there was a carry in value[2](5+20) then
			 * this carry would be passed to the value[3] etc.)
			 */
			static BIG_INT_WORD_TYPE addTwoInts(const BIG_INT_WORD_TYPE wordHigh, const BIG_INT_WORD_TYPE wordLow, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount);
			//void addTwoInts(const BIG_INT_WORD_TYPE wordHigh, const BIG_INT_WORD_TYPE wordLow, const BIG_INT_WORD_COUNT_TYPE index);
			
			/**
			 * this method adds one word (at a specific position)
			 * and returns a carry (if it was)
			 *
			 * if we've got (value_size=3):
			 *
			 * table[0] = 10;
			 * table[1] = 30;
			 * table[2] = 5;
			 *
			 * and we call:
			 *
			 * AddInt(2,1)
			 *
			 * then it'll be:
			 *
			 * table[0] = 10;
			 * table[1] = 30 + 2;
			 * table[2] = 5;
			 *
			 * of course if there was a carry from table[2] it would be returned
			 */
			static BIG_INT_WORD_TYPE addInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount);
			
			
		// ----- substraction -----
			
			/**
			 * this method subtractes one word from the other and subtracting
			 * carry if it has been defined
			 * (result = a - b - carry)
			 * carry have to be 0 or 1
			 *
			 * returns carry(borow)
			 */
			static BIG_INT_WORD_TYPE subTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE* result);
			
			/**
			 * this method subtracts one word (at a specific position)
			 * and returns a carry (if it was)
			 *
			 * if we've got (value_size=3):
			 *
			 * table[0] = 10;
			 * table[1] = 30;
			 * table[2] = 5;
			 *
			 * and we call:
			 *
			 * SubInt(2,1)
			 *
			 * then it'll be:
			 *
			 * table[0] = 10;
			 * table[1] = 30 - 2;
			 * table[2] = 5;
			 *
			 * of course if there was a carry from table[2] it would be returned
			 */
			static BIG_INT_WORD_TYPE subInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, const BIG_INT_WORD_COUNT_TYPE targetWordCount);
			
			
		// ----- multiplication -----
			
			/**
			 * multiplication: result_high:result_low = a * b
			 * -  result_high - higher word of the result
			 * -  result_low  - lower word of the result
			 *
			 * this methos never returns a carry
			 *
			 * this method is used in the second version of the multiplication algorithms
			 */
			static void mulTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE* resultHigh, BIG_INT_WORD_TYPE* resultLow);
			
			/**
			 * Multiply an n-word input (in) by a 1-word (k) input and add the
			 * low n words of the product to the destination (out).  *Returns the n+1st word
			 * of the product.*
			 */
			static inline BIG_INT_WORD_TYPE mulAdd(BIG_INT_WORD_TYPE* out, BIG_INT_WORD_COUNT_TYPE indexOut, const BIG_INT_WORD_TYPE* in, BIG_INT_WORD_COUNT_TYPE indexIn, const BIG_INT_WORD_COUNT_TYPE len, const BIG_INT_WORD_TYPE k) {
				/*
				 * The algorithm used here is adapted from Colin Plumb's C library.
				 * see lbn32.c lbnMulAdd1_32(BNWORD32 *out, BNWORD32 const *in, unsigned len, BNWORD32 k), line 583
				 *
				 * lbnMulAdd1_32: Multiply an n-word input by a 1-word input and add the
				 * low n words of the product to the destination.  *Returns the n+1st word
				 * of the product.*  (That turns out to be more convenient than adding
				 * it into the destination and dealing with a possible unit carry out
				 * of *that*.)  This uses either the mul32_ppmma and mul32_ppmmaa macros,
				 * or C multiplication with the BNWORD64 type.
				 *
				 * If you're going to write assembly primitives, this is the one to
				 * start with.  It is by far the most commonly called function.
				 *
				 */
				
				assert(len > 0);
				
				uint64_t kLong = k;
				uint64_t carry = 0;
				
				for (BIG_INT_WORD_COUNT_TYPE i = 0; i<len; i++) {
					carry = (uint64_t)in[indexIn] * kLong +
					(uint64_t)out[indexOut] + carry;
					out[indexOut] = (BIG_INT_WORD_TYPE)carry;
					carry = (BIG_INT_WORD_TYPE)(carry >> BIG_INT_BITS_PER_WORD);
					indexOut++;
					indexIn++;
					
				}

				return (BIG_INT_WORD_TYPE)carry;
			}
			
		// ----- division -----
			// -- divTwoWords
			
			/**
			 * this method calculates 64bits word a:b / 32bits c (a higher, b lower word)
			 * result = a:b / divisor and rest - remainder
			 * 		a: higher word of the dividend
			 *		b: higher word of the dividend
			 *
			 *
			 * WARNING:
			 * the divisor has to be suitably large for the result being keeped in one word,
			 * if divisor is equal zero there'll be a hardware interruption (0)
			 * and probably the end of your program
			 *
			 */
			static void divTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, const BIG_INT_WORD_TYPE divisor, BIG_INT_WORD_TYPE* result, BIG_INT_WORD_TYPE *remainder = NULL);
			
			// -- divTwoWordsKnuth
			
		private:
			/**
			 *
			 * the same algorithm like the division algorithm for all words which is based on
			 * "The art of computer programming 2" (4.3.1 page 272)
			 * Donald E. Knuth
			 * but now with the radix=2^32
			 */
			static void divTwoWordsKnuth(BIG_INT_WORD_TYPE a, BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE c, BIG_INT_WORD_TYPE* result, BIG_INT_WORD_TYPE* remainder = NULL);
			static uint divTwoWordsKnuth_normalize(BIG_INT_WORD_TYPE &a, BIG_INT_WORD_TYPE &b, BIG_INT_WORD_TYPE &c);
			static BIG_INT_WORD_TYPE divTwoWordsKnuth_unnormalize(BIG_INT_WORD_TYPE u, const uint d);
			static BIG_INT_WORD_TYPE divTwoWordsKnuth_calculate(const BIG_INT_WORD_TYPE u, const BIG_INT_WORD_TYPE u3, const BIG_INT_WORD_TYPE v);
			static void divTwoWordsKnuth_multiplySubtract(BIG_INT_WORD_TYPE &u, BIG_INT_WORD_TYPE &u3, BIG_INT_WORD_TYPE &q, const BIG_INT_WORD_TYPE v);
			
		// ----- multiplicative inverse -----
		public:
			
			/**
			 * Returns the multiplicative inverse of val mod 2^32.  Assumes val is odd.
			 */
			static uint32_t inverseMod32(uint32_t val);
			
			/**
			 * Returns the multiplicative inverse of val mod 2^64.  Assumes val is odd.
			 */
			static uint64_t inverseMod64(uint64_t val);
		};
	}
}
