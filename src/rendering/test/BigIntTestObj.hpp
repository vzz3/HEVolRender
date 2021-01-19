#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "../VulkanDevice.hpp"
#include "../data/Volume.hpp"
#include "../data/Image.hpp"
#include "../FrameBuffer.hpp"

#include "../VulkanSwapChain.hpp"
#include "../data/BigIntGpuVolumeSet.hpp"

#include "./BigIntTestCase.hpp"
//#define BIG_INT_GPU_TEST_OPERATION_copy 1

namespace ppvr {
	namespace rendering {
		namespace test {
			class BigIntTestObj {
			
				struct BigIntTestUniformBufferObject {
					uint32_t testOperationType;
				};
		
		
			public:
				BigIntTestObj(VulkanDevice& yDev, const BigIntTestCase& yTestCase);
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
				
				void createUniformBuffer(size_t ySwapChainImageCount);
				void cleanupUniformBuffer();
				
				void createDescriptorPool(size_t ySwapChainImageCount);
				void cleanupDescriptorPool();
				
				void createDescriptorSet(size_t ySwapChainImageCount);
				void cleanupDescriptorSet();
				
				void updateUniformBuffer(uint32_t yCurrentSwapChainImageIndex);
				
			private:
				// --- render pipline ---
				
				void createDescriptorSetLayout();
				void cleanupDescriptorSetLayout();
				
				void createPipeline(const VulkanSwapChain& ySwapChain);
				void cleanupPipeline();
				
			public:
				void draw(VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex);
				void evaluateTest(FrameBuffer& yFBO);
				
			private:
				// from constructor
				VulkanDevice& dev;
				
				// from [xxx]Sampler()
				VkSampler volumeSampler;
				
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
				Image<PaillierInt> dstImage;
				const BigIntTestCase& testCase;
				data::BigIntGpuVolumeSet gpuVolumeSet;
				
			};
		}
	}
}
