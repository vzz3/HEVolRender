#pragma once

#include "../../math/SInfinitBigInt.hpp"
#include "EncodingScheme.hpp"
#include "EncodedNumber.hpp"
#include "EncryptedNumber.hpp"
#include "../crypto/PublicKey.hpp"
#include "../crypto/SecureKey.hpp"

// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)
using namespace ppvr::math;
using namespace ppvr::paillier::crypto;

namespace ppvr {
	namespace paillier {
		namespace math {
			/**
			 * A class representing an encrypted number.
			 */
			class PaillierContext {
				
			// ----- member variables -----
			public:
				
				/**
				 * The default encoding digits after the comma.
				 */
				static constexpr double DefaultPrecission = 0.0001; // 0.0000001; // better then 1/255
				
				/**
				 * The default base value.
				 */
				static constexpr uint_fast32_t DEFAULT_BASE = 16;
				
				/**
				 * The mantissa as ciphertext.
				 */
				const EncodingScheme encoder;
				
			public:
				/**
				 * Constructs a Paillier context that allowes the calculation with encrypted floating point numbers.
				 *
				 * @param yEncoder
				 */
				PaillierContext(const EncodingScheme& yEncoder);
				
				/**
				 * Constructs a Paillier context that allowes the calculation with encrypted floating point numbers.
				 *
				 * @param yPK
				 * @param ySignedEncoding
				 * @param yPrecision
				 * @param yBase
				 */
				PaillierContext(const PublicKey& yPublicKey, const bool ySignedEncoding, const int_fast32_t yPrecision, const uint_fast32_t yBase);
				~PaillierContext();
				
				
				/**
				 * @return public key of this PaillierContext.
				 */
				const crypto::PublicKey getPublicKey() const {
					return encoder.getPublicKey();
				}
				
				/**
				 * @return the encoding scheme of this PaillierContext
				 */
				const EncodingScheme getEncodingScheme() const {
					return encoder;
				}
				
				EncodedNumber encode(const int64_t yValue) const {
					return encoder.encode(yValue);
				}
				EncodedNumber encode(SInfinitBigInt yValue) const {
					return encoder.encode(yValue);
				}
				EncodedNumber encode(const double yValue, const double yPrecision) const {
					return encoder.encode(yValue, yPrecision);
				}
				
				SInfinitBigInt decodeBigInt(const EncodedNumber& yEncoded) const {
					return encoder.decodeBigInt(yEncoded);
				}
				
				double decodeDouble(const EncodedNumber& yEncoded) const {
					return encoder.decodeDouble(yEncoded);
				}
				
				int64_t decodeInt64(const EncodedNumber& yEncoded) const {
					return encoder.decodeInt64(yEncoded);
				}
				
				int_fast8_t signum(const EncodedNumber& yNumber) const {
					return encoder.signum(yNumber);
				}
				
				/**
				 * Decreases the exponent of an {@code EncodedNumber} to {@code newExp}. If
				 * {@code newExp} is greater than the {@code EncodedNumber}'s current
				 * {@code exponent}, throws an IllegalArgumentException.
				 *
				 * @param yEncodedNumber the {@code EncodedNumber} which {@code exponent}
				 * will be reduced.
				 * @param yNewExp the new {@code exponent}, must be less than the current
				 * {@code exponent}.
				 * @return an {@code EncodedNumber} representing the same value with
				 * {@code exponent} equals to {@code newExp}.
				 */
				EncodedNumber decreaseExponentTo(const EncodedNumber& yEncodedNumber, const int32_t yNewExp) const;
				
				/**
				 * Decreases the exponent of an {@code EncryptedNumber} to {@code newExp}.
				 * If {@code newExp} is greater than the {@code EncryptedNumber}'s current
				 * {@code exponent}, throws an IllegalArgumentException.
				 *
				 * @param yEncryptedNumber the {@code EncryptedNumber} which {@code exponent}
				 * will be reduced.
				 * @param yNewExp the new {@code exponent}, must be less than the current
				 * {@code exponent}.
				 * @return an {@code EncryptedNumber} representing the same value with
				 * {@code exponent} equals to {@code newExp}.
				 */
				EncryptedNumber decreaseExponentTo(const EncryptedNumber& yEncryptedNumber, const int32_t yNewExp) const;
				
				/**
				 * Obfuscates an {@code EncryptedNumber} (add randome noice).
				 *
				 * @param yEncryptedNumber the {@code EncryptedNumber} to be obfuscated.
				 * @return The obfuscated version of yEncryptedNumber
				 */
				EncryptedNumber obfuscate(const EncryptedNumber& yEncryptedNumber) const;
				
