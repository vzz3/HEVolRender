
#include "./BigIntUtil.h.glsl"
#include "./UFixBigInt.h.glsl"


// ----- statics -----

/**
 * @static
 * @public
 */
FIX_BIG_INT_VALUE UFixBigInt_fromVolume(const in sampler ySampler, const in utexture3D yTex[GPU_INT_TEXTURE_SIZE], in ivec3 yPos) {
	FIX_BIG_INT_VALUE val;
	for(uint texIndex = 0; texIndex < GPU_INT_TEXTURE_SIZE; texIndex++) {
		uvec4 voxelPart = texelFetch(usampler3D(yTex[texIndex], ySampler), yPos, 0);
		for(uint channelIndex = 0; channelIndex < GPU_INT_TEXTURE_WORD_COUNT; channelIndex++) {
			val[texIndex*4 + channelIndex] = voxelPart[channelIndex];
		}
	}

	for(uint i = PAILLIER_INT_STORAGE_WORD_SIZE; i < PAILLIER_INT_WORD_SIZE; i++) {
		val[i] = 0;
	}

	return val;
}

// ----- memory managment -----

/**
 * @private
 */
void UFixBigInt_initWords(out FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE initValue) {
	//std::fill_n(&this->value[0], S, initValue);
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<S; i++) {
		me[i] = initValue;
	}
}

// ----- value export - toColorOut -----

/**
 * @const
 * @public
 */
uvec4[GPU_INT_TEXTURE_SIZE] UFixBigInt_toColorOut(const in FIX_BIG_INT_VALUE me) {
	uvec4 texOut[GPU_INT_TEXTURE_SIZE];
	for(uint texIndex = 0; texIndex < GPU_INT_TEXTURE_SIZE; texIndex++) {
		for(uint channelIndex = 0; channelIndex < GPU_INT_TEXTURE_WORD_COUNT; channelIndex++) {
			texOut[texIndex][channelIndex] = me[texIndex*4 + channelIndex];
		}
	}
	//texOut[1].r = 255;
	return texOut;
}

// ----- bit utilities -----

/*
 * @protected
 */
void UFixBigInt_setZero(out FIX_BIG_INT_VALUE me) {
	UFixBigInt_initWords(me, 0);
}

/*
 * @protected
 */
void UFixBigInt_setOne(out FIX_BIG_INT_VALUE me) {
	UFixBigInt_initWords(me, 0);
	me[0] = 1;
}

/**
 * @const
 * @public
 */
bool UFixBigInt_isZero(const in FIX_BIG_INT_VALUE me) {
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<S; i++) {
		if(me[i] != 0) {
			return false;
		}
	}
	return true;
}

/**
 * @const
 * @public
 */
bool UFixBigInt_isOne(const in FIX_BIG_INT_VALUE me) {
	if(me[0] != 1) {
		return false;
	}
	for (BIG_INT_WORD_COUNT_TYPE i = 1; i<S; i++) {
		if(me[i] != 0) {
			return false;
		}
	}
	return true;
}




// ----- shift left -----

/**
 * an auxiliary method for moving bits into the left hand side
 *
 * this method moves only words
 *
 * @private
 */
void UFixBigInt_rcl_moveWords(inout FIX_BIG_INT_VALUE me, out uint restBits, out BIG_INT_WORD_TYPE lastC, const in uint bits, const in BIG_INT_WORD_TYPE c) {
	restBits      = bits % BIG_INT_BITS_PER_WORD;
	uint allWords = bits / BIG_INT_BITS_PER_WORD;
	BIG_INT_WORD_TYPE mask      = ( c > 0) ? BIG_INT_WORD_MAX_VALUE : 0;


	if( allWords >= S ) {
		if( allWords == S && restBits == 0 ) {
			lastC = me[0] & 1;
		}
		// else: last_c is default set to 0

		// clearing
		for(uint i = 0 ; i<S ; ++i) {
			me[i] = mask;
		}

		restBits = 0;
	} else {
		if( allWords > 0 ) {
			// 0 < all_words < value_size

			int first, second;
			lastC = me[S - allWords] & 1; // all_words is greater than 0

			// copying the first part of the value
			for(first = int(S)-1, second=first-int(allWords) ; second>=0 ; --first, --second) {
				me[first] = me[second];
			}

			// setting the rest to 'c'
			for( ; first>=0 ; --first ) {
				me[first] = mask;
			}
		}
	}
}

