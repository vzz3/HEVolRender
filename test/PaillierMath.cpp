#include "../include/catch2/catch.hpp"
#include "../src/paillier/crypto/SecureKey.hpp"
#include "../src/paillier/math/EncodingScheme.hpp"
#include "../src/paillier/math/PaillierContext.hpp"

#include <iostream>

#define LONG_TESTS 0

using ppvr::paillier::crypto::SecureKey;
using ppvr::paillier::crypto::PublicKey;
using ppvr::paillier::math::EncodingScheme;
using ppvr::paillier::math::EncodedNumber;
using ppvr::paillier::math::EncryptedNumber;
using ppvr::paillier::math::PaillierContext;
using ppvr::math::SArbBigInt;

struct TestKeys {
	private:
		static TestKeys* instance;
	public:
		static TestKeys* get() {
			if(instance == nullptr) {
				instance = new TestKeys();
			}
			return instance;
		}

	private:
		TestKeys()
			: sk32{SecureKey::create(sk32modulusLen)}
			, sk256{SecureKey::create(sk256modulusLen)}
		{
		}
	
	public:
		const size_t sk32modulusLen = 32;
		const SecureKey sk32;

		const size_t sk256modulusLen = 256;
		const SecureKey sk256;
};
TestKeys* TestKeys::instance{nullptr};


TEST_CASE( "paillier FP create  EncodingScheme", "[paillierMath]" ) {
	REQUIRE_THROWS (EncodingScheme(TestKeys::get()->sk32.publicKey, false,  8, 1)); // baes neet to be >=2
	REQUIRE_THROWS (EncodingScheme(TestKeys::get()->sk32.publicKey, false,  0, 16)); // does not met: precision > 0
	REQUIRE_NOTHROW(EncodingScheme(TestKeys::get()->sk32.publicKey, false,  1, 16));
	REQUIRE_THROWS (EncodingScheme(TestKeys::get()->sk32.publicKey, true,   1, 16)); // does not met: precision > 1 	if encoding is signed
	REQUIRE_NOTHROW(EncodingScheme(TestKeys::get()->sk32.publicKey, true,   2, 16));
	REQUIRE_NOTHROW (EncodingScheme(TestKeys::get()->sk32.publicKey, false, TestKeys::get()->sk32modulusLen, 16));
	REQUIRE_THROWS (EncodingScheme(TestKeys::get()->sk32.publicKey, false, TestKeys::get()->sk32modulusLen+1, 16)); // does not met: precision < len(publicKey)
	REQUIRE_NOTHROW(EncodingScheme(TestKeys::get()->sk32.publicKey, false, TestKeys::get()->sk32modulusLen-1, 16));


	REQUIRE( EncodingScheme(TestKeys::get()->sk32.publicKey, false, TestKeys::get()->sk32modulusLen-1, 16).isSigned() == false );
	REQUIRE( EncodingScheme(TestKeys::get()->sk32.publicKey, true,  TestKeys::get()->sk32modulusLen-1, 16).isSigned() == true );
}

TEST_CASE( "paillier FP signum", "[paillierMath]" ) {
	const size_t modulusLen = TestKeys::get()->sk32modulusLen;
	const size_t precision = TestKeys::get()->sk32modulusLen;
	const SecureKey sk32 = TestKeys::get()->sk32;

	EncodingScheme es32u(sk32.publicKey, false,  8, 10);
	REQUIRE( es32u.signum(EncodedNumber(PaillierInt::fromInt64(0), 1)) == 0);
	REQUIRE( es32u.signum(EncodedNumber(PaillierInt::fromInt64(1), 1)) == 1);
	REQUIRE( es32u.signum(EncodedNumber(sk32.publicKey.modulus - PaillierInt(1), 1)) == 1);

	EncodingScheme es32s(sk32.publicKey, true,  8, 10);
	REQUIRE( es32s.signum(EncodedNumber(PaillierInt::fromInt64(0), 1)) == 0);
	REQUIRE( es32s.signum(EncodedNumber(PaillierInt::fromInt64(1), 1)) == 1);
	REQUIRE( es32s.signum(EncodedNumber(sk32.publicKey.modulus - PaillierInt(1), 1)) == -1);
	REQUIRE( es32s.signum(EncodedNumber(sk32.publicKey.modulus / PaillierInt(2) + PaillierInt(1), 1)) == -1);
	REQUIRE( es32s.signum(EncodedNumber(sk32.publicKey.modulus / PaillierInt(2) - PaillierInt(1), 1)) == 1);
	REQUIRE( es32s.signum(EncodedNumber(sk32.publicKey.modulus / PaillierInt(2), 1)) == 1);
}

