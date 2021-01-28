#pragma once

#include "./EncryptedVolumeData.hpp"

namespace ppvr {
	namespace rendering {
		namespace uniform {
			struct EncryptedXRayUniformBufferObject {
				EncryptedVolumeData volumeInfo;
			};
		}
	}
}
