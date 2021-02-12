#pragma once
#include <string>
#include <memory>
#include "BigInt_wordDef.h"

#include "Random.hpp"
#include "MagnitudeView.hpp"
//#include "UFixBigInt.hpp"


/*
namespace utils {
	template<std::size_t Alpha = 8>
	class isaac64;
}
*/
// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)

namespace ppvr {
	namespace math {
	
		template <BIG_INT_WORD_COUNT_TYPE S>
		class UFixBigInt;
		
		class UArbBigInt {

		// ----- statics -----
		public:
			//template <BIG_INT_WORD_COUNT_TYPE S>
			//friend int UFixBigInt<S>::fromUArbBigInt();
			
			//template <BIG_INT_WORD_COUNT_TYPE S>
			//friend class UFixBigInt;
			
			friend std::ostream& operator << ( std::ostream& os, const UArbBigInt& value ){
				os << value.toStringDec();
				return os;
			}

			static const UArbBigInt ZERO;
			static const UArbBigInt ONE;
			static const UArbBigInt TWO;
			static const UArbBigInt TEN;
			
		private:
			static const BIG_INT_WORD_TYPE bnExpModThreshTable[]; // Sentinel
			
		public:
			static UArbBigInt fromUint64(const uint64_t& uint64Val);
		protected:
			static UArbBigInt& fromUint64(const uint64_t& uint64Val, UArbBigInt &target );

		public:
			static UArbBigInt fromString(const std::string& str, const BIG_INT_WORD_TYPE base);
		protected:
			static UArbBigInt& fromString(const std::string& str, const BIG_INT_WORD_TYPE base, UArbBigInt &target );

		public:
			template <BIG_INT_WORD_COUNT_TYPE S>
			static UArbBigInt fromUFixBigInt(const UFixBigInt<S>& src);

		protected:
			template <BIG_INT_WORD_COUNT_TYPE S>
			static UArbBigInt& fromUFixBigInt(const UFixBigInt<S>& src, UArbBigInt &target);

		// ----- statics rendome -----
			/*
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
			*/
		public:

			static UArbBigInt randomNumber(const uint& sizeInBit, Random& rnd);
			static UArbBigInt randomNumber(const UArbBigInt& upperBound, Random& rnd);
		protected:
			static UArbBigInt& randomNumber(const uint& sizeInBit, Random& rnd, UArbBigInt &target);
			static UArbBigInt& randomNumber(const UArbBigInt& upperBound, Random& rnd, UArbBigInt &target);

		// ----- member variables -----
		private:
			BIG_INT_WORD_COUNT_TYPE wordSize = 0; // count of used words (wordCount)
			BIG_INT_WORD_COUNT_TYPE wordCapacity = 0; // length of the value array
			BIG_INT_WORD_TYPE *value = NULL;
			//std::shared_ptr<BIG_INT_WORD_TYPE[]> value;
		public:
			inline const BIG_INT_WORD_TYPE* getData() const {
				return this->value;
			}
			
			inline BIG_INT_WORD_TYPE* getDataUnsafe() {
				return this->value;
			}
			
		// ----- constructors -----
		public:
			UArbBigInt();
			UArbBigInt(const BIG_INT_WORD_TYPE& value);
			UArbBigInt(const BIG_INT_WORD_TYPE& value, BIG_INT_WORD_COUNT_TYPE minCapacity);
			
			/**
			 * Copy constructor
			 */
			UArbBigInt(const UArbBigInt& src);
			UArbBigInt(const UArbBigInt& src, BIG_INT_WORD_COUNT_TYPE minCapacity);
			
			/**
			 * Move constructor
			 */
			UArbBigInt(UArbBigInt&& src);
		private:
			UArbBigInt(BIG_INT_WORD_TYPE* value, BIG_INT_WORD_COUNT_TYPE wordCapacity, BIG_INT_WORD_COUNT_TYPE wordSize);
		public:
			~UArbBigInt();

		

		// ----- memory managment -----
		public:
			/**
			 * Copy assignment operator
			 */
			UArbBigInt& operator= (const UArbBigInt& other);

			/**
			 * Move assignment operator
			 */
			UArbBigInt& operator= (UArbBigInt&& other);

		private:

			/**
			 * Increase the capacity of the Integer to a value that's greater or equal to newCapacity.
			 * If new_cap is greater than the current capacity(), new storage is allocated, otherwise the method does nothing.
			 */
			void reserveWords( const BIG_INT_WORD_COUNT_TYPE newCapacity );

			void reserveWordsAndInitUnused( const BIG_INT_WORD_COUNT_TYPE newCapacity, const BIG_INT_WORD_TYPE initValue = 0 );

