#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "VulkanDevice.hpp"
#include "Camera.hpp"
#include "VulkanSwapChain.hpp"
#include <glm/vec2.hpp>

namespace ppvr {
	namespace rendering {
		class ImageDebugView {
		public:
			struct ImagePanel {
				ImagePanel();
				ImagePanel(VkImageView yView, float yScale, glm::vec2 yScreenOffset);
				
				VkImageView view;
				float scale;// = 0.3f;
				glm::vec2 screenOffset;// {(-1.0f + 0.05f), (-1.0f + 0.05f)};
			};
		
		private:
			struct ImageDescriptor {
				VkSampler sampler;
				//VkDescriptorImageInfo descriptorImage;
				
				// from [xxx]UniformBuffers()
				std::vector<VkBuffer> uniformBuffers;	// one for all swap chain images should be enoght becaus it does not change anyway
				std::vector<VkDeviceMemory> uniformBuffersMemory;
				
				// from [xxx]DescriptorPool()
				VkDescriptorPool descriptorPool; // better/posible to use one pool for alle images????
				
				// from [xxx]DescriptorSets()
				std::vector<VkDescriptorSet> descriptorSets;
			};
	
		public:
			ImageDebugView(VulkanDevice& yDev);
			~ImageDebugView();
			
			void initGpuResources();
			void releaseGpuResources();
			
			void initSwapChainResources(const VulkanSwapChain& ySwapChain, std::vector<ImagePanel> yImages);
			void releaseSwapChainResources();
			
		private:
			void cleanup();
			
			// --- image descriptor ---
			
			void createImageDescriptors(const VulkanSwapChain& ySwapChain);
			void cleanupImageDescriptors();
			
			void createSampler(size_t yIndex, const VulkanSwapChain& ySwapChain);
			void cleanupSampler(size_t yIndex);
			
			void createUniformBuffer(size_t yIndex, size_t ySwapChainImageCount);
			void cleanupUniformBuffer(size_t yIndex);
			
			void createDescriptorPool(size_t yIndex, size_t ySwapChainImageCount);
			void cleanupDescriptorPool(size_t yIndex);
			
			void createDescriptorSet(size_t yIndex, size_t ySwapChainImageCount);
			void cleanupDescriptorSet(size_t yIndex);
			
			void updateUniformBuffer(size_t yIndex, uint32_t yCurrentSwapChainImageIndex);
			
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
			
			// from [xxx]Offscreen()
			//OffscreenPass offscreenPass;
			VulkanSwapChain offscreenSwappChain;
			
			// from [xxx]DebugPipeline()
			VkPipeline debugPipline;
			VkPipelineLayout debugPiplineLayout;
			
			// from [xxx]DescriptorSetLayout()
			VkDescriptorSetLayout debugDescriptorSetLayout; // beschreibt die uniforms in der pipline mit den shadern
			
			std::vector<ImagePanel> images; // source, defined by the user of this class
			std::vector<ImageDescriptor> imgDescs; // destination
		};
	}
}