/**
 * this method moves all bits into the left hand side
 * return value <- this <- c
 *
 * the lowest *bits* will be held the 'c' and
 * the state of one additional bit (on the left hand side)
 * will be returned
 *
 * for example:
 * let this is 001010000
 * after rcl_moveBits(3, 1) there'll be 010000111 and rcl_moveBits returns 1
 *
 * This method does not increase the the word count => it drops informations that are on left end!
 *
 * @private
 */
BIG_INT_WORD_TYPE UFixBigInt_rcl_moveBits(inout FIX_BIG_INT_VALUE me, const in uint bits, in BIG_INT_WORD_TYPE c) {
	assert( bits>0 && bits<BIG_INT_BITS_PER_WORD );

	uint move = BIG_INT_BITS_PER_WORD - bits;
	BIG_INT_WORD_COUNT_TYPE i;
	BIG_INT_WORD_TYPE newC;

	if( c != 0 ) {
		c = BIG_INT_BITS_PER_WORD >> move;
	}

	for(i=0 ; i<S ; ++i) {
		newC    = me[i] >> move;
		me[i] = (me[i] << bits) | c;
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
		me[i] &= BIG_INT_WORD_ALL_BIT_MASK;
#endif
		c        = newC;
	}

	return (c & 1);
}

/**
 * moving all bits into the left side 'bits' times
 * return value <- this <- C
 *
 * bits is from a range of <0, man * BIG_INT_BITS_PER_WORD>
 * or it can be even bigger then all bits will be set to 'c'
 *
 * the value c will be set into the lowest bits
 * and the method returns state of the last moved bit
 *
 * if resize is false (default) this method does not increase the the word size => it drops informations that are on left end!
 *
 * @protected
 */
BIG_INT_WORD_TYPE UFixBigInt_rcl(inout FIX_BIG_INT_VALUE me, const in uint bits, const in BIG_INT_WORD_TYPE c) {
	BIG_INT_WORD_TYPE lastC    = 0;
	uint restBits = bits;

	if( bits == 0 )
		return 0;

	if( bits >= BIG_INT_BITS_PER_WORD ) {
		UFixBigInt_rcl_moveWords(me, restBits, lastC, bits, c);
	}

	if( restBits == 0 ) {
		return lastC;
	}
	/*
	 // rest_bits is from 1 to TTMATH_BITS_PER_UINT-1 now
	 if( restBits == 1 ) {
	 lastC = Rcl2_one(c);
	 }
	 else if( restBits == 2 )
	 {
	 // performance tests showed that for rest_bits==2 it's better to use Rcl2_one twice instead of Rcl2(2,c)
	 Rcl2_one(c);
	 last_c = Rcl2_one(c);
	 }
	 else
	 {
	 */
	lastC = UFixBigInt_rcl_moveBits(me, restBits, c);
	/*
	 }
	 */

	return lastC;
}


/**
 * moving all bits into the left side 'bits' times
 *
 * @const
 * @public
 */
FIX_BIG_INT_VALUE UFixBigInt_rcl(const in FIX_BIG_INT_VALUE me, const in uint bits) {
	FIX_BIG_INT_VALUE res = me;
	UFixBigInt_rcl(res, bits, 0);
	return res;
}




// ----- shift right -----

/**
 * an auxiliary method for moving bits into the right hand side
 *
 * this method moves only words
 *
 * @private
 */
void UFixBigInt_rcr_moveWords(inout FIX_BIG_INT_VALUE me, out uint restBits, out BIG_INT_WORD_TYPE lastC, const in uint bits, const in BIG_INT_WORD_TYPE c) {
	restBits      = bits % BIG_INT_BITS_PER_WORD;
	uint allWords = bits / BIG_INT_BITS_PER_WORD;
	BIG_INT_WORD_TYPE mask      = ( c > 0 ) ? BIG_INT_WORD_MAX_VALUE : 0;


	if( allWords >= S ) {
		if( allWords == S && restBits == 0 ) {
			lastC = ((me[S-1] & BIG_INT_WORD_HIGHEST_BIT) > 0) ? 1 : 0;
		}
		// else: last_c is default set to 0

		// clearing
		for(uint i = 0 ; i<S ; ++i) {
			me[i] = mask;
		}
		//this->value[0] = mask;
		//this->wordSize = 1;

		restBits = 0;
	} else if( allWords > 0 ) {
		// 0 < all_words < value_size

		uint first, second;
		lastC = ((me[allWords - 1] & BIG_INT_WORD_HIGHEST_BIT) > 0) ? 1 : 0; // all_words is > 0

		// copying the first part of the value
		for(first=0, second=allWords ; second<S ; ++first, ++second) {
			me[first] = me[second];
		}

		// setting the rest to 'c'
		for( ; first<S ; ++first ) {
			me[first] = mask;
		}
		//this->wordSize = first;
	}
}

