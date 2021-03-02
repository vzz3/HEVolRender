

#include "VulkanRenderer.hpp"
#include <QVulkanFunctions>

VulkanRenderer::VulkanRenderer(VulkanWindow *w)
    :
    //TriangleRenderer(w)
    PlainVulkanRenderer(w)
{
}

void VulkanRenderer::initResources()
{
    //TriangleRenderer::initResources();
	PlainVulkanRenderer::initResources();

    QVulkanInstance *inst = m_window->vulkanInstance();
    //m_devFuncs = inst->deviceFunctions(m_window->device());

    QString info;
    info += QString().asprintf("Number of physical devices: %d\n", m_window->availablePhysicalDevices().count());

    QVulkanFunctions *f = inst->functions();
    VkPhysicalDeviceProperties props;
    f->vkGetPhysicalDeviceProperties(m_window->physicalDevice(), &props);
    info += QString().asprintf("Active physical device name: '%s' version %d.%d.%d\nAPI version %d.%d.%d\n",
                              props.deviceName,
                              VK_VERSION_MAJOR(props.driverVersion), VK_VERSION_MINOR(props.driverVersion),
                              VK_VERSION_PATCH(props.driverVersion),
                              VK_VERSION_MAJOR(props.apiVersion), VK_VERSION_MINOR(props.apiVersion),
                              VK_VERSION_PATCH(props.apiVersion));

    info += QStringLiteral("Supported instance layers:\n");
    for (const QVulkanLayer &layer : inst->supportedLayers())
        info += QString().asprintf("    %s v%u\n", layer.name.constData(), layer.version);
    info += QStringLiteral("Enabled instance layers:\n");
    for (const QByteArray &layer : inst->layers())
        info += QString().asprintf("    %s\n", layer.constData());

    info += QStringLiteral("Supported instance extensions:\n");
    for (const QVulkanExtension &ext : inst->supportedExtensions())
        info += QString().asprintf("    %s v%u\n", ext.name.constData(), ext.version);
    info += QStringLiteral("Enabled instance extensions:\n");
    for (const QByteArray &ext : inst->extensions())
        info += QString().asprintf("    %s\n", ext.constData());
	
	{
		info += QStringLiteral("VkPhysicalDeviceFeatures:\n");
		VkPhysicalDeviceFeatures pDeviceFeatures{};
		inst->functions()->vkGetPhysicalDeviceFeatures(m_window->physicalDevice(), &pDeviceFeatures);
		info += QString().asprintf("    fragmentStoresAndAtomics: %s\n", 		(pDeviceFeatures.fragmentStoresAndAtomics ? "YES" : "NO"));
		info += QString().asprintf("    vertexPipelineStoresAndAtomics: %s\n", 	(pDeviceFeatures.vertexPipelineStoresAndAtomics ? "YES" : "NO"));
	}
	
    info += QString().asprintf("Color format: %u\nDepth-stencil format: %u\n",
                              m_window->colorFormat(), m_window->depthStencilFormat());

    info += QStringLiteral("Supported sample counts:");
    const QVector<int> sampleCounts = m_window->supportedSampleCounts();
    for (int count : sampleCounts)
        info += QLatin1Char(' ') + QString::number(count);
    info += QLatin1Char('\n');
	
	const VkPhysicalDeviceLimits& pdevLimits = props.limits; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkPhysicalDeviceLimits.html
	info += QStringLiteral("VkPhysicalDeviceLimits:\n");
	info += QString().asprintf("    maxFragmentOutputAttachments: %u\n", props.limits.maxFragmentOutputAttachments);
	info += QString().asprintf("    maxColorAttachments: %u    (max. number of FBO color attachments)\n", props.limits.maxColorAttachments);
	info += QString().asprintf("    maxPerStageDescriptorSampledImages: %u\n", props.limits.maxPerStageDescriptorSampledImages);
	info += QString().asprintf("    maxPerStageResources: %u\n", props.limits.maxPerStageResources);
	info += QString().asprintf("    maxDescriptorSetSampledImages: %u\n", props.limits.maxDescriptorSetSampledImages);

    emit static_cast<VulkanWindow *>(m_window)->vulkanInfoReceived(info);
}

void VulkanRenderer::startNextFrame()
{
    //TriangleRenderer::startNextFrame();
    //emit static_cast<VulkanWindow *>(m_window)->frameQueued(int(m_rotation) % 360);
	
	PlainVulkanRenderer::startNextFrame();
}
