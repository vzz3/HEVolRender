
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





/**
 * this = this - word
 * returns the carry (borrow) if this was < word
 *
 * @protected
 */
BIG_INT_WORD_TYPE subInt(inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE word) {
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
 * /
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
		BigIntUtil::divTwoWords(r, dividend[i], divisor, &result.value[i], &r);
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
 * /
BIG_INT_WORD_TYPE UFixBigInt_divInt(const inout FIX_BIG_INT_VALUE me, const in BIG_INT_WORD_TYPE divisor) {
	return UFixBigInt_divInt(me, divisor, me);
}
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
