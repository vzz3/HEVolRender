
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

#ifdef FIX_BIG_INT_AUTO_SIZE_TEMP_VARS
/**
 * @private
 */
void UFixBigInt_initWords(out BIG_INT_WORD_TYPE[FBI_WC_Sp1] dst, const in BIG_INT_WORD_TYPE initValue) {
	//std::fill_n(&this->value[0], S, initValue);
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<S; i++) {
		dst[i] = initValue;
	}
}
#endif

/**
 * @private
 */
void UFixBigInt_copy(const in FIX_BIG_INT_VALUE me, out BIG_INT_WORD_TYPE[FBI_WC_Sp1] target) {
	BIG_INT_WORD_COUNT_TYPE i;
	for (i = 0; i<S; i++) {
		target[i] = me[i];
	}

	for ( ; i<FBI_WC_Sp1; i++) {
		target[i] = 0;
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

#ifdef FIX_BIG_INT_AUTO_SIZE_TEMP_VARS
/*
 * @protected
 */
void UFixBigInt_setZero(out BIG_INT_WORD_TYPE[FBI_WC_Sp1] dst) {
	UFixBigInt_initWords(dst, 0);
}
#endif

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

// ----- word utilities -----
/**
 * @const
 * @public
 */
BIG_INT_WORD_COUNT_TYPE UFixBigInt_getWordSize(const in FIX_BIG_INT_VALUE me) {
	int wordIndex;
	for(wordIndex=int(S)-1; wordIndex > 0 && me[wordIndex] == 0; wordIndex--);
	return wordIndex + 1;
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
BIG_INT_WORD_TYPE UFixBigInt_subInt(inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE word) {
	BIG_INT_WORD_TYPE c = BigIntUtil_subInt(word, 0, me, S);

	// reduce word size if a word was truncated
	//if(this->value[this->wordSize-1] == 0) {
	//	this->wordSize = this->wordSize-1;
	//}

	return c;
}

// TODO: template
BIG_INT_WORD_TYPE UFixBigInt_subInt(inout BIG_INT_WORD_TYPE[2] me, const BIG_INT_WORD_TYPE word) {
	BIG_INT_WORD_COUNT_TYPE index = 0;
	BIG_INT_WORD_COUNT_TYPE targetWordCount = 2;

	BIG_INT_WORD_TYPE c;
	c = BigIntUtil_subTwoWords(me[index], word, 0, me[index]);

	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c > 0; ++i) {
		c = BigIntUtil_subTwoWords(me[i], 0, c, me[i]);
	}

	return c;

	/*
	assert( index < targetWordCount );

	BIG_INT_WORD_TYPE c;
	c = BigIntUtil_subTwoWords(targetArray[index], word, 0, targetArray[index]);

	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c > 0; ++i) {
		c = BigIntUtil_subTwoWords(targetArray[i], 0, c, targetArray[i]);
	}

	return c;
	*/
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
 * multiplication: result = this * ss2
 *
 * The result size R need to be greater then the size of this value therefore there can not be a carry
 *
 * @const
 * @protected
 */
void UFixBigInt_mulInt(const in FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE ss2, out FIX_BIG_INT_VALUE result) {
	//assert(S < R);
	UFixBigInt_setZero(result);

	if( ss2 == 0 ) {
		return;
	}

	BIG_INT_WORD_TYPE r2,r1;
	BIG_INT_WORD_COUNT_TYPE x1size=S;
	BIG_INT_WORD_COUNT_TYPE x1start=0;

	// try to save some CPU sycles if this contains words with 0 at the start or at the end
	if( S > 2 ) {
		// if this word count is smaller than or equal to 2
		// there is no sense to set x1size and x1start to another values

		for(x1size=S ; x1size>0 && me[x1size-1]==0 ; --x1size);

		if( x1size == 0 ) {
			// this is 0: 0*x => 0
			//result.setZero();
			return;
		}

		for(x1start=0 ; x1start<x1size && me[x1start]==0 ; ++x1start);
	}

	// performe the multiplication
	//for(BIG_INT_WORD_COUNT_TYPE x1=x1start ; x1<x1size ; ++x1) {
	for(BIG_INT_WORD_COUNT_TYPE x1=x1start ; x1<x1size && x1 < (S-1); ++x1) {
		BigIntUtil_mulTwoWords(me[x1], ss2, r2, r1 );
		BigIntUtil_addTwoInts(r2, r1, x1, result, S); // this->wordCapacity is > u.wordSize => there can not be a carry bit!
	}

	// multiply with last word if required
	if(x1size == S) {
		BIG_INT_WORD_TYPE carry;

		BigIntUtil_mulTwoWords(me[S-1], ss2, r2, r1);
		carry = r2;
		assert_msg(carry > 0, "mulInt not posible without overflow (r2)");

		carry = BigIntUtil_addInt(r1, S-1, result, S);
		assert_msg(carry > 0, "mulInt not posible without overflow (r1)");
	}
}

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

BIG_INT_WORD_TYPE UFixBigInt_divInt(const in FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE divisor, out FIX_BIG_INT_VALUE result) {
	if(divisor == 0) {
		//std::string msg = "UArbBigInt devision by (uint)0.";
		//std::cerr << msg << std::endl;
		//throw std::invalid_argument(msg)
		assert_msg(divisor != 0, "UFixBigInt devision by (uint)0.")
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

// TODO: template
BIG_INT_WORD_TYPE UFixBigInt_divInt(const in BIG_INT_WORD_TYPE[2] me, const in BIG_INT_WORD_TYPE divisor, out BIG_INT_WORD_TYPE[2] result) {
	if(divisor == 0) {
		assert_msg(divisor != 0, "UFixBigInt devision by (uint)0.")
		return 1/0;
	}

	if( divisor == 1 ) {
		result = me;
		return 0;
	}

	//UInt<value_size> dividend(*this);
	const BIG_INT_WORD_TYPE[2] dividend = me;

	int i;  // i must be with a sign
	BIG_INT_WORD_TYPE r = 0;

	// we're looking for the last word in dividend (most significant word that is not null)
	//result.setZero();
	//for(i=S-1 ; i>0 && dividend[i]==0 ; --i);
	i = int(2) - 1;

	for( ; i>=0 ; --i) {
		BigIntUtil_divTwoWords(r, dividend[i], divisor, result[i], true, r);
	}

	return r;
}


BIG_INT_WORD_TYPE UFixBigInt_divInt(inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE divisor) {
	return UFixBigInt_divInt(me, divisor, me);
}


// -- divKnuth

void UFixBigInt_divKnuth_division(const in FIX_BIG_INT_VALUE me, in FIX_BIG_INT_VALUE divisor, out FIX_BIG_INT_VALUE result, out FIX_BIG_INT_VALUE remainder, const in uint m, const in uint n) {
	// this: dividend
	assert(n >= 2);
	//assert(this != &remainder);

	//BIG_INT_WORD_COUNT_TYPE maxWordCount = this->wordSize;

	remainder = me;

	//UInt<value_size+1> uu, vv;
	//UArbBigInt uu(0, maxWordCount+1);
	BIG_INT_WORD_TYPE[FBI_WC_Sp1] uu;
	UFixBigInt_setZero(uu);

	//UArbBigInt vv(*this, maxWordCount+1);

	//UInt<value_size> q;
	//result.reserveWords(maxWordCount);

	uint d, j=m;
	BIG_INT_WORD_TYPE u_value_size, u0, u1, u2, v1, v0;

	u_value_size = UFixBigInt_divKnuth_normalize(remainder, divisor, n, d);

	if( j+n == S /*remainder.wordSize*/ ) {
		u2 = u_value_size;
	} else {
		assert( (j+n) < S );
		u2 = remainder[j+n];
	}

	//Div3_MakeBiggerV(v, vv);
	//UArbBigInt vv(divisor, maxWordCount+1);
	BIG_INT_WORD_TYPE[FBI_WC_Sp1] vv;
	UFixBigInt_copy(divisor, vv);
	//std::copy(&divisor.value[0], (&divisor.value[0] + divisor.wordSize), vv);
	//vv[divisor.wordSize] = 0;

	//std::fill_n(&result.value[0], S, 0);
	UFixBigInt_setZero(result);

	while( true ) {
		assert( (j+n-1) < S );
		assert( (j+n-1) >= 0 );
		assert( (j+n-2) < S );
		assert( (j+n-2) >= 0 );
		assert( (n-1) < S );
		assert( (n-1) >= 0 );
		assert( (n-2) < S );
		assert( (n-2) >= 0 );

		u1 = remainder[j+n-1]; // divident high
		u0 = remainder[j+n-2]; // divident low
		v1 = divisor[n-1]; // divisor  high
		v0 = divisor[n-2]; // divident low

		BIG_INT_WORD_TYPE qp = UFixBigInt_divKnuth_calculate(u2, u1, u0, v1, v0); // apple metal compiler: XPC_ERROR_CONNECTION_INTERRUPTED

		UFixBigInt_divKnuth_makeNewU(remainder, uu, j, n, u2);
		UFixBigInt_divKnuth_multiplySubtract(uu, vv, qp);
		UFixBigInt_divKnuth_copyNewU(remainder, uu, j, n);

		result[j] = qp;

		// the next loop
		if( j-- == 0 ) {
			break;
		}

		assert( (j+n) < S );
		u2 = remainder[j+n];
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
	UFixBigInt_divKnuth_unnormalize(remainder, d);
	//}

	//*this = result;
}

void UFixBigInt_divKnuth_makeNewU(const in FIX_BIG_INT_VALUE me, inout BIG_INT_WORD_TYPE[FBI_WC_Sp1] uu, in BIG_INT_WORD_COUNT_TYPE j, const in BIG_INT_WORD_COUNT_TYPE n, const in BIG_INT_WORD_TYPE u_max) {
	BIG_INT_WORD_COUNT_TYPE i;

	assert( (j+n) <= (FBI_WC_Sp1) );
	//std::copy_n(&this->value[j], n, &uu.value[0]);
	//i = n;
	for(i=0 ; i<n ; ++i, ++j) {
		uu[i] = me[j];
	}

	// 'n' is from <1..value_size> so and 'i' is from <0..value_size>
	// then table[i] is always correct (look at the declaration of 'uu')
	uu[i] = u_max;


	//for( ++i ; i<value_size+1 ; ++i)
	//	uu.table[i] = 0;
	//uu.wordSize = i+1;
	assert( ((i+1) + ((FBI_WC_Sp1) - (i+1))) == (FBI_WC_Sp1) );
}

void UFixBigInt_divKnuth_copyNewU(inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE[FBI_WC_Sp1] uu, const in BIG_INT_WORD_COUNT_TYPE j, const in BIG_INT_WORD_COUNT_TYPE n) {
	BIG_INT_WORD_COUNT_TYPE i;

	for(i=0 ; i<n ; ++i) {
		assert( (i+j) < S );
		assert( i < (FBI_WC_Sp1) ) ;
		me[i+j] = uu[i];
	}

	if( i+j < S ) {
		assert( (i+j) < S );
		assert( i < (FBI_WC_Sp1) ) ;
		me[i+j] = uu[i];
	}
}

BIG_INT_WORD_TYPE UFixBigInt_divKnuth_normalize(inout FIX_BIG_INT_VALUE me, inout FIX_BIG_INT_VALUE divisor, const in uint n, out uint d) {
	// this = dividend, v = divisor
	// v.table[n-1] is != 0

	assert( (n-1) < S );
	uint bit  = uint(BigIntUtil_findHighestSetBitInWord(divisor[n-1])); // TODO divisor.value[divisor.wordSize - 1] ?
	uint move = (BIG_INT_BITS_PER_WORD - bit - 1);
	d         = move;
	BIG_INT_WORD_TYPE res  = me[S - 1];

	if( move > 0 ) {
		UFixBigInt_rcl(divisor, move, 0);
		UFixBigInt_rcl(me, move, 0);
		res = res >> (bit + 1); // this is the same as the bits that was shiftet out by "this->rcl(move, 0)" - the teoretical new most significant word of this
	}
	else {
		res = 0;
	}

	return res;
}

void UFixBigInt_divKnuth_unnormalize(inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_COUNT_TYPE d) {
	UFixBigInt_rcr(me, d, 0);
	//*remainder = *this;
}

BIG_INT_WORD_TYPE UFixBigInt_divKnuth_calculate(const in BIG_INT_WORD_TYPE u2, const in BIG_INT_WORD_TYPE u1, const in BIG_INT_WORD_TYPE u0, const in BIG_INT_WORD_TYPE v1, const in BIG_INT_WORD_TYPE v0) {

	BIG_INT_WORD_TYPE rp, c;
	bool next_test;

	assert( v1 != 0 );


	 BIG_INT_WORD_TYPE[2] qp; // TODO array with 2 elements is enought, but with do not have a template engine that can generate the required divInt() & subInt() methods version
	// simple solution: use a full size FIX_BIG_INT_VALUE array
	//BIG_INT_WORD_TYPE[S] qp;
	//UFixBigInt_setZero(qp); // => 2021-01-23 16:56:45.054390+0100 ppvr_vulkan[73836:8391347] Compiler failed with XPC_ERROR_CONNECTION_INTERRUPTED 	...I realy have no idea why! But the loop below works as workaround...
	qp[0] = u1;
	qp[1] = u2;
	//qp[2] = 0u;
	//qp[4] = 0u;
	//qp[5] = 0u;
	//for (BIG_INT_WORD_COUNT_TYPE i = 2; i<4; i++) {
	//	qp[i] = 0;
	//}

	//u_temp.DivInt(v1, &rp);
	rp = UFixBigInt_divInt(qp, v1, qp);

	//TTMATH_ASSERT( u_temp.table[1]==0 || u_temp.table[1]==1 )
	assert( qp.value[1]==0 || qp.value[1]==1 );

	do {
		bool decrease = false;

		if( qp[1] == 1 ) {
			decrease = true;
		} else {
			//UInt<2> temp1, temp2;
			BIG_INT_WORD_TYPE temp1[2], temp2[2];

			//UInt<2>::MulTwoWords(u_temp.table[0], v0, temp1.table+1, temp1.table);
			BigIntUtil_mulTwoWords(qp[0], v0, temp1[1], temp1[0]);
			temp2[1] = rp;
			temp2[0] = u0;

			//if( temp1 > temp2 ) {
			if(temp1[1] > temp2[1] || (temp1[1] == temp2[1] && temp1[0] > temp2[0])) {
				decrease = true;
			}
		}

		next_test = false;

		if( decrease ) {
			//qp.SubOne();
			//this->subInt(1, 0, &qp.value[0], 2);
			UFixBigInt_subInt(qp, 1);

			rp += v1;

			if( rp >= v1 ) { // it means that there wasn't a carry (r<b from the book)
				next_test = true;
			}
		}
	}
	while( next_test );

	//qp.value = NULL;
	return qp[0];
}

void UFixBigInt_divKnuth_multiplySubtract(inout BIG_INT_WORD_TYPE[FBI_WC_Sp1] uu, const in BIG_INT_WORD_TYPE[FBI_WC_Sp1] vv, inout BIG_INT_WORD_TYPE qp) {
	// D4 (in the book)

	BIG_INT_WORD_TYPE[FBI_WC_Sp1] vv_temp; UFixBigInt_setZero(vv_temp);

	//UArbBigInt vv_temp(vv);
	UFixBigInt_mulInt(vv, qp, vv_temp);

	//  D5. [Test Remainder]
	if( UFixBigInt_sub(uu, vv_temp, 0, uu) > 0 ) {
		// there was a carry (borrow)
		// D6. [add back]

		//
		// TODO make shure to test this code because the execution of this part is very unlikely (only of the order 2/b)
		//
		//BIG_INT_WORD_COUNT_TYPE uuWordSizeWithoutCarry = uu.wordSize;

		--qp;
		UFixBigInt_add(uu, vv, uu);

		// There can be a carry from this additions but it should be ignored
		// because it cancels with the borrow from uu.Sub(vv_temp).
		// My add() method does not return a carry bit because it automaticaly adds another most significant word.
		// Therefore, I truncate this word again (if it was added.);
		//uu.wordSize = uuWordSizeWithoutCarry;
	}
}

void UFixBigInt_divKnuth(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE divisor, out FIX_BIG_INT_VALUE result, out FIX_BIG_INT_VALUE remainder) {
	const FIX_BIG_INT_VALUE dividend = me;
	if(UFixBigInt_isZero(divisor)) {
		//std::string msg = "UArbBigInt devision by (UArbBigInt)0.";
		//std::cerr << msg << std::endl;
		//throw std::invalid_argument(msg);
		assert_msg(divisor != 0, "UFixBigInt devision by (UFixBigInt)0.")
		UFixBigInt_isZero(result); result[0] = 1/0;
		UFixBigInt_isZero(remainder); remainder[0] = 1/0;
		return;
	}
	if(UFixBigInt_lessThan(dividend, divisor)) {
		// set the reminder to this value and replace this with "0";
		remainder = me;
		UFixBigInt_setZero(result);
		return;
	}
	if(UFixBigInt_isZero(dividend)) {
		// 0/x => result = 0; remainder = 0
		UFixBigInt_setZero(remainder);
		UFixBigInt_setZero(result);
		return;
	}
	if(UFixBigInt_equalTo(dividend, divisor)) {
		// x/x => result = 1; remainder = 0
		UFixBigInt_setZero(remainder);
		UFixBigInt_setOne(result);
		return;
	}

	//uint m,n, test;

	//  'm' - is the index (from 0) of last non-zero word in this->value ('dividend')
	//  'n' - is the index (from 0) of last non-zero word in divisor.value
	BIG_INT_WORD_COUNT_TYPE m = UFixBigInt_getWordSize(dividend) - 1;
	BIG_INT_WORD_COUNT_TYPE n = UFixBigInt_getWordSize(divisor) - 1;

	//test = Div_StandardTest(v, m, n, remainder);
	//if( test < 2 )
	//	return test;

	if( n == 0 ) {
		BIG_INT_WORD_TYPE r;
		r = UFixBigInt_divInt(me,  divisor[0], result );
		//if( remainder ) {
		UFixBigInt_setZero(remainder);
		remainder[0] = r;
		//remainder.wordSize = 1;
		//}
		return;
	}

	// we can only use the third division algorithm when
	// the divisor is greater or equal 2^32 (has more than one 32-bit word)
	++m;
	++n;
	m = m - n;

	UFixBigInt_divKnuth_division(me, divisor, result, remainder, m, n);
}


/**
 * result = this / divisor
 *
 * @const
 * @protected
 */
void UFixBigInt_div(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE divisor, out FIX_BIG_INT_VALUE result, out FIX_BIG_INT_VALUE remainder) {
	 UFixBigInt_divKnuth(me, divisor, result, remainder);
}

/*
 * @const
 * @public
 */
FIX_BIG_INT_VALUE UFixBigInt_div(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other) {
	FIX_BIG_INT_VALUE result, reminder;
	UFixBigInt_div(me, other, result, reminder);
	return result;
}

/*
 * @const
 * @public
 */
FIX_BIG_INT_VALUE UFixBigInt_mod(const in FIX_BIG_INT_VALUE me, const in FIX_BIG_INT_VALUE other) {
	FIX_BIG_INT_VALUE result, reminder;
	UFixBigInt_div(me, other, result, reminder);
	return reminder;
}





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
