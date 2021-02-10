#include "../include/catch2/catch.hpp"
#include "../src/paillier/crypto/SecureKey.hpp"

#define LONG_TESTS 0

using ppvr::paillier::crypto::SecureKey;
using ppvr::paillier::crypto::PublicKey;

TEST_CASE( "paillier create key", "[paillierCrypto]" ) {
	
	// modulusLength must be a multiple of 8
	REQUIRE_THROWS( SecureKey::create(7) );
	REQUIRE_THROWS( SecureKey::create(31));
	REQUIRE_THROWS( SecureKey::create(129));
	
	REQUIRE( SecureKey::create(32).publicKey.modulus.bitLength() == 32 );
	REQUIRE( SecureKey::create(64).publicKey.modulus.bitLength() == 64 );
	REQUIRE( SecureKey::create(128).publicKey.modulus.bitLength() == 128 );
	REQUIRE( SecureKey::create(256).publicKey.modulus.bitLength() == 256 );
	#if !USE_FIX_WIDTH_INTEGER || PAILLIER_MODULUS_BIT_LENGTH >= 512
		REQUIRE( SecureKey::create(512).publicKey.modulus.bitLength() == 512 );
	#endif
	#if !USE_FIX_WIDTH_INTEGER || PAILLIER_MODULUS_BIT_LENGTH >= 1024
		REQUIRE( SecureKey::create(1024).publicKey.modulus.bitLength() == 1024 );
	#endif
	#if !USE_FIX_WIDTH_INTEGER || PAILLIER_MODULUS_BIT_LENGTH >= 2048
		REQUIRE( SecureKey::create(2048).publicKey.modulus.bitLength() == 2048 );
	#endif
}

TEST_CASE( "paillier encrypt", "[paillierCrypto]" ) {
	
	const SecureKey sk = SecureKey::create(128);
	const PublicKey pk = sk.publicKey;
	
	REQUIRE( pk.encryptWithoutObfuscation(0) == pk.encryptWithoutObfuscation(0) );
	REQUIRE( pk.encryptWithoutObfuscation(1) == pk.encryptWithoutObfuscation(1) );
	REQUIRE( pk.encryptWithoutObfuscation(255) == pk.encryptWithoutObfuscation(255) );

	REQUIRE( pk.encrypt(0) != pk.encrypt(0) );
	REQUIRE( pk.encrypt(1) != pk.encrypt(1) );
	REQUIRE( pk.encrypt(255) != pk.encrypt(255) );
	
	const PaillierInt bigTestValue{PaillierInt(2).pow(PaillierInt::fromInt64(pk.modulus.bitLength() - 1))};
	REQUIRE( pk.encrypt(bigTestValue) != pk.encrypt(bigTestValue) );
}

TEST_CASE( "paillier decrypt", "[paillierCrypto]" ) {
	
	const SecureKey sk = SecureKey::create(128);
	const PublicKey pk = sk.publicKey;
	const PaillierInt bigTestValue{PaillierInt(2).pow(PaillierInt::fromInt64(pk.modulus.bitLength() - 1))};
	
	REQUIRE( sk.decrypt(pk.encryptWithoutObfuscation(0)).toInt64() == 0 );
	REQUIRE( sk.decrypt(pk.encryptWithoutObfuscation(1)).toInt64() == 1 );
	REQUIRE( sk.decrypt(pk.encryptWithoutObfuscation(255)).toInt64() == 255 );
	REQUIRE( sk.decrypt(pk.encryptWithoutObfuscation(bigTestValue)) == bigTestValue );
	
	REQUIRE( sk.decrypt(pk.encrypt(0)).toInt64() == 0 );
	REQUIRE( sk.decrypt(pk.encrypt(1)).toInt64() == 1 );
	REQUIRE( sk.decrypt(pk.encrypt(255)).toInt64() == 255 );
	REQUIRE( sk.decrypt(pk.encrypt(bigTestValue)) == bigTestValue );
	REQUIRE( sk.decrypt(pk.encrypt(pk.modulus - PaillierInt(1))) == pk.modulus - PaillierInt(1) ); // Dec(Enc(N - 1)) = N - 1		the highest value that can be encrypted without overflow
}

TEST_CASE( "paillier add", "[paillierCrypto]" ) {
	
	const SecureKey sk = SecureKey::create(128);
	const PublicKey pk = sk.publicKey;
	const PaillierInt bigTestValue{PaillierInt(2).pow(PaillierInt::fromInt64(pk.modulus.bitLength() - 1))};
	const PaillierInt bigTestValueHalf = bigTestValue / 2;
	
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(0), pk.encrypt(0))).toInt64() == 0 );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(0), pk.encrypt(1))).toInt64() == 1 );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(1), pk.encrypt(0))).toInt64() == 1 );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(11), pk.encrypt(14))).toInt64() == 25 );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(99), pk.encrypt(14))).toInt64() == 113 );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(bigTestValueHalf), pk.encrypt(255))) == bigTestValueHalf + PaillierInt(255) );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(bigTestValueHalf), pk.encrypt(bigTestValueHalf))) == bigTestValueHalf * PaillierInt(2));
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(bigTestValueHalf), pk.encrypt(bigTestValueHalf - PaillierInt(1)))) == bigTestValueHalf * PaillierInt(2) - PaillierInt(1) );
	
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(pk.modulus - PaillierInt(2)), pk.encrypt(1))) == pk.modulus - PaillierInt(1) ); // Dec(Enc(N-1) °+ Enc(1)) = N - 1
}

TEST_CASE( "paillier mul", "[paillierCrypto]" ) {
	
	const SecureKey sk = SecureKey::create(128);
	const PublicKey pk = sk.publicKey;
	const PaillierInt bigTestValue{PaillierInt(2).pow(PaillierInt::fromInt64(pk.modulus.bitLength() - 1))};
	const PaillierInt bigTestValueHalf = bigTestValue / 2;
	
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt( 0), PaillierInt( 0))).toInt64() ==    0 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt( 0), PaillierInt( 1))).toInt64() ==    0 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt( 1), PaillierInt( 0))).toInt64() ==    0 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt( 1), PaillierInt( 1))).toInt64() ==    1 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt(11), PaillierInt(21))).toInt64() ==  231 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt(99), PaillierInt(14))).toInt64() == 1386 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt(bigTestValueHalf), PaillierInt(2))) == bigTestValueHalf * PaillierInt(2) );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt(PaillierInt::fromInt64(154697)), PaillierInt::fromInt64(984567))).toInt64() == 154697ll * 984567ll );
	
}
