
struct MontgomeryReducer_Data {
	uint reducerBits;
	FIX_BIG_INT_VALUE modulus;
	FIX_BIG_INT_VALUE mask;
	FIX_BIG_INT_VALUE factor;
};

/**
 * @const
 * @public
 */
FIX_BIG_INT_VALUE MontgomeryReducer_reduce(const in MontgomeryReducer_Data me, const in FIX_BIG_INT_VALUE encodedProduct) {
	FIX_BIG_INT_VALUE temp = UFixBigInt_and(UFixBigInt_mul(UFixBigInt_and(encodedProduct, me.mask ), me.factor), me.mask);			// ((encodedProduct & mask ) * factor) & mask;
	FIX_BIG_INT_VALUE reduced = UFixBigInt_rcr(UFixBigInt_add(encodedProduct, UFixBigInt_mul(temp, me.modulus)), me.reducerBits);	// (encodedProduct + (temp * modulus)) >> reducerBits;
	FIX_BIG_INT_VALUE result = UFixBigInt_lessThan(reduced, me.modulus) ? reduced : UFixBigInt_sub(reduced, me.modulus);			// (reduced < modulus) ? reduced : reduced - modulus;
	assert ( result < me.modulus);

	return result;
}

/**
 * @const
 * @public
 */
FIX_BIG_INT_VALUE MontgomeryReducer_multiply(const in MontgomeryReducer_Data me, const in FIX_BIG_INT_VALUE encodedA, const in FIX_BIG_INT_VALUE encodedB) {
	assert( encodedA < me.modulus );
	assert( encodedB < me.modulus );

	FIX_BIG_INT_VALUE product = UFixBigInt_mul(encodedA, encodedB);
	return MontgomeryReducer_reduce(me, product);
}
