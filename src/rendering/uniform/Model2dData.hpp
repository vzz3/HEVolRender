#pragma once

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace ppvr {
	namespace rendering {
		namespace uniform {
			struct Model2dData {
				//alignas(16) glm::mat3x3 modelMatrix; // modelToWorld // I was not able to get the alignment for vulkan shaders correct.
				alignas(16) glm::mat4x4 modelMatrix; // modelToWorld
			};
		}
	}
}
