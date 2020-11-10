#pragma once
#include <string>
#include "../../math/SInfinitBigInt.hpp"
#include "PublicKey.hpp"

// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)

namespace ppvr {
	namespace paillier {
		namespace crypto {
			class SecureKey {
				
			// ----- static create -----
			public:
				/**
				 * Creates a Paillier keypair of the specified modulus key length.
				 *
				 * @param modulusBitLength the length of the public key modulus. Must be a positive multiple of 8.
				 * @return a Paillier keypair consists of a private key and the corresponding public key.
				 * @throws IllegalArgumentException on illegal {@code modulusLength}.
				 */
				static SecureKey create(uint modulusBitLength);
				
			public:
				SecureKey(const SInfinitBigInt& yP, const SInfinitBigInt& yQ, const PublicKey& yPublicKey);
				~SecureKey();
				
				/**
				 * Implementation of the decryption function of the Paillier encryption
				 * scheme. Returns the plain text of a given cipher text.
				 *
				 * @param ciphertext to be decrypted.
				 * @return the decrypted plaintext.
				 */
				SInfinitBigInt decrypt(SInfinitBigInt ciphertext) const;
				
			private:
				/**
				 * Computes the L function as defined in Paillier's paper. That is: L(x,p) =
				 * (x-1)/p
				 */
				static SInfinitBigInt lFunction(const SInfinitBigInt& x, const SInfinitBigInt& p);
				
				/**
				 * Computes the h-function as defined in Paillier's paper page 12,
				 * 'Decryption using Chinese-remaindering'.
				 */
				static SInfinitBigInt hFunction(const SInfinitBigInt& x, const SInfinitBigInt& xSquared, const PublicKey& yPublicKey);
				
				/**
				 * The Chinese Remainder Theorem as needed for decryption.
				 *
				 * @param mp the solution modulo p.
				 * @param mq the solution modulo q.
				 * @return the solution modulo n=pq.
				 */
				SInfinitBigInt crt(const SInfinitBigInt& mp, const SInfinitBigInt& mq ) const;
				
			// ----- member variables -----
			public:
				/**
				 * The first prime number, {@code p} such that
				 * {@code p*q = publicKey.modulus}.
				 */
				const SInfinitBigInt p;
				
				/**
				 * The first prime number, {@code q} such that
				 * {@code p*q = publicKey.modulus}.
				 */
				const SInfinitBigInt q;
				
				const PublicKey publicKey;
				
			private:
				/**
				 * The value <code>p<sup>2</sup></code>
				 */
				const SInfinitBigInt _pSquared;
				
				/**
				 * The value <code>q<sup>2</sup></code>
				 */
				const SInfinitBigInt _qSquared;
				
				/**
				 * The modular inverse of <code>p modulo q</code>
				 */
				const SInfinitBigInt _pInverse;
				
				/**
				 * Precomputed <code>hp</code> as defined in Paillier's paper page 12:
				 * Decryption using Chinese-remaindering.
				 */
				const SInfinitBigInt _hp;
				
				/**
				 * Precomputed <code>hq</code> as defined in Paillier's paper page 12:
				 * Decryption using Chinese-remaindering.
				 */
				const SInfinitBigInt _hq;
			};
		}
	}
}
