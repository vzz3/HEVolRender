
#include "BigInt.h"
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace ppvr::math;

BigInt BigInt::ZERO(0);
BigInt BigInt::ONE(1);
BigInt BigInt::TWO(2);
BigInt BigInt::TEN(10);

BigInt BigInt::fromUint64(const uint64_t& uint64Val) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = 1;
	size_t wordsFor64Bit = (sizeof(uint64_t) * CHAR_BIT) / BIG_INT_BITS_PER_WORD;
	
	// calculate required word count (move bits of uint64Val to the right by BITS_PER_WORD until uint64Val is zero
	
	// why do I need the extra check "requiredWords < wordsFor64Bit" ?
	// because shifing an unsigned 64bit variable by 64 bit to the right is not 0
	// example of the problem:
	// 		uint64_t int_2e63_test = 0x8000000000000000;	// 2^63 => b(10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000)
	//		uint64_t test_128 = int_2e63_test >> (8 * 7);	// expexted: 128 => b(10000000) OK!
	//		uint64_t test_0 = int_2e63_test >> (8 * 8);		// expected: 0	actual result: 2^63 => b(10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000)
	for(; (uint64Val >> (requiredWords * BIG_INT_BITS_PER_WORD)) > 0 && requiredWords < wordsFor64Bit; requiredWords++);
	
	// alocate word store array
	BIG_INT_WORD_TYPE *value = new BIG_INT_WORD_TYPE[requiredWords];
	
	// copy bits from uint64 into words
	for(BIG_INT_WORD_COUNT_TYPE i = 0; i < requiredWords; i++) {
		value[i] = (BIG_INT_WORD_TYPE)(uint64Val >> (i * BIG_INT_BITS_PER_WORD));
	}
	
	BigInt res(value, requiredWords, requiredWords);
	return res;
}

BigInt BigInt::fromString(const std::string& str, const BIG_INT_WORD_TYPE base) {
	assert(base <= 16);
	
	BigInt val(0);
	BigInt pow(1);
	BigInt bigBase(base);
	BigInt t(0);
	for(size_t i = str.length(); i>0; i--) {
		char c = str[i-1];
		if( base > 10 && c >= 'A' &&  c <= 'F') {
			t = BigInt( 10 + c - 'A' );
		} else if( base > 10 && c >= 'a' &&  c <= 'f') {
			t = BigInt( 10 + c - 'a');
		} else {
			t = BigInt( c - '0');
		}
		val = val + t * pow;
		pow = pow * bigBase;
	}
	
	return val;
}

BigInt::BigInt(const BIG_INT_WORD_TYPE& value): BigInt(value, 0) {}

BigInt::BigInt(const BIG_INT_WORD_TYPE& value, BIG_INT_WORD_COUNT_TYPE minCapacity) {
	BIG_INT_WORD_COUNT_TYPE newCapacity = std::max((BIG_INT_WORD_COUNT_TYPE)1, minCapacity);

	this->value = new BIG_INT_WORD_TYPE[newCapacity];
	this->value[0] = value;
	this->wordSize = 1;
	this->wordCapacity = newCapacity;
	//this->_dataRefCount = 1;
}

BigInt::BigInt(const BigInt &src ) : BigInt(src, 0) {}

BigInt::BigInt(const BigInt &src, BIG_INT_WORD_COUNT_TYPE minCapacity ) {
	BIG_INT_WORD_COUNT_TYPE newCapacity = std::max(src.wordSize, minCapacity);
	
	BIG_INT_WORD_TYPE *newValue = new BIG_INT_WORD_TYPE[newCapacity];
	std::copy(&src.value[0], &src.value[0] + src.wordSize, newValue);
	
	this->wordCapacity = newCapacity;
	this->wordSize = src.wordSize;
	this->value = newValue;
}

BigInt::BigInt(BIG_INT_WORD_TYPE* value, BIG_INT_WORD_COUNT_TYPE wordCapacity, BIG_INT_WORD_COUNT_TYPE wordSize) {
	this->value = value;
	this->wordCapacity = wordCapacity;
	this->wordSize = wordSize;
}

BigInt::~BigInt() {
	delete [] this->value;
}

uint64_t BigInt::toUint64() const {
	uint64_t res = 0;
	uint64_t tmp;
	size_t wordsFor64Bit = (sizeof(uint64_t) * CHAR_BIT) / BIG_INT_BITS_PER_WORD;
	for( size_t i=0; i<wordSize && i<wordsFor64Bit; i++) {
		tmp = this->value[i];
		res = res | (tmp << (i * BIG_INT_BITS_PER_WORD));
	}
	
	return res;
}

std::string BigInt::toStringHex() const {
	static const char* digits = "0123456789ABCDEF";
	
	if(this->wordSize == 0) {
		return "EMPTY";
	}
	
	if(this->wordSize == 1 && this->value[0] == 0) {
		return "0";
	}
	
	size_t bitPerHexDidigit = 4;
	size_t hexDigitsPerWord = BIG_INT_BITS_PER_WORD / bitPerHexDidigit ;
	std::string ret = "";
	for (BIG_INT_WORD_COUNT_TYPE wordIndex = 0; wordIndex < this->wordSize; wordIndex++) {
		BIG_INT_WORD_TYPE word = this->value[wordIndex];
		for (size_t hexDigitIndex=0; hexDigitIndex < hexDigitsPerWord; hexDigitIndex++) {
			BIG_INT_WORD_TYPE digit = word & 0x0F;
			word = word >> bitPerHexDidigit;
			if(digit > 0 || word > 0 || wordIndex < this->wordSize - 1) { // prevent leading zeros
				ret = digits[digit] + ret;
			}
		}
	}
	
	return ret;
}

std::string BigInt::toStringDec() const {
	static const char* digits = "0123456789";
	
	if(this->wordSize == 0) {
		return "EMPTY";
	}
	
	if(this->wordSize == 1 && this->value[0] == 0) {
		return "0";
	}
	
	//std::ostringstream oss;
	//return oss.str();
	std::string ret = "";
	BigInt tmp = *this;
	//BigInt reminder(0);
	BIG_INT_WORD_TYPE decDigit;
	while (ZERO < tmp) {
		//tmp.div(BigInt::TEN, &reminder);
		//decDigit = reminder.value[0];
		decDigit = this->divInt( 10, tmp.value, &tmp.wordSize );
		ret = digits[decDigit] + ret;
	}
	
	return ret;
}

void BigInt::reserveWords( BIG_INT_WORD_COUNT_TYPE newCapacity ) {
	if(newCapacity <= this->wordCapacity) {
		return;
	}
	
	BIG_INT_WORD_TYPE *newValue = new BIG_INT_WORD_TYPE[newCapacity];
	std::copy(&this->value[0], &this->value[0] + this->wordSize, newValue);
	
	// TODO inizialize all remianing words with 0 (the words with the indeces this->wordSize to newCapacity-1)?
	
	// free old word storage array
	delete [] this->value;
	
	// set new data to this
	this->value = newValue;
	this->wordCapacity = newCapacity;
}

void BigInt::setZero() {
	this->value[0] = 0;
	this->wordSize = 1;
}

