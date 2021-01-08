
#include "VulkanDevice.hpp"



using namespace ppvr::rendering;

VulkanDevice::VulkanDevice(VulkanInstance* yVkInstance, VkPhysicalDevice yVkPhysicalDevice, VkDevice yVkDevice, QVulkanDeviceFunctions* yDeviceFunctions, VkCommandPool yGraphicsCommandPool, VkQueue yGraphicsQueue):
	vkInstance(yVkInstance), vkPhysicalDev(yVkPhysicalDevice), vkDev(yVkDevice), funcs(yDeviceFunctions), graphicsCommandPool(yGraphicsCommandPool), graphicsQueue(yGraphicsQueue) {
}
VulkanDevice::VulkanDevice(): VulkanDevice(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr) {

}
VulkanDevice::~VulkanDevice() {};
