#pragma once

/*
 * Requirements on BigInt Type:
 *     - Contructor with one parameter aceptes a "1" as integer literal to create 1 in a math sence.
 *     - bitwise and operator (&)
 *     - multiply operator (*)
 *     - addition operator (+)
 *     - mod operator (%)
 *     - substraction operator (-)
 *     - less then comparison operator (<)
 *     - a left shift operator (>>)
 *     - a member method bitLength() which returns the count of bits between the (least signicant bit) and (the most signicant bit which is one) + 1 e.g. for the binary number 01001000 the bitLength() is 7.
 *     - a member method BigInt.square() that returns a*a
 *     - a member method BigInt.modInverse(BigInt& m) that returns the multiplicative inverse in m
 *     - a member method BigInt.gcd(BigInt& b) that returns the greatest comon divisor (rewuired only for testing in debug builds)
 */

namespace ppvr {
	namespace math {
		template <typename BigInt>
		class MontgomeryReducer {
		
		// ----- member variables -----
		private:
			uint reducerBits;
			BigInt reducer, modulus, mask, reciprocal, factor, convertedOne;
			
		public:
			const BigInt& getConvertedOne() const {
				return convertedOne;
			}
			
		// ----- constructors -----
		public:
			MontgomeryReducer(const BigInt& yModulus);
			
			/**
			 * copy constructor
			 */
			//MontgomeryReducer(const UFixBigInt<S>& src);
			
			~MontgomeryReducer();
			
		
			BigInt convertIn(const BigInt& plainValue) const;
			BigInt convertOut(const BigInt& encodedValue) const;
			
			BigInt multiply(const BigInt& encodedA, const BigInt& encodedB);
			BigInt square(const BigInt& encodedA);
			
			BigInt reduce(const BigInt& encodedProduct) const;
			
		};
	}
}

#include "MontgomeryReducer_impl.hpp"
