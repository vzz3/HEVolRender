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
					
					inline void run() override {
						const uint h = src->height();
						const uint d = src->depth();
						Random* rnd = Random::getForLocalThread();
						
						for(uint y = 0; y < h; y++) {
							for(uint z = 0; z < d; z++) {
								PaillierInt pVoxel = PaillierInt::fromInt64(src->get(x, y, z));
								dst->set(x, y, z, publicKey->encrypt(pVoxel, rnd));
							}
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
