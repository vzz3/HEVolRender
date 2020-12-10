#pragma once
#include "UArbBigInt.hpp"
#include <string>

// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)

namespace ppvr {
	namespace math {
		/**
		 * Signed Arbitrary (Arb) length Big Integer class (length is not limited, not fixed-width(Fix) )
		 */
		class SArbBigInt: protected UArbBigInt {

		// ----- statics -----
		public:
			friend std::ostream& operator << ( std::ostream& os, const SArbBigInt& value ) {
				os << value.toStringDec();
				return os;
			}

			static SArbBigInt fromInt64(const int64_t& int64Val);
		protected:
			static SArbBigInt& fromInt64(const int64_t& int64Val, SArbBigInt &target );

		public:
			static SArbBigInt fromString(const std::string& str, const BIG_INT_WORD_TYPE base);
		protected:
			static SArbBigInt& fromString(std::string str, const BIG_INT_WORD_TYPE base, SArbBigInt &target );

		public:
			static SArbBigInt randomNumber(const uint& sizeInBit, Random& rnd);
			static SArbBigInt randomNumber(const SArbBigInt& upperBound, Random& rnd);
		protected:
			static SArbBigInt& randomNumber(const uint& sizeInBit, Random& rnd, SArbBigInt &target);
			static SArbBigInt& randomNumber(const SArbBigInt& upperBound, Random& rnd, SArbBigInt &target);

		private:

			static const SArbBigInt SmallPrimeProduct;

			static const SArbBigInt FirstPrimes[];

		public:
			/*
			 https://crypto.stackexchange.com/questions/1970/how-are-primes-generated-for-rsa
			 https://www.geeksforgeeks.org/how-to-generate-large-prime-numbers-for-rsa-algorithm/
			 */

			/**
			 * Returns a positive BigInteger that is probably prime, with the
			 * specified bitLength. The probability that a BigInteger returned
			 * by this method is composite does not exceed 2<sup>-100</sup>.
			 *
			 * @param  bitLength bitLength of the returned BigInteger.
			 * @param  rnd source of random bits used to select candidates to be
			 *         tested for primality.
			 * @return a BigInteger of {@code bitLength} bits that is probably prime
			 * @throws ArithmeticException {@code bitLength < 2} or {@code bitLength} is too large.
			 * @see    #bitLength()
			 * @since 1.4
			 */
			static SArbBigInt probablePrime(const uint& bitLength, Random& rnd);

		private:
			/**
			 * Find a random number of the specified bitLength that is probably prime.
			 * This method is used for smaller primes, its performance degrades on
			 * larger bitlengths.
			 *
			 * This method assumes bitLength > 1.
			 */
			static SArbBigInt smallPrime(const uint& bitLength, const uint& certainty, Random& rnd);


			/**
			 * Find a random number of the specified bitLength that is probably prime.
			 * This method is more appropriate for larger bitlengths since it uses
			 * a sieve to eliminate most composites before using a more expensive
			 * test.
			 */
			static SArbBigInt largePrime(const uint& bitLength, const uint& certainty, Random& rnd);

			/**
			 * This step is a a low level primality test which requires the pre-calculation of the first few hundred primes (using Sieve of Eratosthenes).
			 * The prime candidate is divided by the pre-generated primes to check for divisibility. If the prime candidate is perfectly divisible by any of these pre-generated primes, the test fails and a new prime candidate must be picked and tested. This is repeated as long as a value which is coprime to all the primes in our generated primes list is found
			 */
			static void lowLevelPrime(const uint& bitLength, Random& rnd, SArbBigInt &target);

			//static int getPrimeSearchLen(int bitLength);

