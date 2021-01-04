
#include "VulkanDevice.hpp"



using namespace ppvr::rendering;

VulkanDevice::VulkanDevice(VkPhysicalDevice vkPhysicalDevice, VkDevice yVkDevice, QVulkanDeviceFunctions* yDeviceFunctions, VkCommandPool yGraphicsCommandPool, VkQueue yGraphicsQueue):
	vkPhysicalDev(vkPhysicalDevice), vkDev(yVkDevice), funcs(yDeviceFunctions), graphicsCommandPool(yGraphicsCommandPool), graphicsQueue(yGraphicsQueue) {
}
VulkanDevice::VulkanDevice(): VulkanDevice(nullptr, nullptr, nullptr, nullptr, nullptr) {

}
VulkanDevice::~VulkanDevice() {};
