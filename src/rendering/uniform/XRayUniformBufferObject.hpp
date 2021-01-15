#pragma once

#include "./VolumeData.hpp"

namespace ppvr {
	namespace rendering {
		namespace uniform {
			struct XRayUniformBufferObject {
				VolumeData volumeInfo;
			};
		}
	}
}
