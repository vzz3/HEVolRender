
#include "Axis.hpp"

#include "VulkanUtility.hpp"
#include "vertex/ColoredVertex.hpp"


using namespace ppvr::rendering;

Axis::Axis(VulkanDevice& yDev): dev(yDev) {
}
Axis::~Axis() {
	this->cleanup();
};

void Axis::initGpuResources() {
	this->createVertexBuffer();
	this->createDescriptorSetLayout();
}
void Axis::releaseGpuResources() {
	this->cleanupDescriptorSetLayout();
	this->cleanupVertexBuffer();
}

void Axis::initSwapChainResources(const VulkanSwapChain& ySwapChain) {
	this->createUniformBuffers(ySwapChain.swapChainImageCount);
    this->createDescriptorPool(ySwapChain.swapChainImageCount);
	this->createDescriptorSets(ySwapChain.swapChainImageCount);
	this->createGraphicsPipeline(ySwapChain.renderPass, ySwapChain.targetSize);
}

void Axis::releaseSwapChainResources() {
	this->cleanupGraphicsPipeline();
	this->cleanupDescriptorSets();
	this->cleanupDescriptorPool();
	this->cleanupUniformBuffers();
}

void Axis::cleanup() {
	this->releaseSwapChainResources();
	this->releaseGpuResources();
}



void Axis::cleanupVertexBuffer() {
	dev.funcs->vkDestroyBuffer(dev.vkDev, vertexBuffer, nullptr);
	vertexBuffer = VK_NULL_HANDLE;
	
	dev.funcs->vkFreeMemory(dev.vkDev, vertexBufferMemory, nullptr);
	vertexBufferMemory = VK_NULL_HANDLE;
}

void Axis::createVertexBuffer() {
	constexpr bool useStagingBuffer = true;
	
	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
	
	if(!useStagingBuffer) {
		// shader buffer can be used from CPU und GPU
		constexpr VkBufferUsageFlags usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		constexpr VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		VulkanUtility::createBuffer(dev, bufferSize, usage, properties, vertexBuffer, vertexBufferMemory);
		
		// --- Filling the vertex buffer ---
		void* data;
		dev.funcs->vkMapMemory(dev.vkDev, vertexBufferMemory, 0, bufferSize, 0, &data);
			memcpy(data, vertices.data(), (size_t) bufferSize);
		dev.funcs->vkUnmapMemory(dev.vkDev, vertexBufferMemory);
	} else {
		// use a CPU buffer and copy that one to a GPU only buffer
		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		constexpr VkBufferUsageFlags stagingBufferUsage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		constexpr VkMemoryPropertyFlags stagingBufferProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		VulkanUtility::createBuffer(dev, bufferSize, stagingBufferUsage, stagingBufferProperties, stagingBuffer, stagingBufferMemory);

		void* data;
		dev.funcs->vkMapMemory(dev.vkDev, stagingBufferMemory, 0, bufferSize, 0, &data);
			memcpy(data, vertices.data(), (size_t) bufferSize);
		dev.funcs->vkUnmapMemory(dev.vkDev, stagingBufferMemory);

		constexpr VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		constexpr VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		VulkanUtility::createBuffer(dev, bufferSize, usage, properties, vertexBuffer, vertexBufferMemory);
		
		VulkanUtility::copyBuffer(dev, stagingBuffer, vertexBuffer, bufferSize);
		
		dev.funcs->vkDestroyBuffer(dev.vkDev, stagingBuffer, nullptr);
    	dev.funcs->vkFreeMemory(dev.vkDev, stagingBufferMemory, nullptr);
	}
	
}

void Axis::cleanupUniformBuffers() {
	for (size_t i = 0; i < uniformBuffers.size(); i++) {
        dev.funcs->vkDestroyBuffer(dev.vkDev, uniformBuffers[i], nullptr);
		uniformBuffers[i] = VK_NULL_HANDLE;
        dev.funcs->vkFreeMemory(dev.vkDev, uniformBuffersMemory[i], nullptr);
        uniformBuffersMemory[i] = VK_NULL_HANDLE;
    }
}

void Axis::createUniformBuffers(size_t ySwapChainImageCount) {
	constexpr VkDeviceSize bufferSize = sizeof(Camera::CameraUniformBufferObject);

    uniformBuffers.resize(ySwapChainImageCount);
    uniformBuffersMemory.resize(ySwapChainImageCount);
	
    constexpr VkBufferUsageFlags usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	constexpr VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    for (size_t i = 0; i < ySwapChainImageCount; i++) {
        VulkanUtility::createBuffer(dev, bufferSize, usage, properties, uniformBuffers[i], uniformBuffersMemory[i]);
    }
}

void Axis::cleanupDescriptorPool() {
	dev.funcs->vkDestroyDescriptorPool(dev.vkDev, descriptorPool, nullptr);
	descriptorPool = VK_NULL_HANDLE;
}

