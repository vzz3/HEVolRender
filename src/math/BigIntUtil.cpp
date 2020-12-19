
#include "BigIntUtil.hpp"
#include <cassert>


using namespace ppvr::math;

// ----- bit utilities -----

int BigIntUtil::findHighestSetBitInWord(BIG_INT_WORD_TYPE word) {
	if( word == 0 ) {
		return -1;
	}
	
	int bit = BIG_INT_BITS_PER_WORD - 1;
	
	while( (word & BIG_INT_WORD_HIGHEST_BIT) == 0 ) {
		word = word << 1;
		--bit;
	}
	
	return bit;
}

int BigIntUtil::findLowestSetBitInWord(BIG_INT_WORD_TYPE word) {
	if( word == 0 ) {
		return -1;
	}
	
	int bit = 0;
	
	while( (word & 1) == 0 ) {
		word = word >> 1;
		bit++;
	}
	
	return bit;
}

// ----- addition -----

BIG_INT_WORD_TYPE BigIntUtil::addTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE * result) {
	BIG_INT_WORD_TYPE temp;
	if( carry == 0 ) {
		temp = a + b;
		if( temp < a ) {
			carry = 1;
		}
	} else {
		carry = 1;
		temp  = a + b + carry;
		if( temp > a ) { // !(temp<=a)
			carry = 0;
		}
	}
	*result = temp;
	return carry;
}

BIG_INT_WORD_TYPE BigIntUtil::addTwoInts(const BIG_INT_WORD_TYPE wordHigh, const BIG_INT_WORD_TYPE wordLow, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) {
	assert( index < (targetWordCount - 1) ); // TODO
	
	BIG_INT_WORD_TYPE c;
	
	c = BigIntUtil::addTwoWords(targetArray[index],   wordLow, 0, &targetArray[index]);
	c = BigIntUtil::addTwoWords(targetArray[index+1], wordHigh, c, &targetArray[index+1]);
	
	for(BIG_INT_WORD_COUNT_TYPE i=index+2 ; i < targetWordCount && c > 0; ++i) { // TODO
		c = BigIntUtil::addTwoWords(targetArray[i], 0, c, &targetArray[i]);
	}
	return c;
}

/*
 void UArbBigInt::addTwoInts(const BIG_INT_WORD_TYPE wordHigh, const BIG_INT_WORD_TYPE wordLow, const BIG_INT_WORD_COUNT_TYPE index) {
 //assert( index < (targetWordCount - 1) ); // TODO
 this->reserveWords(index+2);
 
 BIG_INT_WORD_TYPE c;
 
 c = addTwoWords((index   < this->wordSize ? this->value[index  ] : 0),   wordLow, 0, &this->value[index  ]);
 c = addTwoWords((index+1 < this->wordSize ? this->value[index+1] : 0),  wordHigh, c, &this->value[index+1]);
 
 if(this->wordSize < index+2) {
 // increas word size if required
 if(this->value[index+1] != 0) {
 this->wordSize = index+2;
 } else if (this->value[index] != 0) {
 this->wordSize = index+1;
 }
 } else {
 // propagate carry to more significant words
 for(BIG_INT_WORD_COUNT_TYPE i=index+2 ; i < this->wordSize && c ; ++i) { // TODO
 c = addTwoWords(this->value[i], 0, c, &this->value[i]);
 }
 }
 
 // add carry to new word
 if(c != 0) {
 BIG_INT_WORD_COUNT_TYPE newWordSize = this->wordSize+1;
 this->reserveWords(newWordSize);
 this->value[this->wordSize] = c;
 this->wordSize = newWordSize;
 }
 }
 */

BIG_INT_WORD_TYPE BigIntUtil::addInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) {
	assert( index < targetWordCount );
	
	BIG_INT_WORD_TYPE c;
	c = BigIntUtil::addTwoWords(targetArray[index], word, 0, &targetArray[index]);
	
	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c ; ++i) {
		c = BigIntUtil::addTwoWords(targetArray[i], 0, c, &targetArray[i]);
	}
	
	return c;
}

