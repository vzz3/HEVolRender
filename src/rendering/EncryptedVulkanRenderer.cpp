

#include "EncryptedVulkanRenderer.hpp"
#include <QVulkanFunctions>
#include <QFile>

#include "./VulkanUtility.hpp"
#include "./data/VolumeFactory.hpp"
#include "./VulkanInitializers.hpp"

#include <fstream>

using namespace ppvr::rendering;


EncryptedVulkanRenderer::EncryptedVulkanRenderer(QVulkanInstance* yQVulkanInstance, VkPhysicalDevice yVkPhysicalDevice, const Camera& yCamera)
	:
		camera(yCamera),
		fboFormates{
			{VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL}
		}
	{
	initVulkan(yQVulkanInstance, yVkPhysicalDevice);
	initGpuResources();
}

EncryptedVulkanRenderer::~EncryptedVulkanRenderer() {
	this->cleanup();
}

void EncryptedVulkanRenderer::cleanup() {
	
	releaseSwapChainResources();
	
	releaseGpuResources();
	cleanupVulakn();
}

void EncryptedVulkanRenderer::cleanupVulakn() {
	device.funcs->vkDestroyCommandPool(device.vkDev, device.graphicsCommandPool, nullptr);
	device.funcs->vkDestroyDevice(device.vkDev, nullptr);
	
	// vkDestroyInstance(instance, nullptr);
}

void EncryptedVulkanRenderer::initVulkan(QVulkanInstance* yQVulkanInstance, VkPhysicalDevice yVkPhysicalDevice) {
	vulkanInstance.funcs = yQVulkanInstance->functions();

	device.vkInstance = &vulkanInstance;
	device.vkPhysicalDev = yVkPhysicalDevice;
	//device.vkDev;
	//device.funcs;
	//device.graphicsCommandPool;
	//device.graphicsQueue;
	

	// Request a single graphics queue
	const float defaultQueuePriority(0.0f);
	VkDeviceQueueCreateInfo queueCreateInfo = {};
	uint32_t queueFamilyCount;
	vulkanInstance.funcs->vkGetPhysicalDeviceQueueFamilyProperties(yVkPhysicalDevice, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
	vulkanInstance.funcs->vkGetPhysicalDeviceQueueFamilyProperties(yVkPhysicalDevice, &queueFamilyCount, queueFamilyProperties.data());
	for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilyProperties.size()); i++) {
		if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			queueFamilyIndex = i;
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = i;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &defaultQueuePriority;
			break;
		}
	}
	// Create logical device
	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
	VK_CHECK_RESULT( vulkanInstance.funcs->vkCreateDevice(yVkPhysicalDevice, &deviceCreateInfo, nullptr, &device.vkDev), "Can not create device.");
	
	// create device functions
	device.funcs = yQVulkanInstance->deviceFunctions(device.vkDev);

	// Get a graphics queue
	device.funcs->vkGetDeviceQueue(device.vkDev, queueFamilyIndex, 0, &device.graphicsQueue);

	// Command pool
	VkCommandPoolCreateInfo cmdPoolInfo = {};
	cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;
	cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	VK_CHECK_RESULT( device.funcs->vkCreateCommandPool(device.vkDev, &cmdPoolInfo, nullptr, &device.graphicsCommandPool), "Can not create command pool.");
}

void EncryptedVulkanRenderer::releaseGpuResources() {
	
	roXRay->releaseGpuResources();
	delete roXRay;
	roXRay = nullptr;
	
	delete m_gpuVolume;
	m_gpuVolume = nullptr;
	
	
	roCubeMap->releaseGpuResources();
	delete roCubeMap;
	roCubeMap = nullptr;
	
	fbo->releaseGpuResources();
	delete fbo;
	fbo = nullptr;
}

void EncryptedVulkanRenderer::initGpuResources() {
	fbo = new FrameBuffer(device, false, fboFormates);
	fbo->initGpuResources();

	roCubeMap = new CubeMap(device);
	roCubeMap->initGpuResources();
	
	
	
	data::VolumeFactory::createVolume(m_volume, 100);
	
	m_gpuVolume = new data::GpuVolume(device);
	m_gpuVolume->uploadVolume(m_volume);
	
	roXRay = new XRay(device);
	roXRay->initGpuResources();
}

void EncryptedVulkanRenderer::releaseSwapChainResources() {
	
	roXRay->releaseSwapChainResources();
	roCubeMap->releaseSwapChainResources();
	
	
	cleanupCommandBuffer();
	fbo->releaseSwapChainResources();
}

