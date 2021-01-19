

#include "EncryptedVulkanRenderer.hpp"
#include <QVulkanFunctions>
#include <QFile>

#include "./VulkanUtility.hpp"
#include "./data/VolumeFactory.hpp"
#include "./VulkanInitializers.hpp"
#include "./data/ImageUtil.hpp"

#include <fstream>

using namespace ppvr::rendering;


EncryptedVulkanRenderer::EncryptedVulkanRenderer(QVulkanInstance* yQVulkanInstance, VkPhysicalDevice yVkPhysicalDevice, const Camera& yCamera, const bool yBigIntTest)
	:
		camera(yCamera),
		initBigIntTest(yBigIntTest),
		//fboFormates{{VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL}}
		fboFormates{
			GPU_INT_TEXTURE_SIZE,
			{GPU_INT_TEXTURE_FORMAT, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL}
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
	if(initBigIntTest) {
		roBigIntTester->releaseGpuResources();
		delete roBigIntTester;
		roBigIntTester = nullptr;
	} else {
		roEncXRay->releaseGpuResources();
		delete roEncXRay;
		roEncXRay = nullptr;
		
		delete m_gpuVolume;
		m_gpuVolume = nullptr;
		
		
		roCubeMap->releaseGpuResources();
		delete roCubeMap;
		roCubeMap = nullptr;
	}
	
	fbo->releaseGpuResources();
	delete fbo;
	fbo = nullptr;
}

void EncryptedVulkanRenderer::initGpuResources() {
	fbo = new FrameBuffer(device, false, fboFormates);
	fbo->initGpuResources();

	if(initBigIntTest) {
		roBigIntTester = new BigIntTestObj(device);
		roBigIntTester->initGpuResources();
	} else {

		roCubeMap = new CubeMap(device, false);
		roCubeMap->initGpuResources();
		
		
		
		data::VolumeFactory::createVolume(m_volume, 100);
		
		m_gpuVolume = new data::GpuVolume(device);
		m_gpuVolume->uploadVolume(m_volume);
		
		roEncXRay = new EncryptedXRay(device);
		roEncXRay->initGpuResources();
	}
}

void EncryptedVulkanRenderer::releaseSwapChainResources() {
	if(initBigIntTest) {
		roBigIntTester->releaseSwapChainResources();
	} else {
		roEncXRay->releaseSwapChainResources();
		roCubeMap->releaseSwapChainResources();
	}
	
	cleanupCommandBuffer();
	fbo->releaseSwapChainResources();
}

void EncryptedVulkanRenderer::initSwapChainResources(QSize yTargetSize, size_t ySwapChainImageCount) {
	fbo->initSwapChainResources(yTargetSize);
	createCommandBuffer();
	
	swapChain.swapChainImageCount = ySwapChainImageCount;
	swapChain.renderPass = fbo->getRenderPass();
	swapChain.targetSize = yTargetSize;
	
	if(initBigIntTest) {
		roBigIntTester->initSwapChainResources(swapChain);
	} else {
		roCubeMap->initSwapChainResources(swapChain);
		roEncXRay->initSwapChainResources(swapChain, m_gpuVolume, roCubeMap->getFrontImageView(), roCubeMap->getBackImageView());
	}
}

void EncryptedVulkanRenderer::cleanupCommandBuffer() {}

void EncryptedVulkanRenderer::createCommandBuffer(size_t ySwapChainImageCount) {}

VkCommandBuffer EncryptedVulkanRenderer::startFrame() {
	VkCommandBuffer commandBuffer;
	VkCommandBufferAllocateInfo allocInfo = VulkanInitializers::commandBufferAllocateInfo(
		device.graphicsCommandPool,			// commandPool
		VK_COMMAND_BUFFER_LEVEL_PRIMARY,	// level
		(uint32_t)1							// commandBufferCount
	);
	VK_CHECK_RESULT (device.funcs->vkAllocateCommandBuffers(device.vkDev, &allocInfo, &commandBuffer), "failed to allocate command buffers!");

	VkCommandBufferBeginInfo beginInfo = VulkanInitializers::commandBufferBeginInfo();
	VK_CHECK_RESULT (device.funcs->vkBeginCommandBuffer(commandBuffer, &beginInfo), "failed to begin recording command buffer!");
	
		//this->draw(camera, commandBuffer, 0);
	return commandBuffer;
}

