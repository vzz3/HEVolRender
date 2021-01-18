#version 450
//#extension GL_EXT_debug_printf : enable
	// https://github.com/KhronosGroup/Vulkan-ValidationLayers/blob/master/tests/vklayertests_gpu.cpp -> search for "GpuDebugPrintf"

#include "lib/uniforms.glsl"
//#include "lib/Model2dUniformBufferObject.glsl"
#include "lib/quadVertices.glsl"

//layout(binding = 0) uniform uboModel {
//	Model2dUniformBufferObject model;
//};

layout (location = 0) out vec2 outUV;


void main() {
	//debugPrintfEXT("Here's a integer %i", gl_VertexIndex);
	outUV = quadVertices_getUvByTriangleIndex(gl_VertexIndex);
	gl_Position = vec4(outUV * 2.0f - 1.0f, 0.0f, 1.0f);

	// fixt to the top left corner of the creen
	//float scale = 0.3f;
	//vec3 screenPos = vec3(outUV * 2.0f - 1.0f); // full screen
	//screenPos = screenPos * scale - (1.0f - (scale)) + 0.05f;

	// scaling and postioning by uniform matrix
	//vec3 screenPos = mat3(model.modelMatrix) * vec3(outUV, 1.0f);

	//gl_Position = vec4(screenPos.xy, 0.0f, 1.0f);
}
