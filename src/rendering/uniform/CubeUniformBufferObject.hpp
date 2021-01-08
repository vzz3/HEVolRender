#pragma once

#include <glm/mat4x4.hpp>
#include "CameraData.hpp"
#include "ModelData.hpp"

namespace ppvr {
	namespace rendering {
		namespace uniform {
			struct CubeUniformBufferObject {
				CameraData camera;
				ModelData model;
			};
		}
	}
}
