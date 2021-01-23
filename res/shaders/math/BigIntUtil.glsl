
#include "BigIntUtil.h.glsl"
#include "../lib/assert.h.glsl"

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
	assert( index < (targetWordCount - 1) ); // TODO

	BIG_INT_WORD_TYPE c;

	c = BigIntUtil_addTwoWords(targetArray[index],   wordLow, 0, targetArray[index]);
	c = BigIntUtil_addTwoWords(targetArray[index+1], wordHigh, c, targetArray[index+1]);

	for(BIG_INT_WORD_COUNT_TYPE i=index+2 ; i < targetWordCount && c > 0; ++i) { // TODO
		c = BigIntUtil_addTwoWords(targetArray[i], 0, c, targetArray[i]);
	}
	return c;
}

BIG_INT_WORD_TYPE BigIntUtil_addInt(const in BIG_INT_WORD_TYPE word, const in BIG_INT_WORD_COUNT_TYPE index, inout FIX_BIG_INT_VALUE targetArray, const in BIG_INT_WORD_COUNT_TYPE targetWordCount) {
	assert( index < targetWordCount );

	BIG_INT_WORD_TYPE c;
	c = BigIntUtil_addTwoWords(targetArray[index], word, 0, targetArray[index]);

	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c > 0; ++i) {
		c = BigIntUtil_addTwoWords(targetArray[i], 0, c, targetArray[i]);
	}

	return c;
}


// ----- substraction -----

BIG_INT_WORD_TYPE BigIntUtil_subTwoWords(const in BIG_INT_WORD_TYPE a, const in BIG_INT_WORD_TYPE b, in BIG_INT_WORD_TYPE carry, out BIG_INT_WORD_TYPE result) {
	if( carry == 0 ) {
		result = a - b;
		if( a < b ) {
			carry = 1;
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
			result = result & BIG_INT_WORD_ALL_BIT_MASK;
#endif
		}
	} else {
		carry   = 1;
		result = a - b - carry;

		if( a > b ) { // !(a <= b )
			carry = 0;
		} else {
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
			result = result & BIG_INT_WORD_ALL_BIT_MASK;
#endif
		}
	}

	return carry;
}