			void initUnusedWords(const BIG_INT_WORD_TYPE initValue = 0);

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
			void clearBit(const uint n);

		public:
			/**
			 * Returns a BigInteger whose value is equivalent to this BigInteger
			 * with the designated bit set.  (Computes {@code (this | (1<<n))}.)
			 *
			 * @param  n index of bit to set.
			 * @return {@code this | (1<<n)}
			 */
			UArbBigInt withBit(const uint n);

			/**
			 * Returns a BigInteger whose value is equivalent to this BigInteger
			 * with the designated bit cleared.
			 * (Computes {@code (this & ~(1<<n))}.)
			 *
			 * @param  n index of bit to clear.
			 * @return {@code this & ~(1<<n)}
			 */
			UArbBigInt withoutBit(const uint n);

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
		public:
			/**
			 * @return the count of used words (index of the word with the most significant bit + 1)
			 */
			inline BIG_INT_WORD_COUNT_TYPE getWordSize() const {
				return this->wordSize;
			}
		protected:
			/**
			 * Decreases the word count to newMaxWordSize.
			 * If the word newMaxWordSize-1 is 0 then set the wordSize to newMaxWordSize-1.
			 * If this is also 0 the set it to newMaxWordSize-2, and so on.
			 * The param newMaxWordSize need to be <= this->wordCapacity
			 *
			 * @param newMaxWordSize new maximal word count
			 */
			void trimWordSize(const BIG_INT_WORD_COUNT_TYPE newMaxWordSize);

			inline BIG_INT_WORD_TYPE getLeastSignificantWord() const {
				return this->value[0];
			}

		private:
			

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
			UArbBigInt operator<< (const uint bits) const;

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
			UArbBigInt operator>> (const uint bits) const;
			
		// ----- boolean operations -----
		protected:
			void boolXor(const UArbBigInt &other);
		public:
			UArbBigInt operator^ (const UArbBigInt& other) const;
			
		protected:
			void boolAnd(const UArbBigInt &other);
		public:
			UArbBigInt operator& (const UArbBigInt& other) const;
			

		// ----- addition -----
		protected:
			/**
			 * this = this + word
			 */
			void addInt(const BIG_INT_WORD_TYPE word);

			void add(const UArbBigInt &other, UArbBigInt &result) const;
			void add(const UArbBigInt &other);

		public:
			UArbBigInt operator+ (const UArbBigInt& other) const;

		// ----- substraction -----
		private:

			

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
			BIG_INT_WORD_TYPE sub(const UArbBigInt& other, BIG_INT_WORD_TYPE carry, UArbBigInt &result) const;
			BIG_INT_WORD_TYPE sub(const UArbBigInt& other);

		public:
			UArbBigInt operator- (const UArbBigInt& other) const;

		// ----- multiplication -----

		protected:
			/**
			 * multiplication: result = this * ss2
			 */
			void mulInt(BIG_INT_WORD_TYPE ss2, UArbBigInt& result) const;

		private:
			void mulSchool(const UArbBigInt& a, const UArbBigInt& b, UArbBigInt& result) const;
			void mulSchoolBasic(const UArbBigInt& a, const UArbBigInt& b, UArbBigInt& result) const;

		protected:
			/**
			 * result = this * b
			 */
			void mul(const UArbBigInt& b, UArbBigInt& result) const;

			/**
			 * this = this * b
			 */
			void mul(const UArbBigInt& b);

		public:
			UArbBigInt operator* (const UArbBigInt& other) const;

		// ----- division -----

		// -- divInt

		protected:
			/**
			 * division by one unsigned word
			 * restul = this / divisor
			 *
			 * returns the remainder
			 */
			BIG_INT_WORD_TYPE divInt(BIG_INT_WORD_TYPE divisor, UArbBigInt& result) const;

			/**
			 * division by one unsigned word
			 * this = this / divisor
			 *
			 * returns the remainder
			 */
			BIG_INT_WORD_TYPE divInt(BIG_INT_WORD_TYPE divisor);

		private:
			// -- divKnuth

			void divKnuth_division(UArbBigInt divisor, UArbBigInt &result, UArbBigInt& remainder, uint m, uint n) const;
			void divKnuth_makeNewU(UArbBigInt &uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n, BIG_INT_WORD_TYPE u_max) const;
			void divKnuth_copyNewU(const UArbBigInt & uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n);

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
			BIG_INT_WORD_TYPE divKnuth_normalize(UArbBigInt& divisor, uint n, uint & d);

