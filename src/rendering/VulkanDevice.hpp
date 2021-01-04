#pragma once

#include <vulkan/vulkan.h>
#include <QVulkanDeviceFunctions>


namespace ppvr {
	namespace rendering {
		class VulkanDevice {
		public:
			VkPhysicalDevice vkPhysicalDev;
			VkDevice vkDev;
			QVulkanDeviceFunctions* funcs;
			
			VkCommandPool graphicsCommandPool;
			VkQueue graphicsQueue;
			
			VulkanDevice(VkPhysicalDevice vkPhysicalDevice, VkDevice yVkDevice, QVulkanDeviceFunctions* yDeviceFunctions, VkCommandPool yGraphicsCommandPool, VkQueue yGraphicsQueue);
			VulkanDevice();
			~VulkanDevice();
		};
	}
}
