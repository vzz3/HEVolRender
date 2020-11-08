#pragma once
#include "BigInt.hpp"
#include <string>

// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)

namespace ppvr {
	namespace math {
		class SInfinitBigInt: protected BigInt {
			
		// ----- statics -----
		public:
			friend std::ostream& operator << ( std::ostream& os, const SInfinitBigInt& value ) {
				os << value.toStringDec();
				return os;
			}
			
			static SInfinitBigInt fromInt64(const int64_t& uint64Val);
		protected:
			static SInfinitBigInt& fromInt64(const int64_t& uint64Val, SInfinitBigInt &target );
			
		public:
			static SInfinitBigInt fromString(const std::string& str, const BIG_INT_WORD_TYPE base);
		protected:
			static SInfinitBigInt& fromString(std::string str, const BIG_INT_WORD_TYPE base, SInfinitBigInt &target );
			
		public:
			static SInfinitBigInt randomNumber(const uint& sizeInBit);
			static SInfinitBigInt randomNumber(const SInfinitBigInt& upperBound);
		protected:
			static SInfinitBigInt& randomNumber(const uint& sizeInBit, SInfinitBigInt &target);
			static SInfinitBigInt& randomNumber(const SInfinitBigInt& upperBound, SInfinitBigInt &target);
			
		// ----- member variables -----
		private:
			int_fast8_t signum;
			
		// ----- constructors -----
		public:
			SInfinitBigInt();
			SInfinitBigInt(const BIG_INT_WORD_TYPE& value, bool negative = false);
			SInfinitBigInt(const BIG_INT_WORD_TYPE& value, BIG_INT_WORD_COUNT_TYPE minCapacity, bool negative = false);
			SInfinitBigInt(const BigInt& value, bool negative = false);
			SInfinitBigInt(const SInfinitBigInt& value);
			~SInfinitBigInt();
			
		// ----- value export - toString / toUint64 -----
		public:
			/**
			 * Converts this BigInteger to a long.
			 * If this BigInteger is too big to fit in a unsingend long long (64bit), only the low-order 64 bits are returned.
			 * Note that this conversion can lose information about the overall magnitude of the BigInteger value
			 * //(as well as return a result with the opposite sign)
			 * .
			 */
			int64_t toInt64() const;
			
			std::string toStringHex() const;
			std::string toStringDec() const;
			
		// ----- memory managment -----
		public:
			/**
			 * Copy assignment operator
			 */
			SInfinitBigInt& operator= (const SInfinitBigInt& other);
			
		// ----- bit utilities -----
		public:
			int bitLength() const;
			
		protected:
			void setZero();
			void setOne();
			void setAbs();
			void setNegate();
			
		private:
			bool isMagnitudeZero() const;
			bool isMagnitudeOne() const;
			
		public:
			bool isZero() const;
			bool isOne() const;
			
		// ----- shift left -----
		protected:
			BIG_INT_WORD_TYPE rcl(const uint bits, const BIG_INT_WORD_TYPE c=0, const bool resize=false);
		public:
			SInfinitBigInt operator<< (const uint bits) const;
			
		// ----- shift right -----
		protected:
			BIG_INT_WORD_TYPE rcr(const uint bits, const BIG_INT_WORD_TYPE c=0);
		public:
			SInfinitBigInt operator>> (const uint bits) const;
			
		// ----- addition -----
		protected:
			/**
			 * this = this + word
			 */
			//void addInt(const BIG_INT_WORD_TYPE word);
			
			void add(const SInfinitBigInt &other, SInfinitBigInt &result) const;
			void add(const SInfinitBigInt &other);
			
		public:
			SInfinitBigInt operator+ (const SInfinitBigInt& other) const;
			
		// ----- substraction -----
		private:
			BIG_INT_WORD_TYPE subInfUInt(const SInfinitBigInt& b, SInfinitBigInt& restul) const;
			//SInfinitBigInt subAsPositive(const BigInt& a, const BigInt& b) const;
			void subAsPositive(const SInfinitBigInt& a, const SInfinitBigInt& b, SInfinitBigInt& restul) const;
		
		protected:
			//BIG_INT_WORD_TYPE subInt(const BIG_INT_WORD_TYPE word);
			void sub(const SInfinitBigInt& other, SInfinitBigInt &result) const;
			void sub(const SInfinitBigInt& other);
		
		public:
			SInfinitBigInt operator- (const SInfinitBigInt& other) const;
			
		// ----- multiplication -----
		protected:
			/**
			 * multiplication: result = this * ss2
			 */
			//void mulInt(BIG_INT_WORD_TYPE ss2, BigInt& result) const;
			
			/**
			 * result = this * b
			 */
			void mul(const SInfinitBigInt& b, SInfinitBigInt& result) const;
			
			/**
			 * this = this * b
			 */
			void mul(const SInfinitBigInt& b);
			
