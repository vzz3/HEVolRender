
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
	BigInt temp = ((encodedProduct & mask ) * factor) & mask;
	BigInt reduced = (encodedProduct + (temp * modulus)) >> reducerBits;
	BigInt result = (reduced < modulus) ? reduced : reduced - modulus;
	assert ( result < modulus);
	
	return result;
}


