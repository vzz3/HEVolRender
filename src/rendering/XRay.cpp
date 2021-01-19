
#include "XRay.hpp"

#include "VulkanUtility.hpp"
#include "VulkanInitializers.hpp"
#include "uniform/XRayUniformBufferObject.hpp"
#include <array>


using namespace ppvr::rendering;



XRay::XRay(VulkanDevice& yDev): dev(yDev) {
}

XRay::~XRay() {
	this->cleanup();
};

void XRay::initGpuResources() {
	this->createDescriptorSetLayout();
}

void XRay::releaseGpuResources() {
	this->cleanupDescriptorSetLayout();
}

void XRay::initSwapChainResources(const VulkanSwapChain& ySwapChain, data::GpuVolume* yVolume, VkImageView yCubeFront, VkImageView yCubeBack) {
	volume = yVolume;
	cubePosView[0] = yCubeFront;
	cubePosView[1] = yCubeBack;
	this->createVolumeDescriptors(ySwapChain);
	this->createPipeline(ySwapChain);
}

void XRay::releaseSwapChainResources() {
	this->cleanupPipeline();
	this->cleanupVolumeDescriptors();
	volume = nullptr;
}

void XRay::cleanup() {
	this->releaseSwapChainResources();
	this->releaseGpuResources();
}

// --- image descriptor ---

void XRay::cleanupVolumeDescriptors() {
	cleanupDescriptorSet();
	cleanupDescriptorPool();
	cleanupUniformBuffer();
	cleanupVolumeSampler();
	cleanupCubePosSampler();
}

void XRay::createVolumeDescriptors(const VulkanSwapChain& ySwapChain) {
	createVolumeSampler(ySwapChain);
	createCubePosSampler(ySwapChain);
	createUniformBuffer(ySwapChain.swapChainImageCount);
	createDescriptorPool(ySwapChain.swapChainImageCount);
	createDescriptorSet(ySwapChain.swapChainImageCount);
		
	for (size_t swapImgIndex = 0; swapImgIndex<ySwapChain.swapChainImageCount; swapImgIndex++) {
		this->updateUniformBuffer(swapImgIndex);
	}
}


void XRay::cleanupVolumeSampler() {
	dev.funcs->vkDestroySampler(dev.vkDev, volumeSampler, nullptr);
	volumeSampler = VK_NULL_HANDLE;
}

void XRay::createVolumeSampler(const VulkanSwapChain& ySwapChain) {
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
	VK_CHECK_RESULT(dev.funcs->vkCreateSampler(dev.vkDev, &samplerInfo, nullptr, &volumeSampler), "failed to create sampler!");
}

void XRay::cleanupCubePosSampler() {
	dev.funcs->vkDestroySampler(dev.vkDev, cubePosSampler, nullptr);
	cubePosSampler = VK_NULL_HANDLE;
}

void XRay::createCubePosSampler(const VulkanSwapChain& ySwapChain) {
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
	VK_CHECK_RESULT(dev.funcs->vkCreateSampler(dev.vkDev, &samplerInfo, nullptr, &cubePosSampler), "failed to create sampler!");
}

void XRay::cleanupUniformBuffer() {
	for (size_t i = 0; i < uniformBuffers.size(); i++) {
        dev.funcs->vkDestroyBuffer(dev.vkDev, uniformBuffers[i], nullptr);
		uniformBuffers[i] = VK_NULL_HANDLE;
        dev.funcs->vkFreeMemory(dev.vkDev, uniformBuffersMemory[i], nullptr);
        uniformBuffersMemory[i] = VK_NULL_HANDLE;
    }
}

void XRay::createUniformBuffer(size_t ySwapChainImageCount) {
	constexpr VkDeviceSize bufferSize = sizeof(uniform::XRayUniformBufferObject);

	uniformBuffers.resize(ySwapChainImageCount);
    uniformBuffersMemory.resize(ySwapChainImageCount);
	
    constexpr VkBufferUsageFlags usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	constexpr VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    for (size_t i = 0; i < ySwapChainImageCount; i++) {
        VulkanUtility::createBuffer(dev, bufferSize, usage, properties, uniformBuffers[i], uniformBuffersMemory[i]);
    }
}