TEST_CASE( "paillier FP encode integer", "[paillierMath]" ) {
	const size_t modulusLen = TestKeys::get()->sk256modulusLen;
	const size_t precision = TestKeys::get()->sk256modulusLen;
	const SecureKey sk = TestKeys::get()->sk256;

	// unsigned encoding
	EncodingScheme esU(sk.publicKey, false,  precision, 10);

	EncodedNumber t1u = esU.encode(0);
	REQUIRE( t1u.mantissa == PaillierInt::fromInt64(0));
	REQUIRE( t1u.exponent == 0);

	EncodedNumber t2u = esU.encode(1);
	REQUIRE( t2u.mantissa == PaillierInt::fromInt64(1));
	REQUIRE( t2u.exponent == 0);

	EncodedNumber t3u = esU.encode(987654321);
	REQUIRE( t3u.mantissa == PaillierInt::fromInt64(987654321));
	REQUIRE( t3u.exponent == 0);

	REQUIRE_THROWS( esU.encode(-1)) ;

	// signed encoding
	EncodingScheme esS(sk.publicKey, true,  precision, 10);

	EncodedNumber t1s = esS.encode(0);
	REQUIRE( t1s.mantissa == PaillierInt::fromInt64(0));
	REQUIRE( t1s.exponent == 0);

	EncodedNumber t2s = esS.encode(1);
	REQUIRE( t2s.mantissa == PaillierInt::fromInt64(1));
	REQUIRE( t2s.exponent == 0);

	EncodedNumber t3s = esS.encode(987654321);
	REQUIRE( t3s.mantissa == PaillierInt::fromInt64(987654321));
	REQUIRE( t3s.exponent == 0);

	EncodedNumber t4s = esS.encode(-1);
	REQUIRE( t4s.mantissa == ( sk.publicKey.modulus - PaillierInt(1)) );
	REQUIRE( t4s.exponent == 0);

	EncodedNumber t5s = esS.encode(-186574268);
	REQUIRE( t5s.mantissa == ( sk.publicKey.modulus - PaillierInt::fromInt64(186574268)) );
	REQUIRE( t5s.exponent == 0);

	// test mantissa optimization
	EncodedNumber t10s = esS.encode(PaillierInt::fromString("987654321000", 10));
	REQUIRE( t10s.mantissa == PaillierInt::fromString("987654321", 10) );
	REQUIRE( t10s.exponent == 3);

	EncodedNumber t11s = esS.encode(345010000);
	REQUIRE( t11s.mantissa == PaillierInt::fromInt64(34501) );
	REQUIRE( t11s.exponent == 4);

	// test big things
	PaillierInt nineByteVal = PaillierInt::fromString("-99 88 77 66 55 44 33 22 11", 16); // 9 Bytes
	REQUIRE(nineByteVal.bitLength() * 3 < modulusLen); // Make shure pow(3) is posible without overflow. If this test fails the test parameters are wrong (modulus to smal)!
	EncodedNumber t6s = esS.encode(nineByteVal);
	REQUIRE( t6s.mantissa == ( sk.publicKey.modulus + nineByteVal) );
	REQUIRE( t6s.exponent == 0);

	EncodedNumber t7s = esS.encode(nineByteVal * nineByteVal);
	REQUIRE( t7s.mantissa == ( nineByteVal * nineByteVal) );
	REQUIRE( t7s.exponent == 0);

	EncodedNumber t8s = esS.encode(nineByteVal.pow(3));
	REQUIRE( t8s.mantissa == ( sk.publicKey.modulus + nineByteVal.pow(3)) );
	REQUIRE( t8s.exponent == 0);



	// Test overflows for signed and unsigned encodings
	REQUIRE_NOTHROW( esU.encode(PaillierInt::fromString("1", 2) << (modulusLen-1)) );
	REQUIRE_THROWS( esU.encode(PaillierInt::fromString("1", 2) << modulusLen)) ;

	REQUIRE_THROWS( esS.encode(PaillierInt::fromString("1", 2) << (modulusLen-1)) );
	REQUIRE_NOTHROW( esS.encode(PaillierInt::fromString("1", 2) << (modulusLen-2)) );
	REQUIRE_THROWS( esS.encode(PaillierInt::fromString("-1", 2) << (modulusLen-1)) );
	REQUIRE_NOTHROW( esS.encode(PaillierInt::fromString("-1", 2) << (modulusLen-2)) );
}

TEST_CASE( "paillier FP encode float", "[paillierMath]" ) {
	const size_t modulusLen = TestKeys::get()->sk256modulusLen;
	const size_t precision = TestKeys::get()->sk256modulusLen;
	const SecureKey sk = TestKeys::get()->sk256;

	// unsigned encoding
	EncodingScheme esU(sk.publicKey, false,  precision, 10);

	REQUIRE_THROWS( esU.encode(NAN, 1.0)) ;
	REQUIRE_THROWS( esU.encode(INFINITY, 1.0)) ;
	REQUIRE_THROWS( esU.encode(0.0, 2.0)) ;
	REQUIRE_THROWS( esU.encode(0.0, 10.0)) ;
	REQUIRE_NOTHROW( esU.encode(0.0, 1.0)) ;
	REQUIRE_NOTHROW( esU.encode(0.0, 0.1)) ;
	REQUIRE_NOTHROW( esU.encode(0.0, 0.0000001)) ;

	REQUIRE_THROWS( esU.encode(-1.0, 1.0)) ;


	EncodedNumber t1u = esU.encode(0.0, 1.0);
	REQUIRE( t1u.mantissa == PaillierInt::fromInt64(0));
	REQUIRE( t1u.exponent == 0);

	EncodedNumber t2u = esU.encode(1.0, 1.0);
	REQUIRE( t2u.mantissa == PaillierInt::fromInt64(1));
	REQUIRE( t2u.exponent == 0);

	EncodedNumber t3u = esU.encode(987654321.0, 1.0);
	REQUIRE( t3u.mantissa == PaillierInt::fromInt64(987654321));
	REQUIRE( t3u.exponent == 0);

	EncodedNumber t4u = esU.encode(0.0, 0.1);
	REQUIRE( t4u.mantissa == PaillierInt::fromInt64(0));
	REQUIRE( t4u.exponent == -1);

	EncodedNumber t5u = esU.encode(0.0, 0.01);
	REQUIRE( t5u.mantissa == PaillierInt::fromInt64(0));
	REQUIRE( t5u.exponent == -2);

	EncodedNumber t6u = esU.encode(123.45, 0.01);
	REQUIRE( t6u.mantissa == PaillierInt::fromInt64(12345));
	REQUIRE( t6u.exponent == -2);

	EncodedNumber t7u = esU.encode(123.456, 0.01);
	REQUIRE( t7u.mantissa == PaillierInt::fromInt64(12345));
	REQUIRE( t7u.exponent == -2);

	EncodedNumber t8u = esU.encode(123.456, 0.001);
	REQUIRE( t8u.mantissa == PaillierInt::fromInt64(123456));
	REQUIRE( t8u.exponent == -3);

	// signed encoding
	EncodingScheme esS(sk.publicKey, true,  precision, 10);

	EncodedNumber t1s = esS.encode(0.0, 1.0);
	REQUIRE( t1s.mantissa == PaillierInt::fromInt64(0));
	REQUIRE( t1s.exponent == 0);

	EncodedNumber t2s = esS.encode(1.0, 1.0);
	REQUIRE( t2s.mantissa == PaillierInt::fromInt64(1));
	REQUIRE( t2s.exponent == 0);

	EncodedNumber t3s = esS.encode(987654321, 1.0);
	REQUIRE( t3s.mantissa == PaillierInt::fromInt64(987654321));
	REQUIRE( t3s.exponent == 0);

	EncodedNumber t4s = esS.encode(-1.0, 1.0);
	REQUIRE( t4s.mantissa == ( sk.publicKey.modulus - PaillierInt(1)) );
	REQUIRE( t4s.exponent == 0);

	EncodedNumber t5s = esS.encode(-186574268.0, 1.0);
	REQUIRE( t5s.mantissa == ( sk.publicKey.modulus - PaillierInt::fromInt64(186574268)) );
	REQUIRE( t5s.exponent == 0);

	EncodedNumber t6s = esS.encode(-1865742689.123456, 0.001);
	REQUIRE( t6s.mantissa == ( sk.publicKey.modulus - PaillierInt::fromInt64(1865742689123)) );
	REQUIRE( t6s.exponent == -3);

	EncodedNumber t7s = esS.encode(-1865742689.123456, 0.0001);
	REQUIRE( t7s.mantissa == ( sk.publicKey.modulus - PaillierInt::fromInt64(18657426891234)) );
	REQUIRE( t7s.exponent == -4);

	EncodedNumber t8s = esS.encode(-1865742689.123456, 0.00001);
	REQUIRE( t8s.mantissa == ( sk.publicKey.modulus - PaillierInt::fromInt64(186574268912345)) );
	REQUIRE( t8s.exponent == -5);

	EncodedNumber t9s = esS.encode(-1865742689.123456, 0.000001);
	REQUIRE( t9s.mantissa == ( sk.publicKey.modulus - PaillierInt::fromInt64(1865742689123456)) );
	REQUIRE( t9s.exponent == -6);

	EncodedNumber t10s = esS.encode(1865742689.123456, 0.000001);
	REQUIRE( t10s.mantissa == ( PaillierInt::fromInt64(1865742689123456)) );
	REQUIRE( t10s.exponent == -6);

	EncodedNumber t11s = esS.encode(1865742689.1234567, 0.0000001); // this can not be encoded without error because it would require a mantissa with more then 52 bits
	REQUIRE( t11s.mantissa != ( PaillierInt::fromInt64(18657426891234567)) );
	REQUIRE( t11s.exponent == -7);

	static const size_t doubleExpBitLen = 11;
	static const size_t doubleManBitLen = 52;
	static const PaillierInt doubleMaxMantisa = PaillierInt(2).pow(PaillierInt(doubleManBitLen + 1)); // = 9007199254740992
	//std::cout << doubleMaxMantisa.toStringDec() << std::endl;

	EncodedNumber t12s = esS.encode((double)doubleMaxMantisa.toInt64(), 1.0); // largest posible mantissa
	REQUIRE( t12s.mantissa == doubleMaxMantisa);
	REQUIRE( t12s.exponent == 0);

	EncodedNumber t13s = esS.encode((double)(doubleMaxMantisa + PaillierInt(1)).toInt64(), 1.0); // mantissa to large 9007199254740993
	REQUIRE( t13s.mantissa != doubleMaxMantisa + PaillierInt(1));
	REQUIRE( t13s.exponent == 0);

}