/**
 * this method moves all bits into the right hand side
 * C -> this -> return value
 *
 * the highest *bits* will be held the 'c' and
 * the state of one additional bit (on the right hand side)
 * will be returned
 *
 * for example:
 * let this is 000000010
 * after rcr_moveBits(2, 1) there'll be 110000000 and rcr_moveBits returns 1
 *
 * @private
 */
BIG_INT_WORD_TYPE UFixBigInt_rcr_moveBits(inout FIX_BIG_INT_VALUE me, const in uint bits, in BIG_INT_WORD_TYPE c) {
	assert ( bits>0 && bits<BIG_INT_BITS_PER_WORD );

	uint move = BIG_INT_BITS_PER_WORD - bits;
	int i; // signed
	BIG_INT_WORD_TYPE newC;

	if( c != 0 ) {
		c = BIG_INT_WORD_MAX_VALUE << move;
	}

	for(i=int(S)-1 ; i>=0 ; --i) {
		newC    = me[i] << move;
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
		newC &= BIG_INT_WORD_ALL_BIT_MASK;
#endif
		me[i] = (me[i] >> bits) | c;
		c        = newC;
	}

	c = ((c & BIG_INT_WORD_HIGHEST_BIT) > 0) ? 1 : 0;

	//if(this->wordSize > 1 && this->value[this->wordSize-1] == 0) {
	//	this->wordSize--;
	//}

	return c;
}

/**
 * moving all bits into the right side 'bits' times
 * c -> this -> return value
 *
 * bits is from a range of <0, man * TTMATH_BITS_PER_UINT>
 * or it can be even bigger then all bits will be set to 'c'
 *
 * the value c will be set into the highest bits
 * and the method returns state of the last moved bit
 *
 * @protected
 */
BIG_INT_WORD_TYPE UFixBigInt_rcr(inout FIX_BIG_INT_VALUE me, const uint bits, const BIG_INT_WORD_TYPE c) {
	BIG_INT_WORD_TYPE lastC    = 0;
	uint restBits = bits;

	if( bits == 0 ) {
		return 0;
	}

	if( bits >= BIG_INT_BITS_PER_WORD ) {
		UFixBigInt_rcr_moveWords(me, restBits, lastC, bits, c);
	}

	if( restBits == 0 ) {
		return lastC;
	}

	/*
	 // rest_bits is from 1 to TTMATH_BITS_PER_UINT-1 now
	 if( rest_bits == 1 )
	 {
	 last_c = Rcr2_one(c);
	 }
	 else if( rest_bits == 2 )
	 {
	 // performance tests showed that for rest_bits==2 it's better to use Rcr2_one twice instead of Rcr2(2,c)
	 Rcr2_one(c);
	 last_c = Rcr2_one(c);
	 }
	 else
	 {
	 */
	lastC = UFixBigInt_rcr_moveBits(me, restBits, c);
	/*
	 }
	 */

	return lastC;
}

/**
 * moving all bits into the right side 'bits' times
 *
 * @const
 * @public
 */
FIX_BIG_INT_VALUE UFixBigInt_rcr(const in FIX_BIG_INT_VALUE me, const uint bits) {
	FIX_BIG_INT_VALUE res = me;
	UFixBigInt_rcr(res, bits, 0);
	return res;
}




// ----- addition -----

/**
 * result = result + word
 * @return carry
 * @const
 * @protected
 */
BIG_INT_WORD_TYPE UFixBigInt_add(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other, out FIX_BIG_INT_VALUE result) {
	BIG_INT_WORD_TYPE carry = 0;
	BIG_INT_WORD_TYPE a,b;//,c;
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<S; i++) {
		a = me[i];
		b = other[i];

		carry = BigIntUtil_addTwoWords(a, b, carry, result[i]);
	}

	return carry;
}

