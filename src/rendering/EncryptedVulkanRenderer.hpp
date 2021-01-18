

#include <QVulkanWindow>
#include <QVulkanWindowRenderer>

#include "./VulkanInstance.hpp"
#include "./VulkanDevice.hpp"
#include "./Axis.hpp"
#include "./Cube.hpp"
#include "./CubeMap.hpp"
#include "./data/Volume.hpp"
#include "./data/GpuVolume.hpp"
#include "./EncryptedXRay.hpp"
#include "./FrameBuffer.hpp"
#include <QImage>

namespace ppvr {
	namespace rendering {
		class EncryptedVulkanRenderer {
			public:
				EncryptedVulkanRenderer(QVulkanInstance* yQVulkanInstance, VkPhysicalDevice yVkPhysicalDevice, const Camera& yCamera, const bool yBigIntTest = false);
				~EncryptedVulkanRenderer();
			
			private:
				void cleanup();
			
			
				void initVulkan(QVulkanInstance* yQVulkanInstance, VkPhysicalDevice yVkPhysicalDevice );
				void cleanupVulakn();
			
				void initGpuResources();
				void releaseGpuResources();
			
				//void initRederObjects();
				//void cleanupRenderObjects();
			
			public:
				void initSwapChainResources(QSize yTargetSize, size_t ySwapChainImageCount); // override;
				void releaseSwapChainResources(); // override;

			private:
			
				void createCommandBuffer(size_t ySwapChainImageCount = 1);
				void cleanupCommandBuffer();
			
				VkCommandBuffer startFrame();
				void startMainRenderPass(VkCommandBuffer yCommandBuffer);
				void endMainRenderPass(VkCommandBuffer yCommandBuffer);
				void endFrame(VkCommandBuffer yCommandBuffer);
			public:
				void draw(size_t yCurrentSwapChainImageIndex);
				QImage framebuffer2host();
				void evaluateTest();
			
				//Camera& camera() {
				//	return m_camera;
				//}
			
			protected:
				const Camera& camera;
				std::vector<FrameBuffer::ImageDefinition> fboFormates;
			
			
				// from [xxx]Vulkan()
				VulkanInstance vulkanInstance;
				VulkanDevice device;
				uint32_t queueFamilyIndex;
			
			
				// from [xxx]SwapChainResources()
				//std::vector<VkCommandBuffer> commandBuffers;
				VulkanSwapChain swapChain;
			
				FrameBuffer* fbo;
				//Camera m_camera;
				//Axis* roAxis = nullptr;
				//Cube* roCube = nullptr;
				CubeMap* roCubeMap = nullptr;

				//QVulkanWindow *m_window;
			
			
				//
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
			
				Volume<uint16_t> m_volume;
				data::GpuVolume* m_gpuVolume = nullptr;
				EncryptedXRay* roEncXRay = nullptr;
		};
	}
}
