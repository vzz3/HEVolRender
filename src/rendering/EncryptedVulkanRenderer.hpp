

#include <QVulkanWindow>
#include <QVulkanWindowRenderer>

#include "./VulkanInstance.hpp"
#include "./VulkanDevice.hpp"
#include "./Axis.hpp"
#include "./Cube.hpp"
#include "./CubeMap.hpp"
#include "./data/Volume.hpp"
#include "./EncryptedXRay.hpp"
#include "./FrameBuffer.hpp"
#include <QImage>
#include "./test/BigIntTestObj.hpp"
#include "../paillier/crypto/PublicKey.hpp"

using ppvr::paillier::crypto::PublicKey;

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
			
			public:
				void setEncryptedVolume(PublicKey* yPK, Volume<PaillierInt>* yEncryptedVolume);
			
				void initGpuResources();
				void releaseGpuResources();
			
				//void initRederObjects();
				//void cleanupRenderObjects();
			
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
				//QImage framebuffer2host();
				void framebuffer2host(Image<PaillierInt>& yDstImage);
			
				void setBigIntTestCase(test::BigIntTestCase* yBigIntTestCase);
				void evaluateTest();
			
				//Camera& camera() {
				//	return m_camera;
				//}
			
			protected:
				const Camera& camera;
				const bool initBigIntTest;
				std::vector<FrameBuffer::ImageDefinition> fboFormates;
			
			
				// from [xxx]Vulkan()
				VulkanInstance vulkanInstance;
				VulkanDevice device;
				uint32_t queueFamilyIndex;
			
			
				// from [xxx]SwapChainResources()
				//std::vector<VkCommandBuffer> commandBuffers;
				VulkanSwapChain swapChain;
			
				FrameBuffer* fbo;
				CubeMap* roCubeMap = nullptr;

			
			
			
				PublicKey* pk;
				Volume<PaillierInt>* encryptedVolume;
				//data::GpuVolume* m_gpuVolume = nullptr;
				data::BigIntGpuVolumeSet* gpuVolumeSet = nullptr;
				EncryptedXRay* roEncXRay = nullptr;
			
				test::BigIntTestCase* bigIntTestCase = nullptr;
				test::BigIntTestObj* roBigIntTester = nullptr;
		};
	}
}
