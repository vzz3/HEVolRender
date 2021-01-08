#pragma once

//#include <vulkan/vulkan.h>
#include <QVulkanFunctions> // The QVulkanFunctions class provides cross-platform access to the instance level core Vulkan 1.0 API.


namespace ppvr {
	namespace rendering {
		class VulkanInstance {
		public:
			QVulkanFunctions* funcs;
			
			VulkanInstance(QVulkanFunctions* yDeviceFunctions);
			VulkanInstance();
			~VulkanInstance();
		};
	}
}
