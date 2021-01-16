
#include "VulkanUtility.hpp"

#include <QFile>
#include "./VulkanInitializers.hpp"


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
	// https://vulkan-tutorial.com/Vertex_buffers/Vertex_buffer_creation
	
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
	// https://vulkan-tutorial.com/Vertex_buffers/Vertex_buffer_creation

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

void VulkanUtility::createImage(VulkanDevice& yDev,
	VkImageType yImageType,
	uint32_t yWidth, uint32_t yHeight, uint32_t yDepth,
	VkFormat yFormat, VkImageTiling yTiling, VkImageUsageFlags yUsage, VkMemoryPropertyFlags yProperties,
	VkImage& yImage, VkDeviceMemory& yImageMemory) {
	//constexpr VkImageType imageType = VK_IMAGE_TYPE_3D;
	//constexpr VkFormat format = VK_FORMAT_R16_UNORM;
	//constexpr VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
	//constexpr VkImageUsageFlags usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	//constexpr VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

	VkImageCreateInfo imageInfo = VulkanInitializers::imageCreateInfo();
	imageInfo.imageType = yImageType;
	imageInfo.extent.width = yWidth;
	imageInfo.extent.height = yHeight;
	imageInfo.extent.depth = yDepth;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = yFormat;
	imageInfo.tiling = yTiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = yUsage;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	VK_CHECK_RESULT (yDev.funcs->vkCreateImage(yDev.vkDev, &imageInfo, nullptr, &yImage), "failed to create image!");

	VkMemoryRequirements memRequirements;
	yDev.funcs->vkGetImageMemoryRequirements(yDev.vkDev, yImage, &memRequirements);

	VkMemoryAllocateInfo allocInfo = VulkanInitializers::memoryAllocateInfo();
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = VulkanUtility::findMemoryType(yDev, memRequirements.memoryTypeBits, yProperties);

	VK_CHECK_RESULT (yDev.funcs->vkAllocateMemory(yDev.vkDev, &allocInfo, nullptr, &yImageMemory), "failed to allocate image memory!");

	VK_CHECK_RESULT (yDev.funcs->vkBindImageMemory(yDev.vkDev, yImage, yImageMemory, 0), "failed to bind image memory!");
}




VkCommandBuffer VulkanUtility::beginSingleTimeCommands(VulkanDevice& yDev) {
	// https://vulkan-tutorial.com/Texture_mapping/Images

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

	yDev.funcs->vkBeginCommandBuffer(commandBuffer, &beginInfo);
	
	return commandBuffer;
}

