#pragma once

#include <glm/mat4x4.hpp>

namespace ppvr {
	namespace rendering {
		namespace uniform {
			struct VolumeData {
				//alignas(16) glm::mat4x4 modelMatrix; // modelToWorld
				alignas(4) float volumeDepth;
			};
		}
	}
}
