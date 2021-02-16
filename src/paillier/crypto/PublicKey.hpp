#pragma once
#include <string>
#include "../Paillier_typeDev.h"

// see "The art of computer programming - volume 2" (4.3 Multiple-Pressision Arithmetic - page 250)
using namespace ppvr::math;

namespace ppvr {
	namespace paillier {
		namespace crypto {
			class PublicKey {

			// ----- member variables -----
			public:
			//protected:
				/**
				 * The modulus (n) of the public key.
				 */
				 const PaillierInt modulus;

			private:
				/**
				 * The modulus squared (n<sup>2</sup>) of the public key.
				 */
				const PaillierInt _modulusSquared;

			public:
				/**
				 * The generator (g) of the public key
				 */
				const PaillierInt generator;

			public:
				/**
				 * Constructs a Paillier public key.
				 *
				 * @param modulus of the public key
				 */
				PublicKey(const PaillierInt & yModulus);
				~PublicKey();

				/*
				const PaillierInt & getModulus() const {
					return modulus;
				}

				const PaillierInt & getGenerator() const {
					return _generator;
				}
				*/
				const PaillierInt& getModulusSquared() const {
					return _modulusSquared;
				}


				/**
				 * Implements the encryption function of the Paillier encryption scheme.
				 *
				 * @param plaintext to be encrypted.
				 * @return corresponding ciphertext.
				 */
				PaillierInt encrypt(const PaillierInt & plaintext, Random* rnd = nullptr) const;

				/**
				 * The encryption function of the Paillier encryption scheme can be divided
				 * into two parts: - The first part, as implemented here, maps the plaintext
				 * into the encrypted space. But be aware, that this function is invertible,
				 * that is, the ciphertext is not yet secure. - Only after the second part,
				 * the 'raw_obfuscate' function, the ciphertext is secure and the
				 * corresponding plaintext can't be recovered without the secret key. The
				 * reason we split the encryption is that the second part is computationally
				 * significantly more expensive than the first part and since the
				 * obfuscation has to be done only once before you can securely share the
				 * generated ciphertext, there are scenarios, where obfuscating at
				 * encryption is unnecessary.
				 *
				 * @param plaintext to be encrypted.
				 * @return corresponding unobfuscated ciphertext.
				 */
				PaillierInt encryptWithoutObfuscation(const PaillierInt & plaintext) const;

				/**
				 * Implements the obfuscation function of the Paillier encryption scheme. It
				 * changes the value of a ciphertext without changing the corresponding
				 * plaintext.
				 *
				 * @param ciphertext to be ofuscated
				 * @return obfuscated ciphertext.
				 */
				PaillierInt obfuscate(const PaillierInt & ciphertext, Random* rnd = nullptr) const;

			private:
				/**
				 * returns a rendom number that is greater the 0 and less then the modulus.
				 * @return
				 */
				PaillierInt getNewRandomNumber(Random* rnd = nullptr) const;

			public:
				/**
				 * Implements the addition function of two ciphertexts of the Paillier
				 * encryption scheme.
				 *
				 * @param ciphertext1 first ciphertext.
				 * @param ciphertext2 second ciphertext.
				 * @return ciphertext of the sum of the two plaintexts corresponding to
				 * {@code ciphertext1} and {@code ciphertext2}.
				 */
				PaillierInt add(const PaillierInt & ciphertext1, const PaillierInt & ciphertext2) const;

				/**
				 * Implements the multiplication function of the Paillier encryption scheme.
				 * In the Paillier scheme you can only multiply an unencrypted value with an
				 * encrypted value.
				 *
				 * @param ciphertext of factor a.
				 * @param plainfactor b.
				 * @return product a*b.
				 */
				PaillierInt multiply(const PaillierInt & ciphertext, const PaillierInt & plainfactor) const;

				/*
				public BigInteger dotProduct(BigInteger[] xPlain, BigInteger[] yEncrypted, SecureKey privateKey4Debug) {
					BigInteger productSumE = this.encrypt(BigInteger.ZERO);
					assert xPlain.length == yEncrypted.length;

					for(int i=0; i < xPlain.length; i++) {
						BigInteger productE = this.multiply(yEncrypted[i], xPlain[i]);
						productSumE = this.add(productSumE, productE);

						double xiPlain = xPlain[i].doubleValue();
						double yiD = privateKey4Debug.decrypt(yEncrypted[i]).doubleValue();
						double productD = privateKey4Debug.decrypt(productE).doubleValue();
						double productSumD = privateKey4Debug.decrypt(productSumE).doubleValue();
						System.out.println("dotProduct [" + i + "] "+xiPlain+" * "+yiD+" = "+(xiPlain * yiD)+"; Dec(p): " + productD + ",  Dec(s): " + productSumD);
					}

					return productSumE;
				}
				*/

				bool operator== (const PublicKey& other) const;
				bool operator!= (const PublicKey& other) const;

			};
		}
	}
}
