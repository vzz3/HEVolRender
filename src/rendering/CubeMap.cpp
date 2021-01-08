
#include "CubeMap.hpp"

#include "VulkanUtility.hpp"
#include "VulkanInitializers.hpp"
#include <array>


using namespace ppvr::rendering;

CubeMap::CubeMap(VulkanDevice& yDev): dev(yDev), cube(yDev) {
	fbDepthFormat = VulkanUtility::getSupportedDepthFormat(*dev.vkInstance, dev.vkPhysicalDev);
}
CubeMap::~CubeMap() {
	this->cleanup();
};

void CubeMap::initGpuResources() {
	cube.initGpuResources();
	this->createDebugDescriptorSetLayout();
	//this->createVertexBuffer();
	//this->createDescriptorSetLayout();
}
void CubeMap::releaseGpuResources() {
	cube.releaseGpuResources();
	this->cleanupDebugDescriptorSetLayout();
	//this->cleanupDescriptorSetLayout();
	//this->cleanupVertexBuffer();
}

void CubeMap::initSwapChainResources(const VulkanSwapChain& ySwapChain) {
	this->createOffscreen(ySwapChain);
	//this->createCommandBuffers();
	this->createDebugDescriptorPool(ySwapChain.swapChainImageCount);
	this->createDebugDescriptorSets(ySwapChain.swapChainImageCount);
	this->createDebugPipeline(ySwapChain);
	
	offscreenSwappChain.renderPass = offscreenPass.renderPass;
	offscreenSwappChain.swapChainImageCount = ySwapChain.swapChainImageCount;
	offscreenSwappChain.targetSize = ySwapChain.targetSize;
	cube.initSwapChainResources(offscreenSwappChain);
	//this->createUniformBuffers(ySwapChain.swapChainImageCount);
    //this->createDescriptorPool(ySwapChain.swapChainImageCount);
	//this->createDescriptorSets(ySwapChain.swapChainImageCount);
	//this->createGraphicsPipeline(ySwapChain.renderPass, ySwapChain.targetSize);
}

void CubeMap::releaseSwapChainResources() {
	cube.releaseSwapChainResources();
	this->cleanupDebugPipeline();
	this->cleanupDebugDescriptorSets();
	this->cleanupDebugDescriptorPool();
	//this->cleanupCommandBuffers();
	this->cleanupOffscreen();
	//this->cleanupGraphicsPipeline();
	//this->cleanupDescriptorSets();
	//this->cleanupDescriptorPool();
	//this->cleanupUniformBuffers();
}

void CubeMap::cleanup() {
	this->releaseSwapChainResources();
	this->releaseGpuResources();
}

void CubeMap::createOffscreen(const VulkanSwapChain& ySwapChain) {
	offscreenPass.width = ySwapChain.targetSize.width();
	offscreenPass.height = ySwapChain.targetSize.height();

	this->createColorAttachment(ySwapChain);
	this->createSampler(ySwapChain);
	if(useDepthTest) {
		this->createDepthAttachment(ySwapChain);
	}
	this->createOffscreenRenderPass(ySwapChain);
	this->createOffscreenFramebuffers(ySwapChain);
}

void CubeMap::cleanupOffscreen() {
	this->cleanupOffscreenFramebuffers();
	this->cleanupOffscreenRenderPass();
	if(useDepthTest) {
		this->cleanupDepthAttachment();
	}
	this->cleanupSampler();
	this->cleanupColorAttachment();
}

void CubeMap::cleanupColorAttachment() {
	// Color attachment
	dev.funcs->vkDestroyImageView(dev.vkDev, offscreenPass.color.view, nullptr);
	offscreenPass.color.view = VK_NULL_HANDLE;
	dev.funcs->vkDestroyImage(dev.vkDev, offscreenPass.color.image, nullptr);
	offscreenPass.color.image = VK_NULL_HANDLE;
	dev.funcs->vkFreeMemory(dev.vkDev, offscreenPass.color.mem, nullptr);
	offscreenPass.color.mem = VK_NULL_HANDLE;
}

