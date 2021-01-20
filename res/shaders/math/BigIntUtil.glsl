
#include "BigIntUtil.h.glsl"

// ----- bit utilities -----


BIG_INT_WORD_TYPE BigIntUtil_setLowFromLowBits(const in BIG_INT_WORD_TYPE target, const in BIG_INT_WORD_TYPE src) {
	BIG_INT_WORD_TYPE res =
	// set low bits to 0 and keep the high bits
	BigIntUtil_getHighAsHighBits(target)
	|
	// set high bits to 0 and keep the low bits
	BigIntUtil_getLowAsLowBits(src)
	;

	return res;
}

BIG_INT_WORD_TYPE BigIntUtil_setLowFromHighBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) {
	BIG_INT_WORD_TYPE res =
	// set low bits to 0 and keep the high bits
	//(target & BIG_INT_WORD_HIGH_BIT_MASK)
	BigIntUtil_getHighAsHighBits(target)
	|
	// move the high bits of src to the low bits
	//(src >> (BIG_INT_BITS_PER_WORD/2))
	BigIntUtil_getHighAsLowBits(src)
	;

	return res;
}

BIG_INT_WORD_TYPE BigIntUtil_setHighFromHighBits(const in BIG_INT_WORD_TYPE target, const in BIG_INT_WORD_TYPE src) {
	BIG_INT_WORD_TYPE res =
	// set high bits to 0 and keep the low bits
	BigIntUtil_getLowAsLowBits(target)
	|
	// set low bits to 0 and keep the high bits
	BigIntUtil_getHighAsHighBits(src)
	;

	return res;
}

BIG_INT_WORD_TYPE BigIntUtil_setHighFromLowBits(const in BIG_INT_WORD_TYPE target, const in BIG_INT_WORD_TYPE src) {
	BIG_INT_WORD_TYPE res =
	// set high bits to 0 and keep the low bits
	//(target & BIG_INT_WORD_LOW_BIT_MASK)
	BigIntUtil_getLowAsLowBits(target)
	|
	// move the low bits of src to the high bits
	//(src << (BIG_INT_BITS_PER_WORD/2))
	BigIntUtil_getLowAsHighBits(src)
	;

	return res;
}

BIG_INT_WORD_TYPE BigIntUtil_getHighAsHighBits(const in BIG_INT_WORD_TYPE src) {
	BIG_INT_WORD_TYPE res = (src & BIG_INT_WORD_HIGH_BIT_MASK);
	return res;
}

BIG_INT_WORD_TYPE BigIntUtil_getHighAsLowBits(const in BIG_INT_WORD_TYPE src) {
	BIG_INT_WORD_TYPE res = (src >> (BIG_INT_BITS_PER_WORD/2));
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
	res &= BIG_INT_WORD_ALL_BIT_MASK;
#endif
	return res;
}

BIG_INT_WORD_TYPE BigIntUtil_getLowAsLowBits(const in BIG_INT_WORD_TYPE src) {
	BIG_INT_WORD_TYPE res = (src & BIG_INT_WORD_LOW_BIT_MASK);
	return res;
}

BIG_INT_WORD_TYPE BigIntUtil_getLowAsHighBits(const in BIG_INT_WORD_TYPE src) {
	BIG_INT_WORD_TYPE res = (src << (BIG_INT_BITS_PER_WORD/2));
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
	res &= BIG_INT_WORD_ALL_BIT_MASK;
#endif
	return res;
}

// ----- addition -----

BIG_INT_WORD_TYPE BigIntUtil_addTwoWords(const in BIG_INT_WORD_TYPE a, const in BIG_INT_WORD_TYPE b, in BIG_INT_WORD_TYPE carry, out BIG_INT_WORD_TYPE result) {
	BIG_INT_WORD_TYPE temp;
	if( carry == 0 ) {
		temp = a + b;
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
		temp = temp & BIG_INT_WORD_ALL_BIT_MASK;
#endif
		if( temp < a ) {
			carry = 1;
		}
	} else {
		carry = 1;
		temp  = a + b + carry;
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
		temp = temp & BIG_INT_WORD_ALL_BIT_MASK;
#endif
		if( temp > a ) { // !(temp<=a)
			carry = 0;
		}
	}
	result = temp;
	return carry;
}

