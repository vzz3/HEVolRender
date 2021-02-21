#pragma once
#include <string>
#include <memory>
#include <sys/types.h>

#include "BigInt_wordDef.h"

#include "Random.hpp"
#include "MontgomeryReducer.hpp"

#define FIX_BIG_INT_AUTO_SIZE_TEMP_VARS

#ifdef FIX_BIG_INT_AUTO_SIZE_TEMP_VARS
	#define FBI_WC_Sp1 (S+1)
	#define FBI_WC_Sm2 (S*2)
	
	/**
	 * For the Mongommery reduction we need at least 9 additional bit
	 * (see the line "this->reducer = one << reducerBits;" in the constructor of the MontgomeryReducer class.
	 * Therfore, we add an additional word if S*2 does not provide at least 9 more bits.
	 */
	#define FBI_WC_MM  ( ((S*2*BIG_INT_BITS_PER_WORD) > (S*BIG_INT_BITS_PER_WORD+9)) ? (S*2) : (S*2+1) )
#else
	#define FBI_WC_Sp1 (S)
	#define FBI_WC_Sm2 (S)
	#define FBI_WC_MM  (S)
#endif

/*
namespace utils {
	template<std::size_t Alpha = 8>
	class isaac64;
}
*/
// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)

namespace ppvr {
	namespace math {
		class UArbBigInt;
	
		template <BIG_INT_WORD_COUNT_TYPE S>
		class UFixBigInt {
			// make every version of this template classe a frend of every other version
			template<BIG_INT_WORD_COUNT_TYPE OS>
			friend class UFixBigInt;
			
			// make the MontgomeryReducer with the current teplate version a firend
			friend class MontgomeryReducer<UFixBigInt<S>>;
			
		public:
			friend std::ostream& operator << ( std::ostream& os, const UFixBigInt<S>& value ){
				os << value.toStringDec();
				return os;
			}
			
			
		// ----- statics -----
			static UFixBigInt<S> fromUint64(const uint64_t& uint64Val);
		protected:
			static UFixBigInt<S>& fromUint64(const uint64_t& uint64Val, UFixBigInt<S> &target );

		public:
			static UFixBigInt<S> fromString(const std::string& str, const BIG_INT_WORD_TYPE base);
		protected:
			static UFixBigInt<S>& fromString(const std::string& str, const BIG_INT_WORD_TYPE base, UFixBigInt<S> &target );

		public:
			static UFixBigInt<S> fromUArbBigInt(const UArbBigInt& src);
		protected:
			static UFixBigInt<S>& fromUArbBigInt(const UArbBigInt& src, UFixBigInt<S> &target);
			
		// ----- statics rendome -----
		public:

			static UFixBigInt<S> randomNumber(const uint& sizeInBit, Random& rnd);
			static UFixBigInt<S> randomNumber(const UFixBigInt<S>& upperBound, Random& rnd);
		protected:
			static UFixBigInt<S>& randomNumber(const uint& sizeInBit, Random& rnd, UFixBigInt<S> &target);
			static UFixBigInt<S>& randomNumber(const UFixBigInt<S>& upperBound, Random& rnd, UFixBigInt<S> &target);

		// ----- member variables -----
		private:
			BIG_INT_WORD_TYPE value[S];
			//std::shared_ptr<BIG_INT_WORD_TYPE[]> value;
			
		public:
			inline const decltype(value)& getData() const {
				return this->value;
			}
			
			inline decltype(value)& getDataUnsafe() {
				return this->value;
			}
			
		// ----- constructors -----
		public:
			UFixBigInt();
			UFixBigInt(const BIG_INT_WORD_TYPE& value);
			
			/**
			 * copy constructor
			 */
			UFixBigInt(const UFixBigInt<S>& src);
			
		protected:
			/*
			 * convert between different word counts/sizes
			 */
			template<BIG_INT_WORD_COUNT_TYPE OS>
			UFixBigInt(const UFixBigInt<OS>& src);
		public:
			~UFixBigInt();
			
		// ----- memory managment -----
		public:
			/**
			 * Copy assignment operator
			 * /
			UArbBigInt& operator= (const UArbBigInt& other);
 		*/
		private:
			void initWords(const BIG_INT_WORD_TYPE initValue = 0);

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
			UFixBigInt<S> withBit(const uint n);

