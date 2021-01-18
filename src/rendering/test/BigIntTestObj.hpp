#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "../VulkanDevice.hpp"
#include "../Camera.hpp"
#include "../VulkanSwapChain.hpp"
#include "../data/GpuVolume.hpp"



namespace ppvr {
	namespace rendering {
		class BigIntTestObj {
	
		public:
			BigIntTestObj(VulkanDevice& yDev);
			~BigIntTestObj();
			
			void initGpuResources();
			void releaseGpuResources();
			
			void initSwapChainResources(const VulkanSwapChain& ySwapChain, data::GpuVolume* yVolume, VkImageView yCubeFront, VkImageView yCubeBack );
			void releaseSwapChainResources();
			
		private:
			void cleanup();
			
			// --- image descriptor ---
			
			void createVolumeDescriptors(const VulkanSwapChain& ySwapChain);
			void cleanupVolumeDescriptors();
			
			void createVolumeSampler(const VulkanSwapChain& ySwapChain);
			void cleanupVolumeSampler();
			
			void createCubePosSampler(const VulkanSwapChain& ySwapChain);
			void cleanupCubePosSampler();
			
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
			
		private:
			
		public:
			void draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex);
		private:
			// from constructor
			VulkanDevice& dev;
			
			data::GpuVolume* volume = nullptr;
			VkImageView cubePosView[2]; // index 0 = front; index 1 = back
			
			
			//VkImageView volumeView;
			
			// from [xxx]Sampler()
			VkSampler volumeSampler;
			
			VkSampler cubePosSampler;
			
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
			VkPipeline debugPipline;
			VkPipelineLayout debugPiplineLayout;
			
			// from [xxx]DescriptorSetLayout()
			VkDescriptorSetLayout descriptorSetLayout; // beschreibt die uniforms in der pipline mit den shadern
			
		};
	}
}
