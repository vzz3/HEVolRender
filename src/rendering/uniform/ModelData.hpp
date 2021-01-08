#pragma once

#include <glm/mat4x4.hpp>

namespace ppvr {
	namespace rendering {
		namespace uniform {
			struct ModelData {
				alignas(16) glm::mat4x4 modelMatrix; // modelToWorld
			};
		}
	}
}