			/**
			 * Returns a BigInteger whose value is equivalent to this BigInteger
			 * with the designated bit cleared.
			 * (Computes {@code (this & ~(1<<n))}.)
			 *
			 * @param  n index of bit to clear.
			 * @return {@code this & ~(1<<n)}
			 */
			UFixBigInt<S> withoutBit(const uint n);

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
			BIG_INT_WORD_COUNT_TYPE getWordSize() const;

		protected:
			/**
			 * Decreases the word count to newMaxWordSize.
			 * If the word newMaxWordSize-1 is 0 then set the wordSize to newMaxWordSize-1.
			 * If this is also 0 the set it to newMaxWordSize-2, and so on.
			 * The param newMaxWordSize need to be <= this->wordCapacity
			 *
			 * @param newMaxWordSize new maximal word count
			 * /
			void trimWordSize(const BIG_INT_WORD_COUNT_TYPE newMaxWordSize);
			 */
			BIG_INT_WORD_TYPE getLeastSignificantWord() const {
				return this->value[0];
			}
			
		public:
			/**
			 * Set the word with the index n and all higher words to zero.
			 */
			void clearHigherWords(const BIG_INT_WORD_COUNT_TYPE n);

		private:
			

		// ----- shift left -----
		private:
			/**
			 * an auxiliary method for moving bits into the left hand side
			 *
			 * this method moves only words
			 *
			 */
			void rcl_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, const uint bits, const BIG_INT_WORD_TYPE c);

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
			BIG_INT_WORD_TYPE rcl(const uint bits, const BIG_INT_WORD_TYPE c=0);

		public:
			UFixBigInt<S> operator<< (const uint bits) const;

		// ----- shift right -----
		private:
			/**
			 * an auxiliary method for moving bits into the right hand side
			 *
			 * this method moves only words
			 */
			void rcr_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, const uint bits, const BIG_INT_WORD_TYPE c);

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
			UFixBigInt<S> operator>> (const uint bits) const;

		// ----- bitwise operations -----
		protected:
			void bitXor(const UFixBigInt<S> &other);
		public:
			UFixBigInt<S> operator^ (const UFixBigInt<S>& other) const;
			
		protected:
			void bitAnd(const BIG_INT_WORD_COUNT_TYPE wordIndex, const BIG_INT_WORD_TYPE other);
			void bitAnd(const UFixBigInt<S> &other);
		public:
			UFixBigInt<S> operator& (const UFixBigInt<S>& other) const;
			
		// ----- addition -----
		protected:
			/**
			 * this = this + word
			 * @return carry
			 */
			//BIG_INT_WORD_TYPE addInt(const BIG_INT_WORD_TYPE word);

			/**
			 * result = result + word
			 * @return carry
			 */
			BIG_INT_WORD_TYPE add(const UFixBigInt<S> &other, UFixBigInt<S> &result) const;
			
			/**
			 * this = this + other
			 * @return carry
			 */
			BIG_INT_WORD_TYPE add(const UFixBigInt<S> &other);

		public:
			UFixBigInt<S> operator+ (const UFixBigInt<S>& other) const;

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
			BIG_INT_WORD_TYPE sub(const UFixBigInt<S>& other, BIG_INT_WORD_TYPE carry, UFixBigInt<S> &result) const;
			BIG_INT_WORD_TYPE sub(const UFixBigInt<S>& other);

		public:
			UFixBigInt<S> operator- (const UFixBigInt<S>& other) const;

		// ----- multiplication -----

		protected:
			/**
			 * multiplication: result = this * ss2
			 *
			 * The result size R need to be greater then the size of this value therefore there can not be a carry
			 */
			//template <BIG_INT_WORD_COUNT_TYPE R>
			void mulInt(const BIG_INT_WORD_TYPE ss2, UFixBigInt<S>& result) const;

		private:
			void mulSchool(const UFixBigInt<S>& a, const UFixBigInt<S>& b, UFixBigInt<S>& result) const;

		protected:
			/**
			 * result = this * b
			 */
			void mul(const UFixBigInt<S>& b, UFixBigInt<S>& result) const;