// ----- substraction -----

BIG_INT_WORD_TYPE BigIntUtil::subTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE* result) {
	if( carry == 0 ) {
		*result = a - b;
		
		if( a < b ) {
			carry = 1;
		}
	} else {
		carry   = 1;
		*result = a - b - carry;
		
		if( a > b ) { // !(a <= b )
			carry = 0;
		}
	}
	
	return carry;
}

BIG_INT_WORD_TYPE BigIntUtil::subInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) {
	assert( index < targetWordCount );
	
	BIG_INT_WORD_TYPE c;
	c = subTwoWords(targetArray[index], word, 0, &targetArray[index]);
	
	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c ; ++i) {
		c = subTwoWords(targetArray[i], 0, c, &targetArray[i]);
	}
	
	return c;
}

// ----- multiplication -----

void BigIntUtil::mulTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE* resultHigh, BIG_INT_WORD_TYPE* resultLow) {
	/*
	 expect BIG_INT_WORD_TYPE to be a 64 bits variable:
	 we don't have a native type which has 128 bits
	 then we're splitting 'a' and 'b' to 4 parts (high and low halves)
	 and using 4 multiplications (with additions and carry correctness)
	 */
	
	BIG_INT_WORD_TYPE aLow = BigIntUtil::getLowAsLowBits(a); 		// aLow = a.low;
	BIG_INT_WORD_TYPE bLow = BigIntUtil::getLowAsLowBits(b); 		// aLow = b.low;
	BIG_INT_WORD_TYPE aHigh = BigIntUtil::getHighAsLowBits(a); 	// aHigh = a.high;
	BIG_INT_WORD_TYPE bHigh = BigIntUtil::getHighAsLowBits(b); 	// bHigh = b.high;
	
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
	temp 	  = BigIntUtil::getHighAsLowBits(res_low1) + bLow * aHigh;	// temp = res_low1.high + b.low * a.high
	res_low1  = BigIntUtil::setHighFromLowBits(res_low1, temp); 			// res_low1.high = temp.low
	res_high1 = BigIntUtil::setLowFromHighBits(res_high1, temp); 			// res_high1.low = temp.high
	res_high1 = BigIntUtil::getLowAsLowBits(res_high1); 					// res_high1.high = 0
	
	res_low2  = BigIntUtil::getHighAsHighBits(res_low2); 					// res_low2.low = 0
	temp	  = bHigh * aLow; 										// b.high * a.low
	res_low2  = BigIntUtil::setHighFromLowBits(res_low2, temp); 			// res_low2.high = temp.low
	
	res_high2 = bHigh * aHigh + BigIntUtil::getHighAsLowBits(temp); 		// res_high2 = b.high * a.high + temp.high
	
	BIG_INT_WORD_TYPE c = BigIntUtil::addTwoWords( res_low1,  res_low2, 0,  resultLow); // c = this->addTwoWords(res_low1, res_low2, 0, &res_low2)
	BigIntUtil::addTwoWords(res_high1, res_high2, c, resultHigh); // there is no carry from here
}

// ----- division -----

// -- divTwoWords

