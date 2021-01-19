
#include "GpuVolume.hpp"

#include "../VulkanUtility.hpp"
#include "../VulkanInitializers.hpp"


using namespace ppvr::rendering::data;
using ppvr::rendering::VulkanDevice;

GpuVolume::GpuVolume(VulkanDevice& yDev): dev(yDev) {
	//this->createStagingBuffer();
}

GpuVolume::~GpuVolume() {
	this->releaseGpuResources();
};

/*
void GpuVolume::initGpuResources() {
	this->createVertexBuffer();
}
void GpuVolume::releaseGpuResources() {
	this->cleanupVertexBuffer();
}

void GpuVolume::initSwapChainResources(const VulkanSwapChain& ySwapChain) {
 
}

void GpuVolume::releaseSwapChainResources() {
	
}
*/
void GpuVolume::releaseGpuResources() {
	//this->releaseSwapChainResources();
	//this->releaseGpuResources();
	
	//this->cleanupStagingBuffer();
	
	this->cleanupImageView();
	
	dev.funcs->vkDestroyImage(dev.vkDev, volumeImage, nullptr);
	volumeImage = VK_NULL_HANDLE;
    dev.funcs->vkFreeMemory(dev.vkDev, volumeImageMemory, nullptr);
    volumeImageMemory = VK_NULL_HANDLE;
}

void GpuVolume::cleanupStagingBuffer() {
	dev.funcs->vkUnmapMemory(dev.vkDev, stagingBufferMemory);
	
	// cleanup the staging buffer
	dev.funcs->vkDestroyBuffer(dev.vkDev, stagingBuffer, nullptr);
	stagingBuffer = VK_NULL_HANDLE;
	
	dev.funcs->vkFreeMemory(dev.vkDev, stagingBufferMemory, nullptr);
	stagingBufferMemory = VK_NULL_HANDLE;
}

void* GpuVolume::createStagingBuffer(const VkFormat yVolumeFormat, const size_t yVolumeFormatSize, const size_t yWidth, const size_t yHeight, const size_t yDepth) {
	mVolumeFormat = yVolumeFormat;
	mVolumeFormatSize = yVolumeFormatSize;
	mWidth = yWidth;
	mHeight = yHeight;
	mDepth = yDepth;
	VkDeviceSize imageSize = this->imageSize();

	// create statign buffer
	//VkBuffer stagingBuffer = nullptr;
	//VkDeviceMemory stagingBufferMemory = nullptr;

	constexpr VkBufferUsageFlags stagingBufferUsage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	constexpr VkMemoryPropertyFlags stagingBufferProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
	VulkanUtility::createBuffer(dev, imageSize, stagingBufferUsage, stagingBufferProperties, stagingBuffer, stagingBufferMemory);
	
	// copy the volume to the staging buffer
	void* data;
	dev.funcs->vkMapMemory(dev.vkDev, stagingBufferMemory, 0, imageSize, 0, &data);
	return data;
	// dev.funcs->vkUnmapMemory(dev.vkDev, stagingBufferMemory);
}

void GpuVolume::createGpuImageFromStagingBuffer() {
	// create the image in GPU memory
	constexpr VkImageType imageType = VK_IMAGE_TYPE_3D;
	constexpr VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
	constexpr VkImageUsageFlags usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	constexpr VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	VulkanUtility::createImage(dev, imageType, mWidth, mHeight, mDepth, mVolumeFormat, tiling, usage, properties, volumeImage, volumeImageMemory);

	// copy the image from the staging buffer to the image memory on the GPU
	VulkanUtility::transitionImageLayout(dev, volumeImage, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		VulkanUtility::copyBufferToImage(dev, stagingBuffer, volumeImage, static_cast<uint32_t>(mWidth), static_cast<uint32_t>(mHeight), static_cast<uint32_t>(mDepth));
	VulkanUtility::transitionImageLayout(dev, volumeImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void GpuVolume::uploadVolume(const Volume<uint16_t>& yVolume) {
	this->releaseGpuResources();
	constexpr VkFormat format = plainVolumeFormat;

	void* data = this->createStagingBuffer(format, sizeof(uint16_t), yVolume.width(), yVolume.height(), yVolume.depth());
		memcpy(data, yVolume.data(), static_cast<size_t>(this->imageSize()));
	//dev.funcs->vkUnmapMemory(dev.vkDev, stagingBufferMemory);
	
	// create the image in GPU memory
	this->createGpuImageFromStagingBuffer();

	// cleanup the staging buffer
	this->cleanupStagingBuffer();
}

void GpuVolume::uploadBigIntVolumePart(const Volume<PaillierInt>& yVolume, const size_t yWordOffset) {
	this->releaseGpuResources();
	
	//assert( typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t) ); // , "encrypted GPU Volume upload currently only support unsigned 32 bit integers"
	
	constexpr VkFormat format = bigIntWordVolumeFormat;


	BIG_INT_WORD_TYPE* data = (BIG_INT_WORD_TYPE*)this->createStagingBuffer(format, (sizeof(BIG_INT_WORD_TYPE)*GPU_INT_TEXTURE_WORD_COUNT), yVolume.width(), yVolume.height(), yVolume.depth());
	
		//memcpy(data, yVolume.data(), static_cast<size_t>(this->imageSize()));
	for (size_t i = 0; i < yVolume.length(); i++) {
		const PaillierInt& bigIntVal = yVolume.get(i);
		size_t dataOffset = i * GPU_INT_TEXTURE_WORD_COUNT;
		
		for (size_t w = 0; w < GPU_INT_TEXTURE_WORD_COUNT; w++) {
			BIG_INT_WORD_TYPE word = bigIntVal.getData()[yWordOffset + w];
    		data[dataOffset + w] = word;
    	}
	}
	//dev.funcs->vkUnmapMemory(dev.vkDev, stagingBufferMemory);
	
	// create the image in GPU memory
	this->createGpuImageFromStagingBuffer();

	// cleanup the staging buffer
	this->cleanupStagingBuffer();
}

size_t GpuVolume::width() const {
	return mWidth;
}
size_t GpuVolume::height() const {
	return mHeight;
}
size_t GpuVolume::depth() const {
	return mDepth;
}

VkImageView GpuVolume::getImageView() {
	if(volumeImageView == nullptr) {
		createImageView();
	}
	return volumeImageView;
}

void GpuVolume::cleanupImageView() {
	dev.funcs->vkDestroyImageView(dev.vkDev, volumeImageView, nullptr);
	volumeImageView = VK_NULL_HANDLE;
	
}

void GpuVolume::createImageView() {
	VkImageViewCreateInfo colorImageView = VulkanInitializers::imageViewCreateInfo();
	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_3D;
	colorImageView.format = mVolumeFormat;
	colorImageView.subresourceRange = {};
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = volumeImage;
	VK_CHECK_RESULT(dev.funcs->vkCreateImageView(dev.vkDev, &colorImageView, nullptr, &volumeImageView), "failed to bind volume image view!");
}