void CubeMap::createColorAttachment(const VulkanSwapChain& ySwapChain) {
	// Color attachment
	VkImageCreateInfo image = VulkanInitializers::imageCreateInfo();
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = colorFormat;
	image.extent.width = offscreenPass.width;
	image.extent.height = offscreenPass.height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	// We will sample directly from the color attachment
	image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

	VK_CHECK_RESULT(dev.funcs->vkCreateImage(dev.vkDev, &image, nullptr, &offscreenPass.color.image), "failed to create color image for offscreen frame buffer!");

	VkMemoryRequirements memReqs;
	dev.funcs->vkGetImageMemoryRequirements(dev.vkDev, offscreenPass.color.image, &memReqs);

	VkMemoryAllocateInfo memAlloc = VulkanInitializers::memoryAllocateInfo();
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = VulkanUtility::findMemoryType(dev, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK_RESULT(dev.funcs->vkAllocateMemory(dev.vkDev, &memAlloc, nullptr, &offscreenPass.color.mem), "failed to allocate memory for off screen frame buffer color image!");
	VK_CHECK_RESULT(dev.funcs->vkBindImageMemory(dev.vkDev, offscreenPass.color.image, offscreenPass.color.mem, 0), "failed to bind off screen frame buffer color image!");

	VkImageViewCreateInfo colorImageView = VulkanInitializers::imageViewCreateInfo();
	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	colorImageView.format = colorFormat;
	colorImageView.subresourceRange = {};
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = offscreenPass.color.image;
	VK_CHECK_RESULT(dev.funcs->vkCreateImageView(dev.vkDev, &colorImageView, nullptr, &offscreenPass.color.view), "failed to bind off screen color image view!");
}

void CubeMap::cleanupSampler() {
	dev.funcs->vkDestroySampler(dev.vkDev, offscreenPass.sampler, nullptr);
	offscreenPass.sampler = VK_NULL_HANDLE;
}

void CubeMap::createSampler(const VulkanSwapChain& ySwapChain) {
	// Create sampler to sample from the attachment in the fragment shader
	VkSamplerCreateInfo samplerInfo = VulkanInitializers::samplerCreateInfo();
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfo.addressModeV = samplerInfo.addressModeU;
	samplerInfo.addressModeW = samplerInfo.addressModeU;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.maxAnisotropy = 1.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 1.0f;
	samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	VK_CHECK_RESULT(dev.funcs->vkCreateSampler(dev.vkDev, &samplerInfo, nullptr, &offscreenPass.sampler), "failed to create sampler!");
}

void CubeMap::cleanupDepthAttachment() {
	dev.funcs->vkDestroyImageView(dev.vkDev, offscreenPass.depth.view, nullptr);
	offscreenPass.depth.view = VK_NULL_HANDLE;
	dev.funcs->vkDestroyImage(dev.vkDev, offscreenPass.depth.image, nullptr);
	offscreenPass.depth.image = VK_NULL_HANDLE;
	dev.funcs->vkFreeMemory(dev.vkDev, offscreenPass.depth.mem, nullptr);
	offscreenPass.depth.mem = VK_NULL_HANDLE;
}

void CubeMap::createDepthAttachment(const VulkanSwapChain& ySwapChain) {
	// Find a suitable depth format
	VkFormat fbDepthFormat = VulkanUtility::getSupportedDepthFormat(*dev.vkInstance, dev.vkPhysicalDev);

	// Depth stencil attachment
	VkImageCreateInfo image = VulkanInitializers::imageCreateInfo();
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = fbDepthFormat;
	image.extent.width = offscreenPass.width;
	image.extent.height = offscreenPass.height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

	VK_CHECK_RESULT(vkCreateImage(dev.vkDev, &image, nullptr, &offscreenPass.depth.image), "failed to create depth image for offscreen frame buffer!");

	VkMemoryRequirements memReqs;
	dev.funcs->vkGetImageMemoryRequirements(dev.vkDev, offscreenPass.depth.image, &memReqs);

	VkMemoryAllocateInfo memAlloc = VulkanInitializers::memoryAllocateInfo();
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = VulkanUtility::findMemoryType(dev, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK_RESULT(vkAllocateMemory(dev.vkDev, &memAlloc, nullptr, &offscreenPass.depth.mem), "failed to allocate memory for off screen frame buffer depth image!");
	VK_CHECK_RESULT(vkBindImageMemory(dev.vkDev, offscreenPass.depth.image, offscreenPass.depth.mem, 0), "failed to bind off screen frame buffer depth image!");

	VkImageViewCreateInfo depthStencilView = VulkanInitializers::imageViewCreateInfo();
	depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	depthStencilView.format = fbDepthFormat;
	depthStencilView.flags = 0;
	depthStencilView.subresourceRange = {};
	depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
	depthStencilView.subresourceRange.baseMipLevel = 0;
	depthStencilView.subresourceRange.levelCount = 1;
	depthStencilView.subresourceRange.baseArrayLayer = 0;
	depthStencilView.subresourceRange.layerCount = 1;
	depthStencilView.image = offscreenPass.depth.image;
	VK_CHECK_RESULT(vkCreateImageView(dev.vkDev, &depthStencilView, nullptr, &offscreenPass.depth.view), "failed to bind off screen depth image view!");
}

void CubeMap::cleanupOffscreenRenderPass() {
	dev.funcs->vkDestroyRenderPass(dev.vkDev, offscreenPass.renderPass, nullptr);
	offscreenPass.renderPass = VK_NULL_HANDLE;
}

void CubeMap::createOffscreenRenderPass(const VulkanSwapChain& ySwapChain) {
	// Create a separate render pass for the offscreen rendering as it may differ from the one used for scene rendering

	std::array<VkAttachmentDescription, 2> attchmentDescriptions = {};
	// Color attachment
	attchmentDescriptions[0].format = colorFormat;
	attchmentDescriptions[0].samples = VK_SAMPLE_COUNT_1_BIT;
	attchmentDescriptions[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attchmentDescriptions[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attchmentDescriptions[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attchmentDescriptions[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attchmentDescriptions[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attchmentDescriptions[0].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	// Depth attachment
	if(useDepthTest) {
		attchmentDescriptions[1].format = fbDepthFormat;
		attchmentDescriptions[1].samples = VK_SAMPLE_COUNT_1_BIT;
		attchmentDescriptions[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attchmentDescriptions[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attchmentDescriptions[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attchmentDescriptions[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attchmentDescriptions[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attchmentDescriptions[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	}
	VkAttachmentReference colorReference = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
	VkAttachmentReference depthReference = { 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };

	VkSubpassDescription subpassDescription = {};
	subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpassDescription.colorAttachmentCount = 1;
	subpassDescription.pColorAttachments = &colorReference;
	if(useDepthTest) {
		subpassDescription.pDepthStencilAttachment = &depthReference;
	}
	
	// Use subpass dependencies for layout transitions
	std::array<VkSubpassDependency, 2> dependencies;

	dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
	dependencies[0].dstSubpass = 0;
	dependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependencies[0].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
	dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	if(useDepthTest) {
		dependencies[1].srcSubpass = 0;
		dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		dependencies[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
	}
	
	// Create the actual renderpass
	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = static_cast<uint32_t>(attchmentDescriptions.size()) - (useDepthTest ? 0 : 1);
	renderPassInfo.pAttachments = attchmentDescriptions.data();
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpassDescription;
	renderPassInfo.dependencyCount = static_cast<uint32_t>(dependencies.size()) - (useDepthTest ? 0 : 1);
	renderPassInfo.pDependencies = dependencies.data();

	VK_CHECK_RESULT(dev.funcs->vkCreateRenderPass(dev.vkDev, &renderPassInfo, nullptr, &offscreenPass.renderPass), "failed to create offscreen render path!");
}

void CubeMap::cleanupOffscreenFramebuffers() {
	dev.funcs->vkDestroyFramebuffer(dev.vkDev, offscreenPass.frameBuffer, nullptr);
	offscreenPass.frameBuffer = VK_NULL_HANDLE;
}

void CubeMap::createOffscreenFramebuffers(const VulkanSwapChain& ySwapChain) {
	VkImageView attachments[2];
	attachments[0] = offscreenPass.color.view;
	if(useDepthTest) {
		attachments[1] = offscreenPass.depth.view;
	}
	VkFramebufferCreateInfo fbufCreateInfo = VulkanInitializers::framebufferCreateInfo();
	fbufCreateInfo.renderPass = offscreenPass.renderPass;
	fbufCreateInfo.attachmentCount = useDepthTest ? 2 : 1;
	fbufCreateInfo.pAttachments = attachments;
	fbufCreateInfo.width = offscreenPass.width;
	fbufCreateInfo.height = offscreenPass.height;
	fbufCreateInfo.layers = 1;

	VK_CHECK_RESULT(dev.funcs->vkCreateFramebuffer(dev.vkDev, &fbufCreateInfo, nullptr, &offscreenPass.frameBuffer), "failed to create offscreen renderPass!");

	// Fill a descriptor for later use in a descriptor set
	offscreenPass.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	offscreenPass.descriptor.imageView = offscreenPass.color.view;
	offscreenPass.descriptor.sampler = offscreenPass.sampler;
}

void CubeMap::cleanupDebugDescriptorPool() {
	dev.funcs->vkDestroyDescriptorPool(dev.vkDev, debugDescriptorPool, nullptr);
	debugDescriptorPool = VK_NULL_HANDLE;
}

void CubeMap::createDebugDescriptorPool(size_t ySwapChainImageCount) {
	std::vector<VkDescriptorPoolSize> poolSizes = {
		//VulkanInitializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, static_cast<uint32_t>(ySwapChainImageCount)),
		VulkanInitializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, static_cast<uint32_t>(ySwapChainImageCount))
	};
	VkDescriptorPoolCreateInfo poolInfo = VulkanInitializers::descriptorPoolCreateInfo(poolSizes, static_cast<uint32_t>(ySwapChainImageCount));
	VK_CHECK_RESULT (vkCreateDescriptorPool(dev.vkDev, &poolInfo, nullptr, &debugDescriptorPool), "failed to create descriptor pool!");
}

void CubeMap::cleanupDebugDescriptorSets() {
	// You don't need to explicitly clean up descriptor sets, because they will be automatically freed when the descriptor pool is destroyed.
}

void CubeMap::createDebugDescriptorSets(size_t ySwapChainImageCount) {
	std::vector<VkDescriptorSetLayout> layouts(ySwapChainImageCount, debugDescriptorSetLayout); // Constructs the container with ySwapChainImageCount copies of debugDescriptorSetLayout.
	VkDescriptorSetAllocateInfo allocInfo = VulkanInitializers::descriptorSetAllocateInfo(
		debugDescriptorPool, 						// descriptorPool
		layouts.data(),								// pSetLayouts
		static_cast<uint32_t>(ySwapChainImageCount)	// descriptorSetCount
	);
	
	debugDescriptorSets.resize(ySwapChainImageCount);
	VK_CHECK_RESULT(dev.funcs->vkAllocateDescriptorSets(dev.vkDev, &allocInfo, debugDescriptorSets.data()),  "failed to allocate descriptor sets!");

	for (size_t i = 0; i < ySwapChainImageCount; i++) {
	/*
		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = uniformBuffers[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(uniform::CameraUniformBufferObject);
	*/
		std::vector<VkWriteDescriptorSet> writeDescriptorSets =
		{
			// Binding 0 : Vertex shader uniform buffer
	/*		VulkanInitializers::writeDescriptorSet(
				debugDescriptorSets[0],					// dstSet
				VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,		// descriptorType
				0,										// dstBinding
				&bufferInfo								// pBufferInfo
			), 		*/
			// Binding 1 : Fragment shader texture sampler
			VulkanInitializers::writeDescriptorSet(
				debugDescriptorSets[i],						// dstSet
				VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,	// descriptorType
				0,											// dstBinding
				&offscreenPass.descriptor					// pImageInfo
			),
		};
		dev.funcs->vkUpdateDescriptorSets(dev.vkDev, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, nullptr);
	}
}

void CubeMap::cleanupDebugDescriptorSetLayout() {
	dev.funcs->vkDestroyDescriptorSetLayout(dev.vkDev, debugDescriptorSetLayout, nullptr);
	debugDescriptorSetLayout = VK_NULL_HANDLE;
}

void CubeMap::createDebugDescriptorSetLayout() {
	std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings;
	//VkDescriptorSetLayoutCreateInfo descriptorLayoutInfo;
	//VkPipelineLayoutCreateInfo pipelineLayoutInfo;

	// Binding 0 : Vertex shader uniform buffer
	/*
	setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
		VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		VK_SHADER_STAGE_VERTEX_BIT,
		0));
		*/
	// Binding 1 : Fragment shader image sampler
	setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
		VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		VK_SHADER_STAGE_FRAGMENT_BIT,
		0));
	// Binding 2 : Fragment shader image sampler
	//setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
	//	VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
	//	VK_SHADER_STAGE_FRAGMENT_BIT,
	//	2));

	VkDescriptorSetLayoutCreateInfo descriptorLayoutInfo = VulkanInitializers::descriptorSetLayoutCreateInfo(setLayoutBindings);

	VK_CHECK_RESULT (dev.funcs->vkCreateDescriptorSetLayout(dev.vkDev, &descriptorLayoutInfo, nullptr, &debugDescriptorSetLayout), "failed to create descriptor set layout!");
}

void CubeMap::cleanupDebugPipeline() {
	dev.funcs->vkDestroyPipeline(dev.vkDev, debugPipline, nullptr);
	debugPipline = VK_NULL_HANDLE;
	
	dev.funcs->vkDestroyPipelineLayout(dev.vkDev, debugPiplineLayout, nullptr);
	debugPiplineLayout = VK_NULL_HANDLE;
}

void CubeMap::createDebugPipeline(const VulkanSwapChain& ySwapChain) {
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = VulkanInitializers::pipelineLayoutCreateInfo(&debugDescriptorSetLayout, 1);
	VK_CHECK_RESULT (dev.funcs->vkCreatePipelineLayout(dev.vkDev, &pipelineLayoutInfo, nullptr, &debugPiplineLayout), "failed to create pipeline layout!");

	VkShaderModule vertShaderModule = VulkanUtility::createShaderModule(this->dev, QStringLiteral("shaders/quad.vert.spv"));
	VkShaderModule fragShaderModule = VulkanUtility::createShaderModule(this->dev, QStringLiteral("shaders/quad.frag.spv"));
	VkPipelineShaderStageCreateInfo vertShaderStageInfo = VulkanInitializers::pipelineShaderStageCreateInfo(vertShaderModule, VK_SHADER_STAGE_VERTEX_BIT);
	VkPipelineShaderStageCreateInfo fragShaderStageInfo = VulkanInitializers::pipelineShaderStageCreateInfo(fragShaderModule, VK_SHADER_STAGE_FRAGMENT_BIT);
	std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages = {vertShaderStageInfo, fragShaderStageInfo};
	
	VkPipelineVertexInputStateCreateInfo vertexInputInfo = VulkanInitializers::pipelineVertexInputStateCreateInfo();
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.vertexAttributeDescriptionCount = 0;
	
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyState = VulkanInitializers::pipelineInputAssemblyStateCreateInfo(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, VK_FALSE);
	VkPipelineViewportStateCreateInfo viewportState = VulkanInitializers::pipelineViewportStateCreateInfo(1, 1, 0);
	VkPipelineRasterizationStateCreateInfo rasterizationState = VulkanInitializers::pipelineRasterizationStateCreateInfo(VK_POLYGON_MODE_FILL, VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_COUNTER_CLOCKWISE,0);
	VkPipelineMultisampleStateCreateInfo multisampleState = VulkanInitializers::pipelineMultisampleStateCreateInfo(VK_SAMPLE_COUNT_1_BIT, 0);
	VkPipelineColorBlendAttachmentState blendAttachmentState = VulkanInitializers::pipelineColorBlendAttachmentState(0xf, VK_FALSE);
	VkPipelineColorBlendStateCreateInfo colorBlendState = VulkanInitializers::pipelineColorBlendStateCreateInfo(1, &blendAttachmentState);
	VkPipelineDepthStencilStateCreateInfo depthStencilState = VulkanInitializers::pipelineDepthStencilStateCreateInfo(VK_FALSE, VK_FALSE, VK_COMPARE_OP_LESS_OR_EQUAL);
	
	std::vector<VkDynamicState> dynamicStateEnables = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
	VkPipelineDynamicStateCreateInfo dynamicState = VulkanInitializers::pipelineDynamicStateCreateInfo(dynamicStateEnables);
	
	VkGraphicsPipelineCreateInfo pipelineInfo = VulkanInitializers::pipelineCreateInfo(debugPiplineLayout, ySwapChain.renderPass, 0);
	pipelineInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
	pipelineInfo.pStages = shaderStages.data();
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssemblyState;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizationState;
	pipelineInfo.pMultisampleState = &multisampleState;
	pipelineInfo.pColorBlendState = &colorBlendState;
	pipelineInfo.pDepthStencilState = &depthStencilState;
	
	pipelineInfo.pDynamicState = &dynamicState;
	
	

	rasterizationState.cullMode = VK_CULL_MODE_NONE;
	
	VK_CHECK_RESULT (dev.funcs->vkCreateGraphicsPipelines(dev.vkDev, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &debugPipline), "failed to create debug graphics pipeline!");
	
	dev.funcs->vkDestroyShaderModule(dev.vkDev, fragShaderModule, nullptr);
	dev.funcs->vkDestroyShaderModule(dev.vkDev, vertShaderModule, nullptr);
}


void CubeMap::drawOffscreenFrame(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex) {
	VkClearValue clearValues[2];
	clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 0.0f } };
	if(useDepthTest) {
		clearValues[1].depthStencil = { 1.0f, 0 };
	}

	VkRenderPassBeginInfo renderPassBeginInfo = VulkanInitializers::renderPassBeginInfo();
	renderPassBeginInfo.renderPass = offscreenPass.renderPass;
	renderPassBeginInfo.framebuffer = offscreenPass.frameBuffer;
	renderPassBeginInfo.renderArea.extent.width = offscreenPass.width;
	renderPassBeginInfo.renderArea.extent.height = offscreenPass.height;
	renderPassBeginInfo.clearValueCount = useDepthTest ? 2 : 1;
	renderPassBeginInfo.pClearValues = clearValues;

	vkCmdBeginRenderPass(yCmdBuf, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	VkViewport viewport = VulkanInitializers::viewport((float)offscreenPass.width, (float)offscreenPass.height, 0.0f, 1.0f);
	vkCmdSetViewport(yCmdBuf, 0, 1, &viewport);

	VkRect2D scissor = VulkanInitializers::rect2D(offscreenPass.width, offscreenPass.height, 0, 0);
	vkCmdSetScissor(yCmdBuf, 0, 1, &scissor);

	VkDeviceSize offsets[1] = { 0 };

	// Mirrored scene
	//vkCmdBindDescriptorSets(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayouts.shaded, 0, 1, &descriptorSets.offscreen, 0, NULL);
	//vkCmdBindPipeline(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines.shadedOffscreen);
	//models.example.draw(drawCmdBuffers[i]);
	cube.draw(yCamera, yCmdBuf, yCurrentSwapChainImageIndex);

	vkCmdEndRenderPass(yCmdBuf);
}


void CubeMap::draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex) {
	/*
	this->updateUniformBuffer(yCamera, yCurrentSwapChainImageIndex);

	dev.funcs->vkCmdBindPipeline(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
    //dev.funcs->vkCmdBindDescriptorSets(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1, &m_descSet[m_window->currentFrame()], 0, nullptr);
    VkBuffer vertexBuffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    dev.funcs->vkCmdBindVertexBuffers(yCmdBuf, 0, 1, vertexBuffers, offsets);
	dev.funcs->vkCmdBindDescriptorSets(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[yCurrentSwapChainImageIndex], 0, nullptr);
    dev.funcs->vkCmdDraw(yCmdBuf, static_cast<uint32_t>(vertices.size()), 1, 0, 0);
    */
    // Display the offscreen render target
	dev.funcs->vkCmdBindDescriptorSets(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, debugPiplineLayout, 0, 1, &debugDescriptorSets[yCurrentSwapChainImageIndex], 0, nullptr);
	dev.funcs->vkCmdBindPipeline(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, debugPipline);
	dev.funcs->vkCmdDraw(yCmdBuf, 6, 1, 0, 0);
}