void BigIntUtil::divTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE divisor, BIG_INT_WORD_TYPE* result, BIG_INT_WORD_TYPE* remainder) {
	// c = divisor
	// (a < c ) for the result to be one word
	assert( divisor != 0 && a < divisor );
	
	if( a == 0 ) {
		*result    = b / divisor;
		if(remainder != NULL) {
			*remainder = b % divisor;
		}
	} else {
		if( BigIntUtil::getHighAsLowBits(divisor) == 0 ) {
			// higher half of 'divisor' is zero
			// then higher half of 'a' is zero too (look at the asserts at the beginning - 'a' is smaller than 'divisor')
			BIG_INT_WORD_TYPE res, temp1, temp2;
			
			temp1 = BigIntUtil::getLowAsHighBits(a); // this->setHighFromLowBits(temp1, a); 	// temp1.high 	= a.low
			temp1 = BigIntUtil::setLowFromHighBits(temp1, b); 								// temp1.low 	= b.high
			res = BigIntUtil::setHighFromLowBits(res, (temp1 / divisor)); 					// res_.high 	= (temp1.u / c).low
			temp2 = BigIntUtil::setHighFromLowBits(temp2, (temp1 % divisor)); 				// temp2.high 	= (temp1.u % c).low
			temp2 = BigIntUtil::setLowFromLowBits(temp2, b); 									// temp2.low 	= b.low
			res = BigIntUtil::setLowFromLowBits(res, (temp2 / divisor)); 						// res_.low 	= (temp2.u / c).low
			*result = res;
			
			if(remainder != NULL) {
				*remainder = temp2 % divisor;
			}
		} else {
			BigIntUtil::divTwoWordsKnuth(a, b, divisor,  result,  remainder);
		}
	}
}

// -- divTwoWordsKnuth

void BigIntUtil::divTwoWordsKnuth(BIG_INT_WORD_TYPE a, BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE c, BIG_INT_WORD_TYPE* result, BIG_INT_WORD_TYPE* remainder ) {
	// a is not zero
	// c.high is not zero
	
	BIG_INT_WORD_TYPE u, q, u3;
	BIG_INT_WORD_TYPE temp_qLow, temp_qHigh;
	
	// normalizing
	BIG_INT_WORD_TYPE d = BigIntUtil::divTwoWordsKnuth_normalize(a, b, c);
	
	u = a;
	
	u3 = BigIntUtil::getHighAsLowBits(b); // u3 = b.high
	q = BigIntUtil::setHighFromLowBits(q, BigIntUtil::divTwoWordsKnuth_calculate(u, u3, c)); // q.high = this->divTwoWordsCalculate(u, u3, c)
	
	temp_qHigh = BigIntUtil::getHighAsLowBits(q);
	BigIntUtil::divTwoWordsKnuth_multiplySubtract(u, u3, temp_qHigh, c); // this->divTwoWordsMultiplySubtract(u, u3, q.high, c)
	q = BigIntUtil::setHighFromLowBits(q, temp_qHigh);
	
	u = BigIntUtil::setHighFromLowBits(u, u); // u.high = u.low
	u = BigIntUtil::setLowFromLowBits(u, u3); // u.low = u3
	u3 = BigIntUtil::getLowAsLowBits(b); // u3 = b.low
	q = BigIntUtil::setLowFromLowBits(q, BigIntUtil::divTwoWordsKnuth_calculate(u, u3, c)); // q.low = this->divTwoWordsCalculate(u, u3, c)
	
	temp_qLow = BigIntUtil::getLowAsLowBits(q);
	BigIntUtil::divTwoWordsKnuth_multiplySubtract(u, u3, temp_qLow, c); // this->divTwoWordsMultiplySubtract(u_, u3, q_.u_.low, c_);
	q = BigIntUtil::setLowFromLowBits(q, temp_qLow);
	
	*result = q;
	
	if(remainder != NULL) {
		// unnormalizing for the remainder
		u = BigIntUtil::getLowAsHighBits(u); // this->setHighFromLowBits(u, u); // u.high = u.low
		u = BigIntUtil::setLowFromLowBits(u, u3); // u.low = u3;
		*remainder = BigIntUtil::divTwoWordsKnuth_unnormalize(u, d);
	}
}

BIG_INT_WORD_TYPE BigIntUtil::divTwoWordsKnuth_normalize(BIG_INT_WORD_TYPE &a, BIG_INT_WORD_TYPE &b, BIG_INT_WORD_TYPE &c) {
	uint d = 0;
	
	for( ; (c & BIG_INT_WORD_HIGHEST_BIT) == 0 ; ++d ) {
		c = c << 1;
		
		BIG_INT_WORD_TYPE bc = b & BIG_INT_WORD_HIGHEST_BIT; // carry from 'b'
		
		b = b << 1;
		a = a << 1; // carry bits from 'a' are simply skipped
		
		if( bc ) {
			a = a | 1;
		}
	}
	
	return d;
}

