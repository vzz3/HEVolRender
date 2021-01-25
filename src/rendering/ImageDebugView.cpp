
#include "ImageDebugView.hpp"

#include "VulkanUtility.hpp"
#include "VulkanInitializers.hpp"
#include "uniform/DebugQuadUniformBufferObject.hpp"
#include <array>


using namespace ppvr::rendering;

ImageDebugView::ImagePanel::ImagePanel()
 	: ImagePanel{ 0, 0.3f, {(-1.0f + 0.05f), (-1.0f + 0.05f)} } {

}

ImageDebugView::ImagePanel::ImagePanel(VkImageView yView, float yScale, glm::vec2 yScreenOffset)
	: view{yView}, scale{yScale}, screenOffset{yScreenOffset} {
	
}


ImageDebugView::ImageDebugView(VulkanDevice& yDev): dev(yDev) {
}

ImageDebugView::~ImageDebugView() {
	this->cleanup();
};

void ImageDebugView::initGpuResources() {
	this->createDescriptorSetLayout();
}

void ImageDebugView::releaseGpuResources() {
	
	this->cleanupDescriptorSetLayout();
}

void ImageDebugView::initSwapChainResources(const VulkanSwapChain& ySwapChain, std::vector<ImagePanel> yImages) {
	images = yImages;
	this->createImageDescriptors(ySwapChain);
	this->createPipeline(ySwapChain);
}

void ImageDebugView::releaseSwapChainResources() {
	this->cleanupPipeline();
	this->cleanupImageDescriptors();
}

void ImageDebugView::cleanup() {
	this->releaseSwapChainResources();
	this->releaseGpuResources();
}

// --- image descriptor ---

void ImageDebugView::cleanupImageDescriptors() {
	for(size_t i=0; i < imgDescs.size(); i++) {
		cleanupDescriptorSet(i);
		cleanupDescriptorPool(i);
		cleanupUniformBuffer(i);
		cleanupSampler(i);
	}
}

void ImageDebugView::createImageDescriptors(const VulkanSwapChain& ySwapChain) {
	imgDescs.resize(images.size());
	
	for(size_t i=0; i < imgDescs.size(); i++) {
		createSampler(i, ySwapChain);
		createUniformBuffer(i, ySwapChain.swapChainImageCount);
		createDescriptorPool(i, ySwapChain.swapChainImageCount);
		createDescriptorSet(i, ySwapChain.swapChainImageCount);
		
		for (size_t swapImgIndex = 0; swapImgIndex<ySwapChain.swapChainImageCount; swapImgIndex++) {
    		this->updateUniformBuffer(i, swapImgIndex);
		}
	}
}


void ImageDebugView::cleanupSampler(size_t yIndex) {
	dev.funcs->vkDestroySampler(dev.vkDev, imgDescs[yIndex].sampler, nullptr);
	imgDescs[yIndex].sampler = VK_NULL_HANDLE;
}

void ImageDebugView::createSampler(size_t yIndex, const VulkanSwapChain& ySwapChain) {
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
	VK_CHECK_RESULT(dev.funcs->vkCreateSampler(dev.vkDev, &samplerInfo, nullptr, &imgDescs[yIndex].sampler), "failed to create sampler!");
}

void ImageDebugView::cleanupUniformBuffer(size_t yIndex) {
	for (size_t i = 0; i < imgDescs[yIndex].uniformBuffers.size(); i++) {
        dev.funcs->vkDestroyBuffer(dev.vkDev, imgDescs[yIndex].uniformBuffers[i], nullptr);
		imgDescs[yIndex].uniformBuffers[i] = VK_NULL_HANDLE;
        dev.funcs->vkFreeMemory(dev.vkDev,  imgDescs[yIndex].uniformBuffersMemory[i], nullptr);
        imgDescs[yIndex].uniformBuffersMemory[i] = VK_NULL_HANDLE;
    }
}

void ImageDebugView::createUniformBuffer(size_t yIndex, size_t ySwapChainImageCount) {
	constexpr VkDeviceSize bufferSize = sizeof(uniform::DebugQuadUniformBufferObject);

    imgDescs[yIndex].uniformBuffers.resize(ySwapChainImageCount);
    imgDescs[yIndex].uniformBuffersMemory.resize(ySwapChainImageCount);
	
    constexpr VkBufferUsageFlags usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	constexpr VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    for (size_t i = 0; i < ySwapChainImageCount; i++) {
        VulkanUtility::createBuffer(dev, bufferSize, usage, properties, imgDescs[yIndex].uniformBuffers[i], imgDescs[yIndex].uniformBuffersMemory[i]);
    }
}