void EncryptedVulkanRenderer::startMainRenderPass(VkCommandBuffer yCommandBuffer) {
	constexpr uint32_t clearValueCount = GPU_INT_TEXTURE_SIZE;
	VkClearValue clearValue{};
	clearValue.color = { { 0.0f, 0.0f, 0.0f, 1.0f } };

	std::vector<VkClearValue> clearValues{clearValueCount, clearValue};
	//clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
	//clearValues[1].depthStencil = { 1.0f, 0 };

	VkRenderPassBeginInfo renderPassInfo = VulkanInitializers::renderPassBeginInfo();
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = fbo->getRenderPass();
	renderPassInfo.framebuffer = fbo->getFramebuffer();
	renderPassInfo.renderArea.offset = {0, 0};
	renderPassInfo.renderArea.extent.width = fbo->getWidth();
	renderPassInfo.renderArea.extent.height = fbo->getHeight();
	renderPassInfo.clearValueCount = clearValueCount;
	renderPassInfo.pClearValues = clearValues.data(); //&clearValues[0];

	device.funcs->vkCmdBeginRenderPass(yCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void EncryptedVulkanRenderer::endMainRenderPass(VkCommandBuffer yCommandBuffer) {
	device.funcs->vkCmdEndRenderPass(yCommandBuffer);
}

void EncryptedVulkanRenderer::endFrame(VkCommandBuffer yCommandBuffer) {
	
		//this->draw(camera, commandBuffer, 0);
	
	VK_CHECK_RESULT (device.funcs->vkEndCommandBuffer(yCommandBuffer), "failed to record command buffer!");
	
	/*
		Submit command buffer to a queue and wait for fence until queue operations have been finished
	*/
	//void submitWork(VkCommandBuffer cmdBuffer, VkQueue queue)
	//{
		VkSubmitInfo submitInfo = VulkanInitializers::submitInfo();
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &yCommandBuffer;
		VkFenceCreateInfo fenceInfo = VulkanInitializers::fenceCreateInfo();
		VkFence fence;
		VK_CHECK_RESULT(device.funcs->vkCreateFence(device.vkDev, &fenceInfo, nullptr, &fence), "failed to create fence!");
		VK_CHECK_RESULT(device.funcs->vkQueueSubmit(device.graphicsQueue, 1, &submitInfo, fence), "failed to queue submit!");
		VK_CHECK_RESULT(device.funcs->vkWaitForFences(device.vkDev, 1, &fence, VK_TRUE, UINT64_MAX), "failed to wait for fances!");
		device.funcs->vkDestroyFence(device.vkDev, fence, nullptr);
	//}
	
	device.funcs->vkFreeCommandBuffers(device.vkDev, device.graphicsCommandPool, 1, &yCommandBuffer);
	yCommandBuffer = nullptr;
	
	
	VK_CHECK_RESULT(device.funcs->vkDeviceWaitIdle(device.vkDev), "failed to wait for the device until it is idle!"); // TODO is this realy required?
}

void EncryptedVulkanRenderer::draw(size_t yCurrentSwapChainImageIndex) {
	if(initBigIntTest) {
		throw std::logic_error("This Instance of EncryptedVulkanRenderer is create with test support only.");
	}
	
	VkCommandBuffer cmdBuf = this->startFrame();
	
	// ------ offscreen render pass ------
	roCubeMap->drawOffscreenFrame(camera, cmdBuf, yCurrentSwapChainImageIndex);
	
	/*
		Note: Explicit synchronization is not required between the render pass, as this is done implicit via sub pass dependencies
		Is this correct?????
	*/
	
	// ------ main render pass ------
	this->startMainRenderPass(cmdBuf);
	
	
	// TODO DRAW
	roEncXRay->draw(camera, cmdBuf, yCurrentSwapChainImageIndex);
	
	this->endMainRenderPass(cmdBuf);
	
	this->endFrame(cmdBuf);
}

QImage EncryptedVulkanRenderer::framebuffer2host() {
	//data::ImageUtil::framebuffer2ppm(device, *fbo, "headless_");
	return data::ImageUtil::framebuffer2QImage(device, *fbo, 0);
}

void EncryptedVulkanRenderer::evaluateTest() {
	if(!initBigIntTest) {
		throw std::logic_error("This Instance of EncryptedVulkanRenderer is create without test support.");
	}
	
	VkCommandBuffer cmdBuf = this->startFrame();
	this->startMainRenderPass(cmdBuf);
	
	// TODO DRAW
	//roEncXRay->draw(camera, cmdBuf, yCurrentSwapChainImageIndex);
	roBigIntTester->draw(cmdBuf, 0);
	
	this->endMainRenderPass(cmdBuf);
	this->endFrame(cmdBuf);
	
	// ------ read back the calculated values
	roBigIntTester->evaluateTest(*fbo);
}