				/**
				 * Encrypts an {@code EncodedNumber}.
				 *
				 * Checks whether the {@code EncodedNumber} to be encrypted has the same
				 * context as this {@code PaillierContext}. Encrypts the
				 * {@code EncodedNumber}'s {@code value}. Note that the {@code exponent} is
				 * not encrypted and the result {@code EncryptedNumber} is not obfuscated.
				 *
				 * @param yEncodedNumber the {@code EncodedNumber} to be encrypted.
				 * @param yObfuscate The encrypted value will be obfuscated (add randome noice) if true.
				 * @return the encryption result.
				 */
				EncryptedNumber encrypt(const EncodedNumber& yEncodedNumber, const bool yObfuscate = false) const;
				
				/**
				 * Encrypts a {@code BigInteger}.
				 *
				 * @param yValue to be encrypted.
				 * @param yObfuscate The encrypted value will be obfuscated (add randome noice) if true.
				 * @return the encryption result.
				 */
				EncryptedNumber encrypt(const SInfinitBigInt& yValue, const bool yObfuscate = false) const;
				
				/**
				 * Encrypts a {@code double}.
				 *
				 * @param value to be encrypted.
				 * @return the encryption result.
				 */
				//EncryptedNumber encrypt(const SInfinitBigInt& yValue, const bool yObfuscate = false) const {
				//	return encrypt(encode(yValue), yObfuscate);
				//}
				
				/**
				 * Encrypts a {@code double}.
				 *
				 * @param yValue to be encrypted.
				 * @param yPrecision denotes how different is the {@code value} from 0,
				 * {@code precision}'s value is between 0 and 1.
				 * @param yObfuscate The encrypted value will be obfuscated (add randome noice) if true.
				 * @return the encryption result.
				 */
				EncryptedNumber encrypt(const double yValue, const double yPrecision, const bool yObfuscate = false) const;
				
				/**
				 * Encrypts a {@code int64_t}.
				 *
				 * @param yValue to be encrypted.
				 * @param yObfuscate The encrypted value will be obfuscated (add randome noice) if true.
				 * @return the encryption result.
				 */
				EncryptedNumber encrypt(const int64_t yValue, const bool yObfuscate = false) const;
				
				/**
				 * Decrypts an encrypted number.
				 *
				 * @param ySecureKey
				 * @param yEncrypted EncryptedNumber to be decrypted.
				 * @return the decryption result.
				 * @throws PaillierKeyMismatchException if the encrypted number was not
				 * encoded with the appropriate public key.
				 */
				EncodedNumber decrypt(const SecureKey& ySecureKey, const EncryptedNumber& yEncrypted) const;
				
				/**
				 * Adds two EncryptedNumbers. Checks whether the {@code PaillierContext} of
				 * {@code operand1} and {@code operand2} are the same as this
				 * {@code PaillierContext}. If the operands' exponents are not the same,
				 * reduce the higher exponent to match with the lower exponent.
				 *
				 * @param yOperand1 first {@code EncryptedNumber}.
				 * @param yOperand2 second {@code EncryptedNumber}.
				 * @return the addition result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match this
				 * {@code PaillierContext}.
				 */
				EncryptedNumber add(const EncryptedNumber& yOperand1, const EncryptedNumber& yOperand2) const;
				
				/**
				 * Adds an {@code EncryptedNumber} and an {@code EncodedNumber}. Encrypts
				 * the {@code EncodedNumber} before adding them together.
				 *
				 * @param yOperand1 an {@code EncryptedNumber}.
				 * @param yOperand2 an {@code EncodedNumber}.
				 * @return the addition result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match this
				 * PaillirContext.
				 */
				EncryptedNumber add(const EncryptedNumber& yOperand1, const EncodedNumber& yOperand2) const;
				
				/**
				 * Adds an {@code EncodedNumber} and an {@code EncryptedNumber}. Encrypts
				 * the {@code EncodedNumber} before adding them together.
				 *
				 * @param yOperand1 an {@code EncodedNumber}.
				 * @param yOperand2 an {@code EncryptedNumber}.
				 * @return the addition result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match this
				 * PaillirContext.
				 */
				EncryptedNumber add(const EncodedNumber& yOperand1, const EncryptedNumber& yOperand2) const;
				
