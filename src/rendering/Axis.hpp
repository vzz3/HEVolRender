#pragma once

#include <vector>
#include "vertex/ColoredVertex.hpp"
#include <vulkan/vulkan.h>
#include <QVulkanDeviceFunctions>
#include "VulkanDevice.hpp"
#include "Camera.hpp"
#include <QSize>
#include "VulkanSwapChain.hpp"

namespace ppvr {
	namespace rendering {
		class Axis {
		public:
			Axis(VulkanDevice& yDev);
			~Axis();
			
			void initGpuResources();
			void releaseGpuResources();
			
			void initSwapChainResources(const VulkanSwapChain& ySwapChain);
			void releaseSwapChainResources();
			
		private:
			void cleanup();
		
			void createVertexBuffer();
			void cleanupVertexBuffer();
			
			void createUniformBuffers(size_t ySwapChainImageCount);
			void cleanupUniformBuffers();
			
			void createDescriptorPool(size_t ySwapChainImageCount);
			void cleanupDescriptorPool();
			
			void createDescriptorSets(size_t ySwapChainImageCount);
			void cleanupDescriptorSets();
			
			void createDescriptorSetLayout();
			void cleanupDescriptorSetLayout();
			
			void createGraphicsPipeline(const VkRenderPass& yRenderPass, const QSize& yTargetSize);
			void cleanupGraphicsPipeline();
			
			
		private:
			void updateUniformBuffer(const Camera& yCamera, uint32_t yCurrentSwapChainImageIndex);
		public:
			void draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex);
		private:
			const std::vector<vertex::ColoredVertex> vertices = {
				// {{postion}, {color}}
				// X
				{{0.0f, 0.0f, 0.0f}, {1.0f, 0.7f, 0.7f}},
				{{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
				
				// Y
				{{0.0f, 0.0f, 0.0f}, {0.7f, 1.0f, 0.7f}},
				{{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
				
				// Z
				{{0.0f, 0.0f, 0.0f}, {0.7f, 0.7f, 1.0f}},
				{{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}
			};
			
			// from constructor
			VulkanDevice& dev;
			
			// from [xxx]VertexBuffer()
			VkBuffer vertexBuffer;
			VkDeviceMemory vertexBufferMemory;
			
			// from [xxx]UniformBuffers()
			std::vector<VkBuffer> uniformBuffers;
			std::vector<VkDeviceMemory> uniformBuffersMemory;
			
			// from [xxx]DescriptorPool()
			VkDescriptorPool descriptorPool;
			
			// from [xxx]descriptorSets()
			std::vector<VkDescriptorSet> descriptorSets;
			
			// from [xxx]DescriptorSetLayout()
			VkDescriptorSetLayout descriptorSetLayout;
			
			// from [xxx]GraphicsPipeline()
			VkPipelineLayout pipelineLayout;
			VkPipeline graphicsPipeline;
			
			
		};
	}
}
