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
			
			/*
			 *
			 * It should be noted that in a real world application, you're not supposed to actually call vkAllocateMemory for every individual buffer. The maximum number of simultaneous memory allocations is limited by the maxMemoryAllocationCount physical device limit, which may be as low as 4096 even on high end hardware like an NVIDIA GTX 1080. The right way to allocate memory for a large number of objects at the same time is to create a custom allocator that splits up a single allocation among many different objects by using the offset parameters that we've seen in many functions.
			 *
			 * You can either implement such an allocator yourself, or use the VulkanMemoryAllocator library provided by the GPUOpen initiative (https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator). However, for this tutorial it's okay to use a separate allocation for every resource, because we won't come close to hitting any of these limits for now.
			 *
			 */
			static void copyBuffer(VulkanDevice& yDev, VkBuffer ySrcBuffer, VkBuffer yDstBuffer, VkDeviceSize ySize);
		
			static VkFormat getSupportedDepthFormat(VulkanInstance& yVkInstance, VkPhysicalDevice yVkPhysicalDevice);
		};
	}
}