void BigInt::setOne() {
	this->value[0] = 1;
	this->wordSize = 1;
}

/**
 * this method returns the number of the highest set bit in word
 * if the 'word' is zero this method returns '-1'
 */
int BigInt::findLeadingBitInWord(BIG_INT_WORD_TYPE word) const {
	if( word == 0 ) {
		return -1;
	}
	
	uint bit = BIG_INT_BITS_PER_WORD - 1;
	
	while( (word & BIG_INT_WORD_HIGHEST_BIT) == 0 ) {
		word = word << 1;
		--bit;
	}
	
	return bit;
}

/**
 * Replace target.low with src.low bits.
 *
 * target:	hhhhllll
 * src:		HHHHLLLL
 * res:		hhhhLLLL
 */
BIG_INT_WORD_TYPE BigInt::setLowFromLowBits(BIG_INT_WORD_TYPE target, BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res =
		// set low bits to 0 and keep the high bits
		this->getHighAsHighBits(target)
		|
		// set high bits to 0 and keep the low bits
		this->getLowAsLowBits(src)
	;
	
	return res;
}

/**
 * Replace target.low with src.high bits.
 *
 * target:	hhhhllll
 * src:		HHHHLLLL
 * res:		hhhhHHHH
 */
BIG_INT_WORD_TYPE BigInt::setLowFromHighBits(BIG_INT_WORD_TYPE target, BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res =
		// set low bits to 0 and keep the high bits
		//(target & BIG_INT_WORD_HIGH_BIT_MASK)
		this->getHighAsHighBits(target)
		|
		// move the high bits of src to the low bits
		//(src >> (BIG_INT_BITS_PER_WORD/2))
		this->getHighAsLowBits(src)
	;
	
	return res;
}

/**
 * Replace target.high with src.high bits.
 *
 * target:	hhhhllll
 * src:		HHHHLLLL
 * res:		HHHHllll
 */
BIG_INT_WORD_TYPE BigInt::setHighFromHighBits(BIG_INT_WORD_TYPE target, BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res =
		// set high bits to 0 and keep the low bits
		this->getLowAsLowBits(target)
		|
		// set low bits to 0 and keep the high bits
		this->getHighAsHighBits(src)
	;
	
	return res;
}

/**
 * Replace target.high with src.low bits.
 *
 * target:	hhhhllll
 * src:		HHHHLLLL
 * res:		LLLLllll
 */
BIG_INT_WORD_TYPE BigInt::setHighFromLowBits(BIG_INT_WORD_TYPE target, BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res =
		// set high bits to 0 and keep the low bits
		//(target & BIG_INT_WORD_LOW_BIT_MASK)
		this->getLowAsLowBits(target)
		|
		// move the low bits of src to the high bits
		//(src << (BIG_INT_BITS_PER_WORD/2))
		this->getLowAsHighBits(src)
	;
	
	return res;
}

/**
 * Set low bit to 0 and keep the high bits.
 *
 * src:	HHHHLLLL
 * res:	HHHH0000
 */
BIG_INT_WORD_TYPE BigInt::getHighAsHighBits(BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res = (src & BIG_INT_WORD_HIGH_BIT_MASK);
	return res;
}

/**
 * Move the high bits of src to the low bits. The high bits will be 0.
 *
 * src:	HHHHLLLL
 * res:	0000HHHH
 */
BIG_INT_WORD_TYPE BigInt::getHighAsLowBits(BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res = (src >> (BIG_INT_BITS_PER_WORD/2));
	return res;
}

/**
 * Set high bit to 0 and keep the low bits.
 *
 * src:	HHHHLLLL
 * res:	0000LLLL
 */
BIG_INT_WORD_TYPE BigInt::getLowAsLowBits(BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res = (src & BIG_INT_WORD_LOW_BIT_MASK);
	return res;
}

/**
 * Move the low bits of src to the high bits. The low bits will be 0.
 *
 * src:	HHHHLLLL
 * res:	LLLL0000
 */
BIG_INT_WORD_TYPE BigInt::getLowAsHighBits(BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res = (src << (BIG_INT_BITS_PER_WORD/2));
	return res;
}

/* ---------- shift left ---------- */

/**
 * an auxiliary method for moving bits into the left hand side
 *
 * this method moves only words
 *
 * This method does not increase the the word count => it drops informations that are on left end!
 */
