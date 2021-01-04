
#include "./ColoredVertex.hpp"

using ppvr::rendering::vertex::ColoredVertex;
//using namespace ppvr::rendering::vertex;

VkVertexInputBindingDescription ColoredVertex::getBindingDescription() {
	VkVertexInputBindingDescription bindingDescription{};
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(ColoredVertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // We're not going to use instanced rendering, so we'll stick to per-vertex data.
	
	return bindingDescription;
}
			
std::array<VkVertexInputAttributeDescription, 2> ColoredVertex::getAttributeDescriptions() {
	std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

	// pos
	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[0].offset = offsetof(ColoredVertex, pos);
	
	// color
	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = offsetof(ColoredVertex, color);

	return attributeDescriptions;
}
