struct CameraUniformBufferObject {
	//float aspectRatio; // = 1.0f;
	//float fieldOfView; // = glm::radians(40.0f); // Converts degrees to radians and returns the result.
	mat4 viewMatrix; // worldToCamera
	mat4 viewInvMatrix; // cameraToWorld
	mat4 vpMatrix;
};
