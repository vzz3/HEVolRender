
#include <cassert>

using ppvr::math::MontgomeryReducer;

// ----- constructors -----

template <typename BigInt>
MontgomeryReducer<BigInt>::MontgomeryReducer(const BigInt& yModulus): modulus{yModulus} {
	// Reducer:
	const BigInt one{1};
	this->reducerBits = (modulus.bitLength() / 8 + 1) * 8;  // This is a multiple of 8 // Equal to log2(reducer)
	this->reducer = one << reducerBits;  // This is a power of 256 // Is a power of 2
	this->mask = reducer - one; // Because x mod reducer = x & (reducer - 1)
	#ifndef BIG_INT_MONTGOMERY_FORCE_READABLE
		this->reducerWords = BIG_INT_BIT_TO_SIZE(this->reducerBits);
	#endif

	assert( this->reducer > this->modulus );
	assert( this->reducer.gcd(modulus).isOne() );
	
	// Other computed numbers:
	this->reciprocal = this->reducer.modInverse(modulus);
	this->factor = (reducer * reciprocal - one ) / modulus;		// reducer * reciprocal => (bitLength(modulus) + 9) * 2 !!!! => we need to ensure that we have min. 18 bit more available then the modulus (modulus sequerd for Paillier)
	this->convertedOne = this->reducer % modulus;
}

template <typename BigInt>
MontgomeryReducer<BigInt>::~MontgomeryReducer() {}

template <typename BigInt>
BigInt MontgomeryReducer<BigInt>::convertIn(const BigInt& plainValue) const {
	BigInt encodedValue = plainValue << reducerBits;
	encodedValue = encodedValue % modulus;
	return encodedValue;
}

template <typename BigInt>
BigInt MontgomeryReducer<BigInt>::convertOut(const BigInt& encodedValue) const {
	BigInt plainValue = encodedValue * reciprocal;
	plainValue = plainValue % modulus;
	return plainValue;
}

template <typename BigInt>
BigInt MontgomeryReducer<BigInt>::multiply(const BigInt& encodedA, const BigInt& encodedB) const {
	assert( encodedA < this->modulus );
	assert( encodedB < this->modulus );
	
	BigInt product = encodedA * encodedB;
	return reduce(product);
}

template <typename BigInt>
BigInt MontgomeryReducer<BigInt>::square(const BigInt& encodedA) const {
	assert( encodedA < this->modulus );
	BigInt squereRes = encodedA.square();
	return reduce(squereRes);
}

template <typename BigInt>
BigInt MontgomeryReducer<BigInt>::reduce(const BigInt& encodedProduct) const {
	#if defined(BIG_INT_MONTGOMERY_FORCE_READABLE)
		// this is the readable version of the montgomery reduction
		BigInt temp = ((encodedProduct & mask ) * factor) & mask;
		BigInt reduced = (encodedProduct + (temp * modulus)) >> reducerBits;
		BigInt result = (reduced < modulus) ? reduced : reduced - modulus;
		assert ( result < modulus);
		
		return result;
	#else
		// this is my test ground for faster operations
		BigInt p1 = encodedProduct;
		
		// (encodedProduct & mask)
		p1.clearHigherWords(this->reducerWords);	// set words to zero that are entirely zero in mask
		p1.bitAnd(this->reducerWords-1, this->mask.getData()[this->reducerWords-1]); // mask out leading zeros in highest word that has not only zeros in mask
		
		// ((encodedProduct & mask ) * factor)
		BigInt p2 = p1 * this->factor;
		
		// ((encodedProduct & mask ) * factor) & mask;
		p2.clearHigherWords(this->reducerWords);	// set words to zero that are entirely zero in mask
		p2.bitAnd(this->reducerWords-1, this->mask.getData()[this->reducerWords-1]); // mask out leading zeros in highest word that has not only zeros in mask
		
		// BigInt reduced = (encodedProduct + (temp * modulus)) >> reducerBits;
		BigInt reduced = (p2 * this->modulus);
		reduced.add(encodedProduct);
		reduced.rcr(reducerBits, 0);
		
		BigInt result = (reduced < this->modulus) ? reduced : reduced - this->modulus;
		assert ( result < modulus);
		
		return result;
	#endif
}