			/**
			 * this = this * b
			 */
			void mul(const UFixBigInt<S>& b);

		public:
			UFixBigInt<S> operator* (const UFixBigInt<S>& other) const;
			
		// ----- division -----

		// -- divInt

		protected:
			/**
			 * division by one unsigned word
			 * restul = this / divisor
			 *
			 * returns the remainder
			 */
			BIG_INT_WORD_TYPE divInt(const BIG_INT_WORD_TYPE divisor, UFixBigInt<S>& result) const;

			/**
			 * division by one unsigned word
			 * this = this / divisor
			 *
			 * returns the remainder
			 */
			BIG_INT_WORD_TYPE divInt(BIG_INT_WORD_TYPE divisor);

		private:
			// -- divKnuth

			void divKnuth_division(UFixBigInt<S> divisor, UFixBigInt<S> &result, UFixBigInt<S>& remainder, const BIG_INT_WORD_COUNT_TYPE m, const BIG_INT_WORD_COUNT_TYPE n) const;
			void divKnuth_makeNewU(UFixBigInt<FBI_WC_Sp1> &uu, const BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n, const BIG_INT_WORD_TYPE u_max) const;
			void divKnuth_copyNewU(const UFixBigInt<FBI_WC_Sp1> & uu, const BIG_INT_WORD_COUNT_TYPE j, const BIG_INT_WORD_COUNT_TYPE n);

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
			BIG_INT_WORD_TYPE divKnuth_normalize(UFixBigInt<S>& divisor, const BIG_INT_WORD_COUNT_TYPE n, uint& d);

			void divKnuth_unnormalize(const BIG_INT_WORD_COUNT_TYPE d);
			BIG_INT_WORD_TYPE divKnuth_calculate(const BIG_INT_WORD_TYPE u2, const BIG_INT_WORD_TYPE u1, const BIG_INT_WORD_TYPE u0, const BIG_INT_WORD_TYPE v1, const BIG_INT_WORD_TYPE v0) const;

			/**
			 * D4. [Multiply and subtract]
			 *		includes also: D5. [Test Remainder] and D6. [add back]
			 *
			 */
			void divKnuth_multiplySubtract(UFixBigInt<FBI_WC_Sp1> & uu,  const UFixBigInt<FBI_WC_Sp1> & vv, BIG_INT_WORD_TYPE & qp) const;

			/**
			 * the third division algorithm
			 *
			 * this algorithm is described in the following book:
			 * "The art of computer programming 2" (4.3.1 page 257)
			 * Donald E. Knuth
			 * !! give the description here (from the book)
			 */
			void divKnuth(const UFixBigInt<S>& divisor, UFixBigInt<S> &result, UFixBigInt<S>& remainder) const;

		protected:
			/**
			 * result = this / divisor
			 */
			void div(const UFixBigInt<S>& divisor, UFixBigInt<S> &result, UFixBigInt<S>& remainder) const;

			/**
			 * this = this / divisor
			 */
			void div(const UFixBigInt<S>& divisor, UFixBigInt<S>& remainder);

		public:
			UFixBigInt<S> operator/ (const UFixBigInt<S>& other) const;
			UFixBigInt<S> operator% (const UFixBigInt<S>& other) const;
			
		// ----- pow(), sqrt() -----
		private:
			/**
			 * Calculates a*a
			 */
			static void square(const UFixBigInt<S>& a, UFixBigInt<S>& result);
			
		public:
			/**
			 * @return this * this
			 */
			UFixBigInt<S> square() const;

			/**
			 * power this = this ^ pow
			 * binary algorithm (r-to-l)
			 */
			UFixBigInt<S> pow(UFixBigInt<S> pow) const;

			/**
			 * square root
			 * e.g. BigInt(9).sqrt() = 3
			 * ('digit-by-digit' algorithm)
			 */
			UFixBigInt<S> sqrt() const;
			
		// ----- modInverse / gcd -----
		private:
			static UFixBigInt<S> gcd(const UFixBigInt<S> & a, const UFixBigInt<S> & b);
		public:
			UFixBigInt<S> gcd(const UFixBigInt<S> & b) const;
			
		private:
			
