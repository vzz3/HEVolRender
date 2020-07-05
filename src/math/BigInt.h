#pragma once
#include <string>
#include <memory>
#include <sys/types.h>

#include "BigInt_wordDev.h"

// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)

namespace ppvr {
	namespace math {
		class BigInt {
		public:
			friend std::ostream& operator << ( std::ostream& os, const BigInt& value ){
				os << value.toStringDec();
				return os;
			}
			
			static BigInt ZERO;
			static BigInt ONE;
			static BigInt TWO;
			static BigInt TEN;
			static BigInt fromUint64(const uint64_t& value);
			static BigInt fromString(const std::string& str, const BIG_INT_WORD_TYPE base);
			
			BigInt();
			BigInt(const BIG_INT_WORD_TYPE& value);
			BigInt(const BIG_INT_WORD_TYPE& value, BIG_INT_WORD_COUNT_TYPE minCapacity);
			BigInt(const BigInt &src);
			BigInt(const BigInt &src, BIG_INT_WORD_COUNT_TYPE minCapacity);
			~BigInt();
			
			/**
			 * Converts this BigInteger to a long.
			 * If this BigInteger is too big to fit in a unsingend long long (64bit), only the low-order 64 bits are returned.
			 * Note that this conversion can lose information about the overall magnitude of the BigInteger value
			 * //(as well as return a result with the opposite sign)
			 * .
			 */
			uint64_t toUint64() const;
			
			std::string toStringHex() const;
			std::string toStringDec() const;
			
			// --- General purpose mathematical methods ---
			BigInt operator<< (const uint bits) const;
			BigInt operator>> (const uint bits) const;
			BigInt operator+ (const BigInt& other) const;
			BigInt operator- (const BigInt& other) const;
			BigInt operator* (const BigInt& other) const;
			BigInt operator/ (const BigInt& other) const;
			BigInt operator% (const BigInt& other) const;
			
			/**
			 * power this = this ^ pow
			 * binary algorithm (r-to-l)
			 */
			BigInt pow(BigInt pow) const;
			
			/**
			 * square root
			 * e.g. BigInt(9).sqrt() = 3
			 * ('digit-by-digit' algorithm)
			 */
			BigInt sqrt() const;
			
			// --- Comparison operators ---
			bool operator< (const BigInt& other) const;
			bool operator<= (const BigInt& other) const;
			bool operator> (const BigInt& other) const;
			bool operator>= (const BigInt& other) const;
			bool operator== (const BigInt& other) const;
			bool operator!= (const BigInt& other) const;
			
			
			
			// Copy assignment operator
			BigInt& operator= (const BigInt& other);
		private:
			//size_t _dataRefCount;
			BIG_INT_WORD_COUNT_TYPE wordSize = 0; // count of used words (wordCount)
			BIG_INT_WORD_COUNT_TYPE wordCapacity = 0; // length of the value array
			BIG_INT_WORD_TYPE *value = NULL;
			//std::shared_ptr<BIG_INT_WORD_TYPE[]> value;
			
			
			BigInt(BIG_INT_WORD_TYPE* value, BIG_INT_WORD_COUNT_TYPE wordCapacity, BIG_INT_WORD_COUNT_TYPE wordSize);
			
			/**
			 * Increase the capacity of the Integer to a value that's greater or equal to newCapacity.
			 * If new_cap is greater than the current capacity(), new storage is allocated, otherwise the method does nothing.
			 */
			void reserveWords( BIG_INT_WORD_COUNT_TYPE newCapacity );
			
		protected:
			void setZero();
			
			void setOne();
			
		public:
			bool isZero() const;
			
			bool isOne() const;
			
			
			/**
			 * Returns true iff this MutableBigInteger is even.
			 */
			bool isEven() const;
			
			/**
			 * Returns true iff this MutableBigInteger is odd.
			 */
			bool isOdd() const;
			