				/**
				 * Adds two {@code EncodedNumber}s. Checks whether the
				 * {@code PaillierContext} of {@code operand1} and {@code operand2} are the
				 * same as this {@code PaillierContext}. If the operands' exponents are not
				 * the same, reduce the higher exponent to match with the lower exponent.
				 *
				 * @param yOperand1 first {@code EncodedNumber}.
				 * @param yOperand2 second {@code EncodedNumber}.
				 * @return the addition result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match
				 * this{@code PaillierContext}.
				 */
				EncodedNumber add(const EncodedNumber& yOperand1, const EncodedNumber& yOperand2) const;
				
				/**
				 * Returns the additive inverse of {@code EncryptedNumber}.
				 *
				 * @param yOperand1 input.
				 * @return the additive inverse result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of {@code operand1} is not the same as this {@code PaillierContext}.
				 */
				EncryptedNumber additiveInverse(const EncryptedNumber& yOperand1) const;
				
				/**
				 * Returns the additive inverse of an {@code EncodedNumber}.
				 *
				 * @param yOperand1 input.
				 * @return the additive inverse.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of {@code operand1} is not the same as this {@code PaillierContext}.
				 */
				EncodedNumber additiveInverse(const EncodedNumber& yOperand1) const;
				
				/**
				 * Subtracts an {@code EncryptedNumber} ({@code operand2}) from another
				 * {@code EncryptedNumber} ({@code operand1}).
				 *
				 * @param yOperand1 first {@code EncryptedNumber}.
				 * @param yOperand2 second {@code EncryptedNumber}.
				 * @return the subtraction result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match this
				 * {@code PaillierContext}.
				 */
				EncryptedNumber subtract(const EncryptedNumber& yOperand1, const EncryptedNumber& yOperand2) const;
				
				/**
				 * Subtracts an {@code EncodedNumber} ({@code operand2}) from an
				 * {@code EncryptedNumber} ({@code operand1}).
				 *
				 * @param yOperand1 an {@code EncryptedNumber}.
				 * @param yOperand2 an {@code EncodedNumber}.
				 * @return the subtraction result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match this
				 * {@code PaillierContext}.
				 */
				EncryptedNumber subtract(const EncryptedNumber& yOperand1, const EncodedNumber& yOperand2) const;
				
				/**
				 * Subtracts an {@code EncryptedNumber} ({@code operand2}) from an
				 * {@code EncodedNumber} ({@code operand1}).
				 *
				 * @param yOperand1 an {@code EncodedNumber}.
				 * @param yOperand2 an {@code EncryptedNumber}.
				 * @return the subtraction result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match this
				 * {@code PaillierContext}.
				 */
				EncryptedNumber subtract(const EncodedNumber& yOperand1, const EncryptedNumber& yOperand2) const;
				
				/**
				 * Subtracts an {@code EncodedNumber} ({@code operand2}) from another
				 * {@code EncodedNumber} ({@code operand1}).
				 *
				 * @param yOperand1 first {@code EncodedNumber}.
				 * @param yOperand2 second {@code EncodedNumber}.
				 * @return the subtraction result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match this
				 * {@code PaillierContext}.
				 */
				EncodedNumber subtract(const EncodedNumber& yOperand1, const EncodedNumber& yOperand2) const;
				
				/**
				 * Multiplies an EncryptedNumber with an {@code EncodedNumber}.
				 *
				 * @param yOperand1 an {@code EncryptedNumber}.
				 * @param yOperand2 an {@code EncodedNumber}.
				 * @return the multiplication result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match this
				 * {@code PaillierContext}.
				 */
				EncryptedNumber multiply(const EncryptedNumber& yOperand1, const EncodedNumber& yOperand2) const;
				
				/**
				 * Multiplies an {@code EncodedNumber} with an {@code EncryptedNumber}.
				 *
				 * @param yOperand1 an {@code EncodedNumber}.
				 * @param yOperand2 an {@code EncryptedNumber}.
				 * @return the multiplication result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match this
				 * {@code PaillierContext}.
				 */
				EncryptedNumber multiply(const EncodedNumber& yOperand1, const EncryptedNumber& yOperand2) const;
				
				/**
				 * Multiplies two {@code EncodedNumber}s.
				 *
				 * @param yOperand1 an {@code EncodedNumber}.
				 * @param yOperand2 an {@code EncodedNumber}.
				 * @return the multiplication result.
				 * @throws PaillierContextMismatchException if the {@code PaillierContext}
				 * of either {@code operand1} or {@code operand2} does not match this
				 * {@code PaillierContext}.
				 */
				EncodedNumber multiply(const EncodedNumber& yOperand1, const EncodedNumber& yOperand2) const;
				
				bool operator== (const PaillierContext& other) const;
				
			};
		}
	}
}
