
#include "CryptoUtil.hpp"

using namespace ppvr::paillier::crypto;
using namespace ppvr::rendering::data;

#include <QThreadPool>

void CryptoUtil::encrypt(const PublicKey& yPublicKey, const Volume<uint16_t>& ySrc, Volume<PaillierInt>& yDst) {
	yDst.resize(ySrc.width(), ySrc.height(), ySrc.depth());
	
	if(true) {
		// multithreaded
		const uint w = ySrc.width();
		
		QThreadPool tPool;
		for(uint x = 0; x < w; x++) {
			VolumeRowEncTask* rowEncTask = new VolumeRowEncTask(&yPublicKey, &ySrc, &yDst, x);
			tPool.start(rowEncTask);
		}
		tPool.waitForDone();
	} else {
		
		#ifdef GPU_MONTGOMERY_REDUCTION
			MontgomeryReducer<PaillierInt> mmr{yPublicKey.getModulusSquared()}; // One for all threads would be enough.
		#endif
	
		size_t n = ySrc.length();
		for (size_t i=0; i<n; i++) {
			PaillierInt pVoxel = PaillierInt::fromInt64(ySrc.get(i));
			//PaillierInt eVoxel = yPublicKey.encryptWithoutObfuscation(pVoxel);
			PaillierInt eVoxel = yPublicKey.encrypt(pVoxel);
			#ifdef GPU_MONTGOMERY_REDUCTION
				eVoxel = mmr.convertIn(eVoxel);
			#endif
			yDst.set(i, eVoxel);
		}
	}
}


void CryptoUtil::decrypt(const SecureKey& ySecureKey, const PaillierInt& yScale, const Image<PaillierInt>& ySrc, Image<uint16_t>& yDst) {
	//PaillierInt test1{1};
	yDst.resize(ySrc.width(), ySrc.height());
	
	if(true) {
		// multithreaded
		const uint w = ySrc.width();
		
		QThreadPool tPool;
		for(uint x = 0; x < w; x++) {
			ImageRowDecTask* rowDecTask = new ImageRowDecTask(&ySecureKey, &ySrc, &yDst, x, &yScale);
			tPool.start(rowDecTask);
		}
		tPool.waitForDone();
	} else {
		// single threaded
		#ifdef GPU_MONTGOMERY_REDUCTION
			MontgomeryReducer<PaillierInt> mmr{ySecureKey.publicKey.getModulusSquared()};
		#endif
		
		size_t n = ySrc.length();
		for (size_t i=0; i<n; i++) {
			PaillierInt ePixel = ySrc.get(i);
			#ifdef GPU_MONTGOMERY_REDUCTION
				ePixel = mmr.convertOut(ePixel);
			#endif
			PaillierInt bigVal = ySecureKey.decrypt(ePixel) ;
			bigVal = bigVal / yScale; //PaillierInt::fromInt64(50);
			yDst.set(i, (uint16_t)bigVal.toInt64());
			
			//if(src > test1) {
			//	std::cout << "Fount Rendering Result at index " << i << ", value: " << src.toStringHex() << ", decrypted: " << bigVal.toStringHex() <<std::endl;
			//}
		}
	}
}