void EncryptedVulkanRenderer::initSwapChainResources(QSize yTargetSize, size_t ySwapChainImageCount) {
	fbo->initSwapChainResources(yTargetSize);
	createCommandBuffer();
	
	swapChain.swapChainImageCount = ySwapChainImageCount;
	swapChain.renderPass = fbo->getRenderPass();
	swapChain.targetSize = yTargetSize;
	
	
	roCubeMap->initSwapChainResources(swapChain);
	roXRay->initSwapChainResources(swapChain, m_gpuVolume, roCubeMap->getFrontImageView(), roCubeMap->getBackImageView());
}

void EncryptedVulkanRenderer::cleanupCommandBuffer() {

}

void EncryptedVulkanRenderer::createCommandBuffer(size_t ySwapChainImageCount) {}

void EncryptedVulkanRenderer::startNextFrame() {
	VkCommandBuffer commandBuffer;
	VkCommandBufferAllocateInfo allocInfo = VulkanInitializers::commandBufferAllocateInfo(
		device.graphicsCommandPool,			// commandPool
		VK_COMMAND_BUFFER_LEVEL_PRIMARY,	// level
		(uint32_t)1							// commandBufferCount
	);
	VK_CHECK_RESULT (device.funcs->vkAllocateCommandBuffers(device.vkDev, &allocInfo, &commandBuffer), "failed to allocate command buffers!");

	VkCommandBufferBeginInfo beginInfo = VulkanInitializers::commandBufferBeginInfo();
	VK_CHECK_RESULT (device.funcs->vkBeginCommandBuffer(commandBuffer, &beginInfo), "failed to begin recording command buffer!");
	
		this->draw(camera, commandBuffer, 0);
	
	VK_CHECK_RESULT (device.funcs->vkEndCommandBuffer(commandBuffer), "failed to record command buffer!");
	
	/*
		Submit command buffer to a queue and wait for fence until queue operations have been finished
	*/
	//void submitWork(VkCommandBuffer cmdBuffer, VkQueue queue)
	//{
		VkSubmitInfo submitInfo = VulkanInitializers::submitInfo();
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;
		VkFenceCreateInfo fenceInfo = VulkanInitializers::fenceCreateInfo();
		VkFence fence;
		VK_CHECK_RESULT(device.funcs->vkCreateFence(device.vkDev, &fenceInfo, nullptr, &fence), "failed to create fence!");
		VK_CHECK_RESULT(device.funcs->vkQueueSubmit(device.graphicsQueue, 1, &submitInfo, fence), "failed to queue submit!");
		VK_CHECK_RESULT(device.funcs->vkWaitForFences(device.vkDev, 1, &fence, VK_TRUE, UINT64_MAX), "failed to wait for fances!");
		device.funcs->vkDestroyFence(device.vkDev, fence, nullptr);
	//}
	
	device.funcs->vkFreeCommandBuffers(device.vkDev, device.graphicsCommandPool, 1, &commandBuffer);
	commandBuffer = nullptr;
	
	
	VK_CHECK_RESULT(device.funcs->vkDeviceWaitIdle(device.vkDev), "failed to wait for the device until it is idle!"); // TODO is this realy required?
}