		protected:
			/**
			 * Returns {@code true} if and only if the designated bit is set.
			 * (Computes {@code ((this & (1<<n)) != 0)}.)
			 *
			 * @param  n index of bit to test.
			 * @return {@code true} if and only if the designated bit is set.
			 * @throws ArithmeticException {@code n} is negative.
			 */
			bool testBit(uint n) const;
			
		private:
			/**
			 * this method returns the number of the highest set bit in word
			 * if the 'word' is zero this method returns '-1'
			 */
			int findHighestSetBitInWord(BIG_INT_WORD_TYPE word) const;
			
			/**
			 * this method returns the number of the lowest set bit in word
			 * if the 'word' is zero this method returns '-1'
			 */
			int findLowestSetBitInWord(BIG_INT_WORD_TYPE word) const;
			
		protected:
			/**
			 * Returns the index of the leftmost (highest-order) one bit in this
			 * BigInteger (the number of zero bits to the left of the leftmost
			 * one bit).  Returns -1 if this BigInteger contains no one bits.
			 *
			 * @return index of the leftmost one bit in this BigInteger.
			 */
			int findHighestSetBit() const;
			
			/**
			 * Returns the index of the rightmost (lowest-order) one bit in this
			 * BigInteger (the number of zero bits to the right of the rightmost
			 * one bit).  Returns -1 if this BigInteger contains no one bits.
			 *
			 * @return index of the rightmost one bit in this BigInteger.
			 */
			int findLowestSetBit() const;
		
		public:
			int bitLength() const;
			
		protected:
			BIG_INT_WORD_COUNT_TYPE getWordSize() const {
				return this->wordSize;
			}
			
		private:
			