/**
 * this = this + other
 * @return carry
 * @const
 * @public
 */
FIX_BIG_INT_VALUE UFixBigInt_add(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other) {
	FIX_BIG_INT_VALUE result;
	BIG_INT_WORD_TYPE carry = UFixBigInt_add(me, other, result);
	//if(carry > 0) {
	//	throw FixBigIntOverflow("add() returned a carry");
	//}
	assert_msg(carry == 0, "add() returned a carry")
	return result;
}

// ----- substraction -----

/**
 * this = this - word
 * returns the carry (borrow) if this was < word
 *
 * @protected
 */
BIG_INT_WORD_TYPE BigIntUtil_subInt(inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE word) {
	BIG_INT_WORD_TYPE c = BigIntUtil_subInt(word, 0, me, S);

	// reduce word size if a word was truncated
	//if(this->value[this->wordSize-1] == 0) {
	//	this->wordSize = this->wordSize-1;
	//}

	return c;
}

/**
 * this method's subtracting other from the 'this' and subtracting
 * carry if it has been defined
 * (result = this - other - carry)
 *
 * carry must be zero or one (might be a bigger value than 1)
 * function returns carry (borrow) (1) (if this < other)
 *
 * @const
 * @protected
 */
BIG_INT_WORD_TYPE UFixBigInt_sub(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other, BIG_INT_WORD_TYPE carry, out FIX_BIG_INT_VALUE result) {
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<S; i++) {
		carry = BigIntUtil_subTwoWords(me[i], other[i], carry, result[i]);
	}
	return carry;
}

/*
 * @const
 * @public
 */
FIX_BIG_INT_VALUE UFixBigInt_sub(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other) {
	assert_msg(other > me, "ERROR substract UArbBigInt a - b with a < b")
	FIX_BIG_INT_VALUE result;
	UFixBigInt_sub(me, other, 0, result);
	return result;
}





// ----- multiplication -----

/**
 * @const
 * @private
 */
void UFixBigInt_mulSchool(const in FIX_BIG_INT_VALUE a, const in FIX_BIG_INT_VALUE b, out FIX_BIG_INT_VALUE result) {
	BIG_INT_WORD_COUNT_TYPE aSize  = S, 	bSize  = S;
	BIG_INT_WORD_COUNT_TYPE aStart = 0,     bStart = 0;

	for( ; aSize>0 && a[aSize-1]==0 ; --aSize);
	for(aStart=0 ; aStart<aSize && a[aStart]==0 ; ++aStart);

	for( ; bSize>0 && b[bSize-1]==0 ; --bSize);
	for(bStart=0 ; bStart<bSize && b[bStart]==0 ; ++bStart);

	UFixBigInt_setZero(result);
	if( aSize==0 || bSize==0 ) {
		return;
	}

	assert_msg((aSize + bSize - 1) > S, "mulSchool not posible without overflow (aSize + bSize >= S)");

	BIG_INT_WORD_TYPE r2, r1, carry = 0;

	for(uint aI=aStart ; aI<aSize ; ++aI) {
		//for(uint bI=bStart ; bI<bSize ; ++bI) {
		for(uint bI=bStart ; bI<bSize && bI+aI < (S-1) ; ++bI) {
			BigIntUtil_mulTwoWords(a[aI], b[bI], r2, r1);
			carry += BigIntUtil_addTwoInts(r2, r1, bI+aI, result, S); // there can be a carry during the last iteration of the outer loop here will never be a carry

		}
	}

	assert_msg(carry > 0, "mulSchool not posible without overflow (loop)");

	// multiply with last word if required
	if( (aSize + bSize - 1) == S ) {
		BigIntUtil_mulTwoWords(a[aSize-1], b[bSize-1], r2, r1);
		carry = r2;
		assert_msg(carry > 0, "mulSchool not posible without overflow (r2)");

		carry = BigIntUtil_addInt(r1, S-1, result, S);
		assert_msg(arry > 0, "mulSchool not posible without overflow (r1)");
	}
}

/*
 * @const
 * @public
 */
FIX_BIG_INT_VALUE UFixBigInt_mul(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE b) {
	FIX_BIG_INT_VALUE result;
	UFixBigInt_mulSchool(me, b, result);
	return result;
}



// ----- division -----

// -- divInt

