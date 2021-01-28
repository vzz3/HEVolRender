
#include "ImageUtil.hpp"

#include "../VulkanUtility.hpp"
#include "../VulkanInitializers.hpp"

#include <fstream>
#include <QDebug>


using namespace ppvr::rendering::data;
using ppvr::rendering::VulkanDevice;
using ppvr::rendering::FrameBuffer;

const std::vector<VkFormat> ImageUtil::R8G8B8A8_Formates = { VK_FORMAT_R8G8B8A8_SINT, VK_FORMAT_R8G8B8A8_SRGB, VK_FORMAT_R8G8B8A8_UINT, VK_FORMAT_R8G8B8A8_SNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_R8G8B8A8_SSCALED, VK_FORMAT_R8G8B8A8_USCALED };

void ImageUtil::framebuffer2ppm(VulkanDevice& yDevice, const FrameBuffer& yFBO, const std::string& yBaseName) {
	
	const char* imageData;
	int32_t width = yFBO.getWidth();
	int32_t height = yFBO.getHeight();
	
	// Create the linear tiled destination image to copy to and to read the memory from
	std::vector<VkImage> dstImages{yFBO.colorAttachmentCount()};
	std::vector<VkDeviceMemory> dstImageMemories{yFBO.colorAttachmentCount()};
	
	// create images
	for (size_t i = 0; i < dstImages.size(); i++) {
	
		assert( inVector(yFBO.getColorImageFormat(i), R8G8B8A8_Formates)); // check if format is supported
	
		VulkanUtility::createImage(yDevice,
			VK_IMAGE_TYPE_2D, 						// VkImageType yImageType
			width, height, 1, 						// yWidth, yHeight, yDepth,
			yFBO.getColorImageFormat(i),			// VkFormat yFormat
			VK_IMAGE_TILING_LINEAR, 				// VkImageTiling yTiling
			VK_IMAGE_USAGE_TRANSFER_DST_BIT, 		//VkImageUsageFlags yUsage
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,	// VkMemoryPropertyFlags yProperties
			dstImages[i], 							// VkImage& yImage
			dstImageMemories[i]						// VkDeviceMemory& yImageMemory
		);
	}
	
	// Do the actual blit from the offscreen image to our host visible destination image
	VkCommandBuffer copyCmd = VulkanUtility::beginSingleTimeCommands(yDevice);
	
	for (size_t i = 0; i < dstImages.size(); i++) {
		// Transition destination image to transfer destination layout
		// TODO check srcStageMask
		VulkanUtility::transitionImageLayout(yDevice, copyCmd, dstImages[i], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		
		// colorAttachment.image is already in VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, and does not need to be transitioned
		// TODO realy???? is this correct?????
		assert(yFBO.getColorImageFinalLayout(i) == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
		
		VulkanUtility::copyImage(yDevice, copyCmd,
			yFBO.getColorAttachment(i).image, dstImages[i],	// srcImage, dstImage
			width, height, 1);
		
		
		// Transition destination image to general layout, which is the required layout for mapping the image memory later on
		VulkanUtility::transitionImageLayout(yDevice, copyCmd, dstImages[i], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
	}
	
	VulkanUtility::endSingleTimeCommands(yDevice, copyCmd); // this command waits for the GPU

	// Get layout of the image (including row pitch)
	VkImageSubresource subResource{};
	subResource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	VkSubresourceLayout subResourceLayout;

	for (size_t i = 0; i < dstImages.size(); i++) {
		yDevice.funcs->vkGetImageSubresourceLayout(yDevice.vkDev, dstImages[i], &subResource, &subResourceLayout);

		// Map image memory so we can start copying from it
		yDevice.funcs->vkMapMemory(yDevice.vkDev, dstImageMemories[i], 0, VK_WHOLE_SIZE, 0, (void**)&imageData);
		imageData += subResourceLayout.offset;

		/*
			Save host visible framebuffer image to disk (ppm format)
		*/

		//const char* filename = "headless.ppm";
		std::stringstream filename;
		filename << yBaseName << i << ".ppm";
		std::ofstream file(filename.str(), std::ios::out | std::ios::binary);

		// ppm header
		file << "P6\n" << width << "\n" << height << "\n" << 255 << "\n";

		// If source is BGR (destination is always RGB) and we can't use blit (which does automatic conversion), we'll have to manually swizzle color components
		// Check if source is BGR and needs swizzle
		std::vector<VkFormat> formatsBGR = { VK_FORMAT_B8G8R8A8_SRGB, VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_B8G8R8A8_SNORM };
		const bool colorSwizzle = inVector(VK_FORMAT_R8G8B8A8_UNORM, formatsBGR);

		// ppm binary pixel data
		for (int32_t y = 0; y < height; y++) {
			unsigned int *row = (unsigned int*)imageData;
			for (int32_t x = 0; x < width; x++) {
				if (colorSwizzle) {
					file.write((char*)row + 2, 1);
					file.write((char*)row + 1, 1);
					file.write((char*)row, 1);
				}
				else {
					file.write((char*)row, 3);
				}
				row++;
			}
			imageData += subResourceLayout.rowPitch;
		}
		file.close();

		qDebug() << "Framebuffer image saved to " << filename.str().c_str() ;
		
		// Clean up resources
		yDevice.funcs->vkUnmapMemory(yDevice.vkDev, dstImageMemories[i]);
		yDevice.funcs->vkFreeMemory(yDevice.vkDev, dstImageMemories[i], nullptr); dstImageMemories[i] = nullptr;
		yDevice.funcs->vkDestroyImage(yDevice.vkDev, dstImages[i], nullptr); dstImages[i] = nullptr;
	}
}

QImage ImageUtil::framebuffer2QImage(VulkanDevice& yDevice, const FrameBuffer& yFBO, const size_t yAttachmentIndex) {
	const char* imageData;
	int32_t width = yFBO.getWidth();
	int32_t height = yFBO.getHeight();
	
	// Create the linear tiled destination image to copy to and to read the memory from
	VkImage dstImage;
	VkDeviceMemory dstImageMemory;
	
	// create images
	{
		VulkanUtility::createImage(yDevice,
			VK_IMAGE_TYPE_2D, 						// VkImageType yImageType
			width, height, 1, 						// yWidth, yHeight, yDepth,
			yFBO.getColorImageFormat(yAttachmentIndex),	// VkFormat yFormat
			VK_IMAGE_TILING_LINEAR, 				// VkImageTiling yTiling
			VK_IMAGE_USAGE_TRANSFER_DST_BIT, 		//VkImageUsageFlags yUsage
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,	// VkMemoryPropertyFlags yProperties
			dstImage, 								// VkImage& yImage
			dstImageMemory							// VkDeviceMemory& yImageMemory
		);
	}
	
	// Do the actual blit from the offscreen image to our host visible destination image
	VkCommandBuffer copyCmd = VulkanUtility::beginSingleTimeCommands(yDevice);
	
	{
		// Transition destination image to transfer destination layout
		// TODO check srcStageMask
		VulkanUtility::transitionImageLayout(yDevice, copyCmd, dstImage, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		
		// colorAttachment.image is already in VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, and does not need to be transitioned
		// TODO realy???? is this correct?????
		assert(yFBO.getColorImageFinalLayout(yAttachmentIndex) == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
		
		VulkanUtility::copyImage(yDevice, copyCmd,
			yFBO.getColorAttachment(yAttachmentIndex).image, dstImage,	// srcImage, dstImage
			width, height, 1);
		
		
		// Transition destination image to general layout, which is the required layout for mapping the image memory later on
		VulkanUtility::transitionImageLayout(yDevice, copyCmd, dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
	}
	
	VulkanUtility::endSingleTimeCommands(yDevice, copyCmd); // this command waits for the GPU

	// Get layout of the image (including row pitch)
	VkImageSubresource subResource{};
	subResource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	VkSubresourceLayout subResourceLayout;

	QImage frameGrabTargetImage = QImage(width, height, QImage::Format_RGBA8888);
	{
		yDevice.funcs->vkGetImageSubresourceLayout(yDevice.vkDev, dstImage, &subResource, &subResourceLayout);

		// Map image memory so we can start copying from it
		yDevice.funcs->vkMapMemory(yDevice.vkDev, dstImageMemory, 0, VK_WHOLE_SIZE, 0, (void**)&imageData);
		imageData += subResourceLayout.offset;

		/*
			Save host visible framebuffer image to disk (ppm format)
		*/
		for (int y = 0; y < frameGrabTargetImage.height(); ++y) {
			memcpy(frameGrabTargetImage.scanLine(y), imageData, frameGrabTargetImage.width() * 4);
			imageData += subResourceLayout.rowPitch;
		}

		
		// Clean up resources
		yDevice.funcs->vkUnmapMemory(yDevice.vkDev, dstImageMemory);
		yDevice.funcs->vkFreeMemory(yDevice.vkDev, dstImageMemory, nullptr); dstImageMemory = nullptr;
		yDevice.funcs->vkDestroyImage(yDevice.vkDev, dstImage, nullptr); dstImage = nullptr;
	}
	
	return frameGrabTargetImage;
}

void ImageUtil::framebuffer2Image(VulkanDevice& yDevice, const FrameBuffer& yFBO, Image<PaillierInt>& yDstImage) {
	
	const char* imageData;
	int32_t width = yFBO.getWidth();
	int32_t height = yFBO.getHeight();
	
	// Create the linear tiled destination image to copy to and to read the memory from
	std::vector<VkImage> dstImages{yFBO.colorAttachmentCount()};
	std::vector<VkDeviceMemory> dstImageMemories{yFBO.colorAttachmentCount()};
	
	// create images
	for (size_t i = 0; i < dstImages.size(); i++) {
		VulkanUtility::createImage(yDevice,
			VK_IMAGE_TYPE_2D, 						// VkImageType yImageType
			width, height, 1, 						// yWidth, yHeight, yDepth,
			yFBO.getColorImageFormat(i),			// VkFormat yFormat
			VK_IMAGE_TILING_LINEAR, 				// VkImageTiling yTiling
			VK_IMAGE_USAGE_TRANSFER_DST_BIT, 		// VkImageUsageFlags yUsage
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,	// VkMemoryPropertyFlags yProperties
			dstImages[i], 							// VkImage& yImage
			dstImageMemories[i]						// VkDeviceMemory& yImageMemory
		);
	}
	
	// Do the actual blit from the offscreen image to our host visible destination image
	VkCommandBuffer copyCmd = VulkanUtility::beginSingleTimeCommands(yDevice);
	
	for (size_t i = 0; i < dstImages.size(); i++) {
		// Transition destination image to transfer destination layout
		// TODO check srcStageMask
		VulkanUtility::transitionImageLayout(yDevice, copyCmd, dstImages[i], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
		
		// colorAttachment.image is already in VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, and does not need to be transitioned
		// TODO realy???? is this correct?????
		assert(yFBO.getColorImageFinalLayout(i) == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
		
		VulkanUtility::copyImage(yDevice, copyCmd,
			yFBO.getColorAttachment(i).image, dstImages[i],	// srcImage, dstImage
			width, height, 1);
		
		
		// Transition destination image to general layout, which is the required layout for mapping the image memory later on
		VulkanUtility::transitionImageLayout(yDevice, copyCmd, dstImages[i], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
	}
	
	VulkanUtility::endSingleTimeCommands(yDevice, copyCmd); // this command waits for the GPU

	// Get layout of the image (including row pitch)
	VkImageSubresource subResource{};
	subResource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	VkSubresourceLayout subResourceLayout;

	for (size_t i = 0; i < dstImages.size(); i++) {
		yDevice.funcs->vkGetImageSubresourceLayout(yDevice.vkDev, dstImages[i], &subResource, &subResourceLayout);

		// Map image memory so we can start copying from it
		yDevice.funcs->vkMapMemory(yDevice.vkDev, dstImageMemories[i], 0, VK_WHOLE_SIZE, 0, (void**)&imageData);
		imageData += subResourceLayout.offset;

		/*
			Save host visible framebuffer image to disk (ppm format)
		*/

		size_t wordOffset = i * GPU_INT_TEXTURE_WORD_COUNT;

		// ppm binary pixel data
		for (int32_t y = 0; y < height; y++) {
			BIG_INT_WORD_TYPE *row = (BIG_INT_WORD_TYPE*)imageData;
			for (int32_t x = 0; x < width; x++) {
				PaillierInt& bigIntVal = yDstImage.get(x,y);
				for (size_t w = 0; w < GPU_INT_TEXTURE_WORD_COUNT; w++) {
					bigIntVal.getDataUnsafe()[wordOffset + w] = *row;
					bigIntVal.fixSignumAfterUnsafeOperation(false);
					row++;
				}
			}
			imageData += subResourceLayout.rowPitch;
		}
		
		// Clean up resources
		yDevice.funcs->vkUnmapMemory(yDevice.vkDev, dstImageMemories[i]);
		yDevice.funcs->vkFreeMemory(yDevice.vkDev, dstImageMemories[i], nullptr); dstImageMemories[i] = nullptr;
		yDevice.funcs->vkDestroyImage(yDevice.vkDev, dstImages[i], nullptr); dstImages[i] = nullptr;
	}
}

QImage ImageUtil::convertToNewQImage(const Image<uint16_t> ySrc) {
	QImage dstImg = QImage(ySrc.width(), ySrc.height(), QImage::Format_RGBA8888);
	memcpy(dstImg.bits(), ySrc.data(), ySrc.length() * sizeof(uint16_t));
	for(size_t y = 0; y < ySrc.height(); y++) {
		for(size_t x = 0; x < ySrc.width(); x++) {
			uint val = (ySrc.get(x, y) >> 8) & 0xFF; // use only the most significant 8 bits from the provided 16 bit
			dstImg.setPixel(x, y, (
					255 << 24	// alpha
					| val << 16	// red
					| val << 8	// green
					| val		// blue
			));
			
			//dstImg.setPixel(x, y, (
			//		255 << 24	// alpha
			//		| (ySrc.get(x, y) & 0xFFFFFF)
			//));
		}
	}
	return dstImg;
}
