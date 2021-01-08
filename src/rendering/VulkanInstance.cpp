
#include "VulkanInstance.hpp"



using namespace ppvr::rendering;

VulkanInstance::VulkanInstance(QVulkanFunctions* yDeviceFunctions):
	funcs(yDeviceFunctions) {
}
VulkanInstance::VulkanInstance(): VulkanInstance(nullptr) {

}
VulkanInstance::~VulkanInstance() {};