TEST_CASE( "paillier FP decode integer", "[paillierMath]" ) {
	const size_t modulusLen = TestKeys::get()->sk256modulusLen;
	const size_t precision = TestKeys::get()->sk256modulusLen;
	const SecureKey sk = TestKeys::get()->sk256;

	// unsigned encoding
	EncodingScheme esU(sk.publicKey, false,  precision, 12);
	EncodingScheme esS(sk.publicKey, true,  precision, 8); // base need to be between 2 and 16

	REQUIRE( esU.decodeInt64(esU.encode(0)) == 0 );
	REQUIRE( esU.decodeInt64(esU.encode(1)) == 1 );
	REQUIRE( esU.decodeInt64(esU.encode(987654321)) == 987654321 );
	REQUIRE( esU.decodeInt64(esU.encode(std::numeric_limits<int64_t>::max())) == std::numeric_limits<int64_t>::max() );

	REQUIRE( esS.decodeInt64(esS.encode(0)) == 0 );
	REQUIRE( esS.decodeInt64(esS.encode(1)) == 1 );
	REQUIRE( esS.decodeInt64(esS.encode(-2)) == -2 );
	REQUIRE( esS.decodeInt64(esS.encode(987654321)) == 987654321 );
	REQUIRE( esS.decodeInt64(esS.encode(-5648648648)) == -5648648648 );
	REQUIRE( esS.decodeInt64(esS.encode(std::numeric_limits<int64_t>::max() * -1)) == std::numeric_limits<int64_t>::max() * -1 );

	REQUIRE( esS.decodeBigInt(esS.encode(1)) == PaillierInt::fromString("1", 10) );
	REQUIRE( esS.decodeBigInt(esS.encode(-1)) == PaillierInt::fromString("-1", 10) );
	REQUIRE( esS.decodeBigInt(esS.encode(-4564564568775367147)) == PaillierInt::fromString("-4564564568775367147", 10) );

	PaillierInt t1 = PaillierInt::fromString("-54 68 24 45 24 34 50 46 57 61 56 48 96", 16);
	REQUIRE( esS.decodeBigInt(esS.encode(t1)) == t1 );
	REQUIRE( esS.decodeBigInt(esS.encode(t1*t1)) == t1 * t1 );

	PaillierInt t2bigInt = PaillierInt::fromString("-48 96 25 87 46 95 78 65 21 48 23 65 21 45", 16);
	EncodedNumber t2encoded = esS.encode(t2bigInt);
	int t2exp = 13;
	EncodedNumber t2encodedNew(t2encoded.mantissa, t2encoded.exponent + t2exp);
	REQUIRE( esS.decodeBigInt(t2encodedNew) == t2bigInt * (PaillierInt::fromString("1" + std::string(t2exp, '0'), esS.getBase())) );
}

