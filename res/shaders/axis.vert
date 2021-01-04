#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform CameraUniformBufferObject {
	//float aspectRatio; // = 1.0f;
	//float fieldOfView; // = glm::radians(40.0f); // Converts degrees to radians and returns the result.
	mat4 viewMatrix; // worldToCamera
	mat4 viewInvMatrix; // cameraToWorld
	mat4 vpMatrix;
} uboCamera;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

void main() {
	//gl_Position = vec4(inPosition, 1.0);
	// gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 0.0, 1.0);
    gl_Position = uboCamera.vpMatrix * vec4(inPosition, 1.0);
    fragColor = inColor;
}