/**
 * division by one unsigned word
 * restul = this / divisor
 *
 * returns the remainder
 *
 * @const
 * @protected
 */
BIG_INT_WORD_TYPE UFixBigInt_divInt(const in FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE divisor, out FIX_BIG_INT_VALUE result) {
	if(divisor == 0) {
		//std::string msg = "UArbBigInt devision by (uint)0.";
		//std::cerr << msg << std::endl;
		//throw std::invalid_argument(msg)
		assert_msg(divisor != 0, "UArbBigInt devision by (uint)0.")
		return 1/0;
	}

	if( divisor == 1 ) {
		result = me;
		return 0;
	}

	//UInt<value_size> dividend(*this);
	const FIX_BIG_INT_VALUE dividend = me;

	int i;  // i must be with a sign
	BIG_INT_WORD_TYPE r = 0;

	// we're looking for the last word in dividend (most significant word that is not null)
	//result.setZero();
	//for(i=S-1 ; i>0 && dividend[i]==0 ; --i);
	i = int(S) - 1;

	for( ; i>=0 ; --i) {
		BigIntUtil_divTwoWords(r, dividend[i], divisor, result[i], true, r);
	}

	return r;
}

/**
 * division by one unsigned word
 * this = this / divisor
 *
 * returns the remainder
 *
 * @protected
 */
BIG_INT_WORD_TYPE UFixBigInt_divInt(inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE divisor) {
	return UFixBigInt_divInt(me, divisor, me);
}


// -- divKnuth

