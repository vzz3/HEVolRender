#pragma once

#include "../../math/SInfinitBigInt.hpp"

// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)
using namespace ppvr::math;

namespace ppvr {
	namespace paillier {
		namespace math {
			/**
			 * A class representing an encrypted number.
			 */
			class EncryptedNumber {
				
			// ----- member variables -----
			public:
				/**
				 * The mantissa as ciphertext.
				 */
				const SInfinitBigInt ciphertext;
				
				/**
				 * The exponent of the encoded number.
				 */
				const int32_t exponent;
				
				/**
				 * Denotes whether the encrypted number has been obfuscated.
				 */
				//const bool isSafe;
				
			public:
				/**
				 * Constructs an encrypted floating point number number.
				 *
				 * @param yCiphertext The mantissa in encrypted representation of the encoded number. (non-negative integer less than the modulus^2 of the public key.)
				 * @param exponent of the encrypted number.
				 * @param isSafe set to true if ciphertext is obfuscated, false otherwise.
				 */
				EncryptedNumber(const SInfinitBigInt& yCiphertext, const int32_t yExponent);//, bool yIsSafe);
				~EncryptedNumber();
				
				//bool operator== (const EncodedNumber& other) const;
				
			};
		}
	}
}
