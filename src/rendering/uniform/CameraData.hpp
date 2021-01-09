#pragma once

#include <glm/mat4x4.hpp>

/*
from: https://vulkan-tutorial.com/Uniform_buffers/Descriptor_pool_and_sets

Vulkan expects the data in your structure to be aligned in memory in a specific way, for example:

Scalars have to be aligned by N (= 4 bytes given 32 bit floats).
A vec2 must be aligned by 2N (= 8 bytes)
A vec3 or vec4 must be aligned by 4N (= 16 bytes)
A nested structure must be aligned by the base alignment of its members rounded up to a multiple of 16.
A mat4 matrix must have the same alignment as a vec4.
You can find the full list of alignment requirements in the specification
(https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/chap14.html#interfaces-resources-layout).
*/


namespace ppvr {
	namespace rendering {
		namespace uniform {
			struct CameraData {
				//float aspectRatio = 1.0f;
				//float fieldOfView = glm::radians(40.0f); // Converts degrees to radians and returns the result.
				alignas(16) glm::mat4x4 viewMatrix; // worldToCamera
				alignas(16) glm::mat4x4 viewInvMatrix; // cameraToWorld
				alignas(16) glm::mat4x4 vpMatrix;
			};
		}
	}
}
