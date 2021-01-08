#pragma once

#include <glm/mat4x4.hpp>

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
