#pragma once
#include <string>
#include <memory>
#include <sys/types.h>

#include "BigInt_wordDev.h"

#include "../../include/isaac-engine/isaac.h"
#include <random>
/*
namespace utils {
	template<std::size_t Alpha = 8>
	class isaac64;
}
*/
// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)

namespace ppvr {
	namespace math {
		class BigInt {
			
		// ----- statics -----
		public:
			friend std::ostream& operator << ( std::ostream& os, const BigInt& value ){
				os << value.toStringDec();
				return os;
			}
			
			static const BigInt ZERO;
			static const BigInt ONE;
			static const BigInt TWO;
			static const BigInt TEN;
			
			static BigInt fromUint64(const uint64_t& uint64Val);
		protected:
			static BigInt& fromUint64(const uint64_t& uint64Val, BigInt &target );
			
		public:
			static BigInt fromString(const std::string& str, const BIG_INT_WORD_TYPE base);
		protected:
			static BigInt& fromString(const std::string& str, const BIG_INT_WORD_TYPE base, BigInt &target );
			
		// ----- statics rendome -----
		private:
			static std::random_device rdev;
			
			// Alpha should (generally) either be 8 for crypto use, or 4 for non-crypto use.
			// If not provided, it defaults to 8
			static constexpr std::size_t isaacAlpha = 8;
			
			typedef utils::isaac64<isaacAlpha> RandomGenerator;
			
			// Alpha determines the size (in elements of result_type) of the
			// internal state, and the size of the initial state for seeding.
			static RandomGenerator randEngine;
			
			static void randomFill(void * buf, std::size_t count);
			
		public:
			
			static BigInt randomNumber(const uint& sizeInBit);
			static BigInt randomNumber(const BigInt& upperBound);
		protected:
			static BigInt& randomNumber(const uint& sizeInBit, BigInt &target);
			static BigInt& randomNumber(const BigInt& upperBound, BigInt &target);
			
		protected:
			 static BIG_INT_WORD_COUNT_TYPE requiredWords(const uint& sizeInBit);
			
		// ----- member variables -----
		private:
			BIG_INT_WORD_COUNT_TYPE wordSize = 0; // count of used words (wordCount)
			BIG_INT_WORD_COUNT_TYPE wordCapacity = 0; // length of the value array
			BIG_INT_WORD_TYPE *value = NULL;
			//std::shared_ptr<BIG_INT_WORD_TYPE[]> value;
			
		// ----- constructors -----
		public:
			BigInt();
			BigInt(const BIG_INT_WORD_TYPE& value);
			BigInt(const BIG_INT_WORD_TYPE& value, BIG_INT_WORD_COUNT_TYPE minCapacity);
			BigInt(const BigInt &src);
			BigInt(const BigInt &src, BIG_INT_WORD_COUNT_TYPE minCapacity);
		private:
			BigInt(BIG_INT_WORD_TYPE* value, BIG_INT_WORD_COUNT_TYPE wordCapacity, BIG_INT_WORD_COUNT_TYPE wordSize);
		public:
			~BigInt();
			
		// ----- value export - toString / toUint64 -----
		public:
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
			
		// ----- memory managment -----
		public:
			/**
			 * Copy assignment operator
			 */
			BigInt& operator= (const BigInt& other);
			
		private:
			
			/**
			 * Increase the capacity of the Integer to a value that's greater or equal to newCapacity.
			 * If new_cap is greater than the current capacity(), new storage is allocated, otherwise the method does nothing.
			 */
			void reserveWords( const BIG_INT_WORD_COUNT_TYPE newCapacity );
			
			void reserveWordsAndInitUnused( const BIG_INT_WORD_COUNT_TYPE newCapacity, const BIG_INT_WORD_TYPE initValue = 0 );
			
			void initUnusedWords(const BIG_INT_WORD_TYPE initValue = 0);
			
		// ----- bit utilities -----
		public:
			int bitLength() const;
			
		protected:
			void setZero();
			void setOne();
			
			/**
			 * Sets the designated bit in this BigInt.
			 * (Computes {@code (this | (1<<n))}.)
			 *
			 * @param  n index of bit to set.
			 */
			void setBit(const uint n);
			
			/**
			 * Clear the designated bit in this BigInt.
			 * (Computes {@code (this & ~(1<<n))}.)
			 *
			 * @param  n index of bit to clear.
			 * @return {@code this & ~(1<<n)}
			 */
			void clearBit(int n);
			
		public:
			/**
			 * Returns a BigInteger whose value is equivalent to this BigInteger
			 * with the designated bit set.  (Computes {@code (this | (1<<n))}.)
			 *
			 * @param  n index of bit to set.
			 * @return {@code this | (1<<n)}
			 */
			BigInt withBit(const uint n);
				
			/**
			 * Returns a BigInteger whose value is equivalent to this BigInteger
			 * with the designated bit cleared.
			 * (Computes {@code (this & ~(1<<n))}.)
			 *
			 * @param  n index of bit to clear.
			 * @return {@code this & ~(1<<n)}
			 */
			BigInt withoutBit(int n);
		
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
			
