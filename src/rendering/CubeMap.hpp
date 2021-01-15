#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "VulkanDevice.hpp"
#include "Camera.hpp"
#include "VulkanSwapChain.hpp"
#include "Cube.hpp"
#include "FrameBuffer.hpp"
#include "ImageDebugView.hpp"

namespace ppvr {
	namespace rendering {
		class CubeMap {
		private:
//			struct FrameBufferAttachment {
//				VkImage image;
//				VkDeviceMemory mem;
//				VkImageView view;
//			};
//			struct OffscreenPass {
//				int32_t width, height;
//				VkFramebuffer frameBuffer;
//				FrameBufferAttachment color, depth;
//				VkRenderPass renderPass;
//				VkSampler sampler;
//				VkDescriptorImageInfo descriptor;
//			};
	
		public:
			CubeMap(VulkanDevice& yDev);
			~CubeMap();
			
			void initGpuResources();
			void releaseGpuResources();
			
			void initSwapChainResources(const VulkanSwapChain& ySwapChain);
			void releaseSwapChainResources();
			
		private:
			void cleanup();
			
			void drawCubeFace(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex, Cube& yCube, FrameBuffer &yFBO);
		public:
			void drawOffscreenFrame(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex);
			
			void draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex);
			
			VkImageView getFrontImageView() const;
			VkImageView getBackImageView() const;
		private:
			//static constexpr VkFormat colorFormat = VK_FORMAT_R8G8B8A8_UNORM; // TODO!!!!
			//VkFormat fbDepthFormat;
			
			static constexpr bool useDepthTest = false;
			
			// TODO: eigentlich sollte auch ein cube mit zwei piplines reichen, den descriptorLayouts, DescriptorSets, VertrexBuffers usw. sind immer gleich.
			Cube frontCube;
			Cube backCube;
			
			FrameBuffer frontFBO;
			FrameBuffer backFBO;
			ImageDebugView offscreenImageView;
			
			// from constructor
			VulkanDevice& dev;
			
			// from [xxx]Offscreen()
			//OffscreenPass offscreenPass;
			VulkanSwapChain frontSwappChain;
			VulkanSwapChain backSwappChain;
			
			
			
			// from [xxx]GraphicsPipeline()
			//VkPipelineLayout pipelineLayout;
			//VkPipeline graphicsPipeline;
			
			
		};
	}
}
