#pragma once


#include "../../paillier/crypto/PublicKey.hpp"
#include "../../paillier/crypto/SecureKey.hpp"
#include "./Volume.hpp"
#include "./Image.hpp"

using ppvr::paillier::crypto::PublicKey;
using ppvr::paillier::crypto::SecureKey;

namespace ppvr {
	namespace rendering {
		namespace data {
			class CryptoUtil {
				
			public:
				static void encrypt(const PublicKey& yPublicKey, const Volume<uint16_t>& ySrc, Volume<PaillierInt>& yDst);
				
				
				static void decrypt(const SecureKey& ySecureKey, const PaillierInt& yScale, const Image<PaillierInt>& ySrc, Image<uint16_t>& yDst);
			};
		}
	}
}
