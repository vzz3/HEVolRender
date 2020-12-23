
#include "PaillierContext.hpp"

//#include <string>
//#include <iostream>
#include "exceptions.hpp"

using namespace ppvr::paillier::math;

PaillierContext::PaillierContext(const EncodingScheme& yEncoder):
	encoder(yEncoder) {

}

PaillierContext::PaillierContext(const PublicKey& yPublicKey, const bool ySignedEncoding, const int_fast32_t yPrecision, const uint_fast32_t yBase):
	PaillierContext(EncodingScheme(yPublicKey, ySignedEncoding, yPrecision, yBase)) {

}

PaillierContext::~PaillierContext() {}

EncodedNumber PaillierContext::decreaseExponentTo(const EncodedNumber& yEncodedNumber, const int32_t yNewExp) const {
	//PaillierInt significand = encodedNumber.getValue();
	//int32_t exponent = encodedNumber.getExponent();
	if (yNewExp > yEncodedNumber.exponent) {
		throw std::invalid_argument("New exponent: " + std::to_string(yNewExp) + "should be more negative than old exponent: " + std::to_string(yEncodedNumber.exponent) + ".");
	}

	const int32_t expDiff = yEncodedNumber.exponent - yNewExp;
	const PaillierInt bigFactor = encoder.getRescalingFactor(expDiff);
	const PaillierInt newEnc = (yEncodedNumber.mantissa * bigFactor) % getPublicKey().modulus;
	return EncodedNumber(newEnc, yNewExp);
}

EncryptedNumber PaillierContext::decreaseExponentTo(const EncryptedNumber& yEncryptedNumber, const int32_t yNewExp) const {
	if (yNewExp > yEncryptedNumber.exponent) {
		throw std::invalid_argument("New exponent: " + std::to_string(yNewExp) + "should be more negative than old exponent: " + std::to_string(yEncryptedNumber.exponent) + ".");
	}

	const int32_t expDiff = yEncryptedNumber.exponent - yNewExp;
	const PaillierInt bigFactor = encoder.getRescalingFactor(expDiff);
	const PaillierInt newEnc = encoder.getPublicKey().multiply(yEncryptedNumber.ciphertext, bigFactor);
	return EncryptedNumber(newEnc, yNewExp);
}

EncryptedNumber PaillierContext::obfuscate(const EncryptedNumber& yEncryptedNumber) const {
	return EncryptedNumber(getPublicKey().obfuscate(yEncryptedNumber.ciphertext), yEncryptedNumber.exponent);
}

EncryptedNumber PaillierContext::encrypt(const EncodedNumber& yEncodedNumber, const bool yObfuscate) const {
	const PaillierInt& mantissa = yEncodedNumber.mantissa;
	const PaillierInt ciphertext = yObfuscate ? encoder.getPublicKey().encrypt(mantissa) : encoder.getPublicKey().encryptWithoutObfuscation(mantissa);
	return EncryptedNumber(ciphertext, yEncodedNumber.exponent);
}

EncryptedNumber PaillierContext::encrypt(const PaillierInt& yValue, const bool yObfuscate) const {
	return encrypt(encode(yValue), yObfuscate);
}

EncryptedNumber PaillierContext::encrypt(const double yValue, const double yPrecision, const bool yObfuscate) const {
	return encrypt(encode(yValue, yPrecision), yObfuscate);
}

EncryptedNumber PaillierContext::encrypt(const int64_t yValue, const bool yObfuscate) const {
	return encrypt(encode(yValue), yObfuscate);
}

EncodedNumber PaillierContext::decrypt(const SecureKey& ySecureKey, const EncryptedNumber& yEncrypted) const {
	if (ySecureKey.publicKey != getPublicKey() ) {
		throw PaillierKeyMismatchException("Secure key does not belong to the public key of this context.");
	}

	return EncodedNumber(ySecureKey.decrypt(yEncrypted.ciphertext), yEncrypted.exponent);
}

EncryptedNumber PaillierContext::add(const EncryptedNumber& yOperand1, const EncryptedNumber& yOperand2) const {
	//checkSameContext(operand1);
	//checkSameContext(operand2);
	PaillierInt mantissa1 = yOperand1.ciphertext;
	PaillierInt mantissa2 = yOperand2.ciphertext;
	int32_t exponent1 = yOperand1.exponent;
	int32_t exponent2 = yOperand2.exponent;
	if (exponent1 > exponent2) {
		mantissa1 = getPublicKey().multiply(mantissa1, encoder.getRescalingFactor(exponent1 - exponent2));
		exponent1 = exponent2;
	} else if (exponent1 < exponent2) {
		mantissa2 = getPublicKey().multiply(mantissa2, encoder.getRescalingFactor(exponent2 - exponent1));
	} // else do nothing
	const PaillierInt result = getPublicKey().add(mantissa1, mantissa2);
	return EncryptedNumber(result, exponent1);
}

