struct EncryptedVolumeUniformBufferObject {
	float volumeDepth;
	//BIG_INT_WORD_TYPE[PAILLIER_INT_WORD_SIZE] modulus;
	//BIG_INT_WORD_TYPE[PAILLIER_INT_WORD_SIZE] modulusSquared;
	uvec4[GPU_INT_UVEC4_STORAGE_SIZE] modulusSquared;

	// Data for MontgomeryReducer
	uint montReducerBits;
	uvec4[GPU_INT_UVEC4_SIZE] montMask;
	uvec4[GPU_INT_UVEC4_SIZE] montFactor;
	uvec4[GPU_INT_UVEC4_STORAGE_SIZE] montConvertedEncZero; // encrypted and montogomery encoded zero

};
