#pragma once

#include <vector>
#include "vertex/ColoredVertex.hpp"
#include <vulkan/vulkan.h>
#include <QVulkanDeviceFunctions>
#include "VulkanDevice.hpp"
#include "Camera.hpp"
#include <QSize>
#include "VulkanSwapChain.hpp"
#include "uniform/CubeUniformBufferObject.hpp"

namespace ppvr {
	namespace rendering {
		class Cube {
		public:
			Cube(VulkanDevice& yDev);
			~Cube();
			
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
			// all cube vertices; format: {{postion}, {color}}
			// front:
			vertex::ColoredVertex vA = {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}}; // left top
			vertex::ColoredVertex vB = {{-1.0f,-1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}; // left bottom
			vertex::ColoredVertex vC = {{ 1.0f,-1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}}; // right bootom
			vertex::ColoredVertex vD = {{ 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}; // right top
			
			// back
			vertex::ColoredVertex vQ = {{-1.0f, 1.0f,-1.0f}, {0.0f, 1.0f, 0.0f}}; // left top
			vertex::ColoredVertex vR = {{ 1.0f, 1.0f,-1.0f}, {1.0f, 1.0f, 0.0f}}; // right top
			vertex::ColoredVertex vS = {{-1.0f,-1.0f,-1.0f}, {0.0f, 0.0f, 0.0f}}; // left bootom
			vertex::ColoredVertex vT = {{ 1.0f,-1.0f,-1.0f}, {1.0f, 0.0f, 0.0f}}; // right bootmom
		
			const std::vector<vertex::ColoredVertex> vertices = {
				vA,vB,vC , vA,vC,vD,   //Front
				vR,vT,vS , vQ,vR,vS,   //Back
				
				vQ,vS,vB , vQ,vB,vA,   //Left
				vD,vC,vT , vD,vT,vR,   //Right
				
				vQ,vA,vD , vQ,vD,vR,   //Top
				vB,vS,vT , vB,vT,vC    //Bot
			};
			
			uniform::CubeUniformBufferObject ubo;
			
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
