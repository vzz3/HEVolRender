
#include "PublicKey.hpp"
#include <iostream>

using namespace ppvr::paillier::crypto;

PublicKey::PublicKey(const SArbBigInt & yModulus)
	: modulus(yModulus)
	, _modulusSquared(yModulus.pow(SArbBigInt(2)))
	, generator(yModulus + SArbBigInt(1)) //the generator is always set to modulus+1, as this allows a significantly more efficient encryption function.
{}

PublicKey::~PublicKey() {}

SArbBigInt PublicKey::encrypt(const SArbBigInt & plaintext) const {
	return obfuscate(encryptWithoutObfuscation(plaintext));
}

SArbBigInt PublicKey::encryptWithoutObfuscation(const SArbBigInt & plaintext) const {
	// we chose g = N + 1, so that we can exploit the fact that
	// (N+1)^plaintext = N*plaintext + 1 mod N^2
	// Advances in Cryptology - ASIACRYPT 2003: 9th International Conference on the ... Page 275 (4.1 The CGHN Public Key Cryptosystem)
	// https://books.google.at/books?id=UFxucQdTZnIC&pg=PA275&lpg=PA275&dq=paillier+g%3Dn%2B1+n%2Bm%2B1&source=bl&ots=BLnQYA74_R&sig=ACfU3U024sGGhwQUe4D26kdcPapNfj0tLw&hl=en&sa=X&ved=2ahUKEwim96Lu0vrpAhWuy6YKHfpZBrcQ6AEwAXoECAgQAQ#v=onepage&q=paillier%20g%3Dn%2B1%20n%2Bm%2B1&f=false
	//
	// sebastian:
	// (1+N)^m mod N^2 = (1+N) * (1+N) * (1+N) * ..... mod N^2
	// (1+2N+N^2) * (1+N) * (1+N) * (1+N) * ..... mod N^2 => ((1+2N+N^2) mod N^2) * ((1+N) mod N^2) * ((1+N) mod N^2) * ((1+N) mod N^2) * ..... => (1+2N) * (1+N) * (1+N) * (1+N) * ..... mod N^2
	// (1+3N+2N^2) * (1+N) * (1+N) * (1+N) * ..... mod N^2 => (1+3N) * (1+N) * (1+N) * (1+N) * ..... mod N^2
	// (1+4N+3N^2) * (1+N) * (1+N) * (1+N) * ..... mod N^2 => (1+4N) * (1+N) * (1+N) * (1+N) * ..... mod N^2
	// :...
	// (1+mN+(m-1)N^2   mod N^2 = 1+mN		=> N*m + 1	mod N^2

	return (modulus * plaintext + SArbBigInt(1)) % _modulusSquared;
}

SArbBigInt PublicKey::obfuscate(const SArbBigInt & ciphertext) const {
	//return BigIntegerUtil.modPow(randomPositiveNumber(modulus), modulus, _modulusSquared).multiply(ciphertext).mod(_modulusSquared);
	SArbBigInt r = getNewRandomNumber();
	return r.modPow(modulus, _modulusSquared) * ciphertext % _modulusSquared;
}

SArbBigInt PublicKey::getNewRandomNumber() const {
	Random& rnd = Random::getForLocalThread();
	return SArbBigInt::randomNumber(modulus, rnd);
}

SArbBigInt PublicKey::add(const SArbBigInt & ciphertext1, const SArbBigInt & ciphertext2) const {
	return ciphertext1 * ciphertext2 % _modulusSquared;
}

SArbBigInt PublicKey::multiply(const SArbBigInt & ciphertext, const SArbBigInt & plainfactor) const {
	return ciphertext.modPow(plainfactor, _modulusSquared);
}

bool PublicKey::operator== (const PublicKey& other) const {
	return this == &other || modulus == other.modulus;
}

bool PublicKey::operator!= (const PublicKey& other) const {
	return !(this->operator==(other));
}
