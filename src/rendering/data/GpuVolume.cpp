
#include "GpuVolume.hpp"

#include "../VulkanUtility.hpp"
#include "../VulkanInitializers.hpp"


using namespace ppvr::rendering::data;
using ppvr::rendering::VulkanDevice;

GpuVolume::GpuVolume(VulkanDevice& yDev): dev(yDev) {
	//this->createStagingBuffer();
}

GpuVolume::~GpuVolume() {
	this->cleanup();
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
void GpuVolume::cleanup() {
	//this->releaseSwapChainResources();
	//this->releaseGpuResources();
	
	//this->cleanupStagingBuffer();
	
	this->cleanupImageView();
	
	dev.funcs->vkDestroyImage(dev.vkDev, volumeImage, nullptr);
	volumeImage = VK_NULL_HANDLE;
    dev.funcs->vkFreeMemory(dev.vkDev, volumeImageMemory, nullptr);
    volumeImageMemory = VK_NULL_HANDLE;
}
/*
void GpuVolume::cleanupStagingBuffer() {
	
	dev.funcs->vkUnmapMemory(dev.vkDev, stagingBufferMemory);
	
	dev.funcs->vkDestroyBuffer(dev.vkDev, stagingBuffer, nullptr);
	stagingBuffer = VK_NULL_HANDLE;
	
	dev.funcs->vkFreeMemory(dev.vkDev, stagingBufferMemory, nullptr);
	stagingBufferMemory = VK_NULL_HANDLE;
}

void GpuVolume::createStagingBuffer() {
	VkDeviceSize imageSize = width * height * depth * sizeof(uint16_t);

	VkBuffer stagingBuffer = nullptr;
	VkDeviceMemory stagingBufferMemory = nullptr;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	constexpr VkBufferUsageFlags stagingBufferUsage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	constexpr VkMemoryPropertyFlags stagingBufferProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
	VulkanUtility::createBuffer(dev, imageSize, stagingBufferUsage, stagingBufferProperties, stagingBuffer, stagingBufferMemory);
	
	void* data;
	dev.funcs->vkMapMemory(dev.vkDev, stagingBufferMemory, 0, imageSize, 0, &data);
	//memcpy(data, pixels, static_cast<size_t>(imageSize));
	//dev.funcs->vkUnmapMemory(dev.vkDev, stagingBufferMemory);
}
*/
void GpuVolume::uploadVolume(const Volume<uint16_t>& yVolume) {
	this->cleanup();

	mWidth = yVolume.width();
	mHeight =  yVolume.height();
	mDepth = yVolume.depth();
	VkDeviceSize imageSize = mWidth * mHeight * mDepth * sizeof(uint16_t);

	// create statign buffer
	VkBuffer stagingBuffer = nullptr;
	VkDeviceMemory stagingBufferMemory = nullptr;

	constexpr VkBufferUsageFlags stagingBufferUsage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	constexpr VkMemoryPropertyFlags stagingBufferProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
	VulkanUtility::createBuffer(dev, imageSize, stagingBufferUsage, stagingBufferProperties, stagingBuffer, stagingBufferMemory);
	
	// copy the volume to the staging buffer
	void* data;
	dev.funcs->vkMapMemory(dev.vkDev, stagingBufferMemory, 0, imageSize, 0, &data);
		memcpy(data, yVolume.data(), static_cast<size_t>(imageSize));
	dev.funcs->vkUnmapMemory(dev.vkDev, stagingBufferMemory);
	
	
	// create the image in GPU memory
	constexpr VkImageType imageType = VK_IMAGE_TYPE_3D;
	constexpr VkFormat format = volumeFormat; //VK_FORMAT_R16_UNORM; // VK_FORMAT_R8G8B8A8_SRGB
	constexpr VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
	constexpr VkImageUsageFlags usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	constexpr VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	VulkanUtility::createImage(dev, imageType, mWidth, mHeight, mDepth, format, tiling, usage, properties, volumeImage, volumeImageMemory);

	// copy the image from the staging buffer to the image memory on the GPU
	VulkanUtility::transitionImageLayout(dev, volumeImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		VulkanUtility::copyBufferToImage(dev, stagingBuffer, volumeImage, static_cast<uint32_t>(mWidth), static_cast<uint32_t>(mHeight), static_cast<uint32_t>(mDepth));
	VulkanUtility::transitionImageLayout(dev, volumeImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	// cleanup the staging buffer
	dev.funcs->vkDestroyBuffer(dev.vkDev, stagingBuffer, nullptr);
	stagingBuffer = VK_NULL_HANDLE;
	
	dev.funcs->vkFreeMemory(dev.vkDev, stagingBufferMemory, nullptr);
	stagingBufferMemory = VK_NULL_HANDLE;
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

VkImageView GpuVolume::getColumeImageView() {
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
	colorImageView.format = volumeFormat;
	colorImageView.subresourceRange = {};
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = volumeImage;
	VK_CHECK_RESULT(dev.funcs->vkCreateImageView(dev.vkDev, &colorImageView, nullptr, &volumeImageView), "failed to bind volume image view!");
}