void XRay::cleanupDescriptorPool() {
	dev.funcs->vkDestroyDescriptorPool(dev.vkDev, descriptorPool, nullptr);
	descriptorPool = VK_NULL_HANDLE;
}

void XRay::createDescriptorPool(size_t ySwapChainImageCount) {
	std::vector<VkDescriptorPoolSize> poolSizes = {
		VulkanInitializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, static_cast<uint32_t>(ySwapChainImageCount)),			// uniform buffer for XRayUniformBufferObject
		VulkanInitializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, static_cast<uint32_t>(ySwapChainImageCount)),	// sampler+image for volume
		VulkanInitializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_SAMPLER, static_cast<uint32_t>(ySwapChainImageCount)),				// sampler for cube postion images
		VulkanInitializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, static_cast<uint32_t>(ySwapChainImageCount * 2)) 		// front and back postions of cube
	};
	VkDescriptorPoolCreateInfo poolInfo = VulkanInitializers::descriptorPoolCreateInfo(poolSizes, static_cast<uint32_t>(ySwapChainImageCount));
	VK_CHECK_RESULT (vkCreateDescriptorPool(dev.vkDev, &poolInfo, nullptr, &descriptorPool), "failed to create descriptor pool!");
}

void XRay::cleanupDescriptorSet() {
	// You don't need to explicitly clean up descriptor sets, because they will be automatically freed when the descriptor pool is destroyed.
}