void BigInt::rcl_moveWords( uint &restBits, BIG_INT_WORD_TYPE &lastC, uint bits, BIG_INT_WORD_TYPE c) {
	restBits      = bits % BIG_INT_BITS_PER_WORD;
	uint allWords = bits / BIG_INT_BITS_PER_WORD;
	BIG_INT_WORD_TYPE mask      = ( c ) ? BIG_INT_WORD_MAX_VALUE : 0;
	
	
	if( allWords >= this->wordSize ) {
		if( allWords == this->wordSize && restBits == 0 ) {
			lastC = this->value[0] & 1;
		}
		// else: last_c is default set to 0
		
		// clearing
		for(uint i = 0 ; i<this->wordSize ; ++i) {
			this->value[i] = mask;
		}
		
		restBits = 0;
	} else {
		if( allWords > 0 ) {
			// 0 < all_words < value_size
			
			int first, second;
			lastC = this->value[this->wordSize - allWords] & 1; // all_words is greater than 0
			
			// copying the first part of the value
			for(first = this->wordSize-1, second=first-allWords ; second>=0 ; --first, --second) {
				this->value[first] = this->value[second];
			}
			
			// setting the rest to 'c'
			for( ; first>=0 ; --first ) {
				this->value[first] = mask;
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
 */
BIG_INT_WORD_TYPE BigInt::rcl_moveBits(uint bits, BIG_INT_WORD_TYPE c) {
	assert( bits>0 && bits<BIG_INT_BITS_PER_WORD );
	
	uint move = BIG_INT_BITS_PER_WORD - bits;
	BIG_INT_WORD_TYPE i, newC;
	
	if( c != 0 ) {
		c = BIG_INT_BITS_PER_WORD >> move;
	}
	
	for(i=0 ; i<this->wordSize ; ++i) {
		newC    = this->value[i] >> move;
		this->value[i] = (this->value[i] << bits) | c;
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
 * This method does not increase the the word count => it drops informations that are on left end!
 */
BIG_INT_WORD_TYPE BigInt::rcl(uint bits, BIG_INT_WORD_TYPE c) {
	BIG_INT_WORD_TYPE lastC    = 0;
	uint restBits = bits;
	
	if( bits == 0 )
		return 0;
	
	if( bits >= BIG_INT_BITS_PER_WORD ) {
		this->rcl_moveWords(restBits, lastC, bits, c);
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
		lastC = this->rcl_moveBits(restBits, c);
	/*
	}
	*/
	
	return lastC;
}

/* ---------- shift right ---------- */

/**
 * an auxiliary method for moving bits into the right hand side
 *
 * this method moves only words
 */
void BigInt::rcr_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, uint bits, BIG_INT_WORD_TYPE c) {
	restBits      = bits % BIG_INT_BITS_PER_WORD;
	uint allWords = bits / BIG_INT_BITS_PER_WORD;
	BIG_INT_WORD_TYPE mask      = ( c ) ? BIG_INT_WORD_MAX_VALUE : 0;
	
	
	if( allWords >= this->wordSize ) {
		if( allWords == this->wordSize && restBits == 0 ) {
			lastC = (this->value[this->wordSize-1] & BIG_INT_WORD_HIGHEST_BIT) ? 1 : 0;
		}
		// else: last_c is default set to 0
		
		// clearing
		for(uint i = 0 ; i<this->wordSize ; ++i) {
			this->value[i] = mask;
		}
		
		restBits = 0;
	} else if( allWords > 0 ) {
		// 0 < all_words < value_size
		
		uint first, second;
		lastC = (this->value[allWords - 1] & BIG_INT_WORD_HIGHEST_BIT) ? 1 : 0; // all_words is > 0
		
		// copying the first part of the value
		for(first=0, second=allWords ; second<this->wordSize ; ++first, ++second) {
			this->value[first] = this->value[second];
		}
		
		// setting the rest to 'c'
		for( ; first<this->wordSize ; ++first ) {
			this->value[first] = mask;
		}
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
 */
BIG_INT_WORD_TYPE BigInt::rcr_moveBits(uint bits, BIG_INT_WORD_TYPE c) {
	assert ( bits>0 && bits<BIG_INT_BITS_PER_WORD );
	
	uint move = BIG_INT_WORD_MAX_VALUE - bits;
	int i; // signed
	BIG_INT_WORD_TYPE newC;
	
	if( c != 0 ) {
		c = BIG_INT_WORD_MAX_VALUE << move;
	}
	
	for(i=this->wordSize-1 ; i>=0 ; --i) {
		newC    = this->value[i] << move;
		this->value[i] = (this->value[i] >> bits) | c;
		c        = newC;
	}
	
	c = (c & BIG_INT_WORD_HIGHEST_BIT) ? 1 : 0;
	
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
 */
BIG_INT_WORD_TYPE BigInt::rcr(uint bits, BIG_INT_WORD_TYPE c) {
	BIG_INT_WORD_TYPE lastC    = 0;
	uint restBits = bits;
	
	if( bits == 0 ) {
		return 0;
	}
	
	if( bits >= BIG_INT_BITS_PER_WORD ) {
		this->rcr_moveWords(restBits, lastC, bits, c);
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
		lastC = rcr_moveBits(restBits, c);
	/*
	}
	 */
	
	return lastC;
}

/* ---------- addition ---------- */

BIG_INT_WORD_TYPE BigInt::addTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE * result) const {
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

BIG_INT_WORD_TYPE BigInt::addTwoInts(const BIG_INT_WORD_TYPE wordHigh, const BIG_INT_WORD_TYPE wordLow, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE * targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const {
	assert( index < (targetWordCount - 1) ); // TODO
	
	BIG_INT_WORD_TYPE c;
	
	c = addTwoWords(targetArray[index],   wordLow, 0, &targetArray[index]);
	c = addTwoWords(targetArray[index+1], wordHigh, c, &targetArray[index+1]);
	
	for(BIG_INT_WORD_COUNT_TYPE i=index+2 ; i < targetWordCount && c ; ++i) { // TODO
		c = addTwoWords(targetArray[i], 0, c, &targetArray[i]);
	}
	return c;
}

/**
 * this method adds one word (at a specific position)
 * and returns a carry (if it was)
 *
 * if we've got (value_size=3):
 *
 * table[0] = 10;
 * table[1] = 30;
 * table[2] = 5;
 *
 * and we call:
 *
 * AddInt(2,1)
 *
 * then it'll be:
 *
 * table[0] = 10;
 * table[1] = 30 + 2;
 * table[2] = 5;
 *
 * of course if there was a carry from table[2] it would be returned
 */
BIG_INT_WORD_TYPE BigInt::addInt(const BIG_INT_WORD_TYPE world, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE *targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const {
	assert( index < targetWordCount );
	
	BIG_INT_WORD_TYPE c;
	c = addTwoWords(targetArray[index], world, 0, &targetArray[index]);
	
	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c ; ++i) {
		c = addTwoWords(targetArray[i], 0, c, &targetArray[i]);
	}
	
	return c;
}

void BigInt::add(const BigInt &other) {
	BIG_INT_WORD_TYPE carry = 0;
	BIG_INT_WORD_TYPE a,b;//,c;
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->wordSize, other.wordSize);
	//BIG_INT_WORD_TYPE* resValue = new BIG_INT_WORD_TYPE[maxWordCount+1];
	if(this->wordCapacity < maxWordCount) {
		this->reserveWords(maxWordCount+1); // If we need to resize the storage array than also preserve the space for a possible carry bit
	}
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<maxWordCount; i++) {
		if(this->wordSize > i) {
			a = this->value[i];
		} else {
			a = 0;
		}
		if(other.wordSize > i) {
			b = other.value[i];
		} else {
			b = 0;
		}
		
		carry = addTwoWords(a, b, carry, &this->value[i]);
	}
	
	if(carry > 0) {
		this->reserveWords(maxWordCount+1); // reserve space for carry bit
		
		this->value[maxWordCount] = carry;
		this->wordSize = maxWordCount+1;
	} else {
		this->wordSize = maxWordCount;
	}
}

BigInt BigInt::operator+ (const BigInt& other) const {
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->wordSize, other.wordSize);
	BigInt result(*this, maxWordCount+1); // copy this to new BigInt with enough space for all words and even a carry bit
	result.add(other);
	return result;
}

/* ---------- substraction ---------- */

/**
 * this method subtractes one word from the other
 * returns carry
 *
 * this method is created only when TTMATH_NOASM macro is defined
 */
BIG_INT_WORD_TYPE BigInt::subTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE * result) const {
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

/**
 * this method subtracts one word (at a specific position)
 * and returns a carry (if it was)
 *
 * if we've got (value_size=3):
 *
 * table[0] = 10;
 * table[1] = 30;
 * table[2] = 5;
 *
 * and we call:
 *
 * SubInt(2,1)
 *
 * then it'll be:
 *
 * table[0] = 10;
 * table[1] = 30 - 2;
 * table[2] = 5;
 *
 * of course if there was a carry from table[2] it would be returned
 */
BIG_INT_WORD_TYPE BigInt::subInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE *targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const {
	assert( index < targetWordCount );
	
	BIG_INT_WORD_TYPE c;
	c = subTwoWords(targetArray[index], word, 0, &targetArray[index]);
	
	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c ; ++i) {
		c = subTwoWords(targetArray[i], 0, c, &targetArray[i]);
	}
	
	return c;
}

/*!
 this method's subtracting ss2 from the 'this' and subtracting
 carry if it has been defined
 (this = this - ss2 - c)
 
 c must be zero or one (might be a bigger value than 1)
 function returns carry (borrow) (1) (if it was)
 */
BIG_INT_WORD_TYPE BigInt::sub(const BigInt& other) {
	//if(other > *this) {
	//	std::string msg = "ERROR substract BigInt a - b with a < b (a=" + this->toStringDec() + ", b=" + other.toStringDec() + ")!";
	//	std::cerr << msg << std::endl;
	//	throw std::runtime_error(msg);
	//}
	
	BIG_INT_WORD_TYPE carry = 0; // carry = "borrow"
	BIG_INT_WORD_TYPE a,b,c;
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->wordSize, other.wordSize);
	BIG_INT_WORD_COUNT_TYPE usedWordIndex = 0;
	
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<this->wordSize; i++) {
		if(other.wordSize > i) {
			b = other.value[i];
		} else {
			b = 0;
		}
		
		carry = subTwoWords(this->value[i], b, carry, &this->value[i]);
		if(this->value[i] > 0) {
			usedWordIndex = i;
		}
	}
	
	// carry > 0 : can not happen if this <= other at the beginning of the method
	//assert(carry == 0);
	
	this->wordSize = usedWordIndex+1;
	
	return carry;
}

BigInt BigInt::operator- (const BigInt& other) const {
	/*
	BIG_INT_WORD_TYPE carry = 0;
	BIG_INT_WORD_TYPE a,b,c;
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->wordCount, other.wordCount);
	BIG_INT_WORD_COUNT_TYPE usedWordIndex = 0;
	BIG_INT_WORD_TYPE* resValue = new BIG_INT_WORD_TYPE[maxWordCount+1];
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<maxWordCount; i++) {
		if(this->wordCount > i) {
			a = this->value[i];
		} else {
			a = 0;
		}
		if(other.wordCount > i) {
			b = other.value[i];
		} else {
			b = 0;
		}
		
		carry = addTwoWords(a, b, carry, &resValue[i]);
		if(resValue[i] > 0) {
			usedWordIndex = i;
		}
	}
	
	if (carry > 0) {
		std::string msg = "ERROR substract BigInt a - b with a < b!";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	
	return BigInt(resValue, usedWordIndex+1);
	*/
	
	
	if(other > *this) {
		std::string msg = "ERROR substract BigInt a - b with a < b (a=" + this->toStringDec() + ", b=" + other.toStringDec() + ")!";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	BigInt result(*this); // copy this to new BigInt
	result.sub(other);
	return result;
}

/* ---------- multiplication ---------- */

void BigInt::mulTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE * resultHigh, BIG_INT_WORD_TYPE * resultLow) const {
	/*
		expect BIG_INT_WORD_TYPE to be a 64 bits variable:
		we don't have a native type which has 128 bits
		then we're splitting 'a' and 'b' to 4 parts (high and low halves)
		and using 4 multiplications (with additions and carry correctness)
	 */
	
	BIG_INT_WORD_TYPE aLow = this->getLowAsLowBits(a);// a & BIG_INT_WORD_LOW_BIT_MASK;
	BIG_INT_WORD_TYPE bLow = this->getLowAsLowBits(b);// b & BIG_INT_WORD_LOW_BIT_MASK;
	BIG_INT_WORD_TYPE aHigh = this->getHighAsLowBits(a);// a >> (sizeof(BIG_INT_WORD_TYPE) * 4);
	BIG_INT_WORD_TYPE bHigh = this->getHighAsLowBits(b);// b >> (sizeof(BIG_INT_WORD_TYPE) * 4);
	
	//uint_ a_;
	//uint_ b_;
	//uint_ res_high1, res_high2;
	//uint_ res_low1,  res_low2;
	
	//a_.u = a;
	//b_.u = b;
	
	BIG_INT_WORD_TYPE res_high1, res_high2;
	BIG_INT_WORD_TYPE res_low1, res_low2;
	
	/*
		the multiplication is as follows (schoolbook algorithm with O(n^2) ):
	 
										 32 bits         32 bits
	 
										 +--------------------------------+
										 |   a_.u_.high   |   a_.u_.low   |
										 +--------------------------------+
										 |   b_.u_.high   |   b_.u_.low   |
		+--------------------------------+--------------------------------+
		|           res_high1.u          |           res_low1.u           |
		+--------------------------------+--------------------------------+
		|           res_high2.u          |           res_low2.u           |
		+--------------------------------+--------------------------------+
	 
		64 bits                          64 bits
	*/
	
	
	//uint_ temp;
	BIG_INT_WORD_TYPE temp;
	
	//res_low1.u        = uint(b_.u_.low) * uint(a_.u_.low);
	res_low1 = bLow * aLow;
	
	// --
	
	//temp.u            = uint(res_low1.u_.high) + uint(b_.u_.low) * uint(a_.u_.high);
	//temp = (res_low1 >> (sizeof(BIG_INT_WORD_TYPE) * 4)) + bLow * aHigh; // res_low1.high + bLow * aHigh
	temp = this->getHighAsLowBits(res_low1) + bLow * aHigh; // res_low1.high + bLow * aHigh
	
	//res_low1.u_.high  = temp.u_.low;
	//res_low1 = (res_low1 & BIG_INT_WORD_LOW_BIT_MASK) | (temp << (sizeof(BIG_INT_WORD_TYPE) * 4)); // replace res_low1.high with temp.low
	res_low1 = this->setHighFromLowBits(res_low1, temp); // replace res_low1.high with temp.low
	
	//res_high1.u_.low  = temp.u_.high;
	//res_high1 = (res_high1 & BIG_INT_WORD_HIGH_BIT_MASK) | (temp >> (sizeof(BIG_INT_WORD_TYPE) * 4)); // replace res_high1.low with temp.high
	res_high1 = this->setLowFromHighBits(res_high1, temp); // replace res_high1.low with temp.high
	
	//res_high1.u_.high = 0;
	//res_high1 = (res_high1 & BIG_INT_WORD_LOW_BIT_MASK); // set higher bits to 0 (res_high1.high = 0)
	res_high1 = this->getLowAsLowBits(res_high1);
	
	// --
	
	//res_low2.u_.low   = 0;
	//res_low2 = (res_low2 & BIG_INT_WORD_HIGH_BIT_MASK); // set lower bits to 0 (res_low2.low = 0)
	res_low2 = this->getHighAsHighBits(res_low2);
	
	//temp.u            = uint(b_.u_.high) * uint(a_.u_.low);
	temp				= bHigh * aLow;
	
	//res_low2.u_.high  = temp.u_.low;
	//res_low2 = (res_low2 & BIG_INT_WORD_LOW_BIT_MASK) | (temp << (sizeof(BIG_INT_WORD_TYPE) * 4));
	res_low2 = this->setHighFromLowBits(res_low2, temp);
	
	// --
	
	//res_high2.u       = uint(b_.u_.high) * uint(a_.u_.high) + uint(temp.u_.high);
	//res_high2 = bHigh * aHigh + (temp >> (sizeof(BIG_INT_WORD_TYPE) * 4)); // bHigh * aHigh + temp.high
	res_high2 = bHigh * aHigh + this->getHighAsLowBits(temp);
	
	// --
	
	//uint c = AddTwoWords(res_low1.u, res_low2.u, 0, &res_low2.u);
	BIG_INT_WORD_TYPE c = addTwoWords(res_low1, res_low2, 0, &res_low2);
	
	//AddTwoWords(res_high1.u, res_high2.u, c, &res_high2.u);                 // there is no carry from here
	addTwoWords(res_high1, res_high2, c, &res_high2);                 // there is no carry from here
	
	*resultHigh = res_high2;
	*resultLow  = res_low2;
}

/**
 * multiplication: this = this * ss2
 */
void BigInt::mulInt(BIG_INT_WORD_TYPE ss2) {
	if( ss2 == 0 ) {
		this->value[0] = 0;
		this->wordSize = 1;
		return;
	}
	
	BigInt u(this->value, this->wordCapacity, this->wordSize); // "copy" the data from this to u
	
	// create new value for this
	this->value = new BIG_INT_WORD_TYPE[u.wordSize+1];
	this->wordCapacity = u.wordSize+1;
	std::fill_n(&this->value[0], this->wordCapacity, 0);
	
	BIG_INT_WORD_TYPE r2,r1;
	BIG_INT_WORD_COUNT_TYPE x1size=u.wordSize;
	BIG_INT_WORD_COUNT_TYPE x1start=0;
	
	// try to save some CPU sycles if this contains words with 0 at the start or at the end
	// if( value_size > 2 )
	if( u.wordSize > 2 ) {
		// if the value_size is smaller than or equal to 2
		// there is no sense to set x1size and x1start to another values
		
		for(x1size=u.wordSize ; x1size>0 && u.value[x1size-1]==0 ; --x1size);
		
		if( x1size == 0 ) {
			// this is 0: 0*x => 0
			this->wordSize = 1;
			return;
		}
		
		for(x1start=0 ; x1start<x1size && u.value[x1start]==0 ; ++x1start);
	}
	
	for(BIG_INT_WORD_COUNT_TYPE x1=x1start ; x1<x1size ; ++x1) {
		this->mulTwoWords(u.value[x1], ss2, &r2, &r1 );
		this->addTwoInts(r2, r1, x1, this->value, this->wordCapacity); // this->wordCapacity is > u.wordSize => there can not be a carry bit!
	}
	
	// check if the most significant word is > 0 and increase the wordSize if it is.
	// TODO remove this if addTwoInts() can take care of the this->wordSize
	if(this->value[this->wordSize-1] != 0) {
		this->wordSize = this->wordCapacity;
	}
}

BigInt BigInt::mulSchool(const BigInt& a, const BigInt& b) const {
//	return mulSchool_1(a, b);
//}
//
//BigInt BigInt::mulSchool_1(const BigInt& a, const BigInt& b) const {
	BIG_INT_WORD_COUNT_TYPE aSize  = a.wordSize, 	bSize  = b.wordSize;
	BIG_INT_WORD_COUNT_TYPE aStart = 0,       		bStart = 0;
	
	if( a.wordSize > 2 ) {
		// if the wordCount is smaller than or equal to 2
		// there is no sense to set aSize (and others) to another values
		
		for(aSize=a.wordSize ; aSize>0 && a.value[aSize-1]==0 ; --aSize);
		
		for(aStart=0 ; aStart<aSize && a.value[aStart]==0 ; ++aStart);
	}
	if( b.wordSize > 2 ) {
		// if the wordCount is smaller than or equal to 2
		// there is no sense to set bSize (and others) to another values
		
		for(bSize=b.wordSize ; bSize>0 && b.value[bSize-1]==0 ; --bSize);
		
		for(bStart=0 ; bStart<bSize && b.value[bStart]==0 ; ++bStart);
	}
	
//	Mul2Big3<ss_size>(ss1, ss2, result, x1start, aSize, x2start, bSize);
//}
//
//BigInt BigInt::mulSchool_2(const BigInt& a, const BigInt& b, const BIG_INT_WORD_COUNT_TYPE aStart, const BIG_INT_WORD_COUNT_TYPE aSize, const BIG_INT_WORD_COUNT_TYPE bStart, BIG_INT_WORD_COUNT_TYPE bSize) const {
	
	if( aSize==0 || bSize==0 ) {
		return BigInt(0);
	}
	
	BIG_INT_WORD_TYPE r2, r1;
	
	BIG_INT_WORD_COUNT_TYPE maxWordCount = aSize + bSize; // std::max(aSize, bSize) * 2;
	BIG_INT_WORD_TYPE* resValue = new BIG_INT_WORD_TYPE[maxWordCount];
	std::fill_n(resValue, maxWordCount, 0);
	
	for(uint aI=aStart ; aI<aSize ; ++aI)
	{
		for(uint bI=bStart ; bI<bSize ; ++bI)
		{
			mulTwoWords(a.value[aI], b.value[bI], &r2, &r1);
			addTwoInts(r2, r1, bI+aI, resValue, maxWordCount);
			// here will never be a carry
		}
	}
	
	// optimize word count
	BIG_INT_WORD_COUNT_TYPE usedWordIndex;
	for(usedWordIndex = maxWordCount; usedWordIndex>0 && resValue[usedWordIndex-1] == 0; --usedWordIndex);
	
	return BigInt(resValue, maxWordCount, usedWordIndex);
}

BigInt BigInt::operator* (const BigInt& other) const {
	return mulSchool(*this, other);
}

/* ---------- division ---------- */

/**
 * this method calculates 64bits word a:b / 32bits c (a higher, b lower word)
 * result = a:b / c and rest - remainder
 *
 *
 * WARNING:
 * the c has to be suitably large for the result being keeped in one word,
 * if c is equal zero there'll be a hardware interruption (0)
 * and probably the end of your program
 *
 */
void BigInt::divTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE c, BIG_INT_WORD_TYPE *result, BIG_INT_WORD_TYPE * rest) const {
	// c = divisor
	// (a < c ) for the result to be one word
	assert( c != 0 && a < c );
	
	//uint_ c_;
	//c_.u = c;
	BIG_INT_WORD_TYPE c_ = c;
	
	if( a == 0 ) {
		*result    = b / c;
		*rest = b % c;
	} else {
		if( this->getHighAsLowBits(c_) == 0 ) {
			// higher half of 'c' is zero
			// then higher half of 'a' is zero too (look at the asserts at the beginning - 'a' is smaller than 'c')
			BIG_INT_WORD_TYPE a_, b_, res_, temp1, temp2;
			
			//a_.u = a;
			a_ = a;
			
			//b_.u = b;
			b_ = b;
			
			//temp1.u_.high = a_.u_.low;
			temp1 = this->setHighFromLowBits(temp1, a_);
			
			//temp1.u_.low  = b_.u_.high;
			temp1 = this->setLowFromHighBits(temp1, b_);
			
			//res_.u_.high  = (unsigned int)(temp1.u / c);
			res_ = this->setHighFromLowBits(res_, (temp1 / c));
			
			//temp2.u_.high = (unsigned int)(temp1.u % c);
			temp2 = this->setHighFromLowBits(temp2, (temp1 % c));
			
			//temp2.u_.low  = b_.u_.low;
			temp2 = this->setLowFromLowBits(temp2, b_);
			
			//res_.u_.low  = (unsigned int)(temp2.u / c);
			res_ = this->setLowFromLowBits(res_, (temp2 / c));
			//*rest        = temp2.u % c;
			*rest = temp2 % c;
			
			//*r = res_.u;
			*result = res_;
		} else {
			return this->divTwoWords2(a, b, c,  result,  rest);
		}
	}
}

/**
 *
 * the same algorithm like the division algorithm for all words which is based on
 * "The art of computer programming 2" (4.3.1 page 257)
 * Donald E. Knuth
 * but now with the radix=2^32
 */
void BigInt::divTwoWords2(BIG_INT_WORD_TYPE a, BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE c, BIG_INT_WORD_TYPE * r, BIG_INT_WORD_TYPE * rest) const {
	// a is not zero
	// c_.u_.high is not zero
	
	//uint_ a_, b_, c_, u_, q_;
	//unsigned int u3; // 32 bit
	BIG_INT_WORD_TYPE u, q, u3;
	BIG_INT_WORD_TYPE temp_qLow, temp_qHigh;
	
	
	
	//a_.u  = a;
	//b_.u  = b;
	//c_.u  = c;
	
	// normalizing
	BIG_INT_WORD_TYPE d = this->divTwoWordsNormalize(a, b, c);
	
	// loop from j=1 to j=0
	//   the first step (for j=2) is skipped because our result is only in one word,
	//   (first 'q' were 0 and nothing would be changed)
	////u_.u_.high = a_.u_.high;
	//u = this->setHighFromHighBits(u, a);
	////u_.u_.low  = a_.u_.low;
	//u = this->setLowFromLowBits(u, a);
	// TODO why not just:
	u = a;
	
	//u3         = b_.u_.high;
	u3 = this->getHighAsLowBits(b);
	//q_.u_.high = DivTwoWordsCalculate(u_, u3, c_);
	q = this->setHighFromLowBits(q, this->divTwoWordsCalculate(u, u3, c));
	//MultiplySubtract(u_, u3, q_.u_.high, c_);
	temp_qHigh = this->getHighAsLowBits(q);
	this->multiplySubtract(u, u3, temp_qHigh, c);
	q = this->setHighFromLowBits(q, temp_qHigh);
	
	//u_.u_.high = u_.u_.low;
	u = this->setHighFromLowBits(u, u);
	//u_.u_.low  = u3;
	u = this->setLowFromLowBits(u, u3);
	//u3         = b_.u_.low;
	u3 = this->getLowAsLowBits(b);
	//q_.u_.low  = DivTwoWordsCalculate(u_, u3, c_);
	q = this->setLowFromLowBits(q, this->divTwoWordsCalculate(u, u3, c));
	//MultiplySubtract(u_, u3, q_.u_.low, c_);
	temp_qLow = this->getLowAsLowBits(q);
	this->multiplySubtract(u, u3, temp_qLow, c);
	q = this->setLowFromLowBits(q, temp_qLow);
	
	//*r = q_.u;
	*r = q;
	
	// unnormalizing for the remainder
	//u_.u_.high = u_.u_.low;
	u = this->getLowAsHighBits(u); // this->setHighFromLowBits(u, u);
	//u_.u_.low  = u3;
	u = this->setLowFromLowBits(u, u3);
	//*rest = DivTwoWordsUnnormalize(u_.u, d);
	*rest = this->divTwoWordsUnnormalize(u, d);
}

BIG_INT_WORD_TYPE BigInt::divTwoWordsNormalize(BIG_INT_WORD_TYPE &a, BIG_INT_WORD_TYPE &b, BIG_INT_WORD_TYPE &c) const {
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

BIG_INT_WORD_TYPE BigInt::divTwoWordsUnnormalize(BIG_INT_WORD_TYPE u, BIG_INT_WORD_TYPE d) const {
	if( d == 0 ) {
		return u;
	}
	
	u = u >> d;
	
	return u;
}

unsigned int BigInt::divTwoWordsCalculate(BIG_INT_WORD_TYPE u, BIG_INT_WORD_TYPE u3, BIG_INT_WORD_TYPE v) const
{
	bool next_test;
	//uint_ qp_, rp_, temp_;
	BIG_INT_WORD_TYPE qp, rp, temp;
	
	//qp_.u = u_.u / uint(v_.u_.high);
	qp = u / this->getHighAsLowBits(v);
	//rp_.u = u_.u % uint(v_.u_.high);
	rp = u % this->getHighAsLowBits(v);
	
	//TTMATH_ASSERT( qp_.u_.high==0 || qp_.u_.high==1 )
	assert( this->getHighAsLowBits(qp) == 0 || this->getHighAsLowBits(qp) == 1);
	
	do {
		bool decrease = false;
		
		//if( qp_.u_.high == 1 )
		if( this->getHighAsLowBits(qp) == 1 ) {
			decrease = true;
		} else {
			//temp_.u_.high = rp_.u_.low;
			temp = this->setHighFromLowBits(temp, rp);
			//temp_.u_.low  = u3;
			temp = this->setLowFromLowBits(temp, u3);
			
			//if( qp_.u * uint(v_.u_.low) > temp_.u )
			if( qp * this->getLowAsLowBits(v) > temp) {
				decrease = true;
			}
		}
		
		next_test = false;
		
		if( decrease ) {
			//--qp_.u;
			--qp;
			//rp_.u += v_.u_.high;
			rp += this->getHighAsLowBits(v);
			
			//if( rp_.u_.high == 0 )
			if( this->getHighAsLowBits(rp) == 0) {
				next_test = true;
			}
		}
	}
	while( next_test );
	
	//return qp_.u_.low;
	return this->getLowAsLowBits(qp);
}

void BigInt::multiplySubtract(BIG_INT_WORD_TYPE &u, BIG_INT_WORD_TYPE & u3, BIG_INT_WORD_TYPE & q, BIG_INT_WORD_TYPE v) const {
	BIG_INT_WORD_TYPE temp, res_high, res_low;
	this->mulTwoWords(v, q,  &res_high, &res_low);
	
	BIG_INT_WORD_TYPE sub_res_high, sub_res_low;
	
	//temp_.u_.high = u_.u_.low;
	temp = this->setHighFromLowBits(temp, u);
	//temp_.u_.low  = u3;
	temp = this->setLowFromLowBits(temp, u3);
	
	//uint c = SubTwoWords(temp_.u, res_low, 0, &sub_res_low_.u);
	BIG_INT_WORD_TYPE c = this->subTwoWords(temp, res_low, 0, &sub_res_low);
	
	//temp_.u_.high = 0;
	temp = this->setHighFromLowBits(temp, 0);
	//temp_.u_.low  = u_.u_.high;
	temp = this->setLowFromHighBits(temp, u);
	//c = SubTwoWords(temp_.u, res_high, c, &sub_res_high_.u);
	c = this->subTwoWords(temp, res_high, c, &sub_res_high);
	
	if( c ) {
		--q;
		
		c = this->addTwoWords(sub_res_low, v, 0, &sub_res_low);
		this->addTwoWords(sub_res_high, 0, c, &sub_res_high);
	}
	
	//u_.u_.high = sub_res_high_.u_.low;
	u = this->setHighFromLowBits(u, sub_res_high);
	//u_.u_.low  = sub_res_low_.u_.high;
	u = this->setLowFromHighBits(u, sub_res_low);
	//u3         = sub_res_low_.u_.low;
	u3 = this->getLowAsLowBits(sub_res_low);
}

/**
 * division by one unsigned word
 *
 * returns the remainder
 */
BIG_INT_WORD_TYPE BigInt::divInt(BIG_INT_WORD_TYPE divisor, BIG_INT_WORD_TYPE *targetArray, BIG_INT_WORD_COUNT_TYPE *targetWordSize) const {
	if(divisor == 0) {
		std::string msg = "BigInt devision by (uint)0.";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	
	if( divisor == 1 ) {
		return 0;
	}
	
	//UInt<value_size> dividend(*this);
	BIG_INT_WORD_TYPE *dividend = targetArray;
	//SetZero();
	//BIG_INT_WORD_TYPE *result = new BIG_INT_WORD_TYPE[targetWordCount];
	//std::fill_n(result, targetWordCount, 0);
	
	int i;  // i must be with a sign
	BIG_INT_WORD_TYPE r = 0;
	
	BIG_INT_WORD_COUNT_TYPE newWordSize = *targetWordSize;
	bool nonZeroWordRes = false;
	
	// we're looking for the last word in dividend (most significant word that is not null)
	//for(i=targetWordSize-1 ; i>0 && dividend[i]==0 ; --i);
	i = *targetWordSize - 1;
	
	for( ; i>=0 ; --i) {
		this->divTwoWords(r, dividend[i], divisor, &targetArray[i], &r);
		// find index+1 of most significant word which is not 0
		if(!nonZeroWordRes && i > 0) {
			if(targetArray[i] == 0) {
				newWordSize = i;
			} else {
				nonZeroWordRes = true;
			}
		}
	}
	
	
	*targetWordSize = newWordSize;
	return r;
}

void BigInt::div_division(BigInt divisor, BigInt * remainder, uint m, uint n) {
	// this = dividend, v = divisor
	const BigInt* dividend = this;
	
	//TTMATH_ASSERT( n>=2 )
	
	BIG_INT_WORD_COUNT_TYPE maxWordCount = dividend->wordSize; // std::max(dividend.wordCount, divisor.wordCount); // dividend.wordCount must be >= divisor.wordCount
	
	//UInt<value_size+1> uu, vv;
	BigInt uu(0, maxWordCount+1);
	//BigInt vv(*this, maxWordCount+1);
	
	//UInt<value_size> q;
	BigInt q(0, maxWordCount);
	
	uint d, u_value_size, j=m;
	BIG_INT_WORD_TYPE u0, u1, u2, v1, v0;
	
	u_value_size = this->div_normalize(divisor, n, d);
	
	if( j+n == this->wordSize ) {
		u2 = u_value_size;
	} else {
		u2 = this->value[j+n];
	}
	
	//Div3_MakeBiggerV(v, vv);
	BigInt vv(divisor, maxWordCount+1);
	//std::copy(&divisor.value[0], (&divisor.value[0] + divisor.wordSize), vv);
	//vv[divisor.wordSize] = 0;
	
	std::fill_n(q.value, maxWordCount, 0);
	
	while( true ) {
		u1 = this->value[j+n-1]; // divident high
		u0 = this->value[j+n-2]; // divident low
		v1 = divisor.value[n-1]; // divisor  high
		v0 = divisor.value[n-2]; // divident low
		
		BIG_INT_WORD_TYPE qp = this->div_calculate(u2,u1,u0, v1,v0);
		
		this->div_makeNewU(uu, j, n, u2);
		this->div_multiplySubtract(uu, vv, qp);
		this->div_copyNewU(uu, j, n);
		
		q.value[j] = qp;
		
		// the next loop
		if( j-- == 0 ) {
			break;
		}
		
		u2 = this->value[j+n];
	}
	
	// set new word size of the result
	BIG_INT_WORD_COUNT_TYPE resultWordSize = maxWordCount;
	for (; resultWordSize>0 && q.value[resultWordSize-1] == 0; resultWordSize--);
	q.wordSize = resultWordSize;
	
	if( remainder ) {
		this->div_unnormalize(remainder, n, d);
	}
	
	*this = q;
	
	//TTMATH_LOG("UInt::Div3_Division")
}


void BigInt::div_makeNewU(BigInt &uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n, BIG_INT_WORD_COUNT_TYPE u_max) const {
	BIG_INT_WORD_COUNT_TYPE i;
	
	//for(i=0 ; i<n ; ++i, ++j)
	//	uu.table[i] = table[j];
	uu.reserveWords(n);
	std::copy(&this->value[j], &this->value[j] + n, &uu.value[0]);
	i = n;
	
	// 'n' is from <1..value_size> so and 'i' is from <0..value_size>
	// then table[i] is always correct (look at the declaration of 'uu')
	uu.value[i] = u_max;
	
	
	//for( ++i ; i<value_size+1 ; ++i)
	//	uu.table[i] = 0;
	
	uu.wordSize = i+1;
	
	//TTMATH_LOG("UInt::Div3_MakeNewU")
}


void BigInt::div_copyNewU(const BigInt & uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n) {
	BIG_INT_WORD_COUNT_TYPE i;
	
	for(i=0 ; i<n ; ++i) {
		this->value[i+j] = uu.value[i];
	}
	
	if( i+j < this->wordSize ) {
		this->value[i+j] = uu.value[i];
	}
	
	//TTMATH_LOG("UInt::Div3_CopyNewU")
}


/*!
 we're making the new 'vv'
 the value is actually the same but the 'table' is bigger (value_size+1)
 * /
void Div3_MakeBiggerV(const UInt<value_size> & v, UInt<value_size+1> & vv)
{
	for(uint i=0 ; i<value_size ; ++i)
		vv.table[i] = v.table[i];
	
	vv.table[value_size] = 0;
	
	TTMATH_LOG("UInt::Div3_MakeBiggerV")
}
*/

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
 */
BIG_INT_WORD_TYPE BigInt::div_normalize(BigInt& divisor, uint n, uint & d) {
	// this = dividend, v = divisor
	// v.table[n-1] is != 0
	
	uint bit  = (uint)this->findLeadingBitInWord(divisor.value[n-1]); // TODO divisor.value[divisor.wordSize - 1] ?
	uint move = (BIG_INT_BITS_PER_WORD - bit - 1);
	d         = move;
	BIG_INT_WORD_TYPE res  = this->value[this->wordSize -1];
	
	if( move > 0 ) {
		divisor.rcl(move, 0);
		this->rcl(move, 0);
		res = res >> (bit + 1); // this is the same as the bits that was shiftet out by "this->rcl(move, 0)" - the teoretical new most significant word of this
	}
	else {
		res = 0;
	}
	
	//TTMATH_LOG("UInt::Div3_Normalize")
	
	return res;
}

void BigInt::div_unnormalize(BigInt * remainder, BIG_INT_WORD_COUNT_TYPE n, BIG_INT_WORD_COUNT_TYPE d) {
	//for(BIG_INT_WORD_COUNT_TYPE i=n ; i<this->wordSize ; ++i) {
	//	this->value[i] = 0;
	//}
	this->wordSize = n;
	
	this->rcr(d,0);
	
	*remainder = *this;
	
	//TTMATH_LOG("UInt::Div3_Unnormalize")
}


BIG_INT_WORD_TYPE BigInt::div_calculate(BIG_INT_WORD_TYPE u2, BIG_INT_WORD_TYPE u1, BIG_INT_WORD_TYPE u0, BIG_INT_WORD_TYPE v1, BIG_INT_WORD_TYPE v0) const {
	//UInt<2> u_temp;
	// u_temp in qp (quotient) umbenant
	BIG_INT_WORD_COUNT_TYPE qpWordCount = 2;
	BIG_INT_WORD_TYPE qp[2];
	BIG_INT_WORD_TYPE rp, c;
	bool next_test;
	
	assert( v1 != 0 );

	
	qp[1] = u2;
	qp[0] = u1;
	//u_temp.DivInt(v1, &rp);
	rp = this->divInt(v1, &qp[0], &qpWordCount);
	
	//TTMATH_ASSERT( u_temp.table[1]==0 || u_temp.table[1]==1 )
	assert( qp[1]==0 || qp[1]==1 );
	
	do {
		bool decrease = false;
		
		if( qp[1] == 1 ) {
			decrease = true;
		} else {
			//UInt<2> temp1, temp2;
			BIG_INT_WORD_TYPE temp1[2], temp2[2];
			
			//UInt<2>::MulTwoWords(u_temp.table[0], v0, temp1.table+1, temp1.table);
			this->mulTwoWords(qp[0], v0, &temp1[1], &temp1[0]);
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
			this->subInt(1, 0, &qp[0], 2);
			
			rp += v1;
			
			if( rp >= v1 ) { // it means that there wasn't a carry (r<b from the book)
				next_test = true;
			}
		}
	}
	while( next_test );
	
	//TTMATH_LOG("UInt::Div3_Calculate")
	
	return qp[0];
}

/**
 * D4. [Multiply and subtract]
 *		includes also: D5. [Test Remainder] and D6. [add back]
 *
 */
void BigInt::div_multiplySubtract(	BigInt & uu,  const BigInt & vv, BIG_INT_WORD_TYPE & qp) const {
	// D4 (in the book)
	
	//UInt<value_size+1> vv_temp(vv);
	BigInt vv_temp(vv);
	vv_temp.mulInt(qp);
	
	//  D5. [Test Remainder]
	if( uu.sub(vv_temp) ) {
		// there was a carry (borrow)
		// D6. [add back]
		
		//
		// TODO make shure to test this code because the execution of this part is very unlikely (only of the order 2/b)
		//
		BIG_INT_WORD_COUNT_TYPE uuWordSizeWithoutCarry = uu.wordSize;
		
		--qp;
		uu.add(vv);
		
		// There can be a carry from this additions but it should be ignored
		// because it cancels with the borrow from uu.Sub(vv_temp).
		// My add() method does not return a carry bit because it automaticaly adds another most significant word.
		// Therefore, I truncate this word again (if it was added.);
		uu.wordSize = uuWordSizeWithoutCarry;
	}
	
	
	//TTMATH_LOG("UInt::Div3_MultiplySubtract")
}


/*!
 the third division algorithm
 
 this algorithm is described in the following book:
 "The art of computer programming 2" (4.3.1 page 257)
 Donald E. Knuth
 !! give the description here (from the book)
 */
void BigInt::div(const BigInt& divisor, BigInt* remainder) {
	const BigInt& dividend = *this;
	if(divisor == BigInt::ZERO) {
		std::string msg = "BigInt devision by (BigInt)0.";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	if(dividend < divisor) {
		// set the reminder to this value and replace this with "0";
		//*remainder = *this; // copy values from this to remainder
		//this->setZero();
		remainder->value = this->value;
		remainder->wordSize = this->wordSize;
		remainder->wordCapacity = this->wordCapacity;
		this->value = new BIG_INT_WORD_TYPE[1];
		this->wordCapacity = 1;
		this->setZero();
		return;
	}
	if(dividend == BigInt::ZERO) {
		// 0/x => result = 0; remainder = 0
		remainder->setZero();
		return;
	}
	if(dividend == divisor) {
		// x/x => result = 1; remainder = 0
		remainder->setZero();
		this->setOne();
		return;
	}
	
	//uint m,n, test;
	
	//  'm' - is the index (from 0) of last non-zero word in this->value ('dividend')
	//  'n' - is the index (from 0) of last non-zero word in divisor.value
	BIG_INT_WORD_COUNT_TYPE m = dividend.wordSize - 1;
	BIG_INT_WORD_COUNT_TYPE n = divisor.wordSize - 1;
	
	//test = Div_StandardTest(v, m, n, remainder);
	//if( test < 2 )
	//	return test;
	
	if( n == 0 ) {
		BIG_INT_WORD_TYPE r;
		r = this->divInt( divisor.value[0], this->value, &this->wordSize );
		//if( remainder ) {
			//remainder->SetZero();
			remainder->value[0] = r;
			remainder->wordSize = 1;
		//}
		return;
	}
	
	// we can only use the third division algorithm when
	// the divisor is greater or equal 2^32 (has more than one 32-bit word)
	++m;
	++n;
	m = m - n;
	this->div_division(divisor, remainder, m, n);
	
	//TTMATH_LOG("UInt::Div3")
}

BigInt BigInt::operator/ (const BigInt& other) const {
	BigInt result(*this); // copy this to new BigInt
	BigInt reminder(0);
	result.div(other, &reminder);
	return result;
}

BigInt BigInt::operator% (const BigInt& other) const {
	BigInt result(*this); // copy this to new BigInt
	BigInt reminder(0);
	result.div(other, &reminder);
	return reminder;
}

bool BigInt::operator< (const BigInt& other) const {
	if (this->wordSize < other.wordSize) {
		return true;
	}
	if (this->wordSize > other.wordSize) {
		return false;
	}
	
	assert(this->wordSize == other.wordSize);
	for (BIG_INT_WORD_COUNT_TYPE i = (this->wordSize - 1); i > 0; i--) {
		if (this->value[i] < other.value[i]) {
			return true;
		}
		
		if (this->value[i] > other.value[i]) {
			return false;
		}
	}
	return (this->value[0] < other.value[0]);
}

bool BigInt::operator<= (const BigInt& other) const {
	if (*this < other) {
		return true;
	}
	
	if (*this == other) {
		return true;
	}
	
	return false;
}

bool BigInt::operator> (const BigInt& other) const {
	return (!(*this <= other));
}

bool BigInt::operator>= (const BigInt& other) const {
	return (!(*this < other));
}

bool BigInt::operator== (const BigInt& other) const {
	if (*this < other) {
		return false;
	}
	
	if (other < *this) {
		return false;
	}
	
	return true;
}

bool BigInt::operator!= (const BigInt& other) const {
	return (!(*this == other));
}

BigInt& BigInt::operator= (const BigInt& other) {
	// check for self-assignment
	if(&other == this) {
		return *this;
	}
	
	// reuse storage when possible
	if(this->wordCapacity < other.wordSize) {
		delete [] this->value;
		this->value = new BIG_INT_WORD_TYPE[other.wordSize];
		this->wordCapacity = other.wordSize;
	}
	
	this->wordSize = other.wordSize;
	std::copy(&other.value[0], (&other.value[0] + other.wordSize), this->value);
	
	return *this;
}