			/**
			 * Replace target.low with src.low bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		hhhhLLLL
			 */
			BIG_INT_WORD_TYPE setLowFromLowBits(BIG_INT_WORD_TYPE target, BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Replace target.low with src.high bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		hhhhHHHH
			 */
			BIG_INT_WORD_TYPE setLowFromHighBits(BIG_INT_WORD_TYPE target, BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Replace target.high with src.high bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		HHHHllll
			 */
			BIG_INT_WORD_TYPE setHighFromHighBits(BIG_INT_WORD_TYPE target, BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Replace target.high with src.low bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		LLLLllll
			 */
			BIG_INT_WORD_TYPE setHighFromLowBits(BIG_INT_WORD_TYPE target, BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Set low bit to 0 and keep the high bits.
			 *
			 * src:	HHHHLLLL
			 * res:	HHHH0000
			 */
			BIG_INT_WORD_TYPE getHighAsHighBits(BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Move the high bits of src to the low bits. The high bits will be 0.
			 *
			 * src:	HHHHLLLL
			 * res:	0000HHHH
			 */
			BIG_INT_WORD_TYPE getHighAsLowBits(BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Set high bit to 0 and keep the low bits.
			 *
			 * src:	HHHHLLLL
			 * res:	0000LLLL
			 */
			BIG_INT_WORD_TYPE getLowAsLowBits(BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Move the low bits of src to the high bits. The low bits will be 0.
			 *
			 * src:	HHHHLLLL
			 * res:	LLLL0000
			 */
			BIG_INT_WORD_TYPE getLowAsHighBits(BIG_INT_WORD_TYPE src) const;
			
			/* ---------- shift left ---------- */
			
			/**
			 * an auxiliary method for moving bits into the left hand side
			 *
			 * this method moves only words
			 *
			 * This method does not increase the the word count => it drops informations that are on left end!
			 */
			void rcl_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, const uint bits, BIG_INT_WORD_TYPE c);
			
			/**
			 * this method moves all bits into the left hand side
			 * return value <- this <- c
			 *
			 * the lowest *bits* will be held the 'c' and
			 * the state of one additional bit (on the left hand side)
			 * will be returned
			 *
			 * for example:
			 * let this is 001010000
			 * after rcl_moveBits(3, 1) there'll be 010000111 and rcl_moveBits returns 1
			 *
			 * This method does not increase the the word count => it drops informations that are on left end!
			 */
			BIG_INT_WORD_TYPE rcl_moveBits(const uint bits, BIG_INT_WORD_TYPE c);
			
			/**
			 * moving all bits into the left side 'bits' times
			 * return value <- this <- C
			 *
			 * bits is from a range of <0, man * BIG_INT_BITS_PER_WORD>
			 * or it can be even bigger then all bits will be set to 'c'
			 *
			 * the value c will be set into the lowest bits
			 * and the method returns state of the last moved bit
			 *
			 * if resize is false (default) this method does not increase the the word size => it drops informations that are on left end!
			 */
			BIG_INT_WORD_TYPE rcl(const uint bits, const BIG_INT_WORD_TYPE c=0, const bool resize=false);
			
			/* ---------- shift right ---------- */
			
			/**
			 * an auxiliary method for moving bits into the right hand side
			 *
			 * this method moves only words
			 */
			void rcr_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, const uint bits, BIG_INT_WORD_TYPE c);
			
			/**
			 * this method moves all bits into the right hand side
			 * C -> this -> return value
			 *
			 * the highest *bits* will be held the 'c' and
			 * the state of one additional bit (on the right hand side)
			 * will be returned
			 *
			 * for example:
			 * let this is 000000010
			 * after rcr_moveBits(2, 1) there'll be 110000000 and rcr_moveBits returns 1
			 */
			BIG_INT_WORD_TYPE rcr_moveBits(const uint bits, BIG_INT_WORD_TYPE c);
			
			/**
			 * moving all bits into the right side 'bits' times
			 * c -> this -> return value
			 *
			 * bits is from a range of <0, man * TTMATH_BITS_PER_UINT>
			 * or it can be even bigger then all bits will be set to 'c'
			 *
			 * the value c will be set into the highest bits
			 * and the method returns state of the last moved bit
			 */
			BIG_INT_WORD_TYPE rcr(const uint bits, const BIG_INT_WORD_TYPE c=0);
		
			/* ---------- addition ---------- */
			
			/**
			 * this method adds two words together
			 * returns carry
			 */
			BIG_INT_WORD_TYPE addTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE * result) const;
			
			/**
			 * this method adds only two unsigned words to the existing value
			 * and these words begin on the 'index' position
			 * (it's used in the multiplication algorithm 2)
			 *
			 * index should be equal or smaller than value_size-2 (index <= value_size-2)
			 * x1 - lower word, x2 - higher word
			 *
			 * for example if we've got value_size equal 4 and:
			 *
			 * table[0] = 3
			 * table[1] = 4
			 * table[2] = 5
			 * table[3] = 6
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
			 * table[0] = 3
			 * table[1] = 4 + x1 = 14
			 * table[2] = 5 + x2 = 25
			 * table[3] = 6
			 *
			 * and no carry at the end of table[3]
			 *
			 * (of course if there was a carry in table[2](5+20) then
			 * this carry would be passed to the table[3] etc.)
			 */
			BIG_INT_WORD_TYPE addTwoInts(const BIG_INT_WORD_TYPE wordHigh, const BIG_INT_WORD_TYPE wordLow, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE * targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const;
			
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
			BIG_INT_WORD_TYPE addInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE *targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const;
			
			void add(const BigInt &other);
			
			/* ---------- substraction ---------- */
			
			/**
			 * this method subtractes one word from the other
			 * returns carry
			 *
			 * this method is created only when TTMATH_NOASM macro is defined
			 */
			BIG_INT_WORD_TYPE subTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE * result) const;
			
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
			BIG_INT_WORD_TYPE subInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE *targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const;
			
			BIG_INT_WORD_TYPE sub(const BigInt& other);
			
			
		/* ---------- multiplication ---------- */
			
			/**
			 * multiplication: result_high:result_low = a * b
			 * -  result_high - higher word of the result
			 * -  result_low  - lower word of the result
			 *
			 * this methos never returns a carry
			 *
			 * this method is used in the second version of the multiplication algorithms
			 */
			void mulTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE * resultHigh, BIG_INT_WORD_TYPE * resultLow) const;
			
			/**
			 * multiplication: this = this * ss2
			 */
			void mulInt(BIG_INT_WORD_TYPE ss2, BigInt& result) const;
			
			void mulSchool(const BigInt& a, const BigInt& b, BigInt& result) const;
			//BigInt mulSchool_1(const BigInt& a, const BigInt& b) const;
			//BigInt mulSchool_2(const BigInt& a, const BigInt& b, const BIG_INT_WORD_COUNT_TYPE aStart, const BIG_INT_WORD_COUNT_TYPE aSize, const BIG_INT_WORD_COUNT_TYPE bStart, BIG_INT_WORD_COUNT_TYPE bSize) const
			
		/* ---------- division ---------- */
			
			/**
			 * this method calculates 64bits word a:b / 32bits c (a higher, b lower word)
			 * result = a:b / c and rest - remainder
			 *
			 *
			 * WARNING:
			 * the c has to be suitably large for the result being keeped in one word,
			 * if c is equal zero there'll be a hardware interruption (0)
			 * and probably the end of your program
			 *
			 */
			void divTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE c, BIG_INT_WORD_TYPE *result, BIG_INT_WORD_TYPE *rest) const;
			
			/**
			 *
			 * the same algorithm like the division algorithm for all words which is based on
			 * "The art of computer programming 2" (4.3.1 page 272)
			 * Donald E. Knuth
			 * but now with the radix=2^32
			 */
			void divTwoWords2(BIG_INT_WORD_TYPE a, BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE c, BIG_INT_WORD_TYPE * r, BIG_INT_WORD_TYPE * rest) const;
			BIG_INT_WORD_TYPE divTwoWordsNormalize(BIG_INT_WORD_TYPE &a, BIG_INT_WORD_TYPE &b, BIG_INT_WORD_TYPE &c) const;
			BIG_INT_WORD_TYPE divTwoWordsUnnormalize(BIG_INT_WORD_TYPE u, BIG_INT_WORD_TYPE d) const;
			unsigned int divTwoWordsCalculate(BIG_INT_WORD_TYPE u, BIG_INT_WORD_TYPE u3, BIG_INT_WORD_TYPE v) const;
			void multiplySubtract(BIG_INT_WORD_TYPE &u, BIG_INT_WORD_TYPE & u3, BIG_INT_WORD_TYPE & q, BIG_INT_WORD_TYPE v) const;
			
			/**
			 * division by one unsigned word
			 *
			 * returns the remainder
			 */
			BIG_INT_WORD_TYPE divInt(BIG_INT_WORD_TYPE divisor, BIG_INT_WORD_TYPE *targetArray, BIG_INT_WORD_COUNT_TYPE *targetWordCount) const;
			
			void div_division(BigInt divisor, BigInt * remainder, uint m, uint n);
			void div_makeNewU(BigInt &uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n, BIG_INT_WORD_TYPE u_max) const;
			void div_copyNewU(const BigInt & uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n);
			BIG_INT_WORD_TYPE div_normalize(BigInt& divisor, uint n, uint & d);
			void div_unnormalize(BigInt * remainder, BIG_INT_WORD_COUNT_TYPE n, BIG_INT_WORD_COUNT_TYPE d);
			BIG_INT_WORD_TYPE div_calculate(BIG_INT_WORD_TYPE u2, BIG_INT_WORD_TYPE u1, BIG_INT_WORD_TYPE u0, BIG_INT_WORD_TYPE v1, BIG_INT_WORD_TYPE v0) const;
			void div_multiplySubtract(	BigInt & uu,  const BigInt & vv, BIG_INT_WORD_TYPE & qp) const;
			
			void div(const BigInt& divisor, BigInt* remainder);
			
		};
	}
}
