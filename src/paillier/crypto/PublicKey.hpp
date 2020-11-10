#pragma once
#include <string>
#include "../../math/SInfinitBigInt.hpp"

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
				 const SInfinitBigInt modulus;
				
			private:
				/**
				 * The modulus squared (n<sup>2</sup>) of the public key.
				 */
				const SInfinitBigInt _modulusSquared;
				
			public:
				/**
				 * The generator (g) of the public key
				 */
				const SInfinitBigInt generator;
				
			public:
				/**
				 * Constructs a Paillier public key.
				 *
				 * @param modulus of the public key
				 */
				PublicKey(const SInfinitBigInt & yModulus);
				~PublicKey();
				
				/*
				const SInfinitBigInt & getModulus() const {
					return modulus;
				}
				
				const SInfinitBigInt & getGenerator() const {
					return _generator;
				}
				
				const SInfinitBigInt & getModulusSquared() const {
					return _modulusSquared;
				}
				*/
				
				
				/**
				 * Implements the encryption function of the Paillier encryption scheme.
				 *
				 * @param plaintext to be encrypted.
				 * @return corresponding ciphertext.
				 */
				SInfinitBigInt encrypt(const SInfinitBigInt & plaintext) const;
				
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
				SInfinitBigInt encryptWithoutObfuscation(const SInfinitBigInt & plaintext) const;
				
				/**
				 * Implements the obfuscation function of the Paillier encryption scheme. It
				 * changes the value of a ciphertext without changing the corresponding
				 * plaintext.
				 *
				 * @param ciphertext to be ofuscated
				 * @return obfuscated ciphertext.
				 */
				SInfinitBigInt obfuscate(const SInfinitBigInt & ciphertext) const;
				
			private:
				/**
				 * returns a rendom number that is greater the 0 and less then the modulus.
				 * @return
				 */
				SInfinitBigInt getNewRandomNumber() const;
			
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
				SInfinitBigInt add(const SInfinitBigInt & ciphertext1, const SInfinitBigInt & ciphertext2) const;
				
				/**
				 * Implements the multiplication function of the Paillier encryption scheme.
				 * In the Paillier scheme you can only multiply an unencrypted value with an
				 * encrypted value.
				 *
				 * @param ciphertext of factor a.
				 * @param plainfactor b.
				 * @return product a*b.
				 */
				SInfinitBigInt multiply(const SInfinitBigInt & ciphertext, const SInfinitBigInt & plainfactor) const;
				
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
				
			};
		}
	}
}
