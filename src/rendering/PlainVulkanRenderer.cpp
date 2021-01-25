

#include "PlainVulkanRenderer.hpp"
#include <QVulkanFunctions>
#include <QFile>

#include "./VulkanUtility.hpp"
#include "./data/VolumeFactory.hpp"

using namespace ppvr::rendering;


PlainVulkanRenderer::PlainVulkanRenderer(QVulkanWindow *w/*, bool msaa = false*/)
    : m_window(w), m_camera(1,1)
{
}

void PlainVulkanRenderer::initResources()
{
    qDebug("PlainVulkanRenderer->initResources()");
	
	m_vulkanInstance.funcs = m_window->vulkanInstance()->functions();

	m_device.vkInstance = &m_vulkanInstance;
	m_device.vkPhysicalDev = m_window->physicalDevice();
	m_device.vkDev = m_window->device();
	m_device.funcs = m_window->vulkanInstance()->deviceFunctions(m_device.vkDev);
	m_device.graphicsCommandPool = m_window->graphicsCommandPool();
	m_device.graphicsQueue = m_window->graphicsQueue();
	
	m_window->vulkanInstance();
	
	roAxis = new Axis(m_device);
	roAxis->initGpuResources();
	
	roCube = new Cube(m_device, VK_CULL_MODE_NONE);
	roCube->initGpuResources();
	
	roFrontCubeMap = new CubeMap(m_device);
	roFrontCubeMap->initGpuResources();
	
	
	//m_volume = new Volume<uint16_t>(4, 4, 4, 16);
	//uint16_t test = (*m_volume)[1][2][3];
	//(*m_volume)[1][2][3] = 18;
	//test = (*m_volume)[1][2][3];
	data::VolumeFactory::createVolume(m_volume, 100);
	
	m_gpuVolume = new data::GpuVolume(&m_device);
	m_gpuVolume->uploadVolume(m_volume);
	roXRay = new XRay(m_device);
	roXRay->initGpuResources();
}

void PlainVulkanRenderer::releaseResources()
{
    qDebug("releaseResources");

	/*
    VkDevice dev = m_window->device();
	
    if (m_pipelineCache) {
        m_devFuncs->vkDestroyPipelineCache(dev, m_pipelineCache, nullptr);
        m_pipelineCache = VK_NULL_HANDLE;
    }

    if (m_descSetLayout) {
        m_devFuncs->vkDestroyDescriptorSetLayout(dev, m_descSetLayout, nullptr);
        m_descSetLayout = VK_NULL_HANDLE;
    }

    if (m_descPool) {
        m_devFuncs->vkDestroyDescriptorPool(dev, m_descPool, nullptr);
        m_descPool = VK_NULL_HANDLE;
    }
	*/
	roXRay->releaseGpuResources();
	delete roXRay;
	roXRay = nullptr;
	
	delete m_gpuVolume;
	m_gpuVolume = nullptr;
	
	//delete m_volume;
	//m_volume = nullptr;
	
	roFrontCubeMap->releaseGpuResources();
	delete roFrontCubeMap;
	roFrontCubeMap = nullptr;
	
	roCube->releaseGpuResources();
	delete roCube;
	roCube = nullptr;
	
	roAxis->releaseGpuResources();
	delete roAxis;
	roAxis = nullptr;
	
}

void PlainVulkanRenderer::initSwapChainResources()
{
    qDebug("PlainVulkanRenderer->initSwapChainResources()");
    m_swapChain.swapChainImageCount = m_window->swapChainImageCount();
	m_swapChain.renderPass = m_window->defaultRenderPass();
	m_swapChain.targetSize = m_window->swapChainImageSize();
	
	m_camera.setViewportSize(m_swapChain.targetSize.width(), m_swapChain.targetSize.height());
	
    roAxis->initSwapChainResources(m_swapChain);
    roCube->initSwapChainResources(m_swapChain);
	roFrontCubeMap->initSwapChainResources(m_swapChain);
	
	roXRay->initSwapChainResources(m_swapChain, m_gpuVolume, roFrontCubeMap->getFrontImageView(), roFrontCubeMap->getBackImageView());
}

void PlainVulkanRenderer::releaseSwapChainResources()
{
    qDebug("PlainVulkanRenderer->releaseSwapChainResources()");
	
	roXRay->releaseSwapChainResources();
	roFrontCubeMap->releaseSwapChainResources();
	roCube->releaseSwapChainResources();
    roAxis->releaseSwapChainResources();
}



