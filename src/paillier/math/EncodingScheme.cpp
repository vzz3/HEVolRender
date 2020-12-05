
#include "EncodingScheme.hpp"

#include <string>
#include <iostream>
#include "exceptions.hpp"

using namespace ppvr::paillier::crypto;
using namespace ppvr::paillier::math;

// https://github.com/data61/python-paillier/blob/master/phe/encoding.py

EncodingScheme::EncodingScheme(const crypto::PublicKey& yPK, const bool ySignedEncoding, const int_fast32_t yPrecision, const int_fast32_t yBase)
	: pk(yPK)
	, signedEncoding(ySignedEncoding)
	, precision(yPrecision)
	, base(yBase)
	, log2Base(std::log((double) base) / std::log(2.0))
{
	if (base < 2) {
		std::string msg = "Base must be at least equals to 2.";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	const SInfinitBigInt& modulus = yPK.modulus;
	//if (value.compareTo(context.getPublicKey().getModulus()) >= 0) {
	//	throw new IllegalArgumentException("value must be less than modulus");
	//}
	if (modulus.bitLength() < precision || precision < 1) {
		std::string msg = "Precision must be greater than zero and less than or equal to the number of bits in the modulus";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	if (signedEncoding && precision < 2) {
		std::string msg = "Precision must be greater than one when signed is true";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
		
	SInfinitBigInt encSpace = modulus.bitLength() == precision ? modulus : SInfinitBigInt(1) << precision;
	if(signedEncoding) {
		maxEncoded = ((encSpace + SInfinitBigInt(1)) >> 1) - SInfinitBigInt(1);
		minEncoded = modulus - maxEncoded;
		maxSignificand = maxEncoded;
		minSignificand = maxEncoded.negate();
	} else {
		maxEncoded = encSpace - SInfinitBigInt(1);
		minEncoded = SInfinitBigInt(0);
		maxSignificand = maxEncoded;
		minSignificand = SInfinitBigInt(0);
	}
}

EncodingScheme::~EncodingScheme() {
}
		
int_fast8_t EncodingScheme::signum(const EncodedNumber& yNumber) const {
	if (yNumber.mantissa.isZero()) {
		return 0;
	}
	if (isUnsigned()) {
		return 1;
	}
	//if this context is signed, then a negative significant is strictly greater
	//than modulus/2.
	SInfinitBigInt halfModulus = pk.modulus >> 1;
	return yNumber.mantissa > halfModulus ? -1 : 1;
}
		
int_fast32_t EncodingScheme::getPrecExponent(double yPrecision) const {
	return (int_fast32_t) std::floor(std::log(yPrecision) / std::log((double) base));
}
		
EncodedNumber EncodingScheme::encode(const int64_t yValue) const {
	return encode(SInfinitBigInt::fromInt64(yValue));
}
			 
EncodedNumber EncodingScheme::encode(SInfinitBigInt yValue) const {
	if (yValue < SInfinitBigInt(0) && isUnsigned()) {
		std::string msg = "Input value cannot be encoded using this EncodingScheme.";
		//std::cerr << msg << std::endl;
		throw EncodeException(msg);
	}
	int exponent = 0;
	if (!yValue.isZero()) {
		while ((yValue % SInfinitBigInt::fromInt64(base)).isZero()) {
			yValue = yValue / SInfinitBigInt::fromInt64(base);
			exponent++;
		}
	}
	if (yValue > maxSignificand || yValue < minSignificand) {
		std::string msg = "Input value cannot be encoded.";
		//std::cerr << msg << std::endl;
		throw EncodeException(msg);
	}
	if (yValue.getSignum() < 0) {
		yValue = yValue + pk.modulus;
	}
	return EncodedNumber(yValue, exponent);
}
		
EncodedNumber EncodingScheme::encode(const double yValue, const double yPrecision) const {
	if (isinf(yValue) || isnan(yValue)) {
		throw EncodeException("Input value cannot be encoded.");
	}

	if (yValue < 0 && isUnsigned()) {
		throw EncodeException("Input value is not valid for this Paillier context.");
	}

	if (yPrecision > 1 || yPrecision <= 0) {
		throw EncodeException("Precision must be 10^-i where i > 0.");
	}

	int exponent = getPrecExponent(yPrecision);
	return EncodedNumber(innerEncode(yValue, exponent), exponent);
}
		
SInfinitBigInt EncodingScheme::innerEncode(const double yValue, const int_fast32_t yExponent) const {
	// Compute BASE^(-exponent)
	//BigDecimal bigDecBaseExponent = (new BigDecimal(base)).pow(-exponent, MathContext.DECIMAL128);
	//double baseExponent = std::pow(base, -exponent);
	
	// Compute the integer representation, ie, value * (BASE^-exponent)
	//BigInteger bigIntRep = ((value.multiply(bigDecBaseExponent)).setScale(0, BigDecimal.ROUND_HALF_UP)).toBigInteger();
	
	// value * (BASE^-exponent) = v * b^-e = v * (1 / b^e) = v / b^e
	SInfinitBigInt bigIntRep = SInfinitBigInt::fromInt64((int64_t)(yValue / std::pow(base, yExponent)));
	
	
	if (bigIntRep > maxSignificand || (yValue < 0 && bigIntRep < minSignificand)) {
		throw EncodeException("Input value cannot be encoded.");
	}
			
	if (bigIntRep.getSignum() < 0) {
		bigIntRep = bigIntRep + pk.modulus;
	}
	
	return bigIntRep;
}

SInfinitBigInt EncodingScheme::getSignificand(const EncodedNumber& yEncoded) const {
	//context.checkSameContext(encoded);
	//const SInfinitBigInt& mantissa = encoded.mantissa;
	
	if (yEncoded.mantissa > pk.modulus) {
		throw DecodeException("The significand of the encoded number is corrupted");
	}
	
	// Non-negative
	if (yEncoded.mantissa <= maxEncoded) {
		return yEncoded.mantissa;
	}
	
	// Negative - note that negative encoded numbers are greater than
	// non-negative encoded numbers and hence minEncoded > maxEncoded
	if (signedEncoding && yEncoded.mantissa >= minEncoded) {
		return yEncoded.mantissa - pk.modulus;
	}
	throw DecodeException("Detected overflow. " + yEncoded.toString() );
}

SInfinitBigInt EncodingScheme::decodeBigInt(const EncodedNumber& yEncoded) const {
	SInfinitBigInt significand = getSignificand(yEncoded);
	return significand * SInfinitBigInt::fromInt64(base).pow(yEncoded.exponent);
}

double EncodingScheme::decodeDouble(const EncodedNumber& yEncoded) const {
	// C++ double fintion
	// http://openbook.rheinwerk-verlag.de/c_von_a_bis_z/005_c_basisdatentypen_008.htm
	// Vorzeichen-Bit (1 Bit): In Bit 63 wird das Vorzeichen der Zahl gespeichert. Ist dieses 0, dann ist die Zahl positiv, bei 1 ist sie negativ.
	// Exponent (11 Bit): In Bit 52 bis 62 wird der Exponent mit einer Verschiebung (Bias) der Zahl gespeichert (Bias bei double 1023).
	// Mantisse (52 Bit): In Bit 0 bis 51 wird der Bruchteil der Mantisse gespeichert. Das erste Bit der Mantisse ist immer 1 und wird nicht gespeichert.
	static const size_t doubleExpBitLen = 11;
	static const size_t doubleManBitLen = 52;
	
	SInfinitBigInt significand = getSignificand(yEncoded);
	int32_t exponent = yEncoded.exponent;
	
	size_t mantissaBitLen = significand.bitLength();
	
	if(mantissaBitLen > doubleManBitLen) {
		size_t mantissaOverflowLen = mantissaBitLen - doubleManBitLen;
		//SInfinitBigInt overflowFactor = SInfinitBigInt(2).pow(mantissaOverflowLen);
		//SInfinitBigInt overflowRadixLen = LOG(overflowFactor) / LOG(base) + 0.5; // meine int classe kann aber kein log...
		// overflowFactor = 2^mantissaOverflowLen
		// overflowRadixLen = LOG(overflowFactor) / LOG(base) + 0.5 = LOG(2^mantissaOverflowLen) / LOG(base) + 0.5
		//					= LOG2(2^mantissaOverflowLen) / LOG2(base) + 0.5 = mantissaOverflowLen / LOG2(base) + 0.5
		//					= mantissaOverflowLen / ( LOG(base) / LOG(2) ) + 0.5
		size_t overflowRadixLen = (size_t)((double)mantissaOverflowLen / std::log2(base));// + 0.5);
		SInfinitBigInt scale = SInfinitBigInt::fromInt64(base).pow(SInfinitBigInt::fromInt64(overflowRadixLen));
		//std::cout << "scale: " << scale << std::endl;
		significand = significand / scale;
		//std::cout <<  "significand: " << significand << std::endl;
		assert(significand.bitLength() <= 63); // the result need to fit into a signed 64bit int variable
		exponent += overflowRadixLen;
	}
	
	
	double expFactor = std::pow(base, exponent);
	/*
	size_t exponentBitLen = std::log2(std::log2(std::abs(expFactor))) + 0.5);
	if(exponentBitLen > doubleExpBitLen) {
		throw DecodeException("The magnitude of the exponent " + std::to_string(exponent) + " has more then 11 bits and can therfore not represented as double. Posible with a better toDouble decoding algorithm?");
	}
	*/
	double decoded = (double)significand.toInt64() * expFactor;
	if ( isinf(decoded) || isnan(decoded) ) {
		throw DecodeException("Decoded value cannot be represented as double.");
	}
	
	/*
	//BigDecimal exp = BigDecimal.valueOf(base).pow(Math.abs(encoded.getExponent()));
	SInfinitBigInt exp = SInfinitBigInt::fromInt64(base).pow(SInfinitBigInt::fromInt64(std::abs(yEncoded.exponent)));
	BigDecimal bigDecoded;
	if (encoded.getExponent() < 0) {
		bigDecoded = new BigDecimal(significand).divide(exp, MathContext.DECIMAL128);
	} else {
		bigDecoded = new BigDecimal(significand).multiply(exp, MathContext.DECIMAL128);
	}
	double decoded = bigDecoded.doubleValue();
	if (Double.isInfinite(decoded) || Double.isNaN(decoded)) {
		throw new DecodeException("Decoded value cannot be represented as double.");
	}
	 */
	return decoded;
}

int64_t EncodingScheme::decodeInt64(const EncodedNumber& yEncoded) const {
	static const SInfinitBigInt uint64Min = SInfinitBigInt::fromInt64(std::numeric_limits<int64_t>::min());
	static const SInfinitBigInt uint64Max = SInfinitBigInt::fromInt64(std::numeric_limits<int64_t>::max());
	
	SInfinitBigInt decoded = decodeBigInt(yEncoded);
	if (decoded < uint64Min || decoded > uint64Max ) {
		throw new DecodeException("Decoded value cannot be represented as long.");
	}
	return decoded.toInt64();
}

bool EncodingScheme::operator== (const EncodingScheme& other) const {
	return this == &other || (
			signedEncoding == other.signedEncoding
			&& precision == other.precision
			&& maxEncoded == other.maxEncoded
			&& minEncoded == other.minEncoded
			&& maxSignificand == other.maxSignificand
			&& minSignificand == other.minSignificand
			&& base == other.base
			&& pk == other.pk
	);
}

