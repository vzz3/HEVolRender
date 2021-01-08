#version 450
#extension GL_ARB_separate_shader_objects : enable

#include "lib/uniforms.glsl"
#include "lib/CameraUniformBufferObject.glsl"
#include "lib/ModelUniformBufferObject.glsl"

layout(binding = 0) uniform uboModel {
	CameraUniformBufferObject camera;
	ModelUniformBufferObject model;
};

//layout(binding = 0, set = UBO_MODEL) uniform uboModel {
//	ModelUniformBufferObject model;
//};

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

void main() {
	//gl_Position = vec4(inPosition, 1.0);
	// gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 0.0, 1.0);
	//gl_Position = camera.vpMatrix * vec4(inPosition, 1.0);
    gl_Position = camera.vpMatrix * model.modelMatrix * vec4(inPosition, 1.0);
    fragColor = inColor;
}