void ImageDebugView::cleanupDescriptorPool(size_t yIndex) {
	dev.funcs->vkDestroyDescriptorPool(dev.vkDev, imgDescs[yIndex].descriptorPool, nullptr);
	imgDescs[yIndex].descriptorPool = VK_NULL_HANDLE;
}

void ImageDebugView::createDescriptorPool(size_t yIndex, size_t ySwapChainImageCount) {
	std::vector<VkDescriptorPoolSize> poolSizes = {
		VulkanInitializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, static_cast<uint32_t>(ySwapChainImageCount)),
		VulkanInitializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, static_cast<uint32_t>(ySwapChainImageCount))
	};
	VkDescriptorPoolCreateInfo poolInfo = VulkanInitializers::descriptorPoolCreateInfo(poolSizes, static_cast<uint32_t>(ySwapChainImageCount));
	VK_CHECK_RESULT (dev.funcs->vkCreateDescriptorPool(dev.vkDev, &poolInfo, nullptr, &imgDescs[yIndex].descriptorPool), "failed to create descriptor pool!");
}

void ImageDebugView::cleanupDescriptorSet(size_t yIndex) {
	// You don't need to explicitly clean up descriptor sets, because they will be automatically freed when the descriptor pool is destroyed.
}

void ImageDebugView::createDescriptorSet(size_t yIndex, size_t ySwapChainImageCount) {
	std::vector<VkDescriptorSetLayout> layouts(ySwapChainImageCount, debugDescriptorSetLayout); // Constructs the container with ySwapChainImageCount copies of debugDescriptorSetLayout.
	VkDescriptorSetAllocateInfo allocInfo = VulkanInitializers::descriptorSetAllocateInfo(
		imgDescs[yIndex].descriptorPool,				// descriptorPool
		layouts.data(),								// pSetLayouts
		static_cast<uint32_t>(ySwapChainImageCount)	// descriptorSetCount
	);
	
	imgDescs[yIndex].descriptorSets.resize(ySwapChainImageCount);
	VK_CHECK_RESULT(dev.funcs->vkAllocateDescriptorSets(dev.vkDev, &allocInfo, imgDescs[yIndex].descriptorSets.data()),  "failed to allocate descriptor sets!");

	for (size_t i = 0; i < ySwapChainImageCount; i++) {
		
		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = imgDescs[yIndex].uniformBuffers[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(uniform::DebugQuadUniformBufferObject);
		
		VkDescriptorImageInfo imageInfo{};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfo.imageView = images[yIndex].view;
		imageInfo.sampler = imgDescs[yIndex].sampler;
	
		std::vector<VkWriteDescriptorSet> writeDescriptorSets =
		{
			// Binding 0 : Vertex shader uniform buffer
			VulkanInitializers::writeDescriptorSet(
				imgDescs[yIndex].descriptorSets[i],			// dstSet
				VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,			// descriptorType
				0,											// dstBinding
				&bufferInfo									// pBufferInfo
			),
			// Binding 1 : Fragment shader texture sampler
			VulkanInitializers::writeDescriptorSet(
				imgDescs[yIndex].descriptorSets[i],			// dstSet
				VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,	// descriptorType
				1,											// dstBinding
				&imageInfo									// pImageInfo
			),
		};
		dev.funcs->vkUpdateDescriptorSets(dev.vkDev, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, nullptr);
	}
}

void ImageDebugView::updateUniformBuffer(size_t yIndex, uint32_t yCurrentSwapChainImageIndex) {
//	static auto startTime = std::chrono::high_resolution_clock::now();
//
//	auto currentTime = std::chrono::high_resolution_clock::now();
//	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
//
//	UniformBufferObject ubo{};
//	ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//	ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//	ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 10.0f);
//	ubo.proj[1][1] *= -1;

	float scale = images[yIndex].scale;// 0.3f;
	float s =  2.0f 		* scale;
	float x = -1.0f  + images[yIndex].screenOffset.x;
	float y = -1.0f  + images[yIndex].screenOffset.y;
	//glm::mat3x3 mm = glm::transpose(glm::mat3x3({ // I write in row major but glm/glsl uses column major
	//			    s,	    s,	    x, // row 0
	//			 0.0f,	 1.0f,	    y, // row 1
	//			 0.0f,	 0.0f,	 1.0f, // row 2
	//		})); // I was not able to get the alignment for vulkan shaders correct.
	glm::mat3x3 mm = glm::transpose(glm::mat3x3({ // I write in row major but glm/glsl uses column major
				    s,	 0.0f,	    x,	 0.0f, // row 0
				 0.0f,	    s,	    y,	 0.0f, // row 1
				 0.0f,	 0.0f,	 1.0f,	 0.0f, // row 2
				 0.0f,	 0.0f,	 0.0f,	 1.0f, // row 3
			}));
	uniform::DebugQuadUniformBufferObject ubo{};
	ubo.model.modelMatrix = mm;

	constexpr VkDeviceSize uboSize = sizeof(uniform::DebugQuadUniformBufferObject);
	void* data;
	dev.funcs->vkMapMemory(dev.vkDev, imgDescs[yIndex].uniformBuffersMemory[yCurrentSwapChainImageIndex], 0, uboSize, 0, &data);
		memcpy(data, &ubo, uboSize);
	dev.funcs->vkUnmapMemory(dev.vkDev, imgDescs[yIndex].uniformBuffersMemory[yCurrentSwapChainImageIndex]);
}

// --- render pipline ---

void ImageDebugView::cleanupDescriptorSetLayout() {
	dev.funcs->vkDestroyDescriptorSetLayout(dev.vkDev, debugDescriptorSetLayout, nullptr);
	debugDescriptorSetLayout = VK_NULL_HANDLE;
}

void ImageDebugView::createDescriptorSetLayout() {
	std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings;
	//VkDescriptorSetLayoutCreateInfo descriptorLayoutInfo;
	//VkPipelineLayoutCreateInfo pipelineLayoutInfo;

	// Binding 0 : Vertex shader uniform buffer
	setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
		VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		VK_SHADER_STAGE_VERTEX_BIT,
		0));
	// Binding 1 : Fragment shader image sampler
	setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
		VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		VK_SHADER_STAGE_FRAGMENT_BIT,
		1));
	// Binding 2 : Fragment shader image sampler
	//setLayoutBindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(
	//	VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
	//	VK_SHADER_STAGE_FRAGMENT_BIT,
	//	2));

	VkDescriptorSetLayoutCreateInfo descriptorLayoutInfo = VulkanInitializers::descriptorSetLayoutCreateInfo(setLayoutBindings);

	VK_CHECK_RESULT (dev.funcs->vkCreateDescriptorSetLayout(dev.vkDev, &descriptorLayoutInfo, nullptr, &debugDescriptorSetLayout), "failed to create descriptor set layout!");
}

