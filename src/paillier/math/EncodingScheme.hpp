#pragma once

#include "../Paillier_typeDev.h"
#include "../crypto/PublicKey.hpp"
#include "EncodedNumber.hpp"

// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)
using namespace ppvr::math;

namespace ppvr {
	namespace paillier {
		namespace math {
			class EncodingScheme {

			// ----- member variables -----
			private:

				/**
				 * Denotes whether the numbers represented are signed or unsigned.
				 */
				const bool signedEncoding;

				/**
				 * The precision of this PaillierContext, denotes the number of bits used to
				 * represent valid numbers that can be encrypted using the associated
				 * {@code publicKey}.
				 */
				const int_fast32_t precision;

				/**
				 * The base used to compute encoding.
				 */
				const uint_fast32_t base;

				/**
				 * The result of log<sub>2</sub>base.
				 */
				const double log2Base;

				/**
				 * The maximum {@code value} of the {@code EncodedNumber} that can be
				 * encrypted using the associated {@code publicKey}.
				 */
				PaillierInt maxEncoded;

				/**
				 * The minimum {@code value} of the {@code EncodedNumber} that can be
				 * encrypted using the associated {@code publicKey}.
				 */
				PaillierInt minEncoded;

				/**
				 * The maximum value that can be encoded and encrypted using the associated
				 * {@code publicKey}.
				 */
				PaillierInt maxSignificand;

				/**
				 * The minimum value that can be encoded and encrypted using the associated
				 * {@code publicKey}.
				 */
				PaillierInt minSignificand;



				const crypto::PublicKey pk;

			public:
				/**
				 * Constructs a floating point encoding sheme
				 *
				 * @param yPK
				 * @param ySignedEncoding
				 * @param yPrecision
				 * @param yBase
				 */
				EncodingScheme(const crypto::PublicKey& yPK, const bool ySignedEncoding, const int_fast32_t yPrecision, const uint_fast32_t yBase);
				~EncodingScheme();

				const crypto::PublicKey getPublicKey() const {
					return pk;
				}

				/**
				 * Checks whether this EncodingScheme supports signed numbers.
				 *
				 * @return true if this EncodingScheme support signed numbers, false
				 * otherwise.
				 */
				bool isSigned() const {
					return signedEncoding;
				}

				/**
				 * Checks whether this EncodingScheme supports unsigned numbers.
				 *
				 * @return true if this EncodingScheme support unsigned numbers, false
				 * otherwise.
				 */
				bool isUnsigned() const {
					return !signedEncoding;
				}

				uint_fast32_t getBase() const {
					return base;
				}

				int_fast32_t getPrecision() const {
					return precision;
				}

				const PaillierInt& getMaxEncoded() const {
					return maxEncoded;
				}

				const PaillierInt& getMinEncoded() const {
					return minEncoded;
				}

				const PaillierInt& getMaxSignificand() const {
					return maxSignificand;
				}

				const PaillierInt& getMinSignificand() const {
					return minSignificand;
				}

				/**
				 * Returns the signum function of this EncodedNumber.
				 *
				 * @return -1, 0 or 1 as the value of this EncodedNumber is negative, zero
				 * or positive.
				 */
				int_fast8_t signum(const EncodedNumber& yNumber) const;

			private:
				/**
				 * Returns an exponent derived from precision. The exponent is calculated as
				 * <code>floor(log<sub>base</sub>precision)</code>.
				 *
				 * @param precision input precision used to generate an exponent.
				 * @return exponent for this {@code precision}.
				 */
				int_fast32_t getPrecExponent(double yPrecision) const;

			public:
				/**
				 * Encodes a {@code long} using this {@code PaillierContext}.
				 *
				 * @param value the {@code long} to be encoded.
				 * @return the encoding result.
				 * @throws EncodeException if the {@code value} is not valid.
				 */
				EncodedNumber encode(const int64_t yValue) const;

