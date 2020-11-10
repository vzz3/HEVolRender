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
	REQUIRE( SecureKey::create(512).publicKey.modulus.bitLength() == 512 );
	//REQUIRE( SecureKey::create(1024).publicKey.getModulus().bitLength() == 1024 );
	//REQUIRE( SecureKey::create(2048).publicKey.getModulus().bitLength() == 2048 );
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
	
	const SInfinitBigInt bigTestValue{SInfinitBigInt(2).pow(SInfinitBigInt::fromInt64(pk.modulus.bitLength() - 1))};
	REQUIRE( pk.encrypt(bigTestValue) != pk.encrypt(bigTestValue) );
}

TEST_CASE( "paillier decrypt", "[paillierCrypto]" ) {
	
	const SecureKey sk = SecureKey::create(128);
	const PublicKey pk = sk.publicKey;
	const SInfinitBigInt bigTestValue{SInfinitBigInt(2).pow(SInfinitBigInt::fromInt64(pk.modulus.bitLength() - 1))};
	
	REQUIRE( sk.decrypt(pk.encryptWithoutObfuscation(0)).toInt64() == 0 );
	REQUIRE( sk.decrypt(pk.encryptWithoutObfuscation(1)).toInt64() == 1 );
	REQUIRE( sk.decrypt(pk.encryptWithoutObfuscation(255)).toInt64() == 255 );
	REQUIRE( sk.decrypt(pk.encryptWithoutObfuscation(bigTestValue)) == bigTestValue );
	
	REQUIRE( sk.decrypt(pk.encrypt(0)).toInt64() == 0 );
	REQUIRE( sk.decrypt(pk.encrypt(1)).toInt64() == 1 );
	REQUIRE( sk.decrypt(pk.encrypt(255)).toInt64() == 255 );
	REQUIRE( sk.decrypt(pk.encrypt(bigTestValue)) == bigTestValue );
	REQUIRE( sk.decrypt(pk.encrypt(pk.modulus - SInfinitBigInt(1))) == pk.modulus - SInfinitBigInt(1) ); // Dec(Enc(N - 1)) = N - 1		the highest value that can be encrypted without overflow
}

TEST_CASE( "paillier add", "[paillierCrypto]" ) {
	
	const SecureKey sk = SecureKey::create(128);
	const PublicKey pk = sk.publicKey;
	const SInfinitBigInt bigTestValue{SInfinitBigInt(2).pow(SInfinitBigInt::fromInt64(pk.modulus.bitLength() - 1))};
	const SInfinitBigInt bigTestValueHalf = bigTestValue / 2;
	
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(0), pk.encrypt(0))).toInt64() == 0 );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(0), pk.encrypt(1))).toInt64() == 1 );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(1), pk.encrypt(0))).toInt64() == 1 );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(11), pk.encrypt(14))).toInt64() == 25 );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(99), pk.encrypt(14))).toInt64() == 113 );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(bigTestValueHalf), pk.encrypt(255))) == bigTestValueHalf + SInfinitBigInt(255) );
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(bigTestValueHalf), pk.encrypt(bigTestValueHalf))) == bigTestValueHalf * SInfinitBigInt(2));
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(bigTestValueHalf), pk.encrypt(bigTestValueHalf - SInfinitBigInt(1)))) == bigTestValueHalf * SInfinitBigInt(2) - SInfinitBigInt(1) );
	
	REQUIRE( sk.decrypt(pk.add(pk.encrypt(pk.modulus - SInfinitBigInt(2)), pk.encrypt(1))) == pk.modulus - SInfinitBigInt(1) ); // Dec(Enc(N-1) °+ Enc(1)) = N - 1
}

TEST_CASE( "paillier mul", "[paillierCrypto]" ) {
	
	const SecureKey sk = SecureKey::create(128);
	const PublicKey pk = sk.publicKey;
	const SInfinitBigInt bigTestValue{SInfinitBigInt(2).pow(SInfinitBigInt::fromInt64(pk.modulus.bitLength() - 1))};
	const SInfinitBigInt bigTestValueHalf = bigTestValue / 2;
	
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt( 0), SInfinitBigInt( 0))).toInt64() ==    0 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt( 0), SInfinitBigInt( 1))).toInt64() ==    0 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt( 1), SInfinitBigInt( 0))).toInt64() ==    0 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt( 1), SInfinitBigInt( 1))).toInt64() ==    1 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt(11), SInfinitBigInt(21))).toInt64() ==  231 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt(99), SInfinitBigInt(14))).toInt64() == 1386 );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt(bigTestValueHalf), SInfinitBigInt(2))) == bigTestValueHalf * SInfinitBigInt(2) );
	REQUIRE( sk.decrypt(pk.multiply(pk.encrypt(SInfinitBigInt::fromInt64(154697)), SInfinitBigInt::fromInt64(984567))).toInt64() == 154697ll * 984567ll );
	
}
