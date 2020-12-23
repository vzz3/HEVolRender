
#include "EncodedNumber.hpp"

#include <string>
#include <iostream>

using namespace ppvr::paillier::math;

EncodedNumber::EncodedNumber(const PaillierInt& yMantissa, const int32_t yExponent)
	: mantissa (yMantissa)
	, exponent(yExponent)
{
	if (yMantissa.getSignum() < 0) {
		std::string msg = "ERROR EncodedNumber: value must be non-negative";
		std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	//if (value.compareTo(context.getPublicKey().getModulus()) >= 0) {
	//	throw new IllegalArgumentException("value must be less than modulus");
	//}
}

EncodedNumber::~EncodedNumber() {}

std::string EncodedNumber::toString() const {
	std::string res = mantissa.toStringDec() + "e" + std::to_string(exponent);
	return res;
}

bool EncodedNumber::operator== (const EncodedNumber& other) const {
	return this == &other || (mantissa == other.mantissa && exponent == other.exponent);
}
