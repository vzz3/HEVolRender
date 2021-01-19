#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "../VulkanDevice.hpp"
#include "../data/Volume.hpp"
#include "../data/Image.hpp"
#include "../FrameBuffer.hpp"

#include "../VulkanSwapChain.hpp"
#include "../data/BigIntGpuVolumeSet.hpp"

#define BIG_INT_GPU_TEST_OPERATION_copy 1

namespace ppvr {
	namespace rendering {
		class BigIntTestObj {
		
			struct BigIntTestUniformBufferObject {
				uint32_t testOperationType;
			};
	
	
		public:
			BigIntTestObj(VulkanDevice& yDev);
			~BigIntTestObj();
			
			void initGpuResources();
			void releaseGpuResources();
			
			void initSwapChainResources(const VulkanSwapChain& ySwapChain);
			void releaseSwapChainResources();
			
		private:
			void cleanup();
			
			// --- image descriptor ---
			
			void createVolumeDescriptors(const VulkanSwapChain& ySwapChain);
			void cleanupVolumeDescriptors();
			
			void createVolumeSampler(const VulkanSwapChain& ySwapChain);
			void cleanupVolumeSampler();
			
			//void createCubePosSampler(const VulkanSwapChain& ySwapChain);
			//void cleanupCubePosSampler();
			
			void createUniformBuffer(size_t ySwapChainImageCount);
			void cleanupUniformBuffer();
			
			void createDescriptorPool(size_t ySwapChainImageCount);
			void cleanupDescriptorPool();
			
			void createDescriptorSet(size_t ySwapChainImageCount);
			void cleanupDescriptorSet();
			
			void updateUniformBuffer(uint32_t yCurrentSwapChainImageIndex);
			
		//public:
			//void setImages(std::vector<ImagePanel> yImages);
			
		private:
			// --- render pipline ---
			
			void createDescriptorSetLayout();
			void cleanupDescriptorSetLayout();
			
			void createPipeline(const VulkanSwapChain& ySwapChain);
			void cleanupPipeline();
			
		public:
			void draw(VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex);
			
		private:
			void createTest();
		public:
			void evaluateTest(FrameBuffer& yFBO);
			
		private:
			// from constructor
			VulkanDevice& dev;
			
			//data::GpuVolume* volume = nullptr;
			
			
			//VkImageView volumeView;
			
			// from [xxx]Sampler()
			VkSampler volumeSampler;
			
			//VkSampler cubePosSampler;
			
			//VkDescriptorImageInfo descriptorImage;
		
			// from [xxx]UniformBuffers()
			std::vector<VkBuffer> uniformBuffers;
			std::vector<VkDeviceMemory> uniformBuffersMemory;
		
			// from [xxx]DescriptorPool()
			VkDescriptorPool descriptorPool;
		
			// from [xxx]DescriptorSets()
			std::vector<VkDescriptorSet> descriptorSets;
			
			
			// from [xxx]Offscreen()
			//OffscreenPass offscreenPass;
			VulkanSwapChain offscreenSwappChain;
			
			// from [xxx]DebugPipeline()
			VkPipeline pipline;
			VkPipelineLayout piplineLayout;
			
			// from [xxx]DescriptorSetLayout()
			VkDescriptorSetLayout descriptorSetLayout; // beschreibt die uniforms in der pipline mit den shadern
			
			// ------------
			Volume<PaillierInt> srcVolume;
			Image<PaillierInt> refImage;
			Image<PaillierInt> dstImage;
			
			data::BigIntGpuVolumeSet gpuVolumeSet;
			std::string testCaseName{"GPU big int copy"};
		};
	}
}