BIG_INT_WORD_TYPE BigIntUtil_addTwoInts(const in BIG_INT_WORD_TYPE wordHigh, const in BIG_INT_WORD_TYPE wordLow
	, const in BIG_INT_WORD_COUNT_TYPE index, inout FIX_BIG_INT_VALUE targetArray, const in BIG_INT_WORD_COUNT_TYPE targetWordCount) {
	//assert( index < (targetWordCount - 1) ); // TODO

	BIG_INT_WORD_TYPE c;

	c = BigIntUtil_addTwoWords(targetArray[index],   wordLow, 0, targetArray[index]);
	c = BigIntUtil_addTwoWords(targetArray[index+1], wordHigh, c, targetArray[index+1]);

	for(BIG_INT_WORD_COUNT_TYPE i=index+2 ; i < targetWordCount && c > 0; ++i) { // TODO
		c = BigIntUtil_addTwoWords(targetArray[i], 0, c, targetArray[i]);
	}
	return c;
}

BIG_INT_WORD_TYPE BigIntUtil_addInt(const in BIG_INT_WORD_TYPE word, const in BIG_INT_WORD_COUNT_TYPE index, inout FIX_BIG_INT_VALUE targetArray, const in BIG_INT_WORD_COUNT_TYPE targetWordCount) {
	//assert( index < targetWordCount );

	BIG_INT_WORD_TYPE c;
	c = BigIntUtil_addTwoWords(targetArray[index], word, 0, targetArray[index]);

	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c > 0; ++i) {
		c = BigIntUtil_addTwoWords(targetArray[i], 0, c, targetArray[i]);
	}

	return c;
}

// ----- multiplication -----

void BigIntUtil_mulTwoWords(const in BIG_INT_WORD_TYPE a, const in BIG_INT_WORD_TYPE b, out BIG_INT_WORD_TYPE resultHigh, out BIG_INT_WORD_TYPE resultLow) {
	/*
	 expect BIG_INT_WORD_TYPE to be a 64 bits variable:
	 we don't have a native type which has 128 bits
	 then we're splitting 'a' and 'b' to 4 parts (high and low halves)
	 and using 4 multiplications (with additions and carry correctness)
	 */

	BIG_INT_WORD_TYPE aLow = BigIntUtil_getLowAsLowBits(a); 		// aLow = a.low;
	BIG_INT_WORD_TYPE bLow = BigIntUtil_getLowAsLowBits(b); 		// aLow = b.low;
	BIG_INT_WORD_TYPE aHigh = BigIntUtil_getHighAsLowBits(a); 	// aHigh = a.high;
	BIG_INT_WORD_TYPE bHigh = BigIntUtil_getHighAsLowBits(b); 	// bHigh = b.high;

	BIG_INT_WORD_TYPE res_high1, res_high2;
	BIG_INT_WORD_TYPE res_low1, res_low2;

	/*
	 the multiplication is as follows (schoolbook algorithm with O(n^2) ):

	 32 bits          32 bits

	 +--------------------------------+
	 |     a.high     |     a.low     |
	 +--------------------------------+
	 |     b.high     |     b.low     |
	 +--------------------------------+--------------------------------+
	 |            res_high1           |            res_low1            |
	 +--------------------------------+--------------------------------+
	 |            res_high2           |            res_low2            |
	 +--------------------------------+--------------------------------+

	 64 bits                          64 bits
	 */


	BIG_INT_WORD_TYPE temp;

	res_low1  = bLow * aLow; 										// res_low1 = b.low * a.low
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
	res_low1 &= BIG_INT_WORD_ALL_BIT_MASK;
#endif
	temp 	  = BigIntUtil_getHighAsLowBits(res_low1) + bLow * aHigh;	// temp = res_low1.high + b.low * a.high
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
	temp &= BIG_INT_WORD_ALL_BIT_MASK;
#endif
	res_low1  = BigIntUtil_setHighFromLowBits(res_low1, temp); 			// res_low1.high = temp.low
	res_high1 = BigIntUtil_setLowFromHighBits(res_high1, temp); 			// res_high1.low = temp.high
	res_high1 = BigIntUtil_getLowAsLowBits(res_high1); 					// res_high1.high = 0

	res_low2  = BigIntUtil_getHighAsHighBits(res_low2); 					// res_low2.low = 0
	temp	  = bHigh * aLow; 										// b.high * a.low
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
	temp &= BIG_INT_WORD_ALL_BIT_MASK;
#endif
	res_low2  = BigIntUtil_setHighFromLowBits(res_low2, temp); 			// res_low2.high = temp.low

	res_high2 = bHigh * aHigh + BigIntUtil_getHighAsLowBits(temp); 		// res_high2 = b.high * a.high + temp.high
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
	res_high2 &= BIG_INT_WORD_ALL_BIT_MASK;
#endif

	BIG_INT_WORD_TYPE c = BigIntUtil_addTwoWords( res_low1,  res_low2, 0,  resultLow); // c = this->addTwoWords(res_low1, res_low2, 0, &res_low2)
	BigIntUtil_addTwoWords(res_high1, res_high2, c, resultHigh); // there is no carry from here
}
