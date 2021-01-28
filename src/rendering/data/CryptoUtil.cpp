
#include "CryptoUtil.hpp"

using namespace ppvr::paillier::crypto;
using namespace ppvr::rendering::data;

void CryptoUtil::encrypt(const PublicKey& yPublicKey, const Volume<uint16_t>& ySrc, Volume<PaillierInt>& yDst) {
	yDst.resize(ySrc.width(), ySrc.height(), ySrc.depth());
	size_t n = ySrc.length();
	for (size_t i=0; i<n; i++) {
		//yDst.set(i, yPublicKey.encrypt(ySrc.get(i)));
		yDst.set(i, yPublicKey.encryptWithoutObfuscation(PaillierInt::fromInt64(ySrc.get(i))));
	}
}


void CryptoUtil::decrypt(const SecureKey& ySecureKey, const PaillierInt& yScale, const Image<PaillierInt>& ySrc, Image<uint16_t>& yDst) {
	//PaillierInt test1{1};
	yDst.resize(ySrc.width(), ySrc.height());
	size_t n = ySrc.length();
	for (size_t i=0; i<n; i++) {
		//PaillierInt src = ySrc.get(i);
		
		PaillierInt bigVal = ySecureKey.decrypt(ySrc.get(i)) ;/// yScale;
		bigVal = bigVal / PaillierInt::fromInt64(50);
		yDst.set(i, (uint16_t)bigVal.toInt64());
		
		//if(src > test1) {
		//	std::cout << "Fount Rendering Result at index " << i << ", value: " << src.toStringHex() << ", decrypted: " << bigVal.toStringHex() <<std::endl;
		//}
	}
}
