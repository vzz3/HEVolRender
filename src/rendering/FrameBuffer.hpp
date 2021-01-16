#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "VulkanDevice.hpp"
#include "Camera.hpp"
#include "VulkanSwapChain.hpp"
#include "Cube.hpp"

namespace ppvr {
	namespace rendering {
		class FrameBuffer {
		public:
			struct ImageDefinition {
				//ImageDefinition(VkFormat yFormat);
				ImageDefinition(VkFormat yFormat, VkImageLayout yFinalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
				VkFormat format;
				VkImageLayout finalLayout;
			};
		
			struct FrameBufferAttachment {
				VkImage image;
				VkDeviceMemory mem;
				VkImageView view;
			};
			
		public:
			FrameBuffer(VulkanDevice& yDev, bool yUseDepth);
			FrameBuffer(VulkanDevice& yDev, bool yUseDepth, const std::vector<ImageDefinition>& yFbColorFormats);
			FrameBuffer(VulkanDevice& yDev, bool yUseDepth, const std::vector<ImageDefinition>& yFbColorFormats, VkFormat yFbDepthFormat);
			~FrameBuffer();
			
			void initGpuResources();
			void releaseGpuResources();
			
			void initSwapChainResources(const QSize& yTargetSize);
			void releaseSwapChainResources();
			
		private:
			void cleanup();
		
			// ---  Offscreen ---
			void createColorAttachments();
			void cleanupColorAttachments();
			
			void createColorAttachment(size_t yIndex);
			void cleanupColorAttachment(size_t yIndex);
			
			void createDepthAttachment();
			void cleanupDepthAttachment();
			
			void createRenderPass();
			void cleanupRenderPass();
			
			void createFrameBuffer();
			void cleanupFrameBuffer();
			
			//void createSampler(const VulkanSwapChain& ySwapChain);
			//void cleanupSampler();
			
		public:
			int32_t getWidth() const;
			int32_t getHeight() const;
			
			size_t colorAttachmentCount() const;
			size_t attachmentCount() const;
			const FrameBufferAttachment& getColorAttachment(size_t yIndex) const;
			const FrameBufferAttachment& getDepthAttachment() const;
			const VkRenderPass& getRenderPass() const;
			const VkFramebuffer& getFramebuffer() const;
			
			//void draw(const Camera& yCamera, VkCommandBuffer& yCmdBuf, size_t yCurrentSwapChainImageIndex);
		private:
			// from constructor
			VulkanDevice& dev;
			const bool useDepthTest = false;
			//static constexpr VkFormat colorFormat = VK_FORMAT_R8G8B8A8_UNORM; // TODO!!!!
			const std::vector<ImageDefinition> fbColorFormats;
			const VkFormat fbDepthFormat;
			
			// from initSwapChainResources
			int32_t width, height;
			
			
			// from [xxx]ColorAttachments()
			std::vector<FrameBufferAttachment> colors;
			
			// from [xxx]DepthAttachment()
			FrameBufferAttachment depth;
			
			// from [xxx]RenderPass()
			VkRenderPass renderPass;
			
			// from [xxx]RenderPass()
			VkFramebuffer frameBuffer;
			
			//VkSampler sampler;
			//VkDescriptorImageInfo descriptor;
			//VulkanSwapChain offscreenSwappChain;
		};
	}
}
