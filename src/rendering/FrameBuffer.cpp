
#include "FrameBuffer.hpp"

#include "VulkanUtility.hpp"
#include "VulkanInitializers.hpp"
#include <array>
#include "uniform/DebugQuadUniformBufferObject.hpp"


using namespace ppvr::rendering;


//FrameBuffer::ImageDefinition::ImageDefinition(VkFormat yFormat)
//	: FrameBuffer::ImageDefinition{
//		yFormat,
//		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
//	}
//{
//
//}

FrameBuffer::ImageDefinition::ImageDefinition(VkFormat yFormat, VkImageLayout yFinalLayout)
	: format{yFormat}, finalLayout{yFinalLayout}
{
	
}




FrameBuffer::FrameBuffer(VulkanDevice& yDev, bool yUseDepth)
	: FrameBuffer{
		yDev,
		yUseDepth,
		std::vector<ImageDefinition>{VK_FORMAT_R8G8B8A8_UNORM}
	}
{
	
}

FrameBuffer::FrameBuffer(VulkanDevice& yDev, bool yUseDepth, const std::vector<ImageDefinition>& yFbColorFormats)
	: FrameBuffer{
		yDev,
		yUseDepth,
		yFbColorFormats,
		VulkanUtility::getSupportedDepthFormat(*yDev.vkInstance, yDev.vkPhysicalDev)
	} {
	
}

FrameBuffer::FrameBuffer(VulkanDevice& yDev, bool yUseDepth, const std::vector<ImageDefinition>& yFbColorFormats, VkFormat yFbDepthFormat)
 	: dev{yDev}, useDepthTest{yUseDepth}, fbColorFormats{yFbColorFormats}, fbDepthFormat{yFbDepthFormat} {

	colors.resize(fbColorFormats.size());
}

FrameBuffer::~FrameBuffer() {
	this->cleanup();
};

void FrameBuffer::initGpuResources() {
	
}

void FrameBuffer::releaseGpuResources() {
}

void FrameBuffer::initSwapChainResources(const QSize& yTargetSize) { //QSize targetSize
	width = yTargetSize.width();
	height = yTargetSize.height();

	this->createColorAttachments();
	//this->createSampler(ySwapChain);
	if(useDepthTest) {
		this->createDepthAttachment();
	}
	this->createRenderPass();
	this->createFrameBuffer();
}

void FrameBuffer::releaseSwapChainResources() {
	this->cleanupFrameBuffer();
	this->cleanupRenderPass();
	if(useDepthTest) {
		this->cleanupDepthAttachment();
	}
	//this->cleanupSampler();
	this->cleanupColorAttachments();
}

void FrameBuffer::cleanup() {
	this->releaseSwapChainResources();
	this->releaseGpuResources();
}

void FrameBuffer::cleanupColorAttachments() {
	for(size_t i=0; i < colors.size(); i++) {
		this->cleanupColorAttachment(i);
	}
}

void FrameBuffer::createColorAttachments() {
	for(size_t i=0; i < fbColorFormats.size(); i++) {
		this->createColorAttachment(i);
	}
}

void FrameBuffer::cleanupColorAttachment(size_t yIndex) {
	// Color attachment
	dev.funcs->vkDestroyImageView(dev.vkDev, colors[yIndex].view, nullptr);
	colors[yIndex].view = VK_NULL_HANDLE;
	dev.funcs->vkDestroyImage(dev.vkDev, colors[yIndex].image, nullptr);
	colors[yIndex].image = VK_NULL_HANDLE;
	dev.funcs->vkFreeMemory(dev.vkDev, colors[yIndex].mem, nullptr);
	colors[yIndex].mem = VK_NULL_HANDLE;
}