TEST_CASE( "paillier FP decode float", "[paillierMath]" ) {
	const size_t modulusLen = TestKeys::get()->sk256modulusLen;
	const size_t precision = TestKeys::get()->sk256modulusLen;
	const SecureKey sk = TestKeys::get()->sk256;

	// unsigned encoding
	EncodingScheme esU(sk.publicKey, false,  precision, 12);
	EncodingScheme esS(sk.publicKey, true,  precision, 8); // base need to be between 2 and 16

	REQUIRE( esU.decodeDouble(esU.encode(0)) == 0.0 );
	REQUIRE( esU.decodeDouble(esU.encode(1)) == 1.0 );
	REQUIRE( esU.decodeDouble(esU.encode(987654321.0)) == 987654321.0 );

	REQUIRE( esS.decodeDouble(esS.encode(5433)) == 5433 );
	REQUIRE( esS.decodeDouble(esS.encode(-187653)) == -187653.0 );

	static const size_t doubleExpBitLen = 11;
	static const size_t doubleManBitLen = 52;
	static const PaillierInt doubleMaxMantissa = PaillierInt(2).pow(PaillierInt(doubleManBitLen + 1)); // = 9007199254740992
	//std::cout << doubleMaxMantisa.toStringDec() << std::endl;
	EncodedNumber doubleMaxMantissaEnc = esS.encode(doubleMaxMantissa);
	REQUIRE( esS.decodeDouble(doubleMaxMantissaEnc) == (double)doubleMaxMantissa.toInt64() ); // largest posible mantissa

	int expAdd = 32;
	REQUIRE( esS.decodeDouble( EncodedNumber(doubleMaxMantissaEnc.mantissa, doubleMaxMantissaEnc.exponent + expAdd) ) == (double)(doubleMaxMantissa.toInt64()) * pow(2, log2(esS.getBase()) * expAdd) ); // largest posible mantissa multiplied purly by the exponent

	int expSub = 13;
	REQUIRE( esS.decodeDouble( EncodedNumber(doubleMaxMantissaEnc.mantissa, doubleMaxMantissaEnc.exponent - expSub) ) == (double)(doubleMaxMantissa.toInt64()) / pow(2, log2(esS.getBase()) * expSub) );

	EncodedNumber doubleMantissaOverflowEnc1 = esS.encode(doubleMaxMantissa + PaillierInt(1));
	REQUIRE( esS.decodeDouble( doubleMantissaOverflowEnc1 ) == (double)((doubleMaxMantissa + PaillierInt(1)).toInt64()/esS.getBase()) * (double)esS.getBase() );

	REQUIRE( (int64_t)esS.decodeDouble( esS.encode(doubleMaxMantissa + PaillierInt::fromInt64(1024)) ) == (doubleMaxMantissa + PaillierInt::fromInt64(1024)).toInt64() );
	REQUIRE( (int64_t)esS.decodeDouble( esS.encode(doubleMaxMantissa + PaillierInt::fromInt64(1025)) ) != (doubleMaxMantissa + PaillierInt::fromInt64(1025)).toInt64() );

	//SArbBigInt t2bigInt =  SArbBigInt::fromString("48 96 25 87 46 95 78 65 21 48 23 65 21 45", 16); // 112 bit
	PaillierInt t2bigInt =  PaillierInt::fromString("1472229330323731852950423889846597", 10); // 112 bit
	//std::cout << t2bigInt.toStringDec() << std::endl;
	// 1472229330323731852950423889846597 exact
	// 1472229330323731248024105223454720.0
	EncodingScheme esSbas2(sk.publicKey, true,  precision,2);
	REQUIRE( esSbas2.decodeDouble( esSbas2.encode(t2bigInt) ) == std::stod(t2bigInt.toStringDec()) );

	// big error that does not mether because it is less then the double mantissa length
	REQUIRE( esSbas2.decodeDouble( esSbas2.encode(t2bigInt) ) == std::stod((t2bigInt + (PaillierInt(1) << (t2bigInt.bitLength() - doubleManBitLen - 3)) ).toStringDec()) );
	// big error that not mether
	REQUIRE( esSbas2.decodeDouble( esSbas2.encode(t2bigInt) ) != std::stod((t2bigInt + (PaillierInt(1) << (t2bigInt.bitLength() - doubleManBitLen + 1)) ).toStringDec()) );

	EncodingScheme esSbas4(sk.publicKey, true, precision, 4);
	REQUIRE( esSbas4.decodeDouble( esSbas4.encode(t2bigInt) ) == (std::stod(t2bigInt.toStringDec())) );

	EncodingScheme esSbas8(sk.publicKey, true, precision, 8);
	REQUIRE( esSbas8.decodeDouble( esSbas8.encode(t2bigInt) ) == (std::stod(t2bigInt.toStringDec())) );

	EncodingScheme esSbas10(sk.publicKey, true, precision, 10);
	REQUIRE( esSbas10.decodeDouble( esSbas10.encode(t2bigInt) ) == (std::stod(t2bigInt.toStringDec())) );

	EncodingScheme esSbas16(sk.publicKey, true, precision, 16);
	REQUIRE( esSbas16.decodeDouble( esSbas16.encode(t2bigInt) ) == (std::stod(t2bigInt.toStringDec())) );

	// move the comma below the mantissa of a double
	REQUIRE( esSbas2.decodeDouble( EncodedNumber(esSbas2.encode(t2bigInt).mantissa, -8) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(2, 8) );
	REQUIRE( esSbas10.decodeDouble( EncodedNumber(esSbas10.encode(t2bigInt).mantissa, -4) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(10, 4) );

	// move the comma into the mantissa of a double
	int exp = t2bigInt.bitLength() - doubleManBitLen + 1;
	REQUIRE( esSbas2.decodeDouble( EncodedNumber(esSbas2.encode(t2bigInt).mantissa, -exp    ) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(2, exp    ) ); // one digit after the comma
	REQUIRE( esSbas2.decodeDouble( EncodedNumber(esSbas2.encode(t2bigInt).mantissa, -exp - 1) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(2, exp + 1) ); // two digit after the comma
	REQUIRE( esSbas2.decodeDouble( EncodedNumber(esSbas2.encode(t2bigInt).mantissa, -exp - 4) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(2, exp + 4) ); // four digit after the comma

	REQUIRE( esSbas16.decodeDouble( EncodedNumber(esSbas16.encode(t2bigInt).mantissa, -exp/4)    ) == (std::stod(t2bigInt.toStringDec())) / std::pow(2, exp) ); // one digit after the comma
	REQUIRE( esSbas16.decodeDouble( EncodedNumber(esSbas16.encode(t2bigInt).mantissa, -exp/4 -1) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(2, exp+4) ); // two digit after the comma
	REQUIRE( esSbas16.decodeDouble( EncodedNumber(esSbas16.encode(t2bigInt).mantissa, -exp/4 -4) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(2, exp+16) ); // four digit after the comma

	// decimale number comparison is a rounding desaster, therfor I do use only comma movements where the roundig errors of the different radix representations are equal
	REQUIRE( esSbas10.decodeDouble( EncodedNumber(esSbas10.encode(t2bigInt).mantissa, -15) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(10, 15) ); // => 1472229330323731712.0
	REQUIRE( esSbas10.decodeDouble( EncodedNumber(esSbas10.encode(t2bigInt).mantissa, -20) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(10, 20) ); // => 14722293303237.318359375
	REQUIRE( esSbas10.decodeDouble( EncodedNumber(esSbas10.encode(t2bigInt).mantissa, -21) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(10, 21) ); // => 1472229330323.7319335938
	REQUIRE( esSbas10.decodeDouble( EncodedNumber(esSbas10.encode(t2bigInt).mantissa, -30) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(10, 30) ); // => 1472.2293303237
	REQUIRE( esSbas10.decodeDouble( EncodedNumber(esSbas10.encode(t2bigInt).mantissa, -31) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(10, 31) ); // => 147.2229330324
	//REQUIRE( esSbas10.decodeDouble( EncodedNumber(esSbas10.encode(t2bigInt).mantissa, -32) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(10, 32) ); // => 14.7222933032 ??????? is not equal????
	//REQUIRE( esSbas10.decodeDouble( EncodedNumber(esSbas10.encode(t2bigInt).mantissa, -33) ) == (std::stod(t2bigInt.toStringDec())) / std::pow(10, 33) ); // => 1.4722293303 ??????? is not equal????
}

TEST_CASE( "paillier FP paillier context encrypt/decrypt", "[paillierMath]" ) {
	const size_t modulusLen = TestKeys::get()->sk256modulusLen;
	const size_t precision = TestKeys::get()->sk256modulusLen;
	const SecureKey sk = TestKeys::get()->sk256;

	const PaillierContext pcS(sk.publicKey, true, precision, 10);
	//const EncodingScheme& esS = pcS.encoder;


	EncodedNumber sEN1 = pcS.encode(3458);
	EncryptedNumber sEN1c1 = pcS.encrypt(sEN1, false);
	EncryptedNumber sEN1c2 = pcS.encrypt(sEN1, false);
	EncryptedNumber sEN1co1 = pcS.encrypt(sEN1, true);
	EncryptedNumber sEN1co2 = pcS.encrypt(sEN1, true);
	REQUIRE( sEN1c1.exponent == 0 );
	REQUIRE( sEN1c2.exponent == 0 );
	REQUIRE( sEN1co1.exponent == 0 );
	REQUIRE( sEN1co1.exponent == 0 );
	REQUIRE( sEN1c1.ciphertext == sEN1c2.ciphertext );
	REQUIRE( sEN1c1.ciphertext != sEN1co1.ciphertext );
	REQUIRE( sEN1c1.ciphertext != sEN1co2.ciphertext );
	REQUIRE( sEN1c2.ciphertext != sEN1co1.ciphertext );
	REQUIRE( sEN1c2.ciphertext != sEN1co2.ciphertext );
	REQUIRE( pcS.decrypt(sk, sEN1c1) == sEN1);
	REQUIRE( pcS.decrypt(sk, sEN1c2) == sEN1);
	REQUIRE( pcS.decrypt(sk, sEN1co2) == sEN1);
	REQUIRE( pcS.decrypt(sk, sEN1co2) == sEN1);

	PaillierInt sArbInt1 = PaillierInt::fromString("-345464564126928411397", 10);
	EncryptedNumber sArbInt1c1 = pcS.encrypt(sArbInt1, false);
	EncryptedNumber sArbInt1c2 = pcS.encrypt(sArbInt1, false);
	EncryptedNumber sArbInt1co1 = pcS.encrypt(sArbInt1, true);
	EncryptedNumber sArbInt1co2 = pcS.encrypt(sArbInt1, true);
	REQUIRE( sArbInt1c1.exponent == 0 );
	REQUIRE( sArbInt1c2.exponent == 0 );
	REQUIRE( sArbInt1co1.exponent == 0 );
	REQUIRE( sArbInt1co1.exponent == 0 );
	REQUIRE( sArbInt1c1.ciphertext == sArbInt1c2.ciphertext );
	REQUIRE( sArbInt1c1.ciphertext != sArbInt1co1.ciphertext );
	REQUIRE( sArbInt1c1.ciphertext != sArbInt1co2.ciphertext );
	REQUIRE( sArbInt1c2.ciphertext != sArbInt1co1.ciphertext );
	REQUIRE( sArbInt1c2.ciphertext != sArbInt1co2.ciphertext );
	REQUIRE( pcS.decodeBigInt( pcS.decrypt(sk, sArbInt1c1) ) == sArbInt1);
	REQUIRE( pcS.decodeBigInt( pcS.decrypt(sk, sArbInt1c2) ) == sArbInt1);
	REQUIRE( pcS.decodeBigInt( pcS.decrypt(sk, sArbInt1co1) ) == sArbInt1);
	REQUIRE( pcS.decodeBigInt( pcS.decrypt(sk, sArbInt1co2) ) == sArbInt1);
	
	int64_t sInt1 = -3454645641269284113;
	EncryptedNumber sInt1c1 = pcS.encrypt(sInt1, false);
	EncryptedNumber sInt1c2 = pcS.encrypt(sInt1, false);
	EncryptedNumber sInt1co1 = pcS.encrypt(sInt1, true);
	EncryptedNumber sInt1co2 = pcS.encrypt(sInt1, true);
	REQUIRE( sInt1c1.exponent == 0 );
	REQUIRE( sInt1c2.exponent == 0 );
	REQUIRE( sInt1co1.exponent == 0 );
	REQUIRE( sInt1co1.exponent == 0 );
	REQUIRE( sInt1c1.ciphertext == sInt1c2.ciphertext );
	REQUIRE( sInt1c1.ciphertext != sInt1co1.ciphertext );
	REQUIRE( sInt1c1.ciphertext != sInt1co2.ciphertext );
	REQUIRE( sInt1c2.ciphertext != sInt1co1.ciphertext );
	REQUIRE( sInt1c2.ciphertext != sInt1co2.ciphertext );
	REQUIRE( pcS.decodeInt64( pcS.decrypt(sk, sInt1c1) ) == sInt1);
	REQUIRE( pcS.decodeInt64( pcS.decrypt(sk, sInt1c2) ) == sInt1);
	REQUIRE( pcS.decodeInt64( pcS.decrypt(sk, sInt1co1) ) == sInt1);
	REQUIRE( pcS.decodeInt64( pcS.decrypt(sk, sInt1co2) ) == sInt1);

	double double1 = -3637.123;
	int32_t exp1 = -2;
	double precision1 = std::pow(10.0, exp1);
	double double1res = -3637.12;
	EncryptedNumber double1c1 = pcS.encrypt(double1, precision1, false);
	EncryptedNumber double1c2 = pcS.encrypt(double1, precision1, false);
	EncryptedNumber double1co1 = pcS.encrypt(double1, precision1, true);
	EncryptedNumber double1co2 = pcS.encrypt(double1, precision1, true);
	REQUIRE( double1c1.exponent == exp1 );
	REQUIRE( double1c2.exponent == exp1 );
	REQUIRE( double1co1.exponent == exp1 );
	REQUIRE( double1co1.exponent == exp1 );
	REQUIRE( double1c1.ciphertext == double1c2.ciphertext );
	REQUIRE( double1c1.ciphertext != double1co1.ciphertext );
	REQUIRE( double1c1.ciphertext != double1co2.ciphertext );
	REQUIRE( double1c2.ciphertext != double1co1.ciphertext );
	REQUIRE( double1c2.ciphertext != double1co2.ciphertext );
	REQUIRE( pcS.decodeDouble( pcS.decrypt(sk, double1c1) ) == double1res);
	REQUIRE( pcS.decodeDouble( pcS.decrypt(sk, double1c2) ) == double1res);
	REQUIRE( pcS.decodeDouble( pcS.decrypt(sk, double1co1) ) == double1res);
	REQUIRE( pcS.decodeDouble( pcS.decrypt(sk, double1co2) ) == double1res);
}

TEST_CASE( "paillier FP paillier context add", "[paillierMath]" ) {
	const size_t modulusLen = TestKeys::get()->sk256modulusLen;
	const size_t precision = TestKeys::get()->sk256modulusLen;
	const SecureKey sk = TestKeys::get()->sk256;

	const PaillierContext pcS(sk.publicKey, true, precision, 10);

	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(0), pcS.encrypt(0)) )) == 0 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(0), pcS.encrypt(1)) )) == 1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(1), pcS.encrypt(0)) )) == 1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(1), pcS.encrypt(1)) )) == 2 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(-1), pcS.encrypt(1)) )) == 0 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(1), pcS.encrypt(-1)) )) == 0 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(-2), pcS.encrypt(-1)) )) == -3 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(-2), pcS.encrypt(1)) )) == -1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(1), pcS.encrypt(-2)) )) == -1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(1284680 ), pcS.encrypt(98765432   )) )) == 1284680  + 98765432    );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(12846800), pcS.encrypt(98765432   )) )) == 12846800 + 98765432    );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(1284680 ), pcS.encrypt(98765432000)) )) == 1284680  + 98765432000 );

	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(1 , true), pcS.encrypt(2, true)) )) == 3 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(1 , true), pcS.encrypt(-2, true)) )) == -1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.add(pcS.encrypt(1284680 , true), pcS.encrypt(98765432000, true)) )) == 1284680  + 98765432000 );


	// encrypted + encrypted
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encrypt( 1.123, 0.01 , false), pcS.encrypt( 0.234, 0.01 , false)) )) == 1.350 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encrypt( 1.123, 0.01 , false), pcS.encrypt( 0.234, 0.001, false)) )) == 1.354 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encrypt( 1.123, 0.001, false), pcS.encrypt( 0.234, 0.01 , false)) )) == 1.353 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encrypt( 1.123, 1    , true ), pcS.encrypt( 0.234, 0.01 , true )) )) == 1.23  );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encrypt( 4.673, 0.001, true ), pcS.encrypt(-9.731, 0.001, true )) )) == 4.673 - 9.731   );

	// encrypted + encoded
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encrypt( 1.123, 0.01 , false), pcS.encode( 0.234, 0.01 )) )) == 1.350 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encrypt( 1.123, 0.01 , false), pcS.encode( 0.234, 0.001)) )) == 1.354 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encrypt( 1.123, 0.001, false), pcS.encode( 0.234, 0.01 )) )) == 1.353 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encrypt( 1.123, 1    , true ), pcS.encode( 0.234, 0.01 )) )) == 1.23  );
	REQUIRE( (double(uint64_t(pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encrypt( 1.123, 0.1  , false), pcS.encode( 0.100, 0.001)) )) * 10000.0)))/10000.0 == 1.2   ); // test canShift optimzation of PaillierContext::add(): 100 >>_10 2 = 1

	// encoded + encrypted
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encode( 1.123, 0.01 ), pcS.encrypt( 0.234, 0.01 , false)) )) == 1.350 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encode( 1.123, 0.01 ), pcS.encrypt( 0.234, 0.001, false)) )) == 1.354 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encode( 1.123, 0.001), pcS.encrypt( 0.234, 0.01 , false)) )) == 1.353 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encode( 1.123, 1    ), pcS.encrypt( 0.234, 0.01 , true )) )) == 1.23 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.add(pcS.encode( 1.120, 0.001 ),pcS.encrypt( 0.234, 0.01 , true )) )) == 1.35   ); // test canShift optimzation PaillierContext::add(): 1120 >>_10 1 = 112

	// encoded + encoded
	REQUIRE( pcS.decodeDouble(                 pcS.add(pcS.encode( 1.123, 0.01 ), pcS.encode( 0.234, 0.01 ))       ) == 1.350 );
	REQUIRE( pcS.decodeDouble(                 pcS.add(pcS.encode( 1.123, 0.01 ), pcS.encode( 0.234, 0.001))       ) == 1.354 );
	REQUIRE( pcS.decodeDouble(                 pcS.add(pcS.encode( 1.123, 0.001), pcS.encode( 0.234, 0.01 ))       ) == 1.353 );
	REQUIRE( pcS.decodeDouble(                 pcS.add(pcS.encode( 1.123, 1    ), pcS.encode( 0.234, 0.01 ))       ) == 1.23  );
}

