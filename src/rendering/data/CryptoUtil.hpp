#pragma once


#include "../../paillier/crypto/PublicKey.hpp"
#include "../../paillier/crypto/SecureKey.hpp"
#include "./Volume.hpp"
#include "./Image.hpp"
#include <QRunnable>

using ppvr::paillier::crypto::PublicKey;
using ppvr::paillier::crypto::SecureKey;

namespace ppvr {
	namespace rendering {
		namespace data {
			class CryptoUtil {
				
			private:
				class VolumeRowEncTask : public QRunnable {
					const uint x;
					const Volume<uint16_t>* src;
					Volume<PaillierInt>* dst;
					const PublicKey* publicKey;
					
				public:
					inline VolumeRowEncTask(const PublicKey* yPublicKey, const Volume<uint16_t>* ySrc, Volume<PaillierInt>* yDst, const uint yX)
					: publicKey{yPublicKey}, src{ySrc}, dst{yDst}, x{yX}  {
						// Auto-deletion is enabled by default.
					}
					
					#ifdef GPU_MONTGOMERY_REDUCTION
						MontgomeryReducer<PaillierInt> mmr{publicKey->getModulusSquared()}; // One for all threads would be enough.
					#endif
					
					inline void run() override {
						const uint h = src->height();
						const uint d = src->depth();
						Random* rnd = Random::getForLocalThread();
						
						for(uint y = 0; y < h; y++) {
							for(uint z = 0; z < d; z++) {
								PaillierInt pVoxel = PaillierInt::fromInt64(src->get(x, y, z));
								//PaillierInt eVoxel = publicKey->encryptWithoutObfuscation(pVoxel);
								PaillierInt eVoxel = publicKey->encrypt(pVoxel, rnd);
								#ifdef GPU_MONTGOMERY_REDUCTION
									eVoxel = mmr.convertIn(eVoxel);
								#endif
								dst->set(x, y, z, eVoxel);
							}
						}
					}
				};
				
				class ImageRowDecTask : public QRunnable {
					const uint x;
					const Image<PaillierInt>* src;
					Image<uint16_t>* dst;
					const SecureKey* secureKey;
					const PaillierInt* scale;
					
				public:
					inline ImageRowDecTask(const SecureKey* ySecureKey, const Image<PaillierInt>* ySrc, Image<uint16_t>* yDst, const uint yX, const PaillierInt* yScale)
					: secureKey{ySecureKey}, src{ySrc}, dst{yDst}, x{yX}, scale{yScale}  {
						// Auto-deletion is enabled by default.
					}
					
					inline void run() override {
						const uint h = src->height();
						Random* rnd = Random::getForLocalThread();
						
						#ifdef GPU_MONTGOMERY_REDUCTION
							MontgomeryReducer<PaillierInt> mmr{secureKey->publicKey.getModulusSquared()}; // One for all threads would be enough.
						#endif
						
						for(uint y = 0; y < h; y++) {
								PaillierInt ePixel = src->get(x, y);
								#ifdef GPU_MONTGOMERY_REDUCTION
									ePixel = mmr.convertOut(ePixel);
								#endif
								PaillierInt bigVal = secureKey->decrypt(ePixel) ;
								bigVal = bigVal / (*scale); //PaillierInt::fromInt64(50);
								dst->set(x, y, (uint16_t)bigVal.toInt64());
						}
					}
				};
				
			public:
				static void encrypt(const PublicKey& yPublicKey, const Volume<uint16_t>& ySrc, Volume<PaillierInt>& yDst);
				
				
				static void decrypt(const SecureKey& ySecureKey, const PaillierInt& yScale, const Image<PaillierInt>& ySrc, Image<uint16_t>& yDst);
			};
		}
	}
}
