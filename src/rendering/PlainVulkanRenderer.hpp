

#include <QVulkanWindow>
#include <QVulkanWindowRenderer>

#include "./VulkanInstance.hpp"
#include "./VulkanDevice.hpp"
#include "./Axis.hpp"
#include "./Cube.hpp"
#include "./CubeMap.hpp"

namespace ppvr {
	namespace rendering {
		class PlainVulkanRenderer : public QVulkanWindowRenderer {
			public:
				PlainVulkanRenderer(QVulkanWindow *w/*, bool msaa = false*/);

				void initResources() override;
				void releaseResources() override;
				void initSwapChainResources() override;
				void releaseSwapChainResources() override;
				

				void startNextFrame() override;


				Camera& camera() {
					return m_camera;
				}
			
			protected:
				Camera m_camera;
				Axis* roAxis = nullptr;
				Cube* roCube = nullptr;
				CubeMap* roFrontCubeMap = nullptr;

				QVulkanWindow *m_window;
				VulkanInstance m_vulkanInstance;
				VulkanDevice m_device;
				VulkanSwapChain m_swapChain;
				/*
				QVulkanDeviceFunctions *m_devFuncs;

				VkDeviceMemory m_bufMem = VK_NULL_HANDLE;
				VkBuffer m_buf = VK_NULL_HANDLE;
				VkDescriptorBufferInfo m_uniformBufInfo[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];

				VkDescriptorPool m_descPool = VK_NULL_HANDLE;
				VkDescriptorSetLayout m_descSetLayout = VK_NULL_HANDLE;
				VkDescriptorSet m_descSet[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];

				VkPipelineCache m_pipelineCache = VK_NULL_HANDLE;
				VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
				VkPipeline m_pipeline = VK_NULL_HANDLE;

				QMatrix4x4 m_proj;
				float m_rotation = 0.0f;
				*/
		};
	}
}
