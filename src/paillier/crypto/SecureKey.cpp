
#include "SecureKey.hpp"
#include <iostream>

using namespace ppvr::paillier::crypto;

SecureKey SecureKey::create(uint modulusBitLength) {
	if (modulusBitLength < 8 || modulusBitLength % 8 != 0) {
		std::string msg = "modulusLength must be a multiple of 8";
		//std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	
	// Find two primes p and q whose multiple has the same number of bits
	// as modulusLength
	SInfinitBigInt p, q, modulus;
	uint primeLength = modulusBitLength / 2;
	Random rnd{};
	do {
		p = SInfinitBigInt::probablePrime(primeLength, rnd);
		do {
			q = SInfinitBigInt::probablePrime(primeLength, rnd);
		} while (p == q); //p and q must not be equal
		modulus = p * q;
	} while (modulus.bitLength() != modulusBitLength);
	
	const PublicKey publicKey(modulus);
	const SecureKey privateKey(p, q, publicKey);
	return privateKey;
}

SecureKey::SecureKey(const SInfinitBigInt& yP, const SInfinitBigInt& yQ, const PublicKey & yPublicKey)
	: p(yP)
	, q(yQ)
	, publicKey(yPublicKey)
	, _pSquared(yP.pow(2))
	, _qSquared(yQ.pow(2))
	, _pInverse(yP.modInverse(yQ))
	, _hp(hFunction(p, _pSquared, publicKey))
	, _hq(hFunction(q, _qSquared, publicKey))
{}

SecureKey::~SecureKey() {}

SInfinitBigInt SecureKey::lFunction(const SInfinitBigInt& x, const SInfinitBigInt& p) {
	return (x - SInfinitBigInt(1) ) / p;
}

SInfinitBigInt SecureKey::hFunction(const SInfinitBigInt& x, const SInfinitBigInt& xSquared, const PublicKey& yPublicKey) {
	return lFunction(yPublicKey.generator.modPow(x - SInfinitBigInt(1), xSquared), x).modInverse(x);
}

SInfinitBigInt SecureKey::crt(const SInfinitBigInt& mp, const SInfinitBigInt& mq) const {
	SInfinitBigInt u = ((mq - mp) * _pInverse) % q;
	u = u * p + mp;
	return u;
}


SInfinitBigInt SecureKey::decrypt(SInfinitBigInt ciphertext) const {
	//return c.modPow(this.lambda,this.pubkey.n2).subtract(BigInteger.ONE).divide(this.pubkey.n).multiply(this.x).mod(this.pubkey.n);
	
	SInfinitBigInt decryptedToP = (lFunction(ciphertext.modPow(p - 1, _pSquared), p) * _hp) % p;
	SInfinitBigInt decryptedToQ = (lFunction(ciphertext.modPow(q - 1, _qSquared), q) * _hq) % q;
	SInfinitBigInt decryptedValue = crt(decryptedToP, decryptedToQ);
	return decryptedValue;
}
