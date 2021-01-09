#version 450

#include "lib/uniforms.glsl"
#include "lib/Model2dUniformBufferObject.glsl"

layout(binding = 0) uniform uboModel {
	Model2dUniformBufferObject model;
};

layout (location = 0) out vec2 outUV;

vec2 uvData[4] = vec2[](
    vec2(0.0, 1.0), // left bottom in vulkan
    vec2(1.0, 1.0),	// right bottom
    vec2(0.0, 0.0),	// left top
	vec2(1.0, 0.0)	// right top
);

uint indexData[6] = uint[](
	0, 1, 2, // left bottom
	3, 2, 1  // right top
);



void main()
{
	outUV = uvData[indexData[gl_VertexIndex]];

	// fixt to the top left corner of the creen
	//float scale = 0.3f;
	//vec3 screenPos = vec3(outUV * 2.0f - 1.0f); // full screen
	//screenPos = screenPos * scale - (1.0f - (scale)) + 0.05f;

	// scaling and postioning by uniform matrix
	//vec3 screenPos = model.modelMatrix * vec3(outUV, 1.0f); // I was not able to get the alignment for vulkan shaders correct.
	vec3 screenPos = mat3(model.modelMatrix) * vec3(outUV, 1.0f);

	gl_Position = vec4(screenPos.xy, 0.0f, 1.0f);
}