void PlainVulkanRenderer::startNextFrame()
{
    VkDevice dev = m_window->device();
    VkCommandBuffer cb = m_window->currentCommandBuffer();
    VkCommandBuffer cmdBuf = cb;
    const QSize sz = m_window->swapChainImageSize();
	
	// ------ offscreen render pass ------
	roFrontCubeMap->drawOffscreenFrame(m_camera, cmdBuf, m_window->currentSwapChainImageIndex());
	
	/*
		Note: Explicit synchronization is not required between the render pass, as this is done implicit via sub pass dependencies
		Is this correct?????
	*/
	
	// ------ main render pass ------
	// --- clear color ---
    VkClearColorValue clearColor = {{ 0, 0, 0, 1 }};
    VkClearDepthStencilValue clearDS = { 1, 0 };
    VkClearValue clearValues[3];
    memset(clearValues, 0, sizeof(clearValues));
    clearValues[0].color = clearValues[2].color = clearColor;
    clearValues[1].depthStencil = clearDS;

	// --- Starting a render pass ---
    VkRenderPassBeginInfo rpBeginInfo;
    memset(&rpBeginInfo, 0, sizeof(rpBeginInfo));
    rpBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpBeginInfo.renderPass = m_window->defaultRenderPass();
    rpBeginInfo.framebuffer = m_window->currentFramebuffer();
    rpBeginInfo.renderArea.extent.width = sz.width();
    rpBeginInfo.renderArea.extent.height = sz.height();
    rpBeginInfo.clearValueCount = m_window->sampleCountFlagBits() > VK_SAMPLE_COUNT_1_BIT ? 3 : 2;
    rpBeginInfo.pClearValues = clearValues;
    //VkCommandBuffer cmdBuf = m_window->currentCommandBuffer();
    m_device.funcs->vkCmdBeginRenderPass(cmdBuf, &rpBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
/*
    quint8 *p;
    VkResult err = m_devFuncs->vkMapMemory(dev, m_bufMem, m_uniformBufInfo[m_window->currentFrame()].offset,
            UNIFORM_DATA_SIZE, 0, reinterpret_cast<void **>(&p));
    if (err != VK_SUCCESS)
        qFatal("Failed to map memory: %d", err);
    QMatrix4x4 m = m_proj;
    m.rotate(m_rotation, 0, 1, 0);
    memcpy(p, m.constData(), 16 * sizeof(float));
    m_devFuncs->vkUnmapMemory(dev, m_bufMem);

    // Not exactly a real animation system, just advance on every frame for now.
    m_rotation += 1.0f;

    m_devFuncs->vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
    m_devFuncs->vkCmdBindDescriptorSets(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelineLayout, 0, 1,
                               &m_descSet[m_window->currentFrame()], 0, nullptr);
    VkDeviceSize vbOffset = 0;
    m_devFuncs->vkCmdBindVertexBuffers(cb, 0, 1, &m_buf, &vbOffset);

    VkViewport viewport;
    viewport.x = viewport.y = 0;
    viewport.width = sz.width();
    viewport.height = sz.height();
    viewport.minDepth = 0;
    viewport.maxDepth = 1;
    m_devFuncs->vkCmdSetViewport(cb, 0, 1, &viewport);

    VkRect2D scissor;
    scissor.offset.x = scissor.offset.y = 0;
    scissor.extent.width = viewport.width;
    scissor.extent.height = viewport.height;
    m_devFuncs->vkCmdSetScissor(cb, 0, 1, &scissor);

    m_devFuncs->vkCmdDraw(cb, 3, 1, 0, 0);
	*/
	
	
	
	//roCube->draw(m_camera, cmdBuf, m_window->currentSwapChainImageIndex());
	roXRay->draw(m_camera, cmdBuf, m_window->currentSwapChainImageIndex());
	roAxis->draw(m_camera, cmdBuf, m_window->currentSwapChainImageIndex());
	roFrontCubeMap->draw(m_camera, cmdBuf, m_window->currentSwapChainImageIndex());
	
	
	
    m_device.funcs->vkCmdEndRenderPass(cmdBuf);

    m_window->frameReady();
    m_window->requestUpdate(); // render continuously, throttled by the presentation rate
}