void EncryptedVulkanRenderer::draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex) {

	// ------ offscreen render pass ------
	roCubeMap->drawOffscreenFrame(camera, yCmdBuf, yCurrentSwapChainImageIndex);
	
	/*
		Note: Explicit synchronization is not required between the render pass, as this is done implicit via sub pass dependencies
		Is this correct?????
	*/
	
	// ------ main render pass ------
	
	VkClearValue clearValues[1];
	clearValues[0].color = { { 0.0f, 0.0f, 0.2f, 1.0f } };
	//clearValues[1].depthStencil = { 1.0f, 0 };

	VkRenderPassBeginInfo renderPassInfo = VulkanInitializers::renderPassBeginInfo();
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = fbo->getRenderPass();
	renderPassInfo.framebuffer = fbo->getFramebuffer();
	renderPassInfo.renderArea.offset = {0, 0};
	renderPassInfo.renderArea.extent.width = fbo->getWidth();
	renderPassInfo.renderArea.extent.height = fbo->getHeight();
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearValues[0];

	device.funcs->vkCmdBeginRenderPass(yCmdBuf, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	
	// TODO DRAW
	roXRay->draw(camera, yCmdBuf, yCurrentSwapChainImageIndex);
	
	device.funcs->vkCmdEndRenderPass(yCmdBuf);
}

void EncryptedVulkanRenderer::framebuffer2host() {
	const char* imageData;
	int32_t width = fbo->getWidth();
	int32_t height = fbo->getHeight();
	
	// Create the linear tiled destination image to copy to and to read the memory from
	std::vector<VkImage> dstImages{fboFormates.size()};
	std::vector<VkDeviceMemory> dstImageMemories{fboFormates.size()};
	
	// create images
	for (size_t i = 0; i < dstImages.size(); i++) {
		VulkanUtility::createImage(device,
			VK_IMAGE_TYPE_2D, 						// VkImageType yImageType
			width, height, 1, 						// yWidth, yHeight, yDepth,
			fboFormates[i].format,					// VkFormat yFormat
			VK_IMAGE_TILING_LINEAR, 				// VkImageTiling yTiling
			VK_IMAGE_USAGE_TRANSFER_DST_BIT, 		//VkImageUsageFlags yUsage
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,	// VkMemoryPropertyFlags yProperties
			dstImages[i], 							// VkImage& yImage
			dstImageMemories[i]						// VkDeviceMemory& yImageMemory
		);
	}
	
	// Do the actual blit from the offscreen image to our host visible destination image
	VkCommandBuffer copyCmd = VulkanUtility::beginSingleTimeCommands(device);
	
	for (size_t i = 0; i < dstImages.size(); i++) {
		// Transition destination image to transfer destination layout
		// TODO check srcStageMask
		VulkanUtility::transitionImageLayout(device, copyCmd, dstImages[i], fboFormates[i].format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		
		// colorAttachment.image is already in VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, and does not need to be transitioned
		// TODO realy???? is this correct?????
		
		VulkanUtility::copyImage(device, copyCmd,
			fbo->getColorAttachment(i).image, dstImages[i],	// srcImage, dstImage
			width, height, 1);
		
		
		// Transition destination image to general layout, which is the required layout for mapping the image memory later on
		VulkanUtility::transitionImageLayout(device, copyCmd, dstImages[i], fboFormates[i].format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
	}
	
	VulkanUtility::endSingleTimeCommands(device, copyCmd); // this command waits for the GPU

	// Get layout of the image (including row pitch)
	VkImageSubresource subResource{};
	subResource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	VkSubresourceLayout subResourceLayout;

	for (size_t i = 0; i < dstImages.size(); i++) {
		device.funcs->vkGetImageSubresourceLayout(device.vkDev, dstImages[i], &subResource, &subResourceLayout);

		// Map image memory so we can start copying from it
		device.funcs->vkMapMemory(device.vkDev, dstImageMemories[i], 0, VK_WHOLE_SIZE, 0, (void**)&imageData);
		imageData += subResourceLayout.offset;

		/*
			Save host visible framebuffer image to disk (ppm format)
		*/

		//const char* filename = "headless.ppm";
		std::stringstream filename;
		filename << "headless_" << i << ".ppm";
		std::ofstream file(filename.str(), std::ios::out | std::ios::binary);

		// ppm header
		file << "P6\n" << width << "\n" << height << "\n" << 255 << "\n";

		// If source is BGR (destination is always RGB) and we can't use blit (which does automatic conversion), we'll have to manually swizzle color components
		// Check if source is BGR and needs swizzle
		std::vector<VkFormat> formatsBGR = { VK_FORMAT_B8G8R8A8_SRGB, VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_B8G8R8A8_SNORM };
		const bool colorSwizzle = (std::find(formatsBGR.begin(), formatsBGR.end(), VK_FORMAT_R8G8B8A8_UNORM) != formatsBGR.end());

		// ppm binary pixel data
		for (int32_t y = 0; y < height; y++) {
			unsigned int *row = (unsigned int*)imageData;
			for (int32_t x = 0; x < width; x++) {
				if (colorSwizzle) {
					file.write((char*)row + 2, 1);
					file.write((char*)row + 1, 1);
					file.write((char*)row, 1);
				}
				else {
					file.write((char*)row, 3);
				}
				row++;
			}
			imageData += subResourceLayout.rowPitch;
		}
		file.close();

		qDebug() << "Framebuffer image saved to " << filename.str().c_str() ;
		
		// Clean up resources
		device.funcs->vkUnmapMemory(device.vkDev, dstImageMemories[i]);
		device.funcs->vkFreeMemory(device.vkDev, dstImageMemories[i], nullptr); dstImageMemories[i] = nullptr;
		device.funcs->vkDestroyImage(device.vkDev, dstImages[i], nullptr); dstImages[i] = nullptr;
	}
}
