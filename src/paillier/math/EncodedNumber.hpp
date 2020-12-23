#pragma once

#include "../Paillier_typeDev.h"

// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)
using namespace ppvr::math;

namespace ppvr {
	namespace paillier {
		namespace math {
			class EncodedNumber {

			// ----- member variables -----
			public:
				/**
				 * The value of the encoded number. Must be a non-negative integer less than modulus of the public key.
				 */
				const PaillierInt mantissa;

				/**
				 * The exponent of the encoded number.
				 */
				const int32_t exponent;

			public:
				/**
				 * Constructs an encoded floating point number number.
				 *
				 * @param value of the encoded number must be a non-negative integer less than the modulus of the public key.
				 * @param exponent of the encoded number.
				 */
				EncodedNumber(const PaillierInt& yMantissa, const int32_t yExponent);
				~EncodedNumber();

				std::string toString() const;
				bool operator== (const EncodedNumber& other) const;

			};
		}
	}
}