TEST_CASE( "paillier FP paillier context additiveInverse", "[paillierMath]" ) {
	const size_t modulusLen = TestKeys::get()->sk256modulusLen;
	const size_t precision = TestKeys::get()->sk256modulusLen;
	const SecureKey sk = TestKeys::get()->sk256;

	const PaillierContext pcS(sk.publicKey, true, precision, 10);

	// plaintext
	REQUIRE( pcS.decodeInt64(                   pcS.additiveInverse(pcS.encode(0))                   ) == 0 );
	REQUIRE( pcS.decodeInt64(                   pcS.additiveInverse(pcS.encode(1))                   ) == -1 );
	REQUIRE( pcS.decodeInt64(                   pcS.additiveInverse(pcS.encode(-1))                  ) == 1 );
	REQUIRE( pcS.decodeInt64(                   pcS.additiveInverse(pcS.encode(-9856))               ) == 9856 );
	REQUIRE( pcS.decodeInt64(                   pcS.additiveInverse(pcS.encode(89304670))            ) == -89304670 );

	REQUIRE( pcS.decodeDouble(                  pcS.additiveInverse(pcS.encode(0.0, 0.001))          ) == 0.0 );
	REQUIRE( pcS.decodeDouble(                  pcS.additiveInverse(pcS.encode(1249.6439, 0.001))    ) == -1249.6430 );
	REQUIRE( pcS.decodeDouble(                  pcS.additiveInverse(pcS.encode(-234.560, 0.001))     ) == 234.560 );

	// encrypted
	REQUIRE( pcS.decodeInt64(  pcS.decrypt( sk, pcS.additiveInverse(pcS.encrypt(0))                ) ) == 0 );
	REQUIRE( pcS.decodeInt64(  pcS.decrypt( sk, pcS.additiveInverse(pcS.encrypt(1))                ) ) == -1 );
	REQUIRE( pcS.decodeInt64(  pcS.decrypt( sk, pcS.additiveInverse(pcS.encrypt(-1))               ) ) == 1 );
	REQUIRE( pcS.decodeInt64(  pcS.decrypt( sk, pcS.additiveInverse(pcS.encrypt(349875656347))     ) ) == -349875656347 );
	REQUIRE( pcS.decodeInt64(  pcS.decrypt( sk, pcS.additiveInverse(pcS.encrypt(-951580))          ) ) == 951580 );

	REQUIRE( pcS.decodeDouble( pcS.decrypt( sk, pcS.additiveInverse(pcS.encrypt(0.0, 0.001))       ) ) == 0.0 );
	REQUIRE( pcS.decodeDouble( pcS.decrypt( sk, pcS.additiveInverse(pcS.encrypt(1249.6439, 0.001)) ) ) == -1249.6430 );
	REQUIRE( pcS.decodeDouble( pcS.decrypt( sk, pcS.additiveInverse(pcS.encrypt(-234.560, 0.001))  ) ) == 234.560 );
}

