
#include "EncryptedNumber.hpp"

#include <string>
#include <iostream>

using namespace ppvr::paillier::math;

EncryptedNumber::EncryptedNumber(const SInfinitBigInt& yCiphertext, const int32_t yExponent) //, bool yIsSafe)
	: ciphertext(yCiphertext)
	, exponent(yExponent)
	//, isSafe(yIsSafe)
{
	if (yCiphertext.getSignum() < 0) {
		std::string msg = "ERROR EncryptedNumber: the encrypted mantisssa (ciphertext) value must be non-negative";
		std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	//if (ciphertext.compareTo(context.getPublicKey().getModulusSquared()) >= 0) {
	//	throw new IllegalArgumentException("unsafeCiphertext must be less than modulus squared");
	//}
}

EncryptedNumber::~EncryptedNumber() {}