/*
 * @const
 * @private
 * /
void UFixBigInt_divKnuth_division(UFixBigInt<S> divisor, UFixBigInt<S> &result, UFixBigInt<S>& remainder, uint m, uint n) const {
	// this: dividend
	assert(n >= 2);
	//assert(this != &remainder);

	//BIG_INT_WORD_COUNT_TYPE maxWordCount = this->wordSize;

	remainder = *this;

	//UInt<value_size+1> uu, vv;
	//UArbBigInt uu(0, maxWordCount+1);
	UFixBigInt<FBI_WC_Sp1> uu(0);
	//UArbBigInt vv(*this, maxWordCount+1);

	//UInt<value_size> q;
	//result.reserveWords(maxWordCount);

	uint d, j=m;
	BIG_INT_WORD_TYPE u_value_size, u0, u1, u2, v1, v0;

	u_value_size = remainder.divKnuth_normalize(divisor, n, d);

	if( j+n == S /*remainder.wordSize* / ) {
		u2 = u_value_size;
	} else {
		assert( (j+n) < S );
		u2 = remainder.value[j+n];
	}

	//Div3_MakeBiggerV(v, vv);
	//UArbBigInt vv(divisor, maxWordCount+1);
	UFixBigInt<FBI_WC_Sp1> vv(divisor);
	//std::copy(&divisor.value[0], (&divisor.value[0] + divisor.wordSize), vv);
	//vv[divisor.wordSize] = 0;

	//std::fill_n(&result.value[0], S, 0);
	result.setZero();

	while( true ) {
		assert( (j+n-1) < S );
		assert( (j+n-1) >= 0 );
		assert( (j+n-2) < S );
		assert( (j+n-2) >= 0 );
		assert( (n-1) < S );
		assert( (n-1) >= 0 );
		assert( (n-2) < S );
		assert( (n-2) >= 0 );

		u1 = remainder.value[j+n-1]; // divident high
		u0 = remainder.value[j+n-2]; // divident low
		v1 = divisor.value[n-1]; // divisor  high
		v0 = divisor.value[n-2]; // divident low

		BIG_INT_WORD_TYPE qp = this->divKnuth_calculate(u2,u1,u0, v1,v0);

		remainder.divKnuth_makeNewU(uu, j, n, u2);
		remainder.divKnuth_multiplySubtract(uu, vv, qp);
		remainder.divKnuth_copyNewU(uu, j, n);

		result.value[j] = qp;

		// the next loop
		if( j-- == 0 ) {
			break;
		}

		assert( (j+n) < S );
		u2 = remainder.value[j+n];
	}

	//BIG_INT_WORD_COUNT_TYPE newWordSize;
	//// trim reminder word size
	////for (newWordSize = n; newWordSize>1 && remainder.value[newWordSize-1] == 0; newWordSize--);
	////remainder.wordSize = newWordSize;
	//remainder.trimWordSize(n);

	//// set new word size of the result
	////for (newWordSize = maxWordCount; newWordSize>1 && result.value[newWordSize-1] == 0; newWordSize--);
	////result.wordSize = newWordSize;
	//result.trimWordSize(maxWordCount);

	//if( remainder ) {
	remainder.divKnuth_unnormalize(d);
	//}

	//*this = result;
}

/*
 * @const
 * @private
 * /
void UFixBigInt_divKnuth_makeNewU(UFixBigInt<FBI_WC_Sp1> &uu, const BIG_INT_WORD_COUNT_TYPE j, const BIG_INT_WORD_COUNT_TYPE n, const BIG_INT_WORD_TYPE u_max) const;

/*
 * @private
 * /
void UFixBigInt_divKnuth_copyNewU(const UFixBigInt<FBI_WC_Sp1> & uu, const BIG_INT_WORD_COUNT_TYPE j, const BIG_INT_WORD_COUNT_TYPE n);

/**
 * D1. [Normaliez]
 *
 * we're moving all bits from 'divisor' into the left side of the n-1 word
 * (the highest bit at divisor.value[n-1] will be equal one,
 * the bits from 'dividend' we're moving the same times as 'divisor')
 *
 * return values:
 * -  d - how many times we've moved
 * -  return - the next-left value from 'this' (that after value[value_size-1])
 *
 * @private
 * /
BIG_INT_WORD_TYPE UFixBigInt_divKnuth_normalize(UFixBigInt<S>& divisor, const uint n, uint& d);

/*
 * @private
 * /
void UFixBigInt_divKnuth_unnormalize(const BIG_INT_WORD_COUNT_TYPE d);

/*
 * @const
 * @private
 * /
BIG_INT_WORD_TYPE UFixBigInt_divKnuth_calculate(const BIG_INT_WORD_TYPE u2, const BIG_INT_WORD_TYPE u1, const BIG_INT_WORD_TYPE u0, const BIG_INT_WORD_TYPE v1, const BIG_INT_WORD_TYPE v0) const;

/**
 * D4. [Multiply and subtract]
 *		includes also: D5. [Test Remainder] and D6. [add back]
 *
 * @const
 * @private
 * /
void UFixBigInt_divKnuth_multiplySubtract(UFixBigInt<FBI_WC_Sp1> & uu,  const UFixBigInt<FBI_WC_Sp1> & vv, BIG_INT_WORD_TYPE & qp) const;

/**
 * the third division algorithm
 *
 * this algorithm is described in the following book:
 * "The art of computer programming 2" (4.3.1 page 257)
 * Donald E. Knuth
 * !! give the description here (from the book)
 *
 * @const
 * @private
 * /
void UFixBigInt_divKnuth(const UFixBigInt<S>& divisor, UFixBigInt<S> &result, UFixBigInt<S>& remainder) const;


/**
 * result = this / divisor
 *
 * @const
 * @protected
 * /
void UFixBigInt_div(const UFixBigInt<S>& divisor, UFixBigInt<S> &result, UFixBigInt<S>& remainder) const;

*/



// ----- comparisons -----

bool UFixBigInt_lessThan(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other) {
	for (BIG_INT_WORD_COUNT_TYPE i = (S - 1); i > 0; i--) {
		if (me[i] < other[i]) {
			return true;
		}

		if (me[i] > other[i]) {
			return false;
		}
	}
	return (me[0] < other[0]);
}

bool UFixBigInt_lessThanOrEqualTo(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other) {
	if (UFixBigInt_lessThan(me, other)) {
		return true;
	}

	if (UFixBigInt_equalTo(me, other)) {
		return true;
	}

	return false;
}

bool UFixBigInt_greaterThan(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other) {
	return (!(UFixBigInt_lessThanOrEqualTo(me, other)));
}

bool UFixBigInt_greaterThanOrEqualTo(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other) {
	return (!(UFixBigInt_lessThan(me, other)));
}

bool UFixBigInt_equalTo(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other) {
	if (UFixBigInt_lessThan(me, other)) {
		return false;
	}

	if (UFixBigInt_lessThan(other, me)) {
		return false;
	}

	return true;
}

bool UFixBigInt_notEqualTo(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other) {
	return (!(UFixBigInt_equalTo(me, other)));
}
