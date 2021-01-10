#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "VulkanDevice.hpp"
#include "Camera.hpp"
#include "VulkanSwapChain.hpp"
#include "Cube.hpp"
#include "FrameBuffer.hpp"

namespace ppvr {
	namespace rendering {
		class CubeMap {
		private:
//			struct FrameBufferAttachment {
//				VkImage image;
//				VkDeviceMemory mem;
//				VkImageView view;
//			};
			struct OffscreenPass {
//				int32_t width, height;
//				VkFramebuffer frameBuffer;
//				FrameBufferAttachment color, depth;
//				VkRenderPass renderPass;
				VkSampler sampler;
				VkDescriptorImageInfo descriptor;
			};
	
		public:
			CubeMap(VulkanDevice& yDev);
			~CubeMap();
			
			void initGpuResources();
			void releaseGpuResources();
			
			void initSwapChainResources(const VulkanSwapChain& ySwapChain);
			void releaseSwapChainResources();
			
		private:
			void cleanup();
		
			// ---  Offscreen ---
			//void createOffscreen(const VulkanSwapChain& ySwapChain);
			//void cleanupOffscreen();
			
			//void createColorAttachment(const VulkanSwapChain& ySwapChain);
			//void cleanupColorAttachment();
			
			void createSampler(const VulkanSwapChain& ySwapChain);
			void cleanupSampler();
			
			//void createDepthAttachment(const VulkanSwapChain& ySwapChain);
			//void cleanupDepthAttachment();
			
			//void createOffscreenRenderPass(const VulkanSwapChain& ySwapChain);
			//void cleanupOffscreenRenderPass();
			
			//void createOffscreenFramebuffers(const VulkanSwapChain& ySwapChain);
			//void cleanupOffscreenFramebuffers();
			
			// --- CommandBuffers ---
			//void createCommandBuffers();
			//void cleanupCommandBuffers();
			
			void createDebugUniformBuffers(size_t ySwapChainImageCount);
			void cleanupDebugUniformBuffers();
			
			void createDebugDescriptorPool(size_t ySwapChainImageCount);
			void cleanupDebugDescriptorPool();
			
			void createDebugDescriptorSets(size_t ySwapChainImageCount);
			void cleanupDebugDescriptorSets();
			
			void createDebugDescriptorSetLayout();
			void cleanupDebugDescriptorSetLayout();
			
			void createDebugPipeline(const VulkanSwapChain& ySwapChain);
			void cleanupDebugPipeline();
			
		private:
			void updateDebugUniformBuffer(uint32_t yCurrentSwapChainImageIndex);
		public:
			void drawOffscreenFrame(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex);
			
			void draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex);
		private:
			static constexpr VkFormat colorFormat = VK_FORMAT_R8G8B8A8_UNORM; // TODO!!!!
			VkFormat fbDepthFormat;
			
			static constexpr bool useDepthTest = false;
			
			Cube cube;
			FrameBuffer frontFBO;
			
			
			// from constructor
			VulkanDevice& dev;
			
			// from [xxx]Offscreen()
			OffscreenPass offscreenPass;
			VulkanSwapChain offscreenSwappChain;
			
			// from [xxx]DebugPipeline()
			VkPipeline debugPipline;
			VkPipelineLayout debugPiplineLayout;
			
			// from [xxx]DescriptorSetLayout()
			VkDescriptorSetLayout debugDescriptorSetLayout; // beschreibt die uniforms in der pipline mit den shadern
			
			/*
			// from [xxx]VertexBuffer()
			VkBuffer vertexBuffer;
			VkDeviceMemory vertexBufferMemory;
			*/
			
			// from [xxx]UniformBuffers()
			std::vector<VkBuffer> debugUniformBuffers;
			std::vector<VkDeviceMemory> debugUniformBuffersMemory;
			
			// from [xxx]DescriptorPool()
			VkDescriptorPool debugDescriptorPool;
			
			// from [xxx]descriptorSets()
			std::vector<VkDescriptorSet> debugDescriptorSets;
			
			
			
			// from [xxx]GraphicsPipeline()
			//VkPipelineLayout pipelineLayout;
			//VkPipeline graphicsPipeline;
			
			
		};
	}
}