BIG_INT_WORD_TYPE BigIntUtil::divTwoWordsKnuth_unnormalize(BIG_INT_WORD_TYPE u, BIG_INT_WORD_TYPE d) {
	if( d == 0 ) {
		return u;
	}
	
	u = u >> d;
	
	return u;
}

unsigned int BigIntUtil::divTwoWordsKnuth_calculate(BIG_INT_WORD_TYPE u, BIG_INT_WORD_TYPE u3, BIG_INT_WORD_TYPE v) {
	bool nextTest;
	BIG_INT_WORD_TYPE qp, rp, temp;
	
	qp = u / BigIntUtil::getHighAsLowBits(v); // qp = u / v.high
	rp = u % BigIntUtil::getHighAsLowBits(v); // rp = u % v.high
	
	assert( BigIntUtil::getHighAsLowBits(qp) == 0 || BigIntUtil::getHighAsLowBits(qp) == 1); // assert( qp.hight == 0 || qp.high == 1);
	
	do {
		bool decrease = false;
		if( BigIntUtil::getHighAsLowBits(qp) == 1 ) { // if( qp.high == 1)
			decrease = true;
		} else {
			temp = BigIntUtil::setHighFromLowBits(temp, rp); // temp.hight = rp.low
			temp = BigIntUtil::setLowFromLowBits(temp, u3); // temp.low = u3.low
			
			if( qp * BigIntUtil::getLowAsLowBits(v) > temp) { // if( qp * v.low > temp )
				decrease = true;
			}
		}
		
		nextTest = false;
		
		if( decrease ) {
			--qp;
			rp += BigIntUtil::getHighAsLowBits(v); // rp += v.high
			
			if( BigIntUtil::getHighAsLowBits(rp) == 0) { // if( rp.high == 0 )
				nextTest = true;
			}
		}
	}
	while( nextTest );
	
	return BigIntUtil::getLowAsLowBits(qp); // return qp.low
}

void BigIntUtil::divTwoWordsKnuth_multiplySubtract(BIG_INT_WORD_TYPE &u, BIG_INT_WORD_TYPE & u3, BIG_INT_WORD_TYPE & q, BIG_INT_WORD_TYPE v) {
	BIG_INT_WORD_TYPE temp, res_high, res_low;
	BigIntUtil::mulTwoWords(v, q,  &res_high, &res_low);
	
	BIG_INT_WORD_TYPE sub_res_high, sub_res_low;
	
	temp = BigIntUtil::setHighFromLowBits(temp, u); // temp.high = u.low
	temp = BigIntUtil::setLowFromLowBits(temp, u3); // temp.low = u3.low
	
	BIG_INT_WORD_TYPE c = BigIntUtil::subTwoWords(temp, res_low, 0, &sub_res_low);
	
	temp = BigIntUtil::setHighFromLowBits(temp, 0); // temp.high = 0
	temp = BigIntUtil::setLowFromHighBits(temp, u); // temp.low = u.high
	c = BigIntUtil::subTwoWords(temp, res_high, c, &sub_res_high);
	
	if( c ) {
		--q;
		
		c = BigIntUtil::addTwoWords(sub_res_low, v, 0, &sub_res_low);
		BigIntUtil::addTwoWords(sub_res_high, 0, c, &sub_res_high);
	}
	
	u = BigIntUtil::setHighFromLowBits(u, sub_res_high); // u.high = sub_res_high.low
	u = BigIntUtil::setLowFromHighBits(u, sub_res_low); // u.low = sub_res_low.high
	u3 = BigIntUtil::getLowAsLowBits(sub_res_low); // u3 = sub_res_low.low;
}