EncryptedNumber PaillierContext::add(const EncryptedNumber& yOperand1, const EncodedNumber& yOperand2) const {
	//checkSameContext(operand1);
	//checkSameContext(operand2);
	//addition only works if both numbers have the same exponent. Adjusting the exponent of an
	//encrypted number can only be done with an encrypted multiplication (internally, this is
	//done with a modular exponentiation).
	//It is going to be computationally much cheaper to adjust the encoded number before the
	//encryption as we only need to do a modular multiplication.
	int32_t exponent1 = yOperand1.exponent;
	int32_t exponent2 = yOperand2.exponent;
	PaillierInt mantissa2 = yOperand2.mantissa;
	if (exponent1 < exponent2) {
		mantissa2 = (mantissa2 * encoder.getRescalingFactor(exponent2 - exponent1)) % getPublicKey().modulus;
		return add(yOperand1, encrypt(EncodedNumber(mantissa2, exponent1)));
	}
	if (exponent1 > exponent2 && signum(yOperand2) == 1) {
		//test if we can shift value2 to the right without loosing information
		//Note, this only works for positive values.
		bool canShift = (mantissa2 % encoder.getRescalingFactor(exponent1 - exponent2) ).isZero();
		if (canShift) {
			mantissa2 = mantissa2 / encoder.getRescalingFactor(exponent1 - exponent2);
			return add(yOperand1, encrypt(EncodedNumber(mantissa2, exponent1)));
		}
	}
	return add(yOperand1, encrypt(yOperand2));
}

EncryptedNumber PaillierContext::add(const EncodedNumber& yOperand1, const EncryptedNumber& yOperand2) const {
	return add(yOperand2, yOperand1);
}

EncodedNumber PaillierContext::add(const EncodedNumber& yOperand1, const EncodedNumber& yOperand2) const {
	//checkSameContext(operand1);
	//checkSameContext(operand2);
	//final BigInteger modulus = publicKey.getModulus();
	PaillierInt mantissa1 = yOperand1.mantissa;
	PaillierInt mantissa2 = yOperand2.mantissa;
	int exponent1 = yOperand1.exponent;
	int exponent2 = yOperand2.exponent;
	if (exponent1 > exponent2) {
		mantissa1 = mantissa1 * encoder.getRescalingFactor(exponent1 - exponent2);
		exponent1 = exponent2;
	} else if (exponent1 < exponent2) {
		mantissa2 = mantissa2 * encoder.getRescalingFactor(exponent2 - exponent1);
	}
	const PaillierInt result = (mantissa1 + mantissa2) % getPublicKey().modulus;
	return EncodedNumber(result, exponent1);
}

EncryptedNumber PaillierContext::additiveInverse(const EncryptedNumber& yOperand1) const {
	//checkSameContext(operand1);
	return EncryptedNumber( yOperand1.ciphertext.modInverse(getPublicKey().getModulusSquared()), yOperand1.exponent );
}

EncodedNumber PaillierContext::additiveInverse(const EncodedNumber& yOperand1) const {
	//checkSameContext(operand1);
	if (yOperand1.mantissa.getSignum() == 0) {
		return yOperand1;
	}

	return EncodedNumber(getPublicKey().modulus - yOperand1.mantissa, yOperand1.exponent);
}

EncryptedNumber PaillierContext::subtract(const EncryptedNumber& yOperand1, const EncryptedNumber& yOperand2) const {
	return add(yOperand1, additiveInverse(yOperand2));
}

EncryptedNumber PaillierContext::subtract(const EncryptedNumber& yOperand1, const EncodedNumber& yOperand2) const {
	return add(yOperand1, encrypt(additiveInverse(yOperand2)));
}

EncryptedNumber PaillierContext::subtract(const EncodedNumber& yOperand1, const EncryptedNumber& yOperand2) const {
	return subtract(encrypt(yOperand1), yOperand2);
}

EncodedNumber PaillierContext::subtract(const EncodedNumber& yOperand1, const EncodedNumber& yOperand2) const {
	return add(yOperand1, additiveInverse(yOperand2));
}

EncryptedNumber PaillierContext::multiply(const EncryptedNumber& yOperand1, const EncodedNumber& yOperand2) const {
	//checkSameContext(operand1);
	//checkSameContext(operand2);
	PaillierInt encMantissa = yOperand1.ciphertext;
	PaillierInt mantissa = yOperand2.mantissa;
	PaillierInt negMantissa = getPublicKey().modulus - mantissa;
	// If the plaintext is large, exponentiate using its negative instead.
	if (negMantissa <= encoder.getMaxEncoded()) {
		encMantissa = encMantissa.modInverse(getPublicKey().getModulusSquared());
		mantissa = negMantissa;
	}
	const PaillierInt result = getPublicKey().multiply(encMantissa, mantissa);
	const int32_t exponent = yOperand1.exponent + yOperand2.exponent;
	return EncryptedNumber(result, exponent);
}

EncryptedNumber PaillierContext::multiply(const EncodedNumber& yOperand1, const EncryptedNumber& yOperand2) const {
	return multiply(yOperand2, yOperand1);
}

EncodedNumber PaillierContext::multiply(const EncodedNumber& yOperand1, const EncodedNumber& yOperand2) const {
	//checkSameContext(operand1);
	//checkSameContext(operand2);
	const  PaillierInt result = (yOperand1.mantissa * yOperand2.mantissa) % getPublicKey().modulus;
	const int32_t exponent = yOperand1.exponent + yOperand2.exponent;
	return EncodedNumber(result, exponent);
}

bool PaillierContext::operator== (const PaillierContext& other) const {
	return this == &other || (
			this->encoder == other.encoder
		);
}