			/**
			 * Returns {@code true} if this BigInteger is probably prime,
			 * {@code false} if it's definitely composite.
			 *
			 * This method assumes bitLength > 2.
			 *
			 * @param  certainty a measure of the uncertainty that the caller is
			 *         willing to tolerate: if the call returns {@code true}
			 *         the probability that this BigInteger is prime exceeds
			 *         {@code (1 - 1/2<sup>certainty</sup>)}.  The execution time of
			 *         this method is proportional to the value of this parameter.
			 * @return {@code true} if this BigInteger is probably prime,
			 *         {@code false} if it's definitely composite.
			 */
			bool primeToCertainty(const uint certainty, Random& rnd);

			/**
			 * Returns true if this BigInteger is a Lucas-Lehmer probable prime.
			 *
			 * The following assumptions are made:
			 * This BigInteger is a positive, odd number.
			 */
			bool passesLucasLehmer();

			/**
			 * Computes Jacobi(p,n).
			 * Assumes n positive, odd, n>=3.
			 */
			static int jacobiSymbol(int16_t p, const SArbBigInt& n); // TODO replace int16_t with int

			static SArbBigInt lucasLehmerSequence(int z, const SArbBigInt& k, const SArbBigInt& n);

			/**
			 * Returns true iff this BigInteger passes the specified number of
			 * Miller-Rabin tests. This test is taken from the DSA spec (NIST FIPS
			 * 186-2).
			 *
			 * The following assumptions are made:
			 * This BigInteger is a positive, odd number greater than 2.
			 * iterations<=50.
			 */
			bool passesMillerRabin(int iterations, Random& rnd);

		public:
			/**
			 * Returns {@code true} if this BigInteger is probably prime,
			 * {@code false} if it's definitely composite.  If
			 * {@code certainty} is &le; 0, {@code true} is
			 * returned.
			 *
			 * @param  certainty a measure of the uncertainty that the caller is
			 *         willing to tolerate: if the call returns {@code true}
			 *         the probability that this BigInteger is prime exceeds
			 *         (1 - 1/2<sup>{@code certainty}</sup>).  The execution time of
			 *         this method is proportional to the value of this parameter.
			 * @return {@code true} if this BigInteger is probably prime,
			 *         {@code false} if it's definitely composite.
			 */
			bool isProbablePrime(const uint certainty, Random& rnd);

		// ----- member variables -----
		private:
			int_fast8_t signum;

		public:
			int_fast8_t getSignum() const {
				return this->signum;
			}

		// ----- constructors -----
		public:
			SArbBigInt();
			SArbBigInt(const BIG_INT_WORD_TYPE& value, bool negative = false);
			SArbBigInt(const BIG_INT_WORD_TYPE& value, BIG_INT_WORD_COUNT_TYPE minCapacity, bool negative = false);
			SArbBigInt(const UArbBigInt& value, bool negative = false);
			SArbBigInt(const SArbBigInt& value);
			~SArbBigInt();

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
			SArbBigInt& operator= (const SArbBigInt& other);

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

			/**
			 * Returns a BigInteger whose value is the absolute value of this
			 * BigInteger.
			 *
			 * @return {@code abs(this)}
			 */
			SArbBigInt abs() const;

			/**
			 * Returns a BigInteger whose value is {@code (-this)}.
			 *
			 * @return {@code -this}
			 */
			SArbBigInt negate() const;

		// ----- shift left -----
		protected:
			BIG_INT_WORD_TYPE rcl(const uint bits, const BIG_INT_WORD_TYPE c=0, const bool resize=false);
		public:
			SArbBigInt operator<< (const uint bits) const;

		// ----- shift right -----
		protected:
			BIG_INT_WORD_TYPE rcr(const uint bits, const BIG_INT_WORD_TYPE c=0);
		public:
			SArbBigInt operator>> (const uint bits) const;

		// ----- addition -----
		protected:
			/**
			 * this = this + word
			 */
			//void addInt(const BIG_INT_WORD_TYPE word);

			void add(const SArbBigInt &other, SArbBigInt &result) const;
			void add(const SArbBigInt &other);

		public:
			SArbBigInt operator+ (const SArbBigInt& other) const;