TEST_CASE( "paillier FP paillier context subtract", "[paillierMath]" ) {
	const size_t modulusLen = TestKeys::get()->sk256modulusLen;
	const size_t precision = TestKeys::get()->sk256modulusLen;
	const SecureKey sk = TestKeys::get()->sk256;

	const PaillierContext pcS(sk.publicKey, true, precision, 10);

	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(0), pcS.encrypt(0)) )) == 0 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(0), pcS.encrypt(1)) )) == -1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(1), pcS.encrypt(0)) )) == 1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(1), pcS.encrypt(1)) )) == 0 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(-1), pcS.encrypt(1)) )) == -2 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(1), pcS.encrypt(-1)) )) == 2 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(-2), pcS.encrypt(-1)) )) == -1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(-2), pcS.encrypt(1)) )) == -3 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(1), pcS.encrypt(-2)) )) == 3 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(1284680 ), pcS.encrypt(98765432   )) )) == 1284680  - 98765432    );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(12846800), pcS.encrypt(98765432   )) )) == 12846800 - 98765432    );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(1284680 ), pcS.encrypt(98765432000)) )) == 1284680  - 98765432000 );

	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(1 , true), pcS.encrypt(2, true)) )) == -1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(1 , true), pcS.encrypt(-2, true)) )) == 3 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.subtract(pcS.encrypt(1284680 , true), pcS.encrypt(98765432000, true)) )) == 1284680  - 98765432000 );


	// encrypted + encrypted
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encrypt( 1.123, 0.01 , false), pcS.encrypt( 0.234, 0.01 , false)) )) == 0.890 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encrypt( 1.123, 0.01 , false), pcS.encrypt( 0.234, 0.001, false)) )) == 0.886 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encrypt( 1.123, 0.001, false), pcS.encrypt( 0.234, 0.01 , false)) )) == 0.893 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encrypt( 1.123, 1    , true ), pcS.encrypt( 0.234, 0.01 , true )) )) == 0.770 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encrypt( 4.673, 0.001, true ), pcS.encrypt(-9.731, 0.001, true )) )) == 4.673 + 9.731   );

	// encrypted + encoded
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encrypt( 1.123, 0.01 , false), pcS.encode( 0.234, 0.01 )) )) == 0.890 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encrypt( 1.123, 0.01 , false), pcS.encode( 0.234, 0.001)) )) == 0.886 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encrypt( 1.123, 0.001, false), pcS.encode( 0.234, 0.01 )) )) == 0.893 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encrypt( 1.123, 1    , true ), pcS.encode( 0.234, 0.01 )) )) == 0.770 );
	REQUIRE( (double(uint64_t(pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encrypt( 1.123, 0.1  , false), pcS.encode( 0.100, 0.001)) )) * 10000.0)))/10000.0 == 1.0   ); // test canShift optimzation of PaillierContext::add(): 100 >>_10 2 = 1

	// encoded + encrypted
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encode( 1.123, 0.01 ), pcS.encrypt( 0.234, 0.01 , false)) )) == 0.890 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encode( 1.123, 0.01 ), pcS.encrypt( 0.234, 0.001, false)) )) == 0.886 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encode( 1.123, 0.001), pcS.encrypt( 0.234, 0.01 , false)) )) == 0.893 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encode( 1.123, 1    ), pcS.encrypt( 0.234, 0.01 , true )) )) == 0.770 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.subtract(pcS.encode( 1.120, 0.001 ),pcS.encrypt( 0.234, 0.01 , true )) )) == 0.890 ); // test canShift optimzation PaillierContext::add(): 1120 >>_10 1 = 112

	// encoded + encoded
	REQUIRE( pcS.decodeDouble(                 pcS.subtract(pcS.encode( 1.123, 0.01 ), pcS.encode( 0.234, 0.01 ))       ) == 0.890 );
	REQUIRE( pcS.decodeDouble(                 pcS.subtract(pcS.encode( 1.123, 0.01 ), pcS.encode( 0.234, 0.001))       ) == 0.886 );
	REQUIRE( pcS.decodeDouble(                 pcS.subtract(pcS.encode( 1.123, 0.001), pcS.encode( 0.234, 0.01 ))       ) == 0.893 );
	REQUIRE( pcS.decodeDouble(                 pcS.subtract(pcS.encode( 1.123, 1    ), pcS.encode( 0.234, 0.01 ))       ) == 0.770 );
}

