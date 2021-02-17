
#include "CryptoUtil.hpp"

using namespace ppvr::paillier::crypto;
using namespace ppvr::rendering::data;

#include <QThreadPool>

void CryptoUtil::encrypt(const PublicKey& yPublicKey, const Volume<uint16_t>& ySrc, Volume<PaillierInt>& yDst) {
	yDst.resize(ySrc.width(), ySrc.height(), ySrc.depth());
	
	if(true) {
		const uint w = ySrc.width();
		
		QThreadPool tPool;
		for(uint x = 0; x < w; x++) {
			VolumeRowEncTask* rowEncTask = new VolumeRowEncTask(&yPublicKey, &ySrc, &yDst, x);
			tPool.start(rowEncTask);
		}
		tPool.waitForDone();
	} else {
		size_t n = ySrc.length();
		for (size_t i=0; i<n; i++) {
			PaillierInt pVoxel = PaillierInt::fromInt64(ySrc.get(i));
			yDst.set(i, yPublicKey.encrypt(pVoxel));
			//yDst.set(i, yPublicKey.encryptWithoutObfuscation(pVoxel));
		}
	}
}


void CryptoUtil::decrypt(const SecureKey& ySecureKey, const PaillierInt& yScale, const Image<PaillierInt>& ySrc, Image<uint16_t>& yDst) {
	//PaillierInt test1{1};
	
	#ifdef GPU_MONTGOMERY_REDUCTION
		MontgomeryReducer<PaillierInt> mmr{ySecureKey.publicKey.getModulusSquared()};
	#endif
	
	yDst.resize(ySrc.width(), ySrc.height());
	size_t n = ySrc.length();
	for (size_t i=0; i<n; i++) {
		PaillierInt eVoxel = ySrc.get(i);
		#ifdef GPU_MONTGOMERY_REDUCTION
			eVoxel = mmr.convertOut(eVoxel);
		#endif
		PaillierInt bigVal = ySecureKey.decrypt(eVoxel) ;
		bigVal = bigVal / yScale; //PaillierInt::fromInt64(50);
		yDst.set(i, (uint16_t)bigVal.toInt64());
		
		//if(src > test1) {
		//	std::cout << "Fount Rendering Result at index " << i << ", value: " << src.toStringHex() << ", decrypted: " << bigVal.toStringHex() <<std::endl;
		//}
	}
}