				/**
				 * Encodes a {@code BigInteger} using this {@code PaillierContext}. Throws
				 * EncodeException if the input value is greater than {@code maxSignificand}
				 * or is less than {@code minSignificand}.
				 *
				 * @param value the {@code BigInteger} to be encoded.
				 * @return the encoding result - {@code EncodedNumber}
				 * @throws EncodeException if the {@code value} is not valid.
				 */
				EncodedNumber encode(PaillierInt yValue) const;

				/**
				 * Encodes a {@code double} given a {@code precision} using this
				 * {@code PaillierContext}.
				 *
				 * @param value the {@code double} to be encoded.
				 * @param precision denotes how different is the {@code value} from 0,
				 * {@code precision}'s value is between 0 and 1.
				 * @return the encoding results.
				 * @throws EncodeException if the {@code value} and/or {@code maxExponent}
				 * is not valid.
				 */
				EncodedNumber encode(const double yValue, const double yPrecision) const;

			private:
				/**
				 * Returns an integer ({@code BigInteger}) representation of a floating
				 * point number. The integer representation is computed as
				 * <code>value * base<sup>exponent</sup></code> for non-negative numbers and
				 * <code>modulus + (value * base<sup>exponent</sup>)</code> for negative
				 * numbers.
				 *
				 * @param value a floating point number to be encoded.
				 * @param exponent the exponent to encode the number.
				 * @return the integer representation of the input floating point number.
				 */
				PaillierInt innerEncode(const double yValue, const int_fast32_t yExponent) const;

			private:
				/**
				 * Returns the value of an {@code EncodedNumber} for decoding. Throws a
				 * DecodeException if the value is greater than the {@code publicKey}'s
				 * {@code modulus}. If the value is less than or equal to
				 * {@code maxEncoded}, return the value. If the {@code PaillierContext} is
				 * signed and the value is less than or equal to {@code minEncoded}, return
				 * the value subtracted by {@code publicKey}'s {@code modulus}. Otherwise
				 * the significand is in the overflow region and hence throws a
				 * DecodeException.
				 *
				 * @param encoded the input {@code EncodedNumber}.
				 * @return the significand of the {@code EncodedNumber}.
				 */
				PaillierInt getSignificand(const EncodedNumber& yEncoded) const;

			public:

				/**
				 * Decodes to the exact {@code BigInteger} representation.
				 *
				 * @param encoded the {@code EncodedNumber} to be decoded.
				 * @return the decoding result.
				 * @throws DecodeException if the {@code encoded} cannot be decoded.
				 */
				PaillierInt decodeBigInt(const EncodedNumber& yEncoded) const;

				/**
				 * Decodes to the exact {@code double} representation. Throws
				 * DecodeException if the decoded result is
				 * {@link java.lang.Double#POSITIVE_INFINITY}, {@link java.lang.Double#NEGATIVE_INFINITY}
				 * or {@link java.lang.Double#NaN}.
				 *
				 * @param encoded the {@code EncodedNumber} to be decoded.
				 * @return the decoding result.
				 * @throws DecodeException if the {@code encoded} cannot be decoded.
				 */
				double decodeDouble(const EncodedNumber& yEncoded) const;

				/**
				 * Decodes to the exact {@code long} representation. Throws DecodeException
				 * if the decoded result is greater than {@link java.lang.Long#MAX_VALUE} or
				 * less than {@link java.lang.Long#MIN_VALUE}.
				 *
				 * @param encoded the {@code EncodedNumber} to be decoded.
				 * @return the decoding result.
				 * @throws DecodeException if the {@code encoded} cannot be decoded.
				 */
				int64_t decodeInt64(const EncodedNumber& yEncoded) const;

				/**
				 * Returns the rescaling factor to re-encode an {@code EncodedNumber} using the same {@code base}
				 * but with a different {@code exponent}. The rescaling factor is computed as <code>base</code><sup>expDiff</sup>.
				 *
				 * @param expDiff the exponent to for the new rescaling factor.
				 * @return the rescaling factor.
				 */
				PaillierInt getRescalingFactor(const int32_t expDiff) const;



				bool operator== (const EncodingScheme& other) const;

			};
		}
	}
}
