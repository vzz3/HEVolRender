#version 450

#include "lib/VolumeUniformBufferObject.glsl"

layout(binding = 1) uniform uboBigIntTest {
	uint testOperationType;
};

// http://kylehalladay.com/blog/tutorial/vulkan/2018/01/28/Textue-Arrays-Vulkan.html
//layout (binding = 2) uniform sampler3D samplerVolume;


layout (binding = 3) uniform sampler samplerVolumes;
layout (binding = 4) uniform utexture3D texturesVolumes[2];

layout (location = 0) in vec2 inUV;

layout (location = 0) out uvec4 outFragColor[4];

void main() {
	for(uint i=0; i<4; i++) {
		outFragColor[i] = uvec4(0,0,0,0);
	}
	outFragColor[0] = texture(usampler3D(texturesVolumes[0], samplerVolumes), vec3(inUV, 0.5f));
	//float avg = 1.0f ;//sampleCount;
	//outFragColor = uvec4(avg,avg,avg,1);

	////ivec3 volumePos = ivec3(1, int(inUV.y * 12), 1);
	//ivec3 volumePos = ivec3(gl_FragCoord.xy, 1);
	//outFragColor[0] = texelFetch(usampler3D(texturesVolumes[0], samplerVolumes), volumePos, 0);

	//outFragColor[0] = uvec4(volumePos.x, volumePos.y, 0, 1);
}
