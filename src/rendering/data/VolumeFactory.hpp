#pragma once

#include <vector>
#include "Volume.hpp"
#include <glm/vec3.hpp>

namespace ppvr {
	namespace rendering {
		namespace data {
			class VolumeFactory {
			
			public:
				//VolumeFactory();
				//~VolumeFactory();
			
				static void createVolume(Volume<uint16_t>& yVolume, size_t ySize) {
					return createVolume2(yVolume, ySize);
				}
	
			private:
				static void createVolume1(Volume<uint16_t>& yVolume, const size_t ySize);
				
				static void createVolume2(Volume<uint16_t>& yVolume, const size_t ySize);
				
				static void createVolume3(Volume<uint16_t>& yVolume, const size_t ySize);
				
				
				
			
				template <typename T>
				static void addBox(Volume<T>& yVolume, const glm::uvec3& yMin, const glm::uvec3& yMax, const T& yValue);
				
				template <typename T>
				static void addEllipsoid(Volume<T>& yVolume,  const glm::uvec3& yCenter,  const glm::uvec3& yRadius, const T& yValue);
				
				template <typename T>
				static void addSphere(Volume<T>& yVolume, const glm::uvec3& yCenter, uint32_t yRadius, const T& yValue);
			};
		}
	}
}

#include "VolumeFactory_impl.hpp"