			void divKnuth_unnormalize(BIG_INT_WORD_COUNT_TYPE d);
			BIG_INT_WORD_TYPE divKnuth_calculate(BIG_INT_WORD_TYPE u2, BIG_INT_WORD_TYPE u1, BIG_INT_WORD_TYPE u0, BIG_INT_WORD_TYPE v1, BIG_INT_WORD_TYPE v0) const;

			/**
			 * D4. [Multiply and subtract]
			 *		includes also: D5. [Test Remainder] and D6. [add back]
			 *
			 */
			void divKnuth_multiplySubtract(	UArbBigInt & uu,  const UArbBigInt & vv, BIG_INT_WORD_TYPE & qp) const;

			/**
			 * the third division algorithm
			 *
			 * this algorithm is described in the following book:
			 * "The art of computer programming 2" (4.3.1 page 257)
			 * Donald E. Knuth
			 * !! give the description here (from the book)
			 */
			void divKnuth(const UArbBigInt& divisor, UArbBigInt &result, UArbBigInt& remainder) const;

		protected:
			/**
			 * result = this / divisor
			 */
			void div(const UArbBigInt& divisor, UArbBigInt &result, UArbBigInt& remainder) const;

			/**
			 * this = this / divisor
			 */
			void div(const UArbBigInt& divisor, UArbBigInt& remainder);

		public:
			UArbBigInt operator/ (const UArbBigInt& other) const;
			UArbBigInt operator% (const UArbBigInt& other) const;

		// ----- pow(), sqrt() -----
		private:
			
			static void square(const UArbBigInt& a, UArbBigInt& result);
			
		public:

			/**
			 * power this = this ^ pow
			 * binary algorithm (r-to-l)
			 */
			UArbBigInt pow(UArbBigInt pow) const;

			/**
			 * square root
			 * e.g. BigInt(9).sqrt() = 3
			 * ('digit-by-digit' algorithm)
			 */
			UArbBigInt sqrt() const;

		// ----- modInverse / gcd -----
		private:
			static UArbBigInt gcd(const UArbBigInt & a, const UArbBigInt & b);
			UArbBigInt gcd(const UArbBigInt & b) const;
			
			//static uint gcdExtended_binaryIterative_removePowersOfTwo(UArbBigInt& a, UArbBigInt& b);
			//static void gcdExtended_binaryIterative(const UArbBigInt& aIn, const UArbBigInt& bIn, UArbBigInt& u, UArbBigInt& v, UArbBigInt* gcd = nullptr);
			/**
			 * Function for a binary extended Euclidean Algorithm that uses only unsigned arithmetic.
			 * It returns not only the gcd but alls the the Bézout coefficients, u and v, which satisfy: a.*u + b.*v = gcd.
			 * The Bézout coefficients are useful for solving Diophantine equations.
			 * @return gcd of b and a.

			 */
			static UArbBigInt gcdExtended_binaryIterative(const UArbBigInt& aIn, const UArbBigInt& bIn, UArbBigInt& u, UArbBigInt& v);
			
		public:
			UArbBigInt modInverse(const UArbBigInt & m) const;
			
		// ----- modPow -----
		private:
			static void modPow_naiv(const UArbBigInt& base, UArbBigInt &exponent, const UArbBigInt &modulus, UArbBigInt& result);
			
			/**
			 * Efficient Modular Exponentiation with Montgomery Reduction and the K-Ary method
			 * based on the example implementation : https://www.codeproject.com/Tips/791253/ModPow
			 *
			 * https://www.nayuki.io/page/montgomery-reduction-algorithm
			 * https://www.nayuki.io/res/montgomery-reduction-algorithm/MontgomeryReducer.java
			 */
			static void modPow_montgomery(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result);
			static void modPow_montgomeryEven(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result);
			static void modPow_montgomeryOdd(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result);
			/**
			 * Iterates the exponent from right to left, i.e. the least significant bit to the most significant.
			 */
			static void modPow_montgomeryOdd_leastToMostSig(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result);
			
			
			//static uint32_t CeilLog2(UArbBigInt V);
			//static void gcdExtended_binary4mont(UArbBigInt a, UArbBigInt b, UArbBigInt& u, UArbBigInt& v);
			
		private:
			static UArbBigInt montgomeryIn(const UArbBigInt& A, const UArbBigInt& modulus, const uint reducerBits);
			static UArbBigInt montgomeryOut(const UArbBigInt& A, const UArbBigInt& reciprocal, const UArbBigInt& modulus);
			static UArbBigInt montgomeryMultiply(const UArbBigInt& A, const UArbBigInt& B, const UArbBigInt& modulus, const UArbBigInt& factor, const uint reducerBits, const UArbBigInt& mask);
			static UArbBigInt montgomerySquare(const UArbBigInt& A, const UArbBigInt& modulus, const UArbBigInt& factor, const uint reducerBits, const UArbBigInt& mask);
			static UArbBigInt montgomeryReduce(const UArbBigInt& product, const UArbBigInt& modulus, const UArbBigInt& factor, const uint reducerBits, const UArbBigInt& mask);
			
