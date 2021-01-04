
#include "VulkanUtility.hpp"

#include <QFile>


using namespace ppvr::rendering;

VkShaderModule VulkanUtility::createShader(VulkanDevice& yDev, const QString& yPath) {
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

	if (yDev.funcs->vkCreateBuffer(yDev.vkDev, &bufferInfo, nullptr, &yBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create buffer!");
	}

	// --- Memory requirements ---
	VkMemoryRequirements memRequirements;
	yDev.funcs->vkGetBufferMemoryRequirements(yDev.vkDev, yBuffer, &memRequirements);

	// --- Memory allocation ---
	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(yDev, memRequirements.memoryTypeBits, yProperties);

	if (yDev.funcs->vkAllocateMemory(yDev.vkDev, &allocInfo, nullptr, &yBufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate buffer memory!");
	}

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
