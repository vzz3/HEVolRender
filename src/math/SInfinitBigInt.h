#pragma once
#include "BigInt.h"
#include <string>

// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)

namespace ppvr {
	namespace math {
		class SInfinitBigInt: protected BigInt {
		public:
			friend std::ostream& operator << ( std::ostream& os, const SInfinitBigInt& value ) {
				os << value.toStringDec();
				return os;
			}
			
			static SInfinitBigInt fromInt64(const int64_t& value);
			static SInfinitBigInt fromString(std::string str, const BIG_INT_WORD_TYPE base);
			
			SInfinitBigInt();
			SInfinitBigInt(const BIG_INT_WORD_TYPE& value, bool negative = false);
			SInfinitBigInt(const BIG_INT_WORD_TYPE& value, BIG_INT_WORD_COUNT_TYPE minCapacity, bool negative = false);
			SInfinitBigInt(const BigInt& value, bool negative = false);
			SInfinitBigInt(const SInfinitBigInt& value);
			~SInfinitBigInt();
			
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
			
			// --- General purpose mathematical methods ---
			SInfinitBigInt operator<< (const uint bits) const;
			SInfinitBigInt operator>> (const uint bits) const;
			SInfinitBigInt operator+ (const SInfinitBigInt& other) const;
			SInfinitBigInt operator- (const SInfinitBigInt& other) const;
		private:
			SInfinitBigInt subAsPositive(const BigInt& a, const BigInt& b) const;
		public:
			SInfinitBigInt operator* (const SInfinitBigInt& other) const;
			SInfinitBigInt operator/ (const SInfinitBigInt& other) const;
			SInfinitBigInt operator% (const SInfinitBigInt& other) const;
			
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
			
			
			/* ---------- comparisons ---------- */
			bool operator< (const SInfinitBigInt& other) const;
			bool operator<= (const SInfinitBigInt& other) const;
			bool operator> (const SInfinitBigInt& other) const;
			bool operator>= (const SInfinitBigInt& other) const;
			bool operator== (const SInfinitBigInt& other) const;
			bool operator!= (const SInfinitBigInt& other) const;
			
			
			
			// Copy assignment operator
			SInfinitBigInt& operator= (const SInfinitBigInt& other);
		private:
			int_fast8_t signum;
		
		public:
			int bitLength() const;
			
		protected:
			void setZero();
			void setOne();
			void setAbs();
			void setNegate();
		
		public:
			bool isZero() const;
			
			bool isOne() const;
			
		/* ---------- modInverse / gcd ---------- */
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
			
		/* ---------- modPow ---------- */
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
			
		private:
			
			SInfinitBigInt modPow_naiv(const SInfinitBigInt &exponent, const BigInt &modulus) const;
			
			/**
			 * Returns a BigInteger whose value is (this ** exponent) mod (2**p)
			 */
			SInfinitBigInt modPow2(SInfinitBigInt exponent, int p) const;
			
			/**
			 * Returns a BigInteger whose value is this mod(2**p).
			 * Assumes that this {@code BigInteger >= 0} and {@code p > 0}.
			 */
			SInfinitBigInt mod2(int p) const;
			
		};
	}
}