void ImageDebugView::cleanupPipeline() {
	dev.funcs->vkDestroyPipeline(dev.vkDev, debugPipline, nullptr);
	debugPipline = VK_NULL_HANDLE;
	
	dev.funcs->vkDestroyPipelineLayout(dev.vkDev, debugPiplineLayout, nullptr);
	debugPiplineLayout = VK_NULL_HANDLE;
}

void ImageDebugView::createPipeline(const VulkanSwapChain& ySwapChain) {
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
	
	VK_CHECK_RESULT (dev.funcs->vkCreateGraphicsPipelines(dev.vkDev, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &debugPipline), "failed to create debug graphics pipeline!");
	
	dev.funcs->vkDestroyShaderModule(dev.vkDev, fragShaderModule, nullptr);
	dev.funcs->vkDestroyShaderModule(dev.vkDev, vertShaderModule, nullptr);
}

void ImageDebugView::draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex) {
	
	//this->updateDebugUniformBuffer(yCurrentSwapChainImageIndex);

	// draw all image panles
	for(size_t i=0; i < imgDescs.size(); i++) {
		dev.funcs->vkCmdBindDescriptorSets(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, debugPiplineLayout, 0, 1, &imgDescs[i].descriptorSets[yCurrentSwapChainImageIndex], 0, nullptr);
		dev.funcs->vkCmdBindPipeline(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, debugPipline);
		dev.funcs->vkCmdDraw(yCmdBuf, 6, 1, 0, 0);
	}
}