		// ----- substraction -----
		private:
			BIG_INT_WORD_TYPE subInfUInt(const SArbBigInt& b, SArbBigInt& restul) const;
			//SArbBigInt subAsPositive(const BigInt& a, const BigInt& b) const;
			void subAsPositive(const SArbBigInt& a, const SArbBigInt& b, SArbBigInt& restul) const;

		protected:
			//BIG_INT_WORD_TYPE subInt(const BIG_INT_WORD_TYPE word);
			void sub(const SArbBigInt& other, SArbBigInt &result) const;
			void sub(const SArbBigInt& other);

		public:
			SArbBigInt operator- (const SArbBigInt& other) const;

		// ----- multiplication -----
		protected:
			/**
			 * multiplication: result = this * ss2
			 */
			//void mulInt(BIG_INT_WORD_TYPE ss2, BigInt& result) const;

			/**
			 * result = this * b
			 */
			void mul(const SArbBigInt& b, SArbBigInt& result) const;

			/**
			 * this = this * b
			 */
			void mul(const SArbBigInt& b);

		public:
			SArbBigInt operator* (const SArbBigInt& other) const;

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
			void div(const SArbBigInt& divisor, SArbBigInt &result, SArbBigInt& remainder) const;

			/**
			 * this = this / divisor
			 */
			void div(const SArbBigInt& divisor, SArbBigInt& remainder);

		public:
			SArbBigInt operator/ (const SArbBigInt& other) const;
			SArbBigInt operator% (const SArbBigInt& other) const;

		// ----- pow(), sqrt() -----
		public:
			/**
			 * power this = this ^ pow
			 * binary algorithm (r-to-l)
			 */
			SArbBigInt pow(SArbBigInt pow) const;

			/**
			 * square root
			 * e.g. BigInt(9).sqrt() = 3
			 * ('digit-by-digit' algorithm)
			 */
			SArbBigInt sqrt() const;


		// ----- Comparison operators -----
		public:
			bool operator< (const SArbBigInt& other) const;
			bool operator<= (const SArbBigInt& other) const;
			bool operator> (const SArbBigInt& other) const;
			bool operator>= (const SArbBigInt& other) const;
			bool operator== (const SArbBigInt& other) const;
			bool operator!= (const SArbBigInt& other) const;



		// ----- modInverse / gcd -----
		private:

			/**
			 * Function for extended Euclidean Algorithm
			 * return gcd of b and a.
			 *  also returns the Bézout coefficients, u and v, which satisfy: a.*u + b.*v = gcd.
			 *	The Bézout coefficients are useful for solving Diophantine equations.
			 */
			SArbBigInt gcdExtended(const SArbBigInt &a, const SArbBigInt &b, SArbBigInt &u, SArbBigInt &v) const;

			SArbBigInt gcdExtended_internRecursive(const SArbBigInt &a, const SArbBigInt &b, SArbBigInt &u, SArbBigInt &v) const;
			SArbBigInt gcdExtended_internIterative(const SArbBigInt &a, const SArbBigInt &b, SArbBigInt &u, SArbBigInt &v) const;

			/**
			 * Basic Euclidean Algorithm
			 * returns the gcd of a and b
			 */
			SArbBigInt gcd(const SArbBigInt & a, const SArbBigInt & b) const;

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
			SArbBigInt modInverse(const SArbBigInt &m) const;



		// ----- modPow -----
		private:
			SArbBigInt modPow_naiv(const SArbBigInt &exponent, const UArbBigInt &modulus) const;

			/**
			 * Returns a BigInteger whose value is (this ** exponent) mod (2**p)
			 */
			//SArbBigInt modPow2(SArbBigInt exponent, int p) const;

			/**
			 * Returns a BigInteger whose value is this mod(2**p).
			 * Assumes that this {@code BigInteger >= 0} and {@code p > 0}.
			 */
			//SArbBigInt mod2(int p) const;

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
			SArbBigInt modPow(const SArbBigInt &exponent, const SArbBigInt &m) const;

		};
	}
}