TEST_CASE( "paillier FP paillier context multiply", "[paillierMath]" ) {
	const size_t modulusLen = TestKeys::get()->sk256modulusLen;
	const size_t precision = TestKeys::get()->sk256modulusLen;
	const SecureKey sk = TestKeys::get()->sk256;

	const PaillierContext pcS(sk.publicKey, true, precision, 10);

	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(0), pcS.encode(0)) )) == 0 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(0), pcS.encode(1)) )) == 0 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(1), pcS.encode(0)) )) == 0 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(1), pcS.encode(1)) )) == 1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(-1), pcS.encode(1)) )) == -1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(1), pcS.encode(-1)) )) == -1 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(-2), pcS.encode(-1)) )) == 2 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(-2), pcS.encode(1)) )) == -2 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(1), pcS.encode(-2)) )) == -2 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(18680 ), pcS.encode(975432)) )) == 18680ll  * 975432ll    );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(12846800), pcS.encode(98765432)) )) == 12846800ll * 98765432ll    );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(18680 ), pcS.encode(976000)) )) == 18680ll  * 976000ll );

	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(1 , true), pcS.encode(2)) )) == 2 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(1 , true), pcS.encode(-2)) )) == -2 );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(1284680 , true), pcS.encode(98765432000)) )) == 1284680ll * 98765432000ll );
	REQUIRE( pcS.decodeInt64(pcS.decrypt( sk, pcS.multiply(pcS.encrypt(-1284680 , true), pcS.encode(98765432000)) )) == -1284680ll * 98765432000ll );


	// encrypted + encoded
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encrypt( 1.123, 0.01 , false), pcS.encode( 0.234, 0.01 )) )) == 0.2576 );
	REQUIRE( (double(int64_t( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encrypt( 1.123, 0.01 , false), pcS.encode( 0.234, 0.001)) )) *1000000.0)))/1000000.0 == 0.26208 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encrypt( 1.123, 0.001, false), pcS.encode( 0.234, 0.01 )) )) == 0.25829 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encrypt( 1.123, 1    , true ), pcS.encode( 0.234, 0.01 )) )) == 0.23 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encrypt( 4.673, 0.001, true ), pcS.encode(-9.731, 0.001)) )) == 4.673 * -9.731   );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encrypt( 467.3, 0.001, true ), pcS.encode(-0.0731, 0.0001)) )) == 467.3 * -0.0731   );

	// encoded + encrypted
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encode( 1.123, 0.01 ), pcS.encrypt( 0.234, 0.01 , false)) )) == 0.2576 );
	REQUIRE( (double(int64_t( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encode( 1.123, 0.01 ), pcS.encrypt( 0.234, 0.001, false)) )) *1000000.0)))/1000000.0 == 0.26208 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encode( 1.123, 0.001), pcS.encrypt( 0.234, 0.01 , false)) )) == 0.25829 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encode( 1.123, 1    ), pcS.encrypt( 0.234, 0.01 , true )) )) == 0.23 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encode( 1.120, 0.001 ),pcS.encrypt( 0.234, 0.01 , true )) )) == 0.2576 ); // test canShift optimzation PaillierContext::add(): 1120 >>_10 1 = 112
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encode( 467.3, 0.001 ), pcS.encrypt(-0.0731, 0.0001, true)) )) == 467.3 * -0.0731   );

	// encoded + encoded
	REQUIRE( pcS.decodeDouble(                 pcS.multiply(pcS.encode( 1.123, 0.01 ), pcS.encode( 0.234, 0.01 ))       ) == 0.2576 );
	REQUIRE( (double(int64_t( pcS.decodeDouble(pcS.multiply(pcS.encode( 1.123, 0.01 ), pcS.encode( 0.234, 0.001))       ) *1000000.0)))/1000000.0 == 0.26208 );
	REQUIRE( pcS.decodeDouble(                 pcS.multiply(pcS.encode( 1.123, 0.001), pcS.encode( 0.234, 0.01 ))       ) == 0.25829 );
	REQUIRE( pcS.decodeDouble(                 pcS.multiply(pcS.encode( 1.123, 1    ), pcS.encode( 0.234, 0.01 ))       ) == 0.23 );
	REQUIRE( pcS.decodeDouble(pcS.decrypt( sk, pcS.multiply(pcS.encode( 467.3, 0.001), pcS.encrypt(-0.0731, 0.0001, true)) )) == 467.3 * -0.0731   );
}
