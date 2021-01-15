#pragma once

#include <vulkan/vulkan.h>
#include "../VulkanDevice.hpp"
#include "../VulkanSwapChain.hpp"
#include "./Volume.hpp"

using ppvr::rendering::VulkanDevice;

namespace ppvr {
	namespace rendering {
		namespace data {
			class GpuVolume {
			public:
				GpuVolume(VulkanDevice& yDev);
				~GpuVolume();
				
				//void initGpuResources();
				//void releaseGpuResources();
				
				//void initSwapChainResources(const VulkanSwapChain& ySwapChain);
				//void releaseSwapChainResources();
				
				void uploadVolume(const Volume<uint16_t>& yVolume);
				
				size_t width() const;
				size_t height() const;
				size_t depth() const;
				
				VkImageView getColumeImageView();
			private:
				void cleanup();
				
			
				//void createStagingBuffer();
				//void cleanupStagingBuffer();
				
				//void createImage();
			
				//void createVertexBuffer();
				//void cleanupVertexBuffer();
				
				void createImageView();
				void cleanupImageView();
			private:
				static constexpr VkFormat volumeFormat = VK_FORMAT_R16_UNORM;
				
				// from constructor
				VulkanDevice& dev;
				size_t mWidth, mHeight, mDepth;
				
				
				
				VkImage volumeImage = nullptr;
				VkDeviceMemory volumeImageMemory  = nullptr;
				
				VkImageView volumeImageView = nullptr;
			};
		}
	}
}
