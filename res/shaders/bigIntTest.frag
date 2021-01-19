#version 450

#include "lib/VolumeUniformBufferObject.glsl"

layout(binding = 1) uniform uboBigIntTest {
	uint testOperationType;
};

// http://kylehalladay.com/blog/tutorial/vulkan/2018/01/28/Textue-Arrays-Vulkan.html
//layout (binding = 2) uniform sampler3D samplerVolume;


layout (binding = 3) uniform sampler samplerVolumes;
layout (binding = 4) uniform utexture3D texturesVolumes[4];

layout (location = 0) in vec2 inUV;

layout (location = 0) out uvec4 outFragColor[4];

void main() {
	// inizialize all output variables
	//for(uint i=0; i<4; i++) {
	//	outFragColor[i] = uvec4(0,0,0,0);
	//}

	// working texture() example (pos coordinates are normalized floats)
	//outFragColor[0] = texture(usampler3D(texturesVolumes[0], samplerVolumes), vec3(inUV, 0.5f));

	// working texelFetch() example (pos coordinates are absolute integers)
	//outFragColor[0] = texelFetch(usampler3D(texturesVolumes[0], samplerVolumes), ivec3(gl_FragCoord.xy, 0), 0);

	for(uint i=0; i<4; i++) {
		outFragColor[i] = texelFetch(usampler3D(texturesVolumes[i], samplerVolumes), ivec3(gl_FragCoord.xy, 0), 0);
	}
}
