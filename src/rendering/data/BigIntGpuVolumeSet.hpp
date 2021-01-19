#pragma once

#include <vulkan/vulkan.h>
#include "../VulkanDevice.hpp"
#include "./GpuVolume.hpp"
#include <vector>

using ppvr::rendering::VulkanDevice;

namespace ppvr {
	namespace rendering {
		namespace data {
			class BigIntGpuVolumeSet {
			public:
				BigIntGpuVolumeSet(VulkanDevice& yDev);
				~BigIntGpuVolumeSet();
				
				void releaseGpuResources();
				
				void uploadVolume(const Volume<PaillierInt>& yVolume);
				
				/**
				 * Returns the count of gpuVolumes that are in use.
				 */
				inline size_t size() const {
					return gpuVolumeParts.size();
				}
				
				inline GpuVolume& at(size_t pos) {
					return gpuVolumeParts[pos];
				}
				inline const GpuVolume& at(size_t pos) const {
					return gpuVolumeParts[pos];
				}
				inline GpuVolume& operator[](size_t pos) {
					return gpuVolumeParts[pos];
				}
				inline const GpuVolume& operator[](size_t pos) const {
					return gpuVolumeParts[pos];
				}
				
			private:
				// from constructor
				VulkanDevice& dev;
				
				std::vector<GpuVolume> gpuVolumeParts;
			};
		}
	}
}
