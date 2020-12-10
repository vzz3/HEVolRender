#pragma once
#include <string>
#include "../../math/SArbBigInt.hpp"
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
				SecureKey(const SArbBigInt& yP, const SArbBigInt& yQ, const PublicKey& yPublicKey);
				~SecureKey();

				/**
				 * Implementation of the decryption function of the Paillier encryption
				 * scheme. Returns the plain text of a given cipher text.
				 *
				 * @param ciphertext to be decrypted.
				 * @return the decrypted plaintext.
				 */
				SArbBigInt decrypt(SArbBigInt ciphertext) const;

			private:
				/**
				 * Computes the L function as defined in Paillier's paper. That is: L(x,p) =
				 * (x-1)/p
				 */
				static SArbBigInt lFunction(const SArbBigInt& x, const SArbBigInt& p);

				/**
				 * Computes the h-function as defined in Paillier's paper page 12,
				 * 'Decryption using Chinese-remaindering'.
				 */
				static SArbBigInt hFunction(const SArbBigInt& x, const SArbBigInt& xSquared, const PublicKey& yPublicKey);

				/**
				 * The Chinese Remainder Theorem as needed for decryption.
				 *
				 * @param mp the solution modulo p.
				 * @param mq the solution modulo q.
				 * @return the solution modulo n=pq.
				 */
				SArbBigInt crt(const SArbBigInt& mp, const SArbBigInt& mq ) const;

			// ----- member variables -----
			public:
				/**
				 * The first prime number, {@code p} such that
				 * {@code p*q = publicKey.modulus}.
				 */
				const SArbBigInt p;

				/**
				 * The first prime number, {@code q} such that
				 * {@code p*q = publicKey.modulus}.
				 */
				const SArbBigInt q;

				const PublicKey publicKey;

			private:
				/**
				 * The value <code>p<sup>2</sup></code>
				 */
				const SArbBigInt _pSquared;

				/**
				 * The value <code>q<sup>2</sup></code>
				 */
				const SArbBigInt _qSquared;

				/**
				 * The modular inverse of <code>p modulo q</code>
				 */
				const SArbBigInt _pInverse;

				/**
				 * Precomputed <code>hp</code> as defined in Paillier's paper page 12:
				 * Decryption using Chinese-remaindering.
				 */
				const SArbBigInt _hp;

				/**
				 * Precomputed <code>hq</code> as defined in Paillier's paper page 12:
				 * Decryption using Chinese-remaindering.
				 */
				const SArbBigInt _hq;
			};
		}
	}
}
