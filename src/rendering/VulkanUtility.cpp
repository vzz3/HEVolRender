
#include "VulkanUtility.hpp"

#include <QFile>


using namespace ppvr::rendering;

std::string VulkanUtility::errorString(VkResult yErrorCode) {
	switch (yErrorCode) {
		#define STR(r) case VK_ ##r: return #r
			STR(NOT_READY);
			STR(TIMEOUT);
			STR(EVENT_SET);
			STR(EVENT_RESET);
			STR(INCOMPLETE);
			STR(ERROR_OUT_OF_HOST_MEMORY);
			STR(ERROR_OUT_OF_DEVICE_MEMORY);
			STR(ERROR_INITIALIZATION_FAILED);
			STR(ERROR_DEVICE_LOST);
			STR(ERROR_MEMORY_MAP_FAILED);
			STR(ERROR_LAYER_NOT_PRESENT);
			STR(ERROR_EXTENSION_NOT_PRESENT);
			STR(ERROR_FEATURE_NOT_PRESENT);
			STR(ERROR_INCOMPATIBLE_DRIVER);
			STR(ERROR_TOO_MANY_OBJECTS);
			STR(ERROR_FORMAT_NOT_SUPPORTED);
			STR(ERROR_SURFACE_LOST_KHR);
			STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
			STR(SUBOPTIMAL_KHR);
			STR(ERROR_OUT_OF_DATE_KHR);
			STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
			STR(ERROR_VALIDATION_FAILED_EXT);
			STR(ERROR_INVALID_SHADER_NV);
		#undef STR
	default:
		return "UNKNOWN_ERROR";
	}
}

VkShaderModule VulkanUtility::createShaderModule(VulkanDevice& yDev, const QString& yPath) {
    QFile file(yPath);
    if (!file.open(QIODevice::ReadOnly)) {
        //qWarning("Failed to read shader %s", qPrintable(yPath));
        //return VK_NULL_HANDLE;
        throw std::runtime_error(std::string("Failed to read shader '") + yPath.toStdString() + std::string("'"));
    }
    QByteArray blob = file.readAll();
    file.close();

    VkShaderModuleCreateInfo shaderInfo;
    memset(&shaderInfo, 0, sizeof(shaderInfo));
    shaderInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderInfo.codeSize = blob.size();
    shaderInfo.pCode = reinterpret_cast<const uint32_t *>(blob.constData());
    VkShaderModule shaderModule;
    VkResult err = yDev.funcs->vkCreateShaderModule(yDev.vkDev, &shaderInfo, nullptr, &shaderModule);
    if (err != VK_SUCCESS) {
        qWarning("Failed to create shader module: %d", err);
        return VK_NULL_HANDLE;
    }

    return shaderModule;
}


uint32_t VulkanUtility::findMemoryType(VulkanDevice& yDev, uint32_t yTypeFilter, VkMemoryPropertyFlags yProperties) {
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(yDev.vkPhysicalDev, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((yTypeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & yProperties) == yProperties) {
			return i;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}

void VulkanUtility::createBuffer(VulkanDevice& yDev, VkDeviceSize ySize, VkBufferUsageFlags yUsage, VkMemoryPropertyFlags yProperties, VkBuffer& yBuffer, VkDeviceMemory& yBufferMemory) {
	// --- Buffer creation ---
	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = ySize;
	bufferInfo.usage = yUsage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	VK_CHECK_RESULT (yDev.funcs->vkCreateBuffer(yDev.vkDev, &bufferInfo, nullptr, &yBuffer), "failed to create buffer!");

	// --- Memory requirements ---
	VkMemoryRequirements memRequirements;
	yDev.funcs->vkGetBufferMemoryRequirements(yDev.vkDev, yBuffer, &memRequirements);

	// --- Memory allocation ---
	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(yDev, memRequirements.memoryTypeBits, yProperties);

	VK_CHECK_RESULT (yDev.funcs->vkAllocateMemory(yDev.vkDev, &allocInfo, nullptr, &yBufferMemory), "failed to allocate buffer memory!");

	yDev.funcs->vkBindBufferMemory(yDev.vkDev, yBuffer, yBufferMemory, 0);
}

void VulkanUtility::copyBuffer(VulkanDevice& yDev, VkBuffer ySrcBuffer, VkBuffer yDstBuffer, VkDeviceSize ySize) {
	// --- clreate a command buffer for buffer copy operation ---
	VkCommandBufferAllocateInfo allocInfo{}; // command buffer for
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = yDev.graphicsCommandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	yDev.funcs->vkAllocateCommandBuffers(yDev.vkDev, &allocInfo, &commandBuffer);

	// --- start recording the command buffer ---
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT; // We're only going to use the command buffer once and wait with returning from the function until the copy operation has finished executing. It's good practice to tell the driver about our intent using VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT.

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0; // Optional
		copyRegion.dstOffset = 0; // Optional
		copyRegion.size = ySize;
		vkCmdCopyBuffer(commandBuffer, ySrcBuffer, yDstBuffer, 1, &copyRegion);

	vkEndCommandBuffer(commandBuffer);

	// --- execute the command buffer to complete the transfer ---
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	yDev.funcs->vkQueueSubmit(yDev.graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	yDev.funcs->vkQueueWaitIdle(yDev.graphicsQueue); // We could use a fence and wait with vkWaitForFences, or simply wait for the transfer queue to become idle with vkQueueWaitIdle. A fence would allow you to schedule multiple transfers simultaneously and wait for all of them complete, instead of executing one at a time. That may give the driver more opportunities to optimize.

	yDev.funcs->vkFreeCommandBuffers(yDev.vkDev, yDev.graphicsCommandPool, 1, &commandBuffer);
}

VkFormat VulkanUtility::getSupportedDepthFormat(VulkanInstance& yVkInstance, VkPhysicalDevice yVkPhysicalDevice) {
	// Since all depth formats may be optional, we need to find a suitable depth format to use
	// Start with the highest precision packed format
	std::vector<VkFormat> depthFormats = {
		VK_FORMAT_D32_SFLOAT_S8_UINT,
		VK_FORMAT_D32_SFLOAT,
		VK_FORMAT_D24_UNORM_S8_UINT,
		VK_FORMAT_D16_UNORM_S8_UINT,
		VK_FORMAT_D16_UNORM
	};

	for (auto& format : depthFormats) {
		VkFormatProperties formatProps;
		yVkInstance.funcs->vkGetPhysicalDeviceFormatProperties(yVkPhysicalDevice, format, &formatProps);
		// Format must support depth stencil attachment for optimal tiling
		if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
			return format;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}
