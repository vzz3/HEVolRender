#pragma once
#include <string>
#include "../Paillier_typeDev.h"
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

			private:
				SecureKey(const PaillierInt& yP, const PaillierInt& yQ, const PublicKey& yPublicKey);
			public:
				SecureKey(const PaillierInt& yP, const PaillierInt& yQ);
				~SecureKey();

				/**
				 * Implementation of the decryption function of the Paillier encryption
				 * scheme. Returns the plain text of a given cipher text.
				 *
				 * @param ciphertext to be decrypted.
				 * @return the decrypted plaintext.
				 */
				PaillierInt decrypt(PaillierInt ciphertext) const;

			private:
				/**
				 * Computes the L function as defined in Paillier's paper. That is: L(x,p) =
				 * (x-1)/p
				 */
				static PaillierInt lFunction(const PaillierInt& x, const PaillierInt& p);

				/**
				 * Computes the h-function as defined in Paillier's paper page 12,
				 * 'Decryption using Chinese-remaindering'.
				 */
				static PaillierInt hFunction(const PaillierInt& x, const PaillierInt& xSquared, const PublicKey& yPublicKey);

				/**
				 * The Chinese Remainder Theorem as needed for decryption.
				 *
				 * @param mp the solution modulo p.
				 * @param mq the solution modulo q.
				 * @return the solution modulo n=pq.
				 */
				PaillierInt crt(const PaillierInt& mp, const PaillierInt& mq ) const;

			// ----- member variables -----
			public:
				/**
				 * The first prime number, {@code p} such that
				 * {@code p*q = publicKey.modulus}.
				 */
				const PaillierInt p;

				/**
				 * The first prime number, {@code q} such that
				 * {@code p*q = publicKey.modulus}.
				 */
				const PaillierInt q;

				const PublicKey publicKey;

			private:
				/**
				 * The value <code>p<sup>2</sup></code>
				 */
				const PaillierInt _pSquared;

				/**
				 * The value <code>q<sup>2</sup></code>
				 */
				const PaillierInt _qSquared;

				/**
				 * The modular inverse of <code>p modulo q</code>
				 */
				const PaillierInt _pInverse;

				/**
				 * Precomputed <code>hp</code> as defined in Paillier's paper page 12:
				 * Decryption using Chinese-remaindering.
				 */
				const PaillierInt _hp;

				/**
				 * Precomputed <code>hq</code> as defined in Paillier's paper page 12:
				 * Decryption using Chinese-remaindering.
				 */
				const PaillierInt _hq;
			};
		}
	}
}