			/**
			 * ModPow - Special Case (modulus == 2^p)
			 * this = base
			 * @return this^exponent % 2^p
			 */
			UArbBigInt modPow2(UArbBigInt exponent, uint p) const ;
			/**
			 * Returns a BigInteger whose value is this mod(2^p).
			 * Assumes that this {@code BigInteger >= 0} and {@code p > 0}.
			 */
			UArbBigInt mod2(uint p) const;
			
			static void modPow_montgomeryOdd_window(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result);
			
			/**
			 * Montgomery reduce n, modulo mod.  This reduces modulo mod and divides
			 * by 2^(32*mlen). 
			 */
			static void montReduce(UArbBigInt& n, const UArbBigInt& mod, BIG_INT_WORD_COUNT_TYPE mlen, BIG_INT_WORD_COUNT_TYPE inv);
			static void montgomeryMultiply(const UArbBigInt& a, const UArbBigInt& b, const UArbBigInt& n, BIG_INT_WORD_COUNT_TYPE len, uint64_t inv, UArbBigInt& product);
			static void montgomerySquare(const UArbBigInt& a, const UArbBigInt& n, BIG_INT_WORD_COUNT_TYPE len, uint64_t inv, UArbBigInt& product);
			static void implMontgomeryMultiplyChecks(const UArbBigInt& a, const UArbBigInt& b, const UArbBigInt& n, BIG_INT_WORD_COUNT_TYPE len, UArbBigInt& product);
			
			/**
			 * Multiply an array by one word k and add to result, return the carry
			 */
			static BIG_INT_WORD_TYPE mulAdd(MagnitudeView& out, const MagnitudeView& in, BIG_INT_WORD_COUNT_TYPE offset, BIG_INT_WORD_COUNT_TYPE len, BIG_INT_WORD_TYPE k);
			
			/**
			 * Parameters validation.
			 */
			static void implMulAddCheck(const MagnitudeView& out, const MagnitudeView& in, BIG_INT_WORD_COUNT_TYPE offset, BIG_INT_WORD_COUNT_TYPE len, BIG_INT_WORD_TYPE k);
			
			/**
			 * Java Runtime may use intrinsic for this method.
			 */
			static BIG_INT_WORD_TYPE implMulAdd(MagnitudeView& out, BIG_INT_WORD_COUNT_TYPE indexOut, const MagnitudeView& in, BIG_INT_WORD_COUNT_TYPE indexIn, BIG_INT_WORD_COUNT_TYPE len, BIG_INT_WORD_TYPE k);
			
		public:
			/**
			 * Returns a BigInteger whose value is
			 * <code>(this<sup>exponent</sup> mod m)</code>.  (Unlike {@code pow}, this
			 * method permits negative exponents.)
			 *
			 * @param  exponent the exponent.
			 * @param  modulus the modulus.
			 * @param  result <code>this<sup>exponent</sup> mod m</code>
			 * @throws ArithmeticException {@code m} &le; 0 or the exponent is
			 *         negative and this BigInteger is not <i>relatively
			 *         prime</i> to {@code m}.
			 * @see    #modInverse
			 */
			void modPow(UArbBigInt &exponent, const UArbBigInt &modulus, UArbBigInt& result) const;
			
			/**
			 * Returns a BigInteger whose value is
			 * <code>(this<sup>exponent</sup> mod m)</code>.  (Unlike {@code pow}, this
			 * method permits negative exponents.)
			 *
			 * @param  exponent the exponent.
			 * @param  modulus the modulus.
			 * @return <code>this<sup>exponent</sup> mod m</code>
			 * @throws ArithmeticException {@code m} &le; 0 or the exponent is
			 *         negative and this BigInteger is not <i>relatively
			 *         prime</i> to {@code m}.
			 * @see    #modInverse
			 */
			UArbBigInt modPow(const UArbBigInt &exponent, const UArbBigInt &modulus) const;
			
		// ----- Comparison operators -----
		public:
			bool operator< (const UArbBigInt& other) const;
			bool operator<= (const UArbBigInt& other) const;
			bool operator> (const UArbBigInt& other) const;
			bool operator>= (const UArbBigInt& other) const;
			bool operator== (const UArbBigInt& other) const;
			bool operator!= (const UArbBigInt& other) const;
		};
	}
}

#include "UArbBigInt_impl.hpp"