		// ----- word utilities -----
		protected:
			BIG_INT_WORD_COUNT_TYPE getWordSize() const {
				return this->wordSize;
			}
			
			/**
			 * Decreases the word count to newMaxWordSize.
			 * If the word newMaxWordSize-1 is 0 then set the wordSize to newMaxWordSize-1.
			 * If this is also 0 the set it to newMaxWordSize-2, and so on.
			 * The param newMaxWordSize need to be <= this->wordCapacity
			 *
			 * @param newMaxWordSize new maximal word count
			 */
			void trimWordSize(const BIG_INT_WORD_COUNT_TYPE newMaxWordSize);
			
			BIG_INT_WORD_TYPE getLeastSignificantWord() const {
				return this->value[0];
			}
			
		private:
			/**
			 * Replace target.low with src.low bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		hhhhLLLL
			 */
			BIG_INT_WORD_TYPE setLowFromLowBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Replace target.low with src.high bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		hhhhHHHH
			 */
			BIG_INT_WORD_TYPE setLowFromHighBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Replace target.high with src.high bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		HHHHllll
			 */
			BIG_INT_WORD_TYPE setHighFromHighBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Replace target.high with src.low bits.
			 *
			 * target:	hhhhllll
			 * src:		HHHHLLLL
			 * res:		LLLLllll
			 */
			BIG_INT_WORD_TYPE setHighFromLowBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Set low bit to 0 and keep the high bits.
			 *
			 * src:	HHHHLLLL
			 * res:	HHHH0000
			 */
			BIG_INT_WORD_TYPE getHighAsHighBits(const BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Move the high bits of src to the low bits. The high bits will be 0.
			 *
			 * src:	HHHHLLLL
			 * res:	0000HHHH
			 */
			BIG_INT_WORD_TYPE getHighAsLowBits(const BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Set high bit to 0 and keep the low bits.
			 *
			 * src:	HHHHLLLL
			 * res:	0000LLLL
			 */
			BIG_INT_WORD_TYPE getLowAsLowBits(const BIG_INT_WORD_TYPE src) const;
			
			/**
			 * Move the low bits of src to the high bits. The low bits will be 0.
			 *
			 * src:	HHHHLLLL
			 * res:	LLLL0000
			 */
			BIG_INT_WORD_TYPE getLowAsHighBits(const BIG_INT_WORD_TYPE src) const;
			
		// ----- shift left -----
		private:
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
			
		protected:
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
			
		public:
			BigInt operator<< (const uint bits) const;
			
		// ----- shift right -----
		private:
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
			
		protected:
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
			
		public:
			BigInt operator>> (const uint bits) const;
			
		// ----- addition -----
		private:
			/**
			 * this method adds two words together
			 * returns carry
			 */
			BIG_INT_WORD_TYPE addTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE* result) const;
			
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
			BIG_INT_WORD_TYPE addTwoInts(const BIG_INT_WORD_TYPE wordHigh, const BIG_INT_WORD_TYPE wordLow, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const;
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
			BIG_INT_WORD_TYPE addInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const;
			
		protected:
			/**
			 * this = this + word
			 */
			void addInt(const BIG_INT_WORD_TYPE word);
			
			void add(const BigInt &other, BigInt &result) const;
			void add(const BigInt &other);
			
		public:
			BigInt operator+ (const BigInt& other) const;
			
		// ----- substraction -----
		private:
			
			/**
			 * this method subtractes one word from the other and subtracting
			 * carry if it has been defined
			 * (result = a - b - carry)
			 * carry have to be 0 or 1
			 *
			 * returns carry(borow)
			 */
			BIG_INT_WORD_TYPE subTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE* result) const;
			
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
			BIG_INT_WORD_TYPE subInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const;
			
		protected:
			/**
			 * this = this - word
			 * returns the carry (borrow) if this was < word
			 */
			BIG_INT_WORD_TYPE subInt(const BIG_INT_WORD_TYPE word);
			
			/**
			 * this method's subtracting other from the 'this' and subtracting
			 * carry if it has been defined
			 * (result = this - other - carry)
			 *
			 * carry must be zero or one (might be a bigger value than 1)
			 * function returns carry (borrow) (1) (if this < other)
			 */
			BIG_INT_WORD_TYPE sub(const BigInt& other, BIG_INT_WORD_TYPE carry, BigInt &result) const;
			BIG_INT_WORD_TYPE sub(const BigInt& other);
			
		public:
			BigInt operator- (const BigInt& other) const;
			
		// ----- multiplication -----
		private:
			/**
			 * multiplication: result_high:result_low = a * b
			 * -  result_high - higher word of the result
			 * -  result_low  - lower word of the result
			 *
			 * this methos never returns a carry
			 *
			 * this method is used in the second version of the multiplication algorithms
			 */
			void mulTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE* resultHigh, BIG_INT_WORD_TYPE* resultLow) const;
			
		protected:
			/**
			 * multiplication: result = this * ss2
			 */
			void mulInt(BIG_INT_WORD_TYPE ss2, BigInt& result) const;
			