			/**
			 * Function for a binary extended Euclidean Algorithm that uses only unsigned arithmetic.
			 * It returns not only the gcd but alls the the Bézout coefficients, u and v, which satisfy: a.*u + b.*v = gcd.
			 * The Bézout coefficients are useful for solving Diophantine equations.
			 * @return gcd of b and a.
			 */
			static UFixBigInt<S> gcdExtended_binaryIterative(const UFixBigInt<S>& aIn, const UFixBigInt<S>& bIn, UFixBigInt<S>& u/*, UFixBigInt<S>& v*/);
			
		public:
			UFixBigInt<S> modInverse(const UFixBigInt<S> & m) const;
			
		// ----- modPow -----
		private:
			static void modPow_naiv(UFixBigInt<FBI_WC_Sm2>& base, UFixBigInt<S> &exponent, const UFixBigInt<S> &modulus, UFixBigInt<FBI_WC_Sm2>& result);
			
			/**
			 * Efficient Modular Exponentiation with Montgomery Reduction and the K-Ary method
			 * based on the example implementation : https://www.codeproject.com/Tips/791253/ModPow
			 *
			 * https://www.nayuki.io/page/montgomery-reduction-algorithm
			 * https://www.nayuki.io/res/montgomery-reduction-algorithm/MontgomeryReducer.java
			 */
			static void modPow_montgomery(const UFixBigInt<S>& base, const UFixBigInt<S>& exponent, const UFixBigInt<S>& modulus, UFixBigInt<FBI_WC_Sm2>& result);
			static void modPow_montgomeryEven(const UFixBigInt<S>& base, const UFixBigInt<S>& exponent, const UFixBigInt<S>& modulus, UFixBigInt<FBI_WC_Sm2>& result);
			static void modPow_montgomeryOdd(const UFixBigInt<S>& base, const UFixBigInt<S>& exponent, const UFixBigInt<S>& modulus, UFixBigInt<FBI_WC_Sm2>& result);
			/**
			 * Iterates the exponent from right to left, i.e. the least significant bit to the most significant.
			 */
			static void modPow_montgomeryOdd_leastToMostSig(const UFixBigInt<S>& base, const UFixBigInt<S>& exponent, const UFixBigInt<S>& modulus, UFixBigInt<FBI_WC_Sm2>& result);
			
			/**
			 * Iterates the exponent from left  to right, i.e. the most significant bit to the least significant.
			 */
			static void modPow_montgomeryOdd_mostToLeastSig(const UFixBigInt<S>& base, const UFixBigInt<S>& exponent, const UFixBigInt<S>& modulus, UFixBigInt<FBI_WC_Sm2>& result);
			
			/**
			 * Left-To-Right K-ary Modular Exponentiation
			 */
			static void modPow_montgomeryOdd_kAry(const UFixBigInt<S>& base, const UFixBigInt<S>& exponent, const UFixBigInt<S>& modulus, UFixBigInt<FBI_WC_Sm2>& result);
			
		private:
			/**
			 * ModPow - Special Case (modulus == 2^p)
			 * this = base
			 * @return this^exponent % 2^p
			 */
			UFixBigInt<S> modPow2(UFixBigInt<S> exponent, uint p) const ;
			/**
			 * Returns a BigInteger whose value is this mod(2^p).
			 * Assumes that this {@code BigInteger >= 0} and {@code p > 0}.
			 */
			UFixBigInt<S> mod2(uint p) const;
			
		protected:
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
			void modPow(UFixBigInt<S> &exponent, const UFixBigInt<S> &modulus, UFixBigInt<FBI_WC_Sm2>& result) const;
			
		public:
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
			UFixBigInt<S> modPow(const UFixBigInt<S> &exponent, const UFixBigInt<S> &modulus) const;
			
		// ----- Comparison operators -----
		public:
			bool operator< (const UFixBigInt<S>& other) const;
			bool operator<= (const UFixBigInt<S>& other) const;
			bool operator> (const UFixBigInt<S>& other) const;
			bool operator>= (const UFixBigInt<S>& other) const;
			bool operator== (const UFixBigInt<S>& other) const;
			bool operator!= (const UFixBigInt<S>& other) const;

		};
	}
}

#include "UFixBigInt_impl.hpp"
