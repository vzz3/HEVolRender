#pragma once

#include <vulkan/vulkan.h>
#include <QSize>


namespace ppvr {
	namespace rendering {
		class VulkanSwapChain {
		public:
			size_t swapChainImageCount;
			VkRenderPass renderPass;
			QSize targetSize;
			
			VulkanSwapChain();
			~VulkanSwapChain();
		};
	}
}