		private:
			void mulSchool(const BigInt& a, const BigInt& b, BigInt& result) const;
			
		protected:
			/**
			 * result = this * b
			 */
			void mul(const BigInt& b, BigInt& result) const;
			
			/**
			 * this = this * b
			 */
			void mul(const BigInt& b);
			
		public:
			BigInt operator* (const BigInt& other) const;
			
		// ----- division -----
		private:
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
			void divTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE divisor, BIG_INT_WORD_TYPE* result, BIG_INT_WORD_TYPE *remainder = NULL) const;
			
			// -- divTwoWordsKnuth
			
			/**
			 *
			 * the same algorithm like the division algorithm for all words which is based on
			 * "The art of computer programming 2" (4.3.1 page 272)
			 * Donald E. Knuth
			 * but now with the radix=2^32
			 */
			void divTwoWordsKnuth(BIG_INT_WORD_TYPE a, BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE c, BIG_INT_WORD_TYPE* result, BIG_INT_WORD_TYPE* remainder = NULL) const;
			BIG_INT_WORD_TYPE divTwoWordsKnuth_normalize(BIG_INT_WORD_TYPE &a, BIG_INT_WORD_TYPE &b, BIG_INT_WORD_TYPE &c) const;
			BIG_INT_WORD_TYPE divTwoWordsKnuth_unnormalize(BIG_INT_WORD_TYPE u, BIG_INT_WORD_TYPE d) const;
			unsigned int divTwoWordsKnuth_calculate(BIG_INT_WORD_TYPE u, BIG_INT_WORD_TYPE u3, BIG_INT_WORD_TYPE v) const;
			void divTwoWordsKnuth_multiplySubtract(BIG_INT_WORD_TYPE &u, BIG_INT_WORD_TYPE & u3, BIG_INT_WORD_TYPE & q, BIG_INT_WORD_TYPE v) const;
			
			// -- divInt
			
		protected:
			/**
			 * division by one unsigned word
			 * restul = this / divisor
			 *
			 * returns the remainder
			 */
			BIG_INT_WORD_TYPE divInt(BIG_INT_WORD_TYPE divisor, BigInt& result) const;
			
			/**
			 * division by one unsigned word
			 * this = this / divisor
			 *
			 * returns the remainder
			 */
			BIG_INT_WORD_TYPE divInt(BIG_INT_WORD_TYPE divisor);
			
		private:
			// -- divKnuth
			
			void divKnuth_division(BigInt divisor, BigInt &result, BigInt& remainder, uint m, uint n) const;
			void divKnuth_makeNewU(BigInt &uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n, BIG_INT_WORD_TYPE u_max) const;
			void divKnuth_copyNewU(const BigInt & uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n);
			
			/**
			 * D1. [Normaliez]
			 *
			 * we're moving all bits from 'divisor' into the left side of the n-1 word
			 * (the highest bit at divisor.value[n-1] will be equal one,
			 * the bits from 'dividend' we're moving the same times as 'divisor')
			 *
			 * return values:
			 * -  d - how many times we've moved
			 * -  return - the next-left value from 'this' (that after value[value_size-1])
			 */
			BIG_INT_WORD_TYPE divKnuth_normalize(BigInt& divisor, uint n, uint & d);
			
			void divKnuth_unnormalize(BIG_INT_WORD_COUNT_TYPE d);
			BIG_INT_WORD_TYPE divKnuth_calculate(BIG_INT_WORD_TYPE u2, BIG_INT_WORD_TYPE u1, BIG_INT_WORD_TYPE u0, BIG_INT_WORD_TYPE v1, BIG_INT_WORD_TYPE v0) const;
			
			/**
			 * D4. [Multiply and subtract]
			 *		includes also: D5. [Test Remainder] and D6. [add back]
			 *
			 */
			void divKnuth_multiplySubtract(	BigInt & uu,  const BigInt & vv, BIG_INT_WORD_TYPE & qp) const;
			
			/**
			 * the third division algorithm
			 *
			 * this algorithm is described in the following book:
			 * "The art of computer programming 2" (4.3.1 page 257)
			 * Donald E. Knuth
			 * !! give the description here (from the book)
			 */
			void divKnuth(const BigInt& divisor, BigInt &result, BigInt& remainder) const;
			
		protected:
			/**
			 * result = this / divisor
			 */
			void div(const BigInt& divisor, BigInt &result, BigInt& remainder) const;
			
			/**
			 * this = this / divisor
			 */
			void div(const BigInt& divisor, BigInt& remainder);
			
		public:
			BigInt operator/ (const BigInt& other) const;
			BigInt operator% (const BigInt& other) const;
			
		// ----- pow(), sqrt() -----
		public:

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
			
		// ----- Comparison operators -----
		public:
			bool operator< (const BigInt& other) const;
			bool operator<= (const BigInt& other) const;
			bool operator> (const BigInt& other) const;
			bool operator>= (const BigInt& other) const;
			bool operator== (const BigInt& other) const;
			bool operator!= (const BigInt& other) const;
		};
	}
}