void VulkanUtility::endSingleTimeCommands(  VulkanDevice& yDev, VkCommandBuffer yCommandBuffer) {
	// https://vulkan-tutorial.com/Texture_mapping/Images
	
	vkEndCommandBuffer(yCommandBuffer);

	// --- execute the command buffer to complete the transfer ---
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &yCommandBuffer;

	yDev.funcs->vkQueueSubmit(yDev.graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	yDev.funcs->vkQueueWaitIdle(yDev.graphicsQueue); // We could use a fence and wait with vkWaitForFences, or simply wait for the transfer queue to become idle with vkQueueWaitIdle. A fence would allow you to schedule multiple transfers simultaneously and wait for all of them complete, instead of executing one at a time. That may give the driver more opportunities to optimize.
	
		// e.g.:
		//VkFence fence;
		//VK_CHECK_RESULT(vkCreateFence(device, &fenceInfo, nullptr, &fence));
		//VK_CHECK_RESULT(vkQueueSubmit(queue, 1, &submitInfo, fence));
		//VK_CHECK_RESULT(vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX));
		//vkDestroyFence(device, fence, nullptr);

	yDev.funcs->vkFreeCommandBuffers(yDev.vkDev, yDev.graphicsCommandPool, 1, &yCommandBuffer);
}


void VulkanUtility::copyBuffer(VulkanDevice& yDev,
	VkBuffer ySrcBuffer, VkBuffer yDstBuffer, VkDeviceSize ySize) {
	
	// https://vulkan-tutorial.com/Vertex_buffers/Staging_buffer

	VkCommandBuffer commandBuffer = beginSingleTimeCommands(yDev);
	copyBuffer(yDev, commandBuffer, ySrcBuffer, yDstBuffer, ySize);
	endSingleTimeCommands(yDev, commandBuffer);
}

void VulkanUtility::copyBuffer(VulkanDevice& yDev,
	VkCommandBuffer yCommandBuffer,
	VkBuffer ySrcBuffer, VkBuffer yDstBuffer, VkDeviceSize ySize)
{
	// https://vulkan-tutorial.com/Vertex_buffers/Staging_buffer

	VkBufferCopy copyRegion{};
	copyRegion.srcOffset = 0; // Optional
	copyRegion.dstOffset = 0; // Optional
	copyRegion.size = ySize;
	yDev.funcs->vkCmdCopyBuffer(yCommandBuffer, ySrcBuffer, yDstBuffer, 1, &copyRegion);

}


/*
void VulkanUtility::insertImageMemoryBarrier(
			VulkanDevice& yDev,
			VkCommandBuffer yCmdbuffer,
			VkImage yImage,
			VkAccessFlags ySrcAccessMask,
			VkAccessFlags yDstAccessMask,
			VkImageLayout yOldImageLayout,
			VkImageLayout yNewImageLayout,
			VkPipelineStageFlags ySrcStageMask,
			VkPipelineStageFlags yDstStageMask,
			VkImageSubresourceRange ySubresourceRange)
		{
			VkImageMemoryBarrier imageMemoryBarrier = VulkanInitializers::imageMemoryBarrier();
			imageMemoryBarrier.srcAccessMask = ySrcAccessMask;
			imageMemoryBarrier.dstAccessMask = yDstAccessMask;
			imageMemoryBarrier.oldLayout = yOldImageLayout;
			imageMemoryBarrier.newLayout = yNewImageLayout;
			imageMemoryBarrier.image = image;
			imageMemoryBarrier.subresourceRange = subresourceRange;

			vkCmdPipelineBarrier(
				cmdbuffer,
				srcStageMask,
				dstStageMask,
				0,
				0, nullptr,
				0, nullptr,
				1, &imageMemoryBarrier);
		}
*/

void VulkanUtility::transitionImageLayout(
	VulkanDevice& yDev,
	VkImage yImage, VkFormat yFormat,
	VkImageLayout yOldLayout, VkImageLayout yNewLayout)
{
	// https://vulkan-tutorial.com/Texture_mapping/Images

	VkCommandBuffer commandBuffer = beginSingleTimeCommands(yDev);
	transitionImageLayout(yDev, commandBuffer, yImage, yFormat, yOldLayout, yNewLayout);
	endSingleTimeCommands(yDev, commandBuffer);
}

void VulkanUtility::transitionImageLayout(
	VulkanDevice& yDev,
	VkCommandBuffer yCommandBuffer,
	VkImage yImage, VkFormat yFormat,
	VkImageLayout yOldLayout, VkImageLayout yNewLayout)
{
	// https://vulkan-tutorial.com/Texture_mapping/Images
	
	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = yOldLayout;
	barrier.newLayout = yNewLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = yImage;
	
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;

	if (yOldLayout == VK_IMAGE_LAYOUT_UNDEFINED && yNewLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	} else if (yOldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && yNewLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	} else if (yOldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && yNewLayout == VK_IMAGE_LAYOUT_GENERAL) {
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;

		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	} else {
		throw std::invalid_argument("unsupported layout transition!");
	}

	vkCmdPipelineBarrier(
		yCommandBuffer,
		sourceStage, destinationStage,
		0,
		0, nullptr,
		0, nullptr,
		1, &barrier
	);

}

void VulkanUtility::copyBufferToImage(
	VulkanDevice& yDev,
	VkBuffer yBuffer, VkImage yImage, uint32_t yWidth, uint32_t yHeight, uint32_t yDepth)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands(yDev);
	copyBufferToImage(yDev, commandBuffer, yBuffer, yImage, yWidth, yHeight, yDepth);
	endSingleTimeCommands(yDev, commandBuffer);
}

void VulkanUtility::copyBufferToImage(
	VulkanDevice& yDev,
	VkCommandBuffer yCommandBuffer,
	VkBuffer yBuffer, VkImage yImage, uint32_t yWidth, uint32_t yHeight, uint32_t yDepth)
{
	VkBufferImageCopy region{};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;
	region.imageOffset = {0, 0, 0};
	region.imageExtent = {
		yWidth,
		yHeight,
		yDepth
	};

	yDev.funcs->vkCmdCopyBufferToImage(yCommandBuffer, yBuffer, yImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
}

void VulkanUtility::copyImage(
	VulkanDevice& yDev,
	VkImage ySrcImage, VkImage yDstImage, uint32_t yWidth, uint32_t yHeight, uint32_t yDepth)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands(yDev);
	copyImage(yDev, commandBuffer, ySrcImage, yDstImage, yWidth, yHeight, yDepth);
	endSingleTimeCommands(yDev, commandBuffer);
}

void VulkanUtility::copyImage(
	VulkanDevice& yDev,
	VkCommandBuffer yCommandBuffer,
	VkImage ySrcImage, VkImage yDstImage, uint32_t yWidth, uint32_t yHeight, uint32_t yDepth)
{
	VkImageCopy imageCopyRegion{};
	imageCopyRegion.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	imageCopyRegion.srcSubresource.layerCount = 1;
	imageCopyRegion.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	imageCopyRegion.dstSubresource.layerCount = 1;
	imageCopyRegion.extent.width = yWidth;
	imageCopyRegion.extent.height = yHeight;
	imageCopyRegion.extent.depth = yDepth;

	yDev.funcs->vkCmdCopyImage(
		yCommandBuffer,
		ySrcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
		yDstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		1,
		&imageCopyRegion);
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