void XRay::createDescriptorSet(size_t ySwapChainImageCount) {
	std::vector<VkDescriptorSetLayout> layouts(ySwapChainImageCount, descriptorSetLayout); // Constructs the container with ySwapChainImageCount copies of debugDescriptorSetLayout.
	VkDescriptorSetAllocateInfo allocInfo = VulkanInitializers::descriptorSetAllocateInfo(
		descriptorPool,								// descriptorPool
		layouts.data(),								// pSetLayouts
		static_cast<uint32_t>(ySwapChainImageCount)	// descriptorSetCount
	);
	
	descriptorSets.resize(ySwapChainImageCount);
	VK_CHECK_RESULT(dev.funcs->vkAllocateDescriptorSets(dev.vkDev, &allocInfo, descriptorSets.data()),  "failed to allocate descriptor sets!");

	for (size_t i = 0; i < ySwapChainImageCount; i++) {
		
		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = uniformBuffers[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(uniform::XRayUniformBufferObject);
		
		VkDescriptorImageInfo volumeImageInfo{};
		volumeImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		volumeImageInfo.imageView = volume->getImageView();
		volumeImageInfo.sampler = volumeSampler;
		
		VkDescriptorImageInfo cubePosSamplerInfo{};
		cubePosSamplerInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		cubePosSamplerInfo.imageView = nullptr;
		cubePosSamplerInfo.sampler = cubePosSampler;
		
		constexpr size_t cubePosTexArraySize = 2;
		VkDescriptorImageInfo cubePosImageInfo[cubePosTexArraySize];
		for (size_t i = 0; i < cubePosTexArraySize; i++) {
			cubePosImageInfo[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			cubePosImageInfo[i].imageView = cubePosView[i];
			cubePosImageInfo[i].sampler = nullptr;
		}
	
		std::vector<VkWriteDescriptorSet> writeDescriptorSets = {
			// Binding 0 : Vertex shader uniform buffer
			VulkanInitializers::writeDescriptorSet(
				descriptorSets[i],							// dstSet
				VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,			// descriptorType
				1,											// dstBinding
				&bufferInfo									// pBufferInfo
			),
			// Binding 1 : Fragment shader texture sampler
			VulkanInitializers::writeDescriptorSet(
				descriptorSets[i],							// dstSet
				VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,	// descriptorType
				2,											// dstBinding
				&volumeImageInfo							// pImageInfo
			),
			// Binding 3 : Fragment shader sampler
			VulkanInitializers::writeDescriptorSet(
				descriptorSets[i],							// dstSet
				VK_DESCRIPTOR_TYPE_SAMPLER,					// descriptorType
				3,											// dstBinding
				&cubePosSamplerInfo							// pImageInfo
			),
			// Binding 4 : Fragment shader texture
			VulkanInitializers::writeDescriptorSet(
				descriptorSets[i],							// dstSet
				VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,			// descriptorType
				4,											// dstBinding
				&cubePosImageInfo[0],						// pImageInfo
				cubePosTexArraySize							// descriptorCount
			),
		};
		dev.funcs->vkUpdateDescriptorSets(dev.vkDev, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, nullptr);
	}
}

void XRay::updateUniformBuffer(uint32_t yCurrentSwapChainImageIndex) {

//	float scale = images[yIndex].scale;// 0.3f;
//	float s =  2.0f 		* scale;
//	float x = -1.0f  + images[yIndex].screenOffset.x;
//	float y = -1.0f  + images[yIndex].screenOffset.y;
//	glm::mat3x3 mm = glm::transpose(glm::mat3x3({ // I write in row major but glm/glsl uses column major
//				    s,	 0.0f,	    x,	 0.0f, // row 0
//				 0.0f,	    s,	    y,	 0.0f, // row 1
//				 0.0f,	 0.0f,	 1.0f,	 0.0f, // row 2
//				 0.0f,	 0.0f,	 0.0f,	 1.0f, // row 3
//			}));
//	uniform::DebugQuadUniformBufferObject ubo{};
//	ubo.model.modelMatrix = mm;
//
//	constexpr VkDeviceSize uboSize = sizeof(uniform::DebugQuadUniformBufferObject);
//	void* data;
//	dev.funcs->vkMapMemory(dev.vkDev, imgDescs[yIndex].uniformBuffersMemory[yCurrentSwapChainImageIndex], 0, uboSize, 0, &data);
//		memcpy(data, &ubo, uboSize);
//	dev.funcs->vkUnmapMemory(dev.vkDev, imgDescs[yIndex].uniformBuffersMemory[yCurrentSwapChainImageIndex]);

	uniform::XRayUniformBufferObject ubo{};
	ubo.volumeInfo.volumeDepth = volume->depth();

	constexpr VkDeviceSize uboSize = sizeof(uniform::XRayUniformBufferObject);
	void* data;
	dev.funcs->vkMapMemory(dev.vkDev, uniformBuffersMemory[yCurrentSwapChainImageIndex], 0, uboSize, 0, &data);
		memcpy(data, &ubo, uboSize);
	dev.funcs->vkUnmapMemory(dev.vkDev, uniformBuffersMemory[yCurrentSwapChainImageIndex]);
}

// --- render pipline ---

void XRay::cleanupDescriptorSetLayout() {
	dev.funcs->vkDestroyDescriptorSetLayout(dev.vkDev, descriptorSetLayout, nullptr);
	descriptorSetLayout = VK_NULL_HANDLE;
}

void XRay::createDescriptorSetLayout() {
	std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings;
	//VkDescriptorSetLayoutCreateInfo descriptorLayoutInfo;
	//VkPipelineLayoutCreateInfo pipelineLayoutInfo;

	// Binding 0 : Vertex shader uniform buffer
//	setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
//		VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
//		VK_SHADER_STAGE_VERTEX_BIT,
//		0));
	
	// Binding 1 : Fragment shader uniform buffer
	setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
		VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,			// type
		VK_SHADER_STAGE_FRAGMENT_BIT,				// stageFlags
		1));										// binding
	// Binding 2 : Fragment shader image sampler
	setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
		VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,	// type
		VK_SHADER_STAGE_FRAGMENT_BIT,				// stageFlags
		2));										// binding
	// Binding 4 : Fragment shader sampler
	setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
		VK_DESCRIPTOR_TYPE_SAMPLER,					// type
		VK_SHADER_STAGE_FRAGMENT_BIT,				// stageFlags
		3));										// binding
	// Binding 4 : Fragment shader image
	setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
		VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,			// type
		VK_SHADER_STAGE_FRAGMENT_BIT,				// stageFlags
		4,											// binding
		2));										// descriptorCount

	VkDescriptorSetLayoutCreateInfo descriptorLayoutInfo = VulkanInitializers::descriptorSetLayoutCreateInfo(setLayoutBindings);

	VK_CHECK_RESULT (dev.funcs->vkCreateDescriptorSetLayout(dev.vkDev, &descriptorLayoutInfo, nullptr, &descriptorSetLayout), "failed to create descriptor set layout!");
}

