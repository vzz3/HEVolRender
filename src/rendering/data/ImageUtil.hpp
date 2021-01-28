#pragma once

#include <vulkan/vulkan.h>
#include "../VulkanDevice.hpp"
#include "../FrameBuffer.hpp"
#include <string>
#include <QImage>
#include <vector>
#include "Image.hpp"

#include "../../paillier/Paillier_typeDev.h"

using ppvr::rendering::VulkanDevice;
using ppvr::rendering::FrameBuffer;

namespace ppvr {
	namespace rendering {
		namespace data {
			class ImageUtil {
			
				static const std::vector<VkFormat> R8G8B8A8_Formates;
			
				template <typename T>
				static bool inVector(const T& yNeedle, std::vector<T> yHaystack) {
					const bool found = (std::find(yHaystack.begin(), yHaystack.end(), yNeedle) != yHaystack.end());
					return found;
				}
				
			public:
				static void framebuffer2ppm(VulkanDevice& yDevice, const FrameBuffer& yFBO, const std::string& yBaseName);
				static QImage framebuffer2QImage(VulkanDevice& yDevice, const FrameBuffer& yFBO, const size_t yAttachmentIndex);
				static void framebuffer2Image(VulkanDevice& yDevice, const FrameBuffer& yFBO, Image<PaillierInt>& yDstImage);
				
				
				static QImage convertToNewQImage(const Image<uint16_t> ySrc);
			};
		}
	}
}