void FrameBuffer::createColorAttachment(size_t yIndex) {
	// Color attachment
	VkImageCreateInfo image = VulkanInitializers::imageCreateInfo();
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = this->fbColorFormats[yIndex].format;
	image.extent.width = this->width;
	image.extent.height = this->height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	// We will sample directly from the color attachment
	image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	if(this->fbColorFormats[yIndex].finalLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
		image.usage = image.usage | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
	}

	VK_CHECK_RESULT(dev.funcs->vkCreateImage(dev.vkDev, &image, nullptr, &colors[yIndex].image), "failed to create color image for offscreen frame buffer!");

	VkMemoryRequirements memReqs;
	dev.funcs->vkGetImageMemoryRequirements(dev.vkDev, colors[yIndex].image, &memReqs);

	VkMemoryAllocateInfo memAlloc = VulkanInitializers::memoryAllocateInfo();
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = VulkanUtility::findMemoryType(dev, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK_RESULT(dev.funcs->vkAllocateMemory(dev.vkDev, &memAlloc, nullptr, &colors[yIndex].mem), "failed to allocate memory for off screen frame buffer color image!");
	VK_CHECK_RESULT(dev.funcs->vkBindImageMemory(dev.vkDev, colors[yIndex].image, colors[yIndex].mem, 0), "failed to bind off screen frame buffer color image!");

	VkImageViewCreateInfo colorImageView = VulkanInitializers::imageViewCreateInfo();
	colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	colorImageView.format = this->fbColorFormats[yIndex].format;
	colorImageView.subresourceRange = {};
	colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorImageView.subresourceRange.baseMipLevel = 0;
	colorImageView.subresourceRange.levelCount = 1;
	colorImageView.subresourceRange.baseArrayLayer = 0;
	colorImageView.subresourceRange.layerCount = 1;
	colorImageView.image = colors[yIndex].image;
	VK_CHECK_RESULT(dev.funcs->vkCreateImageView(dev.vkDev, &colorImageView, nullptr, &colors[yIndex].view), "failed to bind off screen color image view!");
}

void FrameBuffer::cleanupDepthAttachment() {
	dev.funcs->vkDestroyImageView(dev.vkDev, depth.view, nullptr);
	depth.view = VK_NULL_HANDLE;
	dev.funcs->vkDestroyImage(dev.vkDev, depth.image, nullptr);
	depth.image = VK_NULL_HANDLE;
	dev.funcs->vkFreeMemory(dev.vkDev, depth.mem, nullptr);
	depth.mem = VK_NULL_HANDLE;
}

void FrameBuffer::createDepthAttachment() {
	// Find a suitable depth format
	VkFormat fbDepthFormat = VulkanUtility::getSupportedDepthFormat(*dev.vkInstance, dev.vkPhysicalDev);

	// Depth stencil attachment
	VkImageCreateInfo image = VulkanInitializers::imageCreateInfo();
	image.imageType = VK_IMAGE_TYPE_2D;
	image.format = fbDepthFormat;
	image.extent.width = width;
	image.extent.height = height;
	image.extent.depth = 1;
	image.mipLevels = 1;
	image.arrayLayers = 1;
	image.samples = VK_SAMPLE_COUNT_1_BIT;
	image.tiling = VK_IMAGE_TILING_OPTIMAL;
	image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

	VK_CHECK_RESULT(dev.funcs->vkCreateImage(dev.vkDev, &image, nullptr, &this->depth.image), "failed to create depth image for offscreen frame buffer!");

	VkMemoryRequirements memReqs;
	dev.funcs->vkGetImageMemoryRequirements(dev.vkDev, this->depth.image, &memReqs);

	VkMemoryAllocateInfo memAlloc = VulkanInitializers::memoryAllocateInfo();
	memAlloc.allocationSize = memReqs.size;
	memAlloc.memoryTypeIndex = VulkanUtility::findMemoryType(dev, memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	VK_CHECK_RESULT(dev.funcs->vkAllocateMemory(dev.vkDev, &memAlloc, nullptr, &this->depth.mem), "failed to allocate memory for off screen frame buffer depth image!");
	VK_CHECK_RESULT(dev.funcs->vkBindImageMemory(dev.vkDev, this->depth.image, this->depth.mem, 0), "failed to bind off screen frame buffer depth image!");

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
	depthStencilView.image = this->depth.image;
	VK_CHECK_RESULT(dev.funcs->vkCreateImageView(dev.vkDev, &depthStencilView, nullptr, &this->depth.view), "failed to bind off screen depth image view!");
}

void FrameBuffer::cleanupRenderPass() {
	dev.funcs->vkDestroyRenderPass(dev.vkDev, renderPass, nullptr);
	renderPass = VK_NULL_HANDLE;
}

void FrameBuffer::createRenderPass() {
	// Create a separate render pass for the offscreen rendering as it may differ from the one used for scene rendering

	size_t i;
	size_t cCount = colorAttachmentCount();
	size_t aCount = attachmentCount();
	
	std::vector<VkAttachmentDescription> attchmentDescriptions{aCount};
	std::vector<VkAttachmentReference> colorReferences{cCount};
	VkAttachmentReference depthReference;
	// Color attachment
	for(i=0; i < cCount; i++) {
		attchmentDescriptions[i].format = fbColorFormats[i].format;
		attchmentDescriptions[i].samples = VK_SAMPLE_COUNT_1_BIT;
		attchmentDescriptions[i].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attchmentDescriptions[i].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attchmentDescriptions[i].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attchmentDescriptions[i].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attchmentDescriptions[i].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attchmentDescriptions[i].finalLayout = fbColorFormats[i].finalLayout; //VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL; VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
		
		colorReferences[i].attachment = i;
		colorReferences[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	}
	// Depth attachment
	if(useDepthTest) {
		attchmentDescriptions[i].format = fbDepthFormat;
		attchmentDescriptions[i].samples = VK_SAMPLE_COUNT_1_BIT;
		attchmentDescriptions[i].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attchmentDescriptions[i].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attchmentDescriptions[i].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attchmentDescriptions[i].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attchmentDescriptions[i].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attchmentDescriptions[i].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		
		depthReference.attachment = i;
		depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	}
	

	VkSubpassDescription subpassDescription = {};
	subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpassDescription.colorAttachmentCount = colorAttachmentCount();
	subpassDescription.pColorAttachments = colorReferences.data();
	if(useDepthTest) {
		subpassDescription.pDepthStencilAttachment = &depthReference;
	}
	
	// Use subpass dependencies for layout transitions
	std::vector<VkSubpassDependency> dependencies{aCount};

	for(i=0; i < cCount; i++) {
		dependencies[i].srcSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[i].dstSubpass = 0;
		dependencies[i].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		dependencies[i].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependencies[i].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
		dependencies[i].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		dependencies[i].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
	}
	if(useDepthTest) {
		dependencies[i].srcSubpass = 0;
		dependencies[i].dstSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[i].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependencies[i].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		dependencies[i].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		dependencies[i].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		dependencies[i].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
	}
	
	// Create the actual renderpass
	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = static_cast<uint32_t>(attchmentDescriptions.size());
	renderPassInfo.pAttachments = attchmentDescriptions.data();
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpassDescription;
	renderPassInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
	renderPassInfo.pDependencies = dependencies.data();

	VK_CHECK_RESULT(dev.funcs->vkCreateRenderPass(dev.vkDev, &renderPassInfo, nullptr, &this->renderPass), "failed to create offscreen render path!");
}

void FrameBuffer::cleanupFrameBuffer() {
	dev.funcs->vkDestroyFramebuffer(dev.vkDev, frameBuffer, nullptr);
	frameBuffer = VK_NULL_HANDLE;
}

void FrameBuffer::createFrameBuffer() {
	size_t i;
	size_t cCount = colorAttachmentCount();
	size_t aCount = attachmentCount();
	
	std::vector<VkImageView> attachments{aCount};
	for(i=0; i < cCount; i++) {
		attachments[i] = colors[i].view;
	}
	if(useDepthTest) {
		attachments[i] = depth.view;
	}
	VkFramebufferCreateInfo fbufCreateInfo = VulkanInitializers::framebufferCreateInfo();
	fbufCreateInfo.renderPass = renderPass;
	fbufCreateInfo.attachmentCount = aCount;
	fbufCreateInfo.pAttachments = attachments.data();
	fbufCreateInfo.width = width;
	fbufCreateInfo.height = height;
	fbufCreateInfo.layers = 1;

	VK_CHECK_RESULT(dev.funcs->vkCreateFramebuffer(dev.vkDev, &fbufCreateInfo, nullptr, &frameBuffer), "failed to create offscreen renderPass!");

	// Fill a descriptor for later use in a descriptor set
	//descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	//descriptor.imageView = offscreenPass.color.view;
	//descriptor.sampler = offscreenPass.sampler;
}


//void FrameBuffer::cleanupSampler() {
//	dev.funcs->vkDestroySampler(dev.vkDev, offscreenPass.sampler, nullptr);
//	offscreenPass.sampler = VK_NULL_HANDLE;
//}
//
//void FrameBuffer::createSampler(const VulkanSwapChain& ySwapChain) {
//	// Create sampler to sample from the attachment in the fragment shader
//	VkSamplerCreateInfo samplerInfo = VulkanInitializers::samplerCreateInfo();
//	samplerInfo.magFilter = VK_FILTER_LINEAR;
//	samplerInfo.minFilter = VK_FILTER_LINEAR;
//	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
//	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
//	samplerInfo.addressModeV = samplerInfo.addressModeU;
//	samplerInfo.addressModeW = samplerInfo.addressModeU;
//	samplerInfo.mipLodBias = 0.0f;
//	samplerInfo.maxAnisotropy = 1.0f;
//	samplerInfo.minLod = 0.0f;
//	samplerInfo.maxLod = 1.0f;
//	samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
//	VK_CHECK_RESULT(dev.funcs->vkCreateSampler(dev.vkDev, &samplerInfo, nullptr, &offscreenPass.sampler), "failed to create sampler!");
//}

int32_t FrameBuffer::getWidth() const {
	return width;
}

int32_t FrameBuffer::getHeight() const {
	return height;
}

size_t FrameBuffer::colorAttachmentCount() const {
	return fbColorFormats.size();
}

size_t FrameBuffer::attachmentCount() const {
	return fbColorFormats.size() + (useDepthTest ? 1 : 0);
}

VkFormat FrameBuffer::getColorImageFormat(size_t yIndex) const {
	return getColorImageDefinition(yIndex).format;
}

VkImageLayout FrameBuffer::getColorImageFinalLayout(size_t yIndex) const {
	return getColorImageDefinition(yIndex).finalLayout;
}

const FrameBuffer::FrameBufferAttachment& FrameBuffer::getColorAttachment(size_t yIndex) const {
	return colors[yIndex];
}

const FrameBuffer::FrameBufferAttachment& FrameBuffer::getDepthAttachment() const {
	if(!useDepthTest) {
		throw std::runtime_error("FrameBuffer does not have a depth attachement");
	}
	return depth;
}

const VkRenderPass& FrameBuffer::getRenderPass() const {
	return renderPass;
}

const VkFramebuffer& FrameBuffer::getFramebuffer() const {
	return frameBuffer;
}

//void FrameBuffer::draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex) {
//
//    // Display the offscreen render target
//	dev.funcs->vkCmdBindDescriptorSets(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, debugPiplineLayout, 0, 1, &debugDescriptorSets[yCurrentSwapChainImageIndex], 0, nullptr);
//	dev.funcs->vkCmdBindPipeline(yCmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, debugPipline);
//	dev.funcs->vkCmdDraw(yCmdBuf, 6, 1, 0, 0);
//}