void XRay::cleanupPipeline() {
	dev.funcs->vkDestroyPipeline(dev.vkDev, pipline, nullptr);
	pipline = VK_NULL_HANDLE;
	
	dev.funcs->vkDestroyPipelineLayout(dev.vkDev, piplineLayout, nullptr);
	piplineLayout = VK_NULL_HANDLE;
}

void XRay::createPipeline(const VulkanSwapChain& ySwapChain) {
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = VulkanInitializers::pipelineLayoutCreateInfo(&descriptorSetLayout, 1);
	VK_CHECK_RESULT (dev.funcs->vkCreatePipelineLayout(dev.vkDev, &pipelineLayoutInfo, nullptr, &piplineLayout), "failed to create pipeline layout!");

	VkShaderModule vertShaderModule = VulkanUtility::createShaderModule(this->dev, QStringLiteral("shaders/xRay.vert.spv"));
	VkShaderModule fragShaderModule = VulkanUtility::createShaderModule(this->dev, QStringLiteral("shaders/xRay.frag.spv"));
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
	
	
	
	VkGraphicsPipelineCreateInfo pipelineInfo = VulkanInitializers::pipelineCreateInfo(piplineLayout, ySwapChain.renderPass, 0);
	pipelineInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
	pipelineInfo.pStages = shaderStages.data();
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssemblyState;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizationState;
	pipelineInfo.pMultisampleState = &multisampleState;
	pipelineInfo.pColorBlendState = &colorBlendState;
	pipelineInfo.pDepthStencilState = &depthStencilState;
	
	//std::vector<VkDynamicState> dynamicStateEnables = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
	//VkPipelineDynamicStateCreateInfo dynamicState = VulkanInitializers::pipelineDynamicStateCreateInfo(dynamicStateEnables);
	//pipelineInfo.pDynamicState = &dynamicState;
	
	// only if VK_DYNAMIC_STATE_VIEWPORT is not used
	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float) ySwapChain.targetSize.width(); //swapChainExtent.width;
	viewport.height = (float) ySwapChain.targetSize.height(); //swapChainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	viewportState.pViewports = &viewport;

	// only if VK_DYNAMIC_STATE_SCISSOR is not used
	VkRect2D scissor{};
	scissor.offset = {0, 0};
	scissor.extent.width = viewport.width;
    scissor.extent.height = viewport.height;
    viewportState.pScissors = &scissor;
	
	

	rasterizationState.cullMode = VK_CULL_MODE_NONE;
	
	VK_CHECK_RESULT (dev.funcs->vkCreateGraphicsPipelines(dev.vkDev, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipline), "failed to create debug graphics pipeline!");
	
	dev.funcs->vkDestroyShaderModule(dev.vkDev, fragShaderModule, nullptr);
	dev.funcs->vkDestroyShaderModule(dev.vkDev, vertShaderModule, nullptr);
}

void XRay::draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex) {
	
	//this->updateDebugUniformBuffer(yCurrentSwapChainImageIndex);

	// draw the quad, 2 triangles
	dev.funcs->vkCmdBindDescriptorSets(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, piplineLayout, 0, 1, &descriptorSets[yCurrentSwapChainImageIndex], 0, nullptr);
	dev.funcs->vkCmdBindPipeline(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipline);
	dev.funcs->vkCmdDraw(yCmdBuf, 6, 1, 0, 0);
}
