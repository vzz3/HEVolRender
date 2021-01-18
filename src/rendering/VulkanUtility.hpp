#pragma once

#include "VulkanDevice.hpp"
#include <vulkan/vulkan.h>
#include <QString>
#include <string>
#include <sstream>
#include <iostream>

#define VK_CHECK_RESULT(f, msg) {																		\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS) {																			\
		std::stringstream msgStream;																	\
		msgStream << msg << ": VkResult is \"" << ppvr::rendering::VulkanUtility::errorString(res) << "\" in " << __FILE__ << " at line " << __LINE__ << "\n"; \
		throw std::runtime_error(msgStream.str());														\
	}																									\
}

namespace ppvr {
	namespace rendering {
		class VulkanUtility {

		// ----- member variables -----
		public:
			static inline VkDeviceSize aligned(VkDeviceSize v, VkDeviceSize byteAlign) {
				return (v + byteAlign - 1) & ~(byteAlign - 1);
			}
			static std::string errorString(VkResult yErrorCode);
			
			static VkShaderModule createShaderModule(VulkanDevice& yDev, const QString& yPath);
			
			static uint32_t findMemoryType(VulkanDevice& yDev, uint32_t yTypeFilter, VkMemoryPropertyFlags yProperties);
			
			static void createBuffer(VulkanDevice& yDev, VkDeviceSize ySize, VkBufferUsageFlags yUsage, VkMemoryPropertyFlags yProperties, VkBuffer& yBuffer, VkDeviceMemory& yBufferMemory);
			
			static void createImage(
				VulkanDevice& yDev,
				VkImageType yImageType,
				uint32_t width, uint32_t height, uint32_t depth,
				VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
				VkImage& image, VkDeviceMemory& imageMemory);
			
			
			static VkCommandBuffer 	beginSingleTimeCommands(VulkanDevice& yDev);
			static void 			endSingleTimeCommands(  VulkanDevice& yDev, VkCommandBuffer yCommandBuffer);
			
			/*
			 *
			 * It should be noted that in a real world application, you're not supposed to actually call vkAllocateMemory for every individual buffer. The maximum number of simultaneous memory allocations is limited by the maxMemoryAllocationCount physical device limit, which may be as low as 4096 even on high end hardware like an NVIDIA GTX 1080. The right way to allocate memory for a large number of objects at the same time is to create a custom allocator that splits up a single allocation among many different objects by using the offset parameters that we've seen in many functions.
			 *
			 * You can either implement such an allocator yourself, or use the VulkanMemoryAllocator library provided by the GPUOpen initiative (https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator). However, for this tutorial it's okay to use a separate allocation for every resource, because we won't come close to hitting any of these limits for now.
			 *
			 */
			static void copyBuffer(
				VulkanDevice& yDev,
				VkBuffer ySrcBuffer, VkBuffer yDstBuffer, VkDeviceSize ySize);
		
			static void copyBuffer(
				VulkanDevice& yDev,
				VkCommandBuffer yCommandBuffer,
				VkBuffer ySrcBuffer, VkBuffer yDstBuffer, VkDeviceSize ySize);
		
			
			
			/*
			static void insertImageMemoryBarrier(
				VulkanDevice& yDev,
				VkCommandBuffer yCmdbuffer,
				VkImage yImage,
				VkAccessFlags ySrcAccessMask,
				VkAccessFlags yDstAccessMask,
				VkImageLayout yOldImageLayout,
				VkImageLayout yNewImageLayout,
				VkPipelineStageFlags ySrcStageMask,
				VkPipelineStageFlags yDstStageMask,
				VkImageSubresourceRange ySubresourceRange);
			*/
			
			static void transitionImageLayout(
				VulkanDevice& yDev,
				VkImage yImage,
				VkImageLayout yOldLayout, VkImageLayout yNewLayout);
			
			static void transitionImageLayout(
				VulkanDevice& yDev,
				VkCommandBuffer yCommandBuffer,
				VkImage yImage,
				VkImageLayout yOldLayout, VkImageLayout yNewLayout);
		
			
		
			static void copyBufferToImage(
				VulkanDevice& yDev,
				VkBuffer yBuffer, VkImage yImage, uint32_t yWidth, uint32_t yHeight, uint32_t yDepth = 1);
			
			static void copyBufferToImage(
				VulkanDevice& yDev,
				VkCommandBuffer yCommandBuffer,
				VkBuffer yBuffer, VkImage yImage, uint32_t yWidth, uint32_t yHeight, uint32_t yDepth = 1);
			
			static void copyImage(
				VulkanDevice& yDev,
				VkImage ySrcImage, VkImage yDstImage, uint32_t yWidth, uint32_t yHeight, uint32_t yDepth = 1);
			
			static void copyImage(
				VulkanDevice& yDev,
				VkCommandBuffer yCommandBuffer,
				VkImage ySrcImage, VkImage yDstImage, uint32_t yWidth, uint32_t yHeight, uint32_t yDepth = 1);
			
			
			static VkFormat getSupportedDepthFormat(VulkanInstance& yVkInstance, VkPhysicalDevice yVkPhysicalDevice);
		};
	}
}
