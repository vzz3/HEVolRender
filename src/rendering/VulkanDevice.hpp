#pragma once

#include <vulkan/vulkan.h>
#include <QVulkanDeviceFunctions>
#include "./VulkanInstance.hpp"

namespace ppvr {
	namespace rendering {
		class VulkanDevice {
		public:
			VulkanInstance* vkInstance;
			
			VkPhysicalDevice vkPhysicalDev;
			VkDevice vkDev;
			QVulkanDeviceFunctions* funcs;
			
			
			
			VkCommandPool graphicsCommandPool;
			VkQueue graphicsQueue;
			
			VulkanDevice(VulkanInstance* yVkInstance, VkPhysicalDevice yVkPhysicalDevice, VkDevice yVkDevice, QVulkanDeviceFunctions* yDeviceFunctions, VkCommandPool yGraphicsCommandPool, VkQueue yGraphicsQueue);
			VulkanDevice();
			~VulkanDevice();
		};
	}
}