void Axis::createDescriptorPool(size_t ySwapChainImageCount) {
	VkDescriptorPoolSize poolSize{};
	poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSize.descriptorCount = static_cast<uint32_t>(ySwapChainImageCount);

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = 1;
	poolInfo.pPoolSizes = &poolSize;
	poolInfo.maxSets = static_cast<uint32_t>(ySwapChainImageCount);

	if (vkCreateDescriptorPool(dev.vkDev, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

void Axis::cleanupDescriptorSets() {
	// You don't need to explicitly clean up descriptor sets, because they will be automatically freed when the descriptor pool is destroyed.
}

void Axis::createDescriptorSets(size_t ySwapChainImageCount) {
	std::vector<VkDescriptorSetLayout> layouts(ySwapChainImageCount, descriptorSetLayout);
	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(ySwapChainImageCount);
	allocInfo.pSetLayouts = layouts.data();

	descriptorSets.resize(ySwapChainImageCount);
	if (dev.funcs->vkAllocateDescriptorSets(dev.vkDev, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < ySwapChainImageCount; i++) {
		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = uniformBuffers[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(Camera::CameraUniformBufferObject);

		VkWriteDescriptorSet descriptorWrite{};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = descriptorSets[i];
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = &bufferInfo;
		descriptorWrite.pImageInfo = nullptr; // Optional
		descriptorWrite.pTexelBufferView = nullptr; // Optional

		dev.funcs->vkUpdateDescriptorSets(dev.vkDev, 1, &descriptorWrite, 0, nullptr);
	}
}

void Axis::cleanupDescriptorSetLayout() {
	dev.funcs->vkDestroyDescriptorSetLayout(dev.vkDev, descriptorSetLayout, nullptr);
	descriptorSetLayout = VK_NULL_HANDLE;
}

void Axis::createDescriptorSetLayout() {
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0; // binding number in shader (layout(binding = 0) uniform...)
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1; // specifies the number of values in the array
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT; // shader type that uses the uniform (VK_SHADER_STAGE_ALL_GRAPHICS for all shaders)
	uboLayoutBinding.pImmutableSamplers = nullptr; // only relevant for image sampling related descriptors
	
	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 1;
	layoutInfo.pBindings = &uboLayoutBinding;

	if (dev.funcs->vkCreateDescriptorSetLayout(dev.vkDev, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}

void Axis::cleanupGraphicsPipeline() {
	dev.funcs->vkDestroyPipeline(dev.vkDev, graphicsPipeline, nullptr);
	graphicsPipeline = VK_NULL_HANDLE;
	
	dev.funcs->vkDestroyPipelineLayout(dev.vkDev, pipelineLayout, nullptr);
	pipelineLayout = VK_NULL_HANDLE;
	//vkDestroyRenderPass(device, renderPass, nullptr);
}

void Axis::createGraphicsPipeline(const VkRenderPass& yRenderPass, const QSize& yTargetSize) {
	// --- setup shaders ---
	VkShaderModule vertShaderModule = VulkanUtility::createShader(this->dev, QStringLiteral("shaders/axis.vert.spv"));
	VkShaderModule fragShaderModule = VulkanUtility::createShader(this->dev, QStringLiteral("shaders/axis.frag.spv"));

	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

	// --- vertex shader input ---
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	auto bindingDescription = vertex::ColoredVertex::getBindingDescription();
	auto attributeDescriptions = vertex::ColoredVertex::getAttributeDescriptions();

	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST; // VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float) yTargetSize.width(); //swapChainExtent.width;
	viewport.height = (float) yTargetSize.height(); //swapChainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor{};
	scissor.offset = {0, 0};
	scissor.extent.width = viewport.width;
    scissor.extent.height = viewport.height;

	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	//pipelineLayoutInfo.setLayoutCount = 0;
	//pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;

	if (dev.funcs->vkCreatePipelineLayout(dev.vkDev, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}
	
	VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    memset(&depthStencilInfo, 0, sizeof(depthStencilInfo));
    depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilInfo.depthTestEnable = VK_TRUE;
    depthStencilInfo.depthWriteEnable = VK_TRUE;
    depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;

	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDepthStencilState = &depthStencilInfo;
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.renderPass = yRenderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	if (dev.funcs->vkCreateGraphicsPipelines(dev.vkDev, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}

	dev.funcs->vkDestroyShaderModule(dev.vkDev, fragShaderModule, nullptr);
	dev.funcs->vkDestroyShaderModule(dev.vkDev, vertShaderModule, nullptr);
}

void Axis::updateUniformBuffer(const Camera& yCamera, uint32_t yCurrentSwapChainImageIndex) {
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

	constexpr VkDeviceSize uboSize = sizeof(Camera::CameraUniformBufferObject);
	void* data;
	dev.funcs->vkMapMemory(dev.vkDev, uniformBuffersMemory[yCurrentSwapChainImageIndex], 0, uboSize, 0, &data);
		memcpy(data, &yCamera.getFinalData(), uboSize);
	dev.funcs->vkUnmapMemory(dev.vkDev, uniformBuffersMemory[yCurrentSwapChainImageIndex]);
}

void Axis::draw(const Camera& yCamera,  VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex) {
	this->updateUniformBuffer(yCamera, yCurrentSwapChainImageIndex);

	dev.funcs->vkCmdBindPipeline(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
    //dev.funcs->vkCmdBindDescriptorSets(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1, &m_descSet[m_window->currentFrame()], 0, nullptr);
    VkBuffer vertexBuffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    dev.funcs->vkCmdBindVertexBuffers(yCmdBuf, 0, 1, vertexBuffers, offsets);
	dev.funcs->vkCmdBindDescriptorSets(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[yCurrentSwapChainImageIndex], 0, nullptr);
    dev.funcs->vkCmdDraw(yCmdBuf, static_cast<uint32_t>(vertices.size()), 1, 0, 0);
}
