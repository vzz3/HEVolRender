
#include "SecureKey.hpp"
#include <iostream>

using namespace ppvr::paillier::crypto;

SecureKey SecureKey::create(uint modulusBitLength) {
	if (modulusBitLength < 8 || modulusBitLength % 8 != 0) {
		std::string msg = "modulusLength must be a multiple of 8";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	// Find two primes p and q whose multiple has the same number of bits
	// as modulusLength
	PaillierInt p, q, modulus;
	uint primeLength = modulusBitLength / 2;
	Random rnd{};
	do {
		p = PaillierInt::probablePrime(primeLength, rnd);
		do {
			q = PaillierInt::probablePrime(primeLength, rnd);
		} while (p == q); //p and q must not be equal
		modulus = p * q;
	} while (modulus.bitLength() != modulusBitLength);

	const PublicKey publicKey(modulus);
	const SecureKey privateKey(p, q, publicKey);
	return privateKey;
}

SecureKey::SecureKey(const PaillierInt& yP, const PaillierInt& yQ, const PublicKey & yPublicKey)
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

PaillierInt SecureKey::lFunction(const PaillierInt& x, const PaillierInt& p) {
	return (x - PaillierInt(1) ) / p;
}

PaillierInt SecureKey::hFunction(const PaillierInt& x, const PaillierInt& xSquared, const PublicKey& yPublicKey) {
	return lFunction(yPublicKey.generator.modPow(x - PaillierInt(1), xSquared), x).modInverse(x);
}

PaillierInt SecureKey::crt(const PaillierInt& mp, const PaillierInt& mq) const {
	PaillierInt u = ((mq - mp) * _pInverse) % q;
	u = u * p + mp;
	return u;
}


PaillierInt SecureKey::decrypt(PaillierInt ciphertext) const {
	//return c.modPow(this.lambda,this.pubkey.n2).subtract(BigInteger.ONE).divide(this.pubkey.n).multiply(this.x).mod(this.pubkey.n);

	PaillierInt decryptedToP = (lFunction(ciphertext.modPow(p - 1, _pSquared), p) * _hp) % p;
	PaillierInt decryptedToQ = (lFunction(ciphertext.modPow(q - 1, _qSquared), q) * _hq) % q;
	PaillierInt decryptedValue = crt(decryptedToP, decryptedToQ);
	return decryptedValue;
}
