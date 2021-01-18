#pragma once

#include <vulkan/vulkan.h>
#include "../VulkanDevice.hpp"
#include "../VulkanSwapChain.hpp"
#include "./Volume.hpp"
#include "../../paillier/Paillier_typeDev.h"

using ppvr::rendering::VulkanDevice;

namespace ppvr {
	namespace rendering {
		namespace data {
			class GpuVolume {
			public:
				GpuVolume(VulkanDevice& yDev);
				~GpuVolume();
				
			private:
				void cleanup();
				
			public:
				//void initGpuResources();
				//void releaseGpuResources();
				
				//void initSwapChainResources(const VulkanSwapChain& ySwapChain);
				//void releaseSwapChainResources();
				
			private:
				inline VkDeviceSize imageSize() {
					return mWidth * mHeight * mDepth * sizeof(uint16_t);
				}
				
				void* createStagingBuffer(const VkFormat yVolumeFormat, const size_t yWidth, const size_t yHeight, const size_t yDepth);
				void cleanupStagingBuffer();
				
				void createGpuImageFromStagingBuffer();
				
			public:
				void uploadVolume(const Volume<uint16_t>& yVolume);
				void uploadBigIntVolumePart(const Volume<PaillierInt>& yVolume, const size_t yWordOffset);
				//void createImage();
			
				//void createVertexBuffer();
				//void cleanupVertexBuffer();
				
				size_t width() const;
				size_t height() const;
				size_t depth() const;
				
				VkImageView getImageView();
			private:
				void createImageView();
				void cleanupImageView();
				
			public:
				static constexpr VkFormat plainVolumeFormat = VK_FORMAT_R16_UNORM;
				
				static constexpr VkFormat bigIntWordVolumeFormat = GPU_INT_TEXTURE_FORMAT;
				
				/*
				 * the count of big int words stored in this volume
				 * /
				static constexpr size_t bigIntWordCount = 4;
				
				static constexpr VkFormat bigIntExponentVolumeFormat = VK_FORMAT_R32_SINT;
				*/
				
			private:
				// from constructor
				VulkanDevice& dev;
				
				size_t mWidth, mHeight, mDepth;
				VkFormat mVolumeFormat = VK_FORMAT_R16_UNORM; //VK_FORMAT_R16_UNORM; // VK_FORMAT_R8G8B8A8_SRGB
				
				VkBuffer stagingBuffer = VK_NULL_HANDLE;
				VkDeviceMemory stagingBufferMemory = VK_NULL_HANDLE;
				
				
				VkImage volumeImage = VK_NULL_HANDLE;
				VkDeviceMemory volumeImageMemory  = VK_NULL_HANDLE;
				
				VkImageView volumeImageView = VK_NULL_HANDLE;
			};
		}
	}
}
