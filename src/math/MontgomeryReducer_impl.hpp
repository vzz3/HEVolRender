
#include <cassert>
#include "BigIntUtil.hpp"


using ppvr::math::MontgomeryReducer;

// ----- constructors -----

template <typename BigInt>
MontgomeryReducer<BigInt>::MontgomeryReducer(const BigInt& yModulus): modulus{yModulus} {
	// Reducer:
	const BigInt one{1};
	#if defined(BIG_INT_MONTGOMERY_FORCE_READABLE) || !defined(BIG_INT_MONTGOMERY_COLIN_PLUMB)
		this->reducerBits = (modulus.bitLength() / 8 + 1) * 8;  // This is a multiple of 8 // Equal to log2(reducer)
	#else
		this->reducerBits = (modulus.bitLength() / BIG_INT_BITS_PER_WORD + 1) * BIG_INT_BITS_PER_WORD;  // This is a multiple of 8 // Equal to log2(reducer)
	#endif
	this->reducer = one << reducerBits;  // This is a power of 256 // Is a power of 2
	this->mask = reducer - one; // Because x mod reducer = x & (reducer - 1)
	#ifndef BIG_INT_MONTGOMERY_FORCE_READABLE
		this->reducerWords = BIG_INT_BIT_TO_SIZE(this->reducerBits);
	
		#if defined(BIG_INT_MONTGOMERY_COLIN_PLUMB)
			// Compute the modular inverse word from the LSW of modulus
			this->inv = BigIntUtil::inverseMod(modulus.getData()[0]) * (BIG_INT_WORD_TYPE)-1;
	
			/* inv must be the negative inverse of mod's least significant word */
			assert( (BIG_INT_WORD_TYPE)(this->inv * modulus.getData()[0]) == (BIG_INT_WORD_TYPE)-1);
		#endif
	#endif

	assert( this->reducer > this->modulus );
	assert( this->reducer.gcd(modulus).isOne() );
	
	// Other computed numbers:
	this->reciprocal = this->reducer.modInverse(modulus);		// in verst case the reducer has 8 bits more then the bitLength(modulus) 
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
		// based on a Java class from (Project Nayuki)
		// https://www.nayuki.io/page/montgomery-reduction-algorithm
		BigInt temp = ((encodedProduct & mask ) * factor) & mask;
		BigInt reduced = (encodedProduct + (temp * modulus)) >> reducerBits;
		BigInt result = (reduced < modulus) ? reduced : reduced - modulus;
		assert ( result < modulus);
		
		return result;
	#else
		// this is my test ground for faster operations
		#if !defined(BIG_INT_MONTGOMERY_COLIN_PLUMB)
			// this is the same algorithem as the easily readable one above, but with some short cutes
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
		#else
			// This is the multiprecision REDC algorithm from Montomery original paper https://doi.org/10.1090%2FS0025-5718-1985-0777282-X
			// also used by Colin Plumb in his C library bnlib (lbnMontReduce_32() in lib32.c:2008)
			BIG_INT_WORD_TYPE t;
			BIG_INT_WORD_TYPE c = 0;
			BIG_INT_WORD_COUNT_TYPE mlen = modulus.getWordSize();
			//BIG_INT_WORD_COUNT_TYPE len = mlen;
			BIG_INT_WORD_COUNT_TYPE targetLen = mlen*2;
			//assert(len);
			
			BigInt reduced = encodedProduct;
			
			reduced.reserveWordsAndInitUnused(targetLen);

			for(BIG_INT_WORD_COUNT_TYPE i = 0; i < mlen; i++) {
				t = BigIntUtil::mulAdd(reduced.getDataUnsafe(), i, this->modulus.getData(), 0, mlen, inv * reduced.getData()[i]); // lbnMulAdd1_32(n, mod, mlen, inv * BIGLITTLE(n[-1],n[0]));
				c += BigIntUtil::addInt(t, i+mlen, reduced.getDataUnsafe(), targetLen); // lbnAdd1_32(BIGLITTLE(n-mlen,n+mlen), len, t);
				//BIGLITTLE(--n,++n);
			}
			reduced.trimWordSize(targetLen);
			reduced.rcr(BIG_INT_BITS_PER_WORD * mlen, 0);
			

			/*
			 * All that adding can cause an overflow past the modulus size,
			 * but it's unusual, and never by much, so a subtraction loop
			 * is the right way to deal with it.
			 * This subtraction happens infrequently - I've only ever seen it
			 * invoked once per reduction, and then just under 22.5% of the time.
			 */
			BigInt result = reduced;
			while (result >= this->modulus) {
				result =  result - this->modulus;
			}
			assert ( result < modulus);
	
			return result;
		#endif
	#endif
}


