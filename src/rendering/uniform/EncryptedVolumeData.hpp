#pragma once

//#include <glm/mat4x4.hpp>
#include "../../paillier/Paillier_typeDev.h"

/*
 From the spec:

 Standard Uniform Buffer Layout

 The 'base alignment' of the type of an OpTypeStruct member of is defined recursively as follows:

 A scalar of size N has a base alignment of N.
 A two-component vector, with components of size N, has a base alignment of 2 N.
 A three- or four-component vector, with components of size N, has a base alignment of 4 N.
 An array has a base alignment equal to the base alignment of its element type, rounded up to a multiple of 16.
 A structure has a base alignment equal to the largest base alignment of any of its members, rounded up to a multiple of 16.
 A row-major matrix of C columns has a base alignment equal to the base alignment of a vector of C matrix components.
 A column-major matrix has a base alignment equal to the base alignment of the matrix column type.
 The std140 layout in GLSL satisfies these rules.

 More about this in the 14.5.4. Offset and Stride Assignment section of the specification.
 
 https://stackoverflow.com/questions/45638520/ubos-and-their-alignments-in-vulkan
 
 */

namespace ppvr {
	namespace rendering {
		namespace uniform {
			struct EncryptedVolumeData {
				//alignas(16) glm::mat4x4 modelMatrix; // modelToWorld
				alignas(16) float volumeDepth;
				//BIG_INT_WORD_TYPE modulus[PAILLIER_INT_WORD_SIZE];
				//alignas(16) BIG_INT_WORD_TYPE modulusSquared[PAILLIER_INT_WORD_SIZE];
				alignas(16) glm::uvec4  modulusSquared[GPU_INT_UVEC4_STORAGE_SIZE];
			};
		}
	}
}
