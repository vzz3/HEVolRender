#pragma once

#include <glm/vec3.hpp>
#include <vulkan/vulkan.h>
#include <array>

namespace ppvr {
	namespace rendering {
		namespace vertex {
			struct ColoredVertex {
				glm::vec3 pos;
				glm::vec3 color;
				
				static VkVertexInputBindingDescription getBindingDescription();
				
				static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
			};
		}
	}
}