		public:
			SInfinitBigInt operator* (const SInfinitBigInt& other) const;
			
		// ----- division -----
		protected:
			/**
			 * division by one unsigned word
			 * restul = this / divisor
			 *
			 * returns the remainder
			 */
			//BIG_INT_WORD_TYPE divInt(BIG_INT_WORD_TYPE divisor, BigInt& result) const;
			
			/**
			 * division by one unsigned word
			 * this = this / divisor
			 *
			 * returns the remainder
			 */
			//BIG_INT_WORD_TYPE divInt(BIG_INT_WORD_TYPE divisor);
			
		
			/**
			 * result = this / divisor
			 */
			void div(const SInfinitBigInt& divisor, SInfinitBigInt &result, SInfinitBigInt& remainder) const;
			
			/**
			 * this = this / divisor
			 */
			void div(const SInfinitBigInt& divisor, SInfinitBigInt& remainder);
			
		public:
			SInfinitBigInt operator/ (const SInfinitBigInt& other) const;
			SInfinitBigInt operator% (const SInfinitBigInt& other) const;
			
		// ----- pow(), sqrt() -----
		public:
			/**
			 * power this = this ^ pow
			 * binary algorithm (r-to-l)
			 */
			SInfinitBigInt pow(SInfinitBigInt pow) const;
			
			/**
			 * square root
			 * e.g. BigInt(9).sqrt() = 3
			 * ('digit-by-digit' algorithm)
			 */
			SInfinitBigInt sqrt() const;
			
			
		// ----- Comparison operators -----
		public:
			bool operator< (const SInfinitBigInt& other) const;
			bool operator<= (const SInfinitBigInt& other) const;
			bool operator> (const SInfinitBigInt& other) const;
			bool operator>= (const SInfinitBigInt& other) const;
			bool operator== (const SInfinitBigInt& other) const;
			bool operator!= (const SInfinitBigInt& other) const;
			
		
			
		// ----- modInverse / gcd -----
		private:
			
			/**
			 * Function for extended Euclidean Algorithm
			 * return gcd of b and a.
			 *  also returns the Bézout coefficients, u and v, which satisfy: a.*u + b.*v = gcd.
			 *	The Bézout coefficients are useful for solving Diophantine equations.
			 */
			SInfinitBigInt gcdExtended(const SInfinitBigInt &a, const SInfinitBigInt &b, SInfinitBigInt &u, SInfinitBigInt &v) const;
			
			SInfinitBigInt gcdExtended_internRecursive(const SInfinitBigInt &a, const SInfinitBigInt &b, SInfinitBigInt &u, SInfinitBigInt &v) const;
			SInfinitBigInt gcdExtended_internIterative(const SInfinitBigInt &a, const SInfinitBigInt &b, SInfinitBigInt &u, SInfinitBigInt &v) const;
			
			/**
			 * Basic Euclidean Algorithm
			 * returns the gcd of a and b
			 */
			SInfinitBigInt gcd(const SInfinitBigInt & a, const SInfinitBigInt & b) const;
			
		public:
			/**
			 * Returns a BigInteger whose value is {@code (this}<sup>-1</sup> {@code mod m)}.
			 *
			 * @param  m the modulus.
			 * @return {@code this}<sup>-1</sup> {@code mod m}.
			 * @throws ArithmeticException {@code  m} &le; 0, or this BigInteger
			 *         has no multiplicative inverse mod m (that is, this BigInteger
			 *         is not <i>relatively prime</i> to m).
			 */
			SInfinitBigInt modInverse(const SInfinitBigInt &m) const;
			
		
			
		// ----- modPow -----
		private:
			SInfinitBigInt modPow_naiv(const SInfinitBigInt &exponent, const BigInt &modulus) const;
			
			/**
			 * Returns a BigInteger whose value is (this ** exponent) mod (2**p)
			 */
			//SInfinitBigInt modPow2(SInfinitBigInt exponent, int p) const;
			
			/**
			 * Returns a BigInteger whose value is this mod(2**p).
			 * Assumes that this {@code BigInteger >= 0} and {@code p > 0}.
			 */
			//SInfinitBigInt mod2(int p) const;
			
		public:
			/**
			 * Returns a BigInteger whose value is
			 * <code>(this<sup>exponent</sup> mod m)</code>.  (Unlike {@code pow}, this
			 * method permits negative exponents.)
			 *
			 * @param  exponent the exponent.
			 * @param  m the modulus.
			 * @return <code>this<sup>exponent</sup> mod m</code>
			 * @throws ArithmeticException {@code m} &le; 0 or the exponent is
			 *         negative and this BigInteger is not <i>relatively
			 *         prime</i> to {@code m}.
			 * @see    #modInverse
			 */
			SInfinitBigInt modPow(const SInfinitBigInt &exponent, const SInfinitBigInt &m) const;
			
		};
	}
}
