#version 450

#include "lib/VolumeUniformBufferObject.glsl"

layout(binding = 1) uniform uboVolume {
	VolumeUniformBufferObject volumeInfo;
};

// http://kylehalladay.com/blog/tutorial/vulkan/2018/01/28/Textue-Arrays-Vulkan.html
layout (binding = 2) uniform sampler3D samplerVolume;


layout (binding = 3) uniform sampler samplerCubePos;
layout (binding = 4) uniform texture2D texturesCubePos[2];

layout (location = 0) in vec2 inUV;

layout (location = 0) out vec4 outFragColor;

void main()
{
	//outFragColor = texture(samplerColor, inUV);

  	vec3 inPos  = texture(sampler2D(texturesCubePos[0], samplerCubePos), inUV).xyz;
	vec3 outPos = texture(sampler2D(texturesCubePos[1], samplerCubePos), inUV).xyz;

	//outFragColor = vec4(outPos, 1.0f);

	float raySamplerDist = (1.0/volumeInfo.volumeDepth);

	float d = 0.0;
	vec3 samplePos;
	vec3 direction =  outPos - inPos;
	float rayLength = length(direction);
	direction = normalize(direction);
	float sum = 0.0;
	//float sampleCount = 0.0;
	while (d < rayLength) {
		samplePos = inPos + (direction * d);
		float density = texture(samplerVolume, samplePos).x;
		////density = Math.max(Math.min(density, 1.0f), 0.0f);
		sum += density;
		//colorSum += differenceQuotient(samplePos, raySamplerDist, tex3D, sampler3D) ;

		//sampleCount++;
		d += raySamplerDist;
	}
	float avg = sum / volumeInfo.volumeDepth * 2.0 ;//sampleCount;
	outFragColor = vec4(avg,avg,avg,1);
}
