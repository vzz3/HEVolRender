
#include "CubeMap.hpp"

#include "VulkanUtility.hpp"
#include "VulkanInitializers.hpp"
#include <array>
#include "uniform/DebugQuadUniformBufferObject.hpp"


using namespace ppvr::rendering;

CubeMap::CubeMap(VulkanDevice& yDev): dev(yDev), cube(yDev), frontFBO{yDev, false}, offscreenImageView{yDev} {
	fbDepthFormat = VulkanUtility::getSupportedDepthFormat(*dev.vkInstance, dev.vkPhysicalDev);
}
CubeMap::~CubeMap() {
	this->cleanup();
};

void CubeMap::initGpuResources() {
	frontFBO.initGpuResources();
	cube.initGpuResources();
	offscreenImageView.initGpuResources();
}

void CubeMap::releaseGpuResources() {
	offscreenImageView.releaseGpuResources();
	cube.releaseGpuResources();
	frontFBO.releaseGpuResources();
}

void CubeMap::initSwapChainResources(const VulkanSwapChain& ySwapChain) {
	frontFBO.initSwapChainResources(ySwapChain);
	
	offscreenSwappChain.renderPass = frontFBO.getRenderPass();
	offscreenSwappChain.swapChainImageCount = ySwapChain.swapChainImageCount;
	offscreenSwappChain.targetSize = ySwapChain.targetSize;
	
	cube.initSwapChainResources(offscreenSwappChain);
	offscreenImageView.initSwapChainResources(ySwapChain, std::vector<ImageDebugView::ImagePanel>{
		//ImageDebugView::ImagePanel{VkImageView view,						float scale, 	glm::vec2 screenOffset		}
		ImageDebugView::ImagePanel{	 frontFBO.getColorAttachment(0).view,	0.3f,			{0.05f, 0.05f}				}
	});
}

void CubeMap::releaseSwapChainResources() {
	offscreenImageView.releaseSwapChainResources();
	cube.releaseSwapChainResources();
	frontFBO.releaseSwapChainResources();
}

void CubeMap::cleanup() {
	this->releaseSwapChainResources();
	this->releaseGpuResources();
}

void CubeMap::drawOffscreenFrame(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex) {
	VkClearValue clearValues[2];
	clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 0.0f } };
	if(useDepthTest) {
		clearValues[1].depthStencil = { 1.0f, 0 };
	}

	VkRenderPassBeginInfo renderPassBeginInfo = VulkanInitializers::renderPassBeginInfo();
	renderPassBeginInfo.renderPass = frontFBO.getRenderPass();// offscreenPass.renderPass;
	renderPassBeginInfo.framebuffer = frontFBO.getFramebuffer();// offscreenPass.frameBuffer;
	renderPassBeginInfo.renderArea.extent.width = frontFBO.getWidth();// offscreenPass.width;
	renderPassBeginInfo.renderArea.extent.height = frontFBO.getHeight();//offscreenPass.height;
	renderPassBeginInfo.clearValueCount = useDepthTest ? 2 : 1;
	renderPassBeginInfo.pClearValues = clearValues;

	vkCmdBeginRenderPass(yCmdBuf, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	VkViewport viewport = VulkanInitializers::viewport((float)frontFBO.getWidth(), (float)frontFBO.getHeight(), 0.0f, 1.0f);
	vkCmdSetViewport(yCmdBuf, 0, 1, &viewport);

	VkRect2D scissor = VulkanInitializers::rect2D(frontFBO.getWidth(), frontFBO.getHeight(), 0, 0);
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
	offscreenImageView.draw(yCamera, yCmdBuf, yCurrentSwapChainImageIndex);
}
