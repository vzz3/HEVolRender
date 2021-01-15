
#include "CubeMap.hpp"

#include "VulkanUtility.hpp"
#include "VulkanInitializers.hpp"
#include <array>
#include "uniform/DebugQuadUniformBufferObject.hpp"


using namespace ppvr::rendering;

CubeMap::CubeMap(VulkanDevice& yDev)
	: dev(yDev),
		frontCube(yDev, VK_CULL_MODE_BACK_BIT),
		backCube(yDev, VK_CULL_MODE_FRONT_BIT),
		frontFBO{yDev, false, std::vector<VkFormat>{VK_FORMAT_R16G16B16A16_UNORM}}, // I do not need t A channel but Mac OS do not support VK_FORMAT_R16G16B16_UNORM (http://vulkan.gpuinfo.org/listformats.php?platform=macos)
		backFBO{yDev, false},
		offscreenImageView{yDev} {
	//fbDepthFormat = VulkanUtility::getSupportedDepthFormat(*dev.vkInstance, dev.vkPhysicalDev);
}
CubeMap::~CubeMap() {
	this->cleanup();
};

void CubeMap::initGpuResources() {
	frontFBO.initGpuResources();
	backFBO.initGpuResources();
	
	frontCube.initGpuResources();
	backCube.initGpuResources();
	
	offscreenImageView.initGpuResources();
}

void CubeMap::releaseGpuResources() {
	offscreenImageView.releaseGpuResources();
	
	backCube.releaseGpuResources();
	frontCube.releaseGpuResources();
	
	backFBO.releaseGpuResources();
	frontFBO.releaseGpuResources();
}

void CubeMap::initSwapChainResources(const VulkanSwapChain& ySwapChain) {
	frontFBO.initSwapChainResources(ySwapChain);
	backFBO.initSwapChainResources(ySwapChain);
	
	frontSwappChain.renderPass = frontFBO.getRenderPass();
	frontSwappChain.swapChainImageCount = ySwapChain.swapChainImageCount;
	frontSwappChain.targetSize = ySwapChain.targetSize;
	frontCube.initSwapChainResources(frontSwappChain);
	
	backSwappChain.renderPass = backFBO.getRenderPass();
	backSwappChain.swapChainImageCount = ySwapChain.swapChainImageCount;
	backSwappChain.targetSize = ySwapChain.targetSize;
	backCube.initSwapChainResources(backSwappChain);
	
	offscreenImageView.initSwapChainResources(ySwapChain, std::vector<ImageDebugView::ImagePanel>{
		//ImageDebugView::ImagePanel{VkImageView view,						float scale, 	glm::vec2 screenOffset		}
		ImageDebugView::ImagePanel{	 getFrontImageView(),	0.3f,			{0.05f      , 0.05f}		},
		ImageDebugView::ImagePanel{	 getBackImageView() ,	0.3f,			{2.00f -0.65, 0.05f}		}
	});
}

void CubeMap::releaseSwapChainResources() {
	offscreenImageView.releaseSwapChainResources();
	
	backCube.releaseSwapChainResources();
	frontCube.releaseSwapChainResources();
	
	backFBO.releaseSwapChainResources();
	frontFBO.releaseSwapChainResources();
}

void CubeMap::cleanup() {
	this->releaseSwapChainResources();
	this->releaseGpuResources();
}



void CubeMap::drawCubeFace(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex, Cube& yCube, FrameBuffer &yFBO) {
	VkClearValue clearValues[2];
	clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 0.0f } };
	if(useDepthTest) {
		clearValues[1].depthStencil = { 1.0f, 0 };
	}

	VkRenderPassBeginInfo renderPassBeginInfo = VulkanInitializers::renderPassBeginInfo();
	renderPassBeginInfo.renderPass = yFBO.getRenderPass();// offscreenPass.renderPass;
	renderPassBeginInfo.framebuffer = yFBO.getFramebuffer();// offscreenPass.frameBuffer;
	renderPassBeginInfo.renderArea.extent.width = yFBO.getWidth();// offscreenPass.width;
	renderPassBeginInfo.renderArea.extent.height = yFBO.getHeight();//offscreenPass.height;
	renderPassBeginInfo.clearValueCount = useDepthTest ? 2 : 1;
	renderPassBeginInfo.pClearValues = clearValues;

	dev.funcs->vkCmdBeginRenderPass(yCmdBuf, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	// für dynamische piplines
	//VkViewport viewport = VulkanInitializers::viewport((float)frontFBO.getWidth(), (float)frontFBO.getHeight(), 0.0f, 1.0f);
	//vkCmdSetViewport(yCmdBuf, 0, 1, &viewport);

	//VkRect2D scissor = VulkanInitializers::rect2D(frontFBO.getWidth(), frontFBO.getHeight(), 0, 0);
	//vkCmdSetScissor(yCmdBuf, 0, 1, &scissor);

	//VkDeviceSize offsets[1] = { 0 };

	yCube.draw(yCamera, yCmdBuf, yCurrentSwapChainImageIndex);

	dev.funcs->vkCmdEndRenderPass(yCmdBuf);
}

void CubeMap::drawOffscreenFrame(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex) {
	
	this->drawCubeFace(yCamera, yCmdBuf, yCurrentSwapChainImageIndex, frontCube, frontFBO);
	this->drawCubeFace(yCamera, yCmdBuf, yCurrentSwapChainImageIndex, backCube, backFBO);
}

void CubeMap::draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex) {	
	offscreenImageView.draw(yCamera, yCmdBuf, yCurrentSwapChainImageIndex);
}

VkImageView CubeMap::getFrontImageView() const {
	return frontFBO.getColorAttachment(0).view;
}

VkImageView CubeMap::getBackImageView() const {
	return backFBO.getColorAttachment(0).view;
}
