
#include "BigIntGpuVolumeSet.hpp"




using namespace ppvr::rendering::data;
using ppvr::rendering::VulkanDevice;

BigIntGpuVolumeSet::BigIntGpuVolumeSet(VulkanDevice& yDev): dev(yDev) {
	//this->createStagingBuffer();
}

BigIntGpuVolumeSet::~BigIntGpuVolumeSet() {
	this->releaseGpuResources();
};

void BigIntGpuVolumeSet::releaseGpuResources() {
	for (auto& gpuVolume : gpuVolumeParts) {
    	gpuVolume.releaseGpuResources();
	}
}

void BigIntGpuVolumeSet::uploadVolume(const Volume<PaillierInt>& yVolume) {
	constexpr size_t requiredVolumes = GPU_INT_TEXTURE_SIZE; // = ciel(PAILLIER_INT_WORD_SIZE / GpuVolume::bigIntWordCount)
	gpuVolumeParts.resize(requiredVolumes, GpuVolume{&dev});
	
	for (size_t i=0; i < requiredVolumes; i++) {
    	gpuVolumeParts[i].uploadBigIntVolumePart(yVolume, i * GPU_INT_TEXTURE_WORD_COUNT);
	}
}
