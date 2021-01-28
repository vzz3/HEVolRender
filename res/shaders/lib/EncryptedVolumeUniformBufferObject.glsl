struct EncryptedVolumeUniformBufferObject {
	float volumeDepth;
	//BIG_INT_WORD_TYPE[PAILLIER_INT_WORD_SIZE] modulus;
	//BIG_INT_WORD_TYPE[PAILLIER_INT_WORD_SIZE] modulusSquared;
	uvec4[GPU_INT_UVEC4_STORAGE_SIZE] modulusSquared;
};