BIG_INT_WORD_TYPE BigIntUtil_subInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, inout FIX_BIG_INT_VALUE targetArray, const in BIG_INT_WORD_COUNT_TYPE targetWordCount) {
	assert( index < targetWordCount );

	BIG_INT_WORD_TYPE c;
	c = BigIntUtil_subTwoWords(targetArray[index], word, 0, targetArray[index]);

	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c > 0; ++i) {
		c = BigIntUtil_subTwoWords(targetArray[i], 0, c, targetArray[i]);
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
	res_high1 = 0; // not required, just silence the worning  "initialize the variable 'res_high1'..."
	res_high1 = BigIntUtil_setLowFromHighBits(res_high1, temp); 			// res_high1.low = temp.high
	res_high1 = BigIntUtil_getLowAsLowBits(res_high1); 					// res_high1.high = 0

	res_low2  = 0;//BigIntUtil_getHighAsHighBits(res_low2); 					// res_low2.low = 0
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




// ----- division -----

// -- divTwoWords

void BigIntUtil_divTwoWords(const in BIG_INT_WORD_TYPE a, const in BIG_INT_WORD_TYPE b, const in BIG_INT_WORD_TYPE divisor, out BIG_INT_WORD_TYPE result, const in bool includeRemainder, out BIG_INT_WORD_TYPE remainder) {
	// c = divisor
	// (a < c ) for the result to be one word
	assert( divisor != 0 && a < divisor );

	if( a == 0 ) {
		result    = b / divisor;
		if(includeRemainder) {
			remainder = b % divisor;
		}
	} else {
		if( BigIntUtil_getHighAsLowBits(divisor) == 0 ) {
			// higher half of 'divisor' is zero
			// then higher half of 'a' is zero too (look at the asserts at the beginning - 'a' is smaller than 'divisor')
			BIG_INT_WORD_TYPE res, temp1, temp2;

			temp1 = BigIntUtil_getLowAsHighBits(a); // this->setHighFromLowBits(temp1, a); 	// temp1.high 	= a.low
			temp1 = BigIntUtil_setLowFromHighBits(temp1, b); 								// temp1.low 	= b.high
			res   = BigIntUtil_setHighFromLowBits(res, (temp1 / divisor)); 					// res_.high 	= (temp1.u / c).low
			temp2 = BigIntUtil_setHighFromLowBits(temp2, (temp1 % divisor)); 				// temp2.high 	= (temp1.u % c).low
			temp2 = BigIntUtil_setLowFromLowBits(temp2, b); 									// temp2.low 	= b.low
			res   = BigIntUtil_setLowFromLowBits(res, (temp2 / divisor)); 						// res_.low 	= (temp2.u / c).low
			result = res;

			if(includeRemainder) {
				remainder = temp2 % divisor;
			}
		} else {
			BigIntUtil_divTwoWordsKnuth(a, b, divisor,  result,  includeRemainder, remainder);
		}
	}
}

// -- divTwoWordsKnuth

void BigIntUtil_divTwoWordsKnuth(in BIG_INT_WORD_TYPE a, in BIG_INT_WORD_TYPE b, in BIG_INT_WORD_TYPE c, out BIG_INT_WORD_TYPE result, const in bool includeRemainder, out BIG_INT_WORD_TYPE remainder ) {
	// a is not zero
	// c.high is not zero

	BIG_INT_WORD_TYPE u, q, u3;
	BIG_INT_WORD_TYPE temp_qLow, temp_qHigh;

	// normalizing
	BIG_INT_WORD_TYPE d = BigIntUtil_divTwoWordsKnuth_normalize(a, b, c);

	u = a;

	u3 = BigIntUtil_getHighAsLowBits(b); // u3 = b.high
	q = BigIntUtil_setHighFromLowBits(q, BigIntUtil_divTwoWordsKnuth_calculate(u, u3, c)); // q.high = this->divTwoWordsCalculate(u, u3, c)

	temp_qHigh = BigIntUtil_getHighAsLowBits(q);
	BigIntUtil_divTwoWordsKnuth_multiplySubtract(u, u3, temp_qHigh, c); // this->divTwoWordsMultiplySubtract(u, u3, q.high, c)
	q = BigIntUtil_setHighFromLowBits(q, temp_qHigh);

	u = BigIntUtil_setHighFromLowBits(u, u); // u.high = u.low
	u = BigIntUtil_setLowFromLowBits(u, u3); // u.low = u3
	u3 = BigIntUtil_getLowAsLowBits(b); // u3 = b.low
	q = BigIntUtil_setLowFromLowBits(q, BigIntUtil_divTwoWordsKnuth_calculate(u, u3, c)); // q.low = this->divTwoWordsCalculate(u, u3, c)

	temp_qLow = BigIntUtil_getLowAsLowBits(q);
	BigIntUtil_divTwoWordsKnuth_multiplySubtract(u, u3, temp_qLow, c); // this->divTwoWordsMultiplySubtract(u_, u3, q_.u_.low, c_);
	q = BigIntUtil_setLowFromLowBits(q, temp_qLow);

	result = q;

	if(includeRemainder) {
		// unnormalizing for the remainder
		u = BigIntUtil_getLowAsHighBits(u); // this->setHighFromLowBits(u, u); // u.high = u.low
		u = BigIntUtil_setLowFromLowBits(u, u3); // u.low = u3;
		remainder = BigIntUtil_divTwoWordsKnuth_unnormalize(u, d);
	}
}

uint BigIntUtil_divTwoWordsKnuth_normalize(inout BIG_INT_WORD_TYPE a, inout BIG_INT_WORD_TYPE b, inout BIG_INT_WORD_TYPE c) {
	uint d = 0;

	for( ; (c & BIG_INT_WORD_HIGHEST_BIT) == 0 ; ++d ) {
		c = c << 1;

		BIG_INT_WORD_TYPE bc = b & BIG_INT_WORD_HIGHEST_BIT; // carry from 'b'

		b = b << 1;
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
		b &= BIG_INT_WORD_ALL_BIT_MASK;
#endif
		a = a << 1; // carry bits from 'a' are simply skipped
#ifdef BIG_INT_LESS_BITS_THEN_WORD_TYPE
		a &= BIG_INT_WORD_ALL_BIT_MASK;
#endif

		if( bc > 0 ) {
			a = a | 1;
		}
	}

	return d;
}

BIG_INT_WORD_TYPE BigIntUtil_divTwoWordsKnuth_unnormalize(in BIG_INT_WORD_TYPE u, const in uint d) {
	if( d == 0 ) {
		return u;
	}

	u = u >> d;

	return u;
}

BIG_INT_WORD_TYPE BigIntUtil_divTwoWordsKnuth_calculate(const in BIG_INT_WORD_TYPE u, const in BIG_INT_WORD_TYPE u3, const in BIG_INT_WORD_TYPE v) {
	bool nextTest;
	BIG_INT_WORD_TYPE qp, rp, temp;

	qp = u / BigIntUtil_getHighAsLowBits(v); // qp = u / v.high
	rp = u % BigIntUtil_getHighAsLowBits(v); // rp = u % v.high

	assert( BigIntUtil_getHighAsLowBits(qp) == 0 || BigIntUtil_getHighAsLowBits(qp) == 1); // assert( qp.hight == 0 || qp.high == 1);

	do {
		bool decrease = false;
		if( BigIntUtil_getHighAsLowBits(qp) == 1 ) { // if( qp.high == 1)
			decrease = true;
		} else {
			temp = BigIntUtil_setHighFromLowBits(temp, rp); // temp.hight = rp.low
			temp = BigIntUtil_setLowFromLowBits(temp, u3); // temp.low = u3.low

			if( qp * BigIntUtil_getLowAsLowBits(v) > temp) { // if( qp * v.low > temp )
				decrease = true;
			}
		}

		nextTest = false;

		if( decrease ) {
			--qp;
			rp += BigIntUtil_getHighAsLowBits(v); // rp += v.high

			if( BigIntUtil_getHighAsLowBits(rp) == 0) { // if( rp.high == 0 )
				nextTest = true;
			}
		}
	}
	while( nextTest );

	return BigIntUtil_getLowAsLowBits(qp); // return qp.low
}

void BigIntUtil_divTwoWordsKnuth_multiplySubtract(inout BIG_INT_WORD_TYPE u, inout BIG_INT_WORD_TYPE u3, inout BIG_INT_WORD_TYPE q, const in BIG_INT_WORD_TYPE v) {
	BIG_INT_WORD_TYPE temp, res_high, res_low;
	BigIntUtil_mulTwoWords(v, q,  res_high, res_low);

	BIG_INT_WORD_TYPE sub_res_high, sub_res_low;

	temp = BigIntUtil_setHighFromLowBits(temp, u); // temp.high = u.low
	temp = BigIntUtil_setLowFromLowBits(temp, u3); // temp.low = u3.low

	BIG_INT_WORD_TYPE c = BigIntUtil_subTwoWords(temp, res_low, 0, sub_res_low);

	temp = BigIntUtil_setHighFromLowBits(temp, 0); // temp.high = 0
	temp = BigIntUtil_setLowFromHighBits(temp, u); // temp.low = u.high
	c = BigIntUtil_subTwoWords(temp, res_high, c, sub_res_high);

	if( c > 0) {
		--q;

		c = BigIntUtil_addTwoWords(sub_res_low, v, 0, sub_res_low);
		BigIntUtil_addTwoWords(sub_res_high, 0, c, sub_res_high);
	}

	u = BigIntUtil_setHighFromLowBits(u, sub_res_high); // u.high = sub_res_high.low
	u = BigIntUtil_setLowFromHighBits(u, sub_res_low); // u.low = sub_res_low.high
	u3 = BigIntUtil_getLowAsLowBits(sub_res_low); // u3 = sub_res_low.low;
}
