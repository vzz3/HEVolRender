
struct MontgomeryReducer_Data {
	uint reducerBits;
	FIX_BIG_INT_VALUE modulus;
	FIX_BIG_INT_VALUE mask;
	FIX_BIG_INT_VALUE factor;
	BIG_INT_WORD_COUNT_TYPE reducerWords;
};

/**
 * @const
 * @public
 */
FIX_BIG_INT_VALUE MontgomeryReducer_reduce(const in MontgomeryReducer_Data me, const in FIX_BIG_INT_VALUE encodedProduct) {
	#if defined(BIG_INT_MONTGOMERY_FORCE_READABLE)
		// this is the readable version of the montgomery reduction
		FIX_BIG_INT_VALUE temp = UFixBigInt_and(UFixBigInt_mul(UFixBigInt_and(encodedProduct, me.mask ), me.factor), me.mask);			// ((encodedProduct & mask ) * factor) & mask;
		FIX_BIG_INT_VALUE reduced = UFixBigInt_rcr(UFixBigInt_add(encodedProduct, UFixBigInt_mul(temp, me.modulus)), me.reducerBits);	// (encodedProduct + (temp * modulus)) >> reducerBits;
		FIX_BIG_INT_VALUE result = UFixBigInt_lessThan(reduced, me.modulus) ? reduced : UFixBigInt_sub(reduced, me.modulus);			// (reduced < modulus) ? reduced : reduced - modulus;
		assert ( result < me.modulus);

		return result;
	#else
		// this is my test ground for faster operations
		FIX_BIG_INT_VALUE p1 = encodedProduct;

		// (encodedProduct & mask)
		UFixBigInt_clearHigherWords(p1, me.reducerWords);	// set words to zero that are entirely zero in mask
		UFixBigInt_bitAnd(p1, me.reducerWords-1, me.mask[me.reducerWords-1]); // mask out leading zeros in highest word that has not only zeros in mask

		// ((encodedProduct & mask ) * factor)
		FIX_BIG_INT_VALUE p2 = UFixBigInt_mul(p1, me.factor);

		// ((encodedProduct & mask ) * factor) & mask;
		UFixBigInt_clearHigherWords(p2, me.reducerWords);	// set words to zero that are entirely zero in mask
		UFixBigInt_bitAnd(p2, me.reducerWords-1, me.mask[me.reducerWords-1]); // mask out leading zeros in highest word that has not only zeros in mask

		// BigInt reduced = (encodedProduct + (temp * modulus)) >> reducerBits;
		FIX_BIG_INT_VALUE reduced = UFixBigInt_rcr(UFixBigInt_add(encodedProduct, UFixBigInt_mul(p2, me.modulus)), me.reducerBits);	// (encodedProduct + (p2 * modulus)) >> reducerBits;

		FIX_BIG_INT_VALUE result = UFixBigInt_lessThan(reduced, me.modulus) ? reduced : UFixBigInt_sub(reduced, me.modulus); // (reduced < modulus) ? reduced : reduced - modulus;
		assert ( result < modulus);

		return result;
	#endif
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
