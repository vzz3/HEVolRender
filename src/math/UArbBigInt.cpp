
#include "UArbBigInt.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>		/* ciel */
#include <math.h>       /* log2 */
//#include <Security/Security.h>
#include "BigIntUtil.hpp"
#include <cassert>
#include <utility> // std::swap



using namespace ppvr::math;

// ----- statics -----

const UArbBigInt UArbBigInt::ZERO(0);
const UArbBigInt UArbBigInt::ONE(1);
const UArbBigInt UArbBigInt::TWO(2);
const UArbBigInt UArbBigInt::TEN(10);

#if _BIG_INT_WORD_LENGTH_PRESET_ >= 16
	const BIG_INT_WORD_TYPE UArbBigInt::bnExpModThreshTable[] = {7, 25, 81, 241, 673, 1793, BIG_INT_WORD_MAX_VALUE}; // Sentinel
#else
	const BIG_INT_WORD_TYPE UArbBigInt::bnExpModThreshTable[] = {7, 25, 81, 241, BIG_INT_WORD_MAX_VALUE}; // Sentinel
#endif

UArbBigInt UArbBigInt::fromUint64(const uint64_t& uint64Val) {
	UArbBigInt res(0);
	UArbBigInt::fromUint64(uint64Val, res);
	return res;
}

UArbBigInt& UArbBigInt::fromUint64(const uint64_t& uint64Val, UArbBigInt &target ) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = 1;
	size_t wordsFor64Bit = (sizeof(uint64_t) * CHAR_BIT) / BIG_INT_BITS_PER_WORD;

	// calculate required word count (move bits of uint64Val to the right by BITS_PER_WORD until uint64Val is zero

	// why do I need the extra check "requiredWords < wordsFor64Bit" ?
	// because shifing an unsigned 64bit variable by 64 bit to the right is not 0
	// example of the problem:
	// 		uint64_t int_2e63_test = 0x8000000000000000;	// 2^63 => b(10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000)
	//		uint64_t test_128 = int_2e63_test >> (8 * 7);	// expected: 128 => b(10000000) OK!
	//		uint64_t test_0 = int_2e63_test >> (8 * 8);		// expected: 0	actual result: 2^63 => b(10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000)
	for(; (uint64Val >> (requiredWords * BIG_INT_BITS_PER_WORD)) > 0 && requiredWords < wordsFor64Bit; requiredWords++);

	// alocate word store array
	target.reserveWords(requiredWords);

	// copy bits from uint64 into words
	for(BIG_INT_WORD_COUNT_TYPE i = 0; i < requiredWords; i++) {
		target.value[i] = (BIG_INT_WORD_TYPE)(uint64Val >> (i * BIG_INT_BITS_PER_WORD));
	}

	//UArbBigInt res(value, requiredWords, requiredWords);
	target.wordSize = requiredWords;
	return target;
}

UArbBigInt UArbBigInt::fromString(const std::string& str, const BIG_INT_WORD_TYPE base) {
	UArbBigInt res(0);
	UArbBigInt::fromString(str, base, res);
	return res;
}

UArbBigInt& UArbBigInt::fromString(const std::string& str, const BIG_INT_WORD_TYPE base, UArbBigInt &target ) {
	assert(base <= 16);

	// wordSize for 8bit words (2^8=256, l: string Length, b: base)
	// wordSize = log_256(b^l)
	//			= log_2(b^l) / 8
	//			= (log_b(b^l) / log_b(2) ) * (1/8)
	//			= (l / log_b(2)) * (1/8)
	//			= (l / (log_2(2) / log_2(b)) * (1/8)
	//			= (l / (       1 / log_2(b)) * (1/8)
	//			= (l * log_2(b) * (1/8)
	//std::cout << "string length: " << str.length() << std::endl;
	double sizeInBit = (double)str.length() * (log2((double)base));
	uint wordSize = std::ceil(sizeInBit / (double)BIG_INT_BITS_PER_WORD);
	//uint wordSize = 1;
	//UArbBigInt val(0, wordSize);
	target.reserveWords(wordSize);

	//UArbBigInt val(0);
	UArbBigInt pow(1, wordSize);
	UArbBigInt powTmp(0, wordSize);
	//UArbBigInt bigBase(base);
	//UArbBigInt t(0, 1);
	BIG_INT_WORD_TYPE d;
	UArbBigInt dPow(0, wordSize);
	for(size_t i = str.length(); i>0; i--) {
		char c = str[i-1];
		if(c >= '0' &&  c <= '9') {
			d = c - '0';
		} else if( base > 10 && c >= 'A' &&  c <= 'F') {
			d = 10 + c - 'A';
		} else if( base > 10 && c >= 'a' &&  c <= 'f') {
			d = 10 + c - 'a';
		} else {
			continue;
		}

		//powTmp = pow;

		// target = target + pow * t
		pow.mulInt(d, dPow);
		target.add(dPow);

		// pow = pow * base
		powTmp = pow;
		powTmp.mulInt(base, pow);
	}

	return target;
}


// ----- statics rendome -----

UArbBigInt UArbBigInt::randomNumber(const uint& sizeInBit, Random& rnd) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BIG_INT_REQUIRED_WORDS(sizeInBit);
	UArbBigInt res(0, requiredWords);
	UArbBigInt::randomNumber(sizeInBit, rnd, res);
	return res;
}

UArbBigInt UArbBigInt::randomNumber(const UArbBigInt& upperBound, Random& rnd) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BIG_INT_REQUIRED_WORDS(upperBound.bitLength());
	UArbBigInt res(0, requiredWords);
	UArbBigInt::randomNumber(upperBound, rnd, res);
	return res;
}

UArbBigInt& UArbBigInt::randomNumber(const uint& sizeInBit, Random& rnd, UArbBigInt &target) {
	if(sizeInBit < 1) {
		std::string msg = "ERROR randomNumber: the sizeInBit parameter must be greater then 0 ";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	// reserve required words
	BIG_INT_WORD_COUNT_TYPE requiredWords = BIG_INT_REQUIRED_WORDS(sizeInBit);
	target.setZero(); // prevent unessesery coping values that will be overwritten by random numbers anyway.
	target.reserveWords(requiredWords);

	// calculate required
	size_t requiredBytes = (sizeInBit + (CHAR_BIT - 1)) / CHAR_BIT;
	size_t oversizeInBits = requiredWords * BIG_INT_BITS_PER_WORD - sizeInBit;
	BIG_INT_WORD_TYPE oversizeMask = BIG_INT_WORD_MAX_VALUE >> oversizeInBits;

	do {
		// copy randome numbers
		/*
		int rc = SecRandomCopyBytes(kSecRandomDefault, requiredBytes, &(target.value[0]));
		if (rc != 0) {
			std::string msg = "ERROR SecRandomCopyBytes: " + std::to_string(rc);
			std::cerr << msg << std::endl;
			throw std::runtime_error(msg);
		}
		*/
		rnd.randomFill(&(target.value[0]), requiredBytes);

		// set new theoretical word size
		//target.wordSize = requiredWords;

		// set bits that are over sizeInBit to zero
		target.value[requiredWords-1] = target.value[requiredWords-1] & oversizeMask;

		// Set new word size of the result. If SecRandomCopyBytes generates many leading zeros the newWordSize can be less then requiredWords.
		//BIG_INT_WORD_COUNT_TYPE newWordSize;
		//for (newWordSize = requiredWords; newWordSize>1 && target.value[newWordSize-1] == 0; newWordSize--);
		//target.wordSize = newWordSize;
		target.trimWordSize(requiredWords);

	} while (target.isZero());

	return target;
}

UArbBigInt& UArbBigInt::randomNumber(const UArbBigInt& upperBound, Random& rnd, UArbBigInt &target) {
	if(upperBound.isZero()) {
		std::string msg = "ERROR upperBound: must be strictly greater than one";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	uint bits = upperBound.bitLength();
	do {
		UArbBigInt::randomNumber(bits, rnd, target);
		// make sure r <= upperBound (modulus)
	} while (target >= upperBound);
	return target;
}








// ----- constructors -----

UArbBigInt::UArbBigInt(): UArbBigInt(0, 0) {
	
}

UArbBigInt::UArbBigInt(const BIG_INT_WORD_TYPE& value): UArbBigInt(value, 0) {
	
}

UArbBigInt::UArbBigInt(const BIG_INT_WORD_TYPE& value, BIG_INT_WORD_COUNT_TYPE minCapacity) {
	BIG_INT_WORD_COUNT_TYPE newCapacity = std::max((BIG_INT_WORD_COUNT_TYPE)1, minCapacity);

	this->value = new BIG_INT_WORD_TYPE[newCapacity];
	this->value[0] = value;
	this->wordSize = 1;
	this->wordCapacity = newCapacity;
	//this->_dataRefCount = 1;
}

UArbBigInt::UArbBigInt(const UArbBigInt& src ) : UArbBigInt(src, 0) {
	
}

UArbBigInt::UArbBigInt(const UArbBigInt& src, BIG_INT_WORD_COUNT_TYPE minCapacity ) {
	BIG_INT_WORD_COUNT_TYPE newCapacity = std::max(src.wordSize, minCapacity);

	BIG_INT_WORD_TYPE *newValue = new BIG_INT_WORD_TYPE[newCapacity];
	std::copy(&src.value[0], &src.value[0] + src.wordSize, newValue);

	this->wordCapacity = newCapacity;
	this->wordSize = src.wordSize;
	this->value = newValue;
}

UArbBigInt::UArbBigInt(UArbBigInt&& src): UArbBigInt(src.value, src.wordCapacity, src.wordSize) {
	src.value = nullptr;
	src.wordCapacity = 0;
	src.wordSize = 0;
}

UArbBigInt::UArbBigInt(BIG_INT_WORD_TYPE* value, BIG_INT_WORD_COUNT_TYPE wordCapacity, BIG_INT_WORD_COUNT_TYPE wordSize) {
	this->value = value;
	this->wordCapacity = wordCapacity;
	this->wordSize = wordSize;
}

UArbBigInt::~UArbBigInt() {
	if(this->value != NULL) {
		delete [] this->value;
	}
}





// ----- memory managment -----

// asignment operators (operator=()) are at the an of the file

void UArbBigInt::reserveWords( const BIG_INT_WORD_COUNT_TYPE newCapacity ) {
	if(newCapacity <= this->wordCapacity) {
		return;
	}

	BIG_INT_WORD_TYPE *newValue = new BIG_INT_WORD_TYPE[newCapacity];
	std::copy(&this->value[0], &this->value[0] + this->wordSize, newValue);

	// free old word storage array
	delete [] this->value;

	// set new data to this
	this->value = newValue;
	this->wordCapacity = newCapacity;
}

void UArbBigInt::reserveWordsAndInitUnused( const BIG_INT_WORD_COUNT_TYPE newCapacity, const BIG_INT_WORD_TYPE initValue ) {
	this->reserveWords(newCapacity);

	// inizialize all words with an index >= this->wordSize (all alocated but not used words. this can be more then the (newCapacity - this->wordSize) because this->this->wordCapacity can be > then newCapacity)
	this->initUnusedWords(initValue);
}

void UArbBigInt::initUnusedWords(const BIG_INT_WORD_TYPE initValue) {
	std::fill_n(&this->value[this->wordSize], this->wordCapacity - this->wordSize, initValue);
}


// ----- value export - toString / toUint64 -----

uint64_t UArbBigInt::toUint64() const {
	uint64_t res = 0;
	uint64_t tmp;
	size_t wordsFor64Bit = (sizeof(uint64_t) * CHAR_BIT) / BIG_INT_BITS_PER_WORD;
	for( size_t i=0; i<wordSize && i<wordsFor64Bit; i++) {
		tmp = this->value[i];
		res = res | (tmp << (i * BIG_INT_BITS_PER_WORD));
	}

	return res;
}

std::string UArbBigInt::toStringHex() const {
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

std::string UArbBigInt::toStringDec() const {
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
	UArbBigInt tmp = *this;
	//UArbBigInt reminder(0);
	BIG_INT_WORD_TYPE decDigit;
	while (ZERO < tmp) {
		//tmp.div(UArbBigInt::TEN, &reminder);
		//decDigit = reminder.value[0];
		decDigit = tmp.divInt( 10 );
		ret = digits[decDigit] + ret;
	}

	return ret;
}


// ----- bit utilities -----

int UArbBigInt::bitLength() const {
	return findHighestSetBit()+1;
}

void UArbBigInt::setZero() {
	this->value[0] = 0;
	this->wordSize = 1;
}

void UArbBigInt::setOne() {
	this->value[0] = 1;
	this->wordSize = 1;
}

void UArbBigInt::setBit(const uint n) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BIG_INT_REQUIRED_WORDS(n+1);
	this->reserveWordsAndInitUnused(requiredWords);

	BIG_INT_WORD_COUNT_TYPE restBits = n % BIG_INT_BITS_PER_WORD;
	BIG_INT_WORD_COUNT_TYPE allWords = n / BIG_INT_BITS_PER_WORD;

	this->value[allWords] |= (BIG_INT_WORD_TYPE(1) << restBits);

	this->wordSize = std::max(this->wordSize, allWords + 1);
}

void UArbBigInt::clearBit(const uint n) {
	uint oldBitLength = this->bitLength();
	if(n <= oldBitLength) {
		uint restBits   = n % BIG_INT_BITS_PER_WORD;
		uint allWords 	= n / BIG_INT_BITS_PER_WORD;

		this->value[allWords] &= ~(BIG_INT_WORD_TYPE(1) << restBits);

		// if the higest bit was cleard, the word count could have changed
		if(n+1 == oldBitLength) {
			this->trimWordSize(this->wordSize);
		}
	}
}

UArbBigInt UArbBigInt::withBit(const uint n) {
	UArbBigInt res(*this);
	res.setBit(n);
	return res;
}

UArbBigInt UArbBigInt::withoutBit(const uint n) {
	UArbBigInt res(*this);
	res.clearBit(n);
	return res;
}

bool UArbBigInt::isZero() const {
	return (this->wordSize == 1 && this->value[0] == 0);
}

bool UArbBigInt::isOne() const {
	return (this->wordSize == 1 && this->value[0] == 1);
}

bool UArbBigInt::isEven() const {
	return !(this->testBit(0));
}

bool UArbBigInt::isOdd() const {
	return this->testBit(0);
}

bool UArbBigInt::testBit(uint n) const {
	uint restBits   = n % BIG_INT_BITS_PER_WORD;
	uint allWords 	= n / BIG_INT_BITS_PER_WORD;

	return ((this->value[allWords] >> restBits) & 1);
}

int UArbBigInt::findHighestSetBit() const {
	if(this->isZero()) {
		return -1;
	}

	int wordIndex = this->wordSize-1;

	const BIG_INT_WORD_TYPE word = this->value[wordIndex];
	int bit = BigIntUtil::findHighestSetBitInWord(word);

	return wordIndex * BIG_INT_BITS_PER_WORD + bit;
}

int UArbBigInt::findLowestSetBit() const {
	if(this->isZero()) {
		return -1;
	}

	int wordIndex=0;
	for(wordIndex=0; wordIndex < this->wordSize && this->value[wordIndex] == 0; wordIndex++);

	const BIG_INT_WORD_TYPE word = this->value[wordIndex];
	int bit = BigIntUtil::findLowestSetBitInWord(word);

	return wordIndex * BIG_INT_BITS_PER_WORD + bit;
}


// ----- word utilities -----

inline void UArbBigInt::trimWordSize(BIG_INT_WORD_COUNT_TYPE newMaxWordSize) {
	assert(newMaxWordSize <= this->wordCapacity);
	BIG_INT_WORD_COUNT_TYPE newWordSize;// = std::min(newMaxWordSize, this->wordCapacity); disable this min check for performance resons
	for (newWordSize = newMaxWordSize; newWordSize>1 && this->value[newWordSize-1] == 0; newWordSize--);
	this->wordSize = newWordSize;
}


// ----- shift left -----

void UArbBigInt::rcl_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, const uint bits, BIG_INT_WORD_TYPE c) {
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

BIG_INT_WORD_TYPE UArbBigInt::rcl_moveBits(const uint bits, BIG_INT_WORD_TYPE c) {
	assert( bits>0 && bits<BIG_INT_BITS_PER_WORD );

	uint move = BIG_INT_BITS_PER_WORD - bits;
	BIG_INT_WORD_COUNT_TYPE i;
	BIG_INT_WORD_TYPE newC;

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

BIG_INT_WORD_TYPE UArbBigInt::rcl(const uint bits, const BIG_INT_WORD_TYPE c, const bool resize) {
	BIG_INT_WORD_TYPE lastC    = 0;
	uint restBits = bits;
	if(resize) {
		// calculate required word size
		BIG_INT_WORD_COUNT_TYPE curLasWordIndex = this->wordSize - 1;
		uint newTotalBits = (curLasWordIndex) * BIG_INT_BITS_PER_WORD // currently total bits used
			+ BigIntUtil::findHighestSetBitInWord(this->value[curLasWordIndex]) + 1 // bits used in the current word (if findLeadingSetBitInWord() returns -1 the "this->wordSize" is already wrong!)
			+ bits;
		uint newWordCount = newTotalBits / BIG_INT_BITS_PER_WORD;
		if(newTotalBits % BIG_INT_BITS_PER_WORD > 0) {
			newWordCount++;
		}

		// reserver space for new words
		this->reserveWords(newWordCount);

		// init new words with zero
		std::fill_n(&this->value[this->wordSize], (newWordCount - this->wordSize), 0);

		// set new word size
		this->wordSize = newWordCount;
	}

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

UArbBigInt UArbBigInt::operator<< (const uint bits) const {
	UArbBigInt res(*this);
	res.rcl(bits, 0, true);
	return res;
}


// ----- shift right -----

void UArbBigInt::rcr_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, const uint bits, BIG_INT_WORD_TYPE c) {
	restBits      = bits % BIG_INT_BITS_PER_WORD;
	uint allWords = bits / BIG_INT_BITS_PER_WORD;
	BIG_INT_WORD_TYPE mask      = ( c ) ? BIG_INT_WORD_MAX_VALUE : 0;


	if( allWords >= this->wordSize ) {
		if( allWords == this->wordSize && restBits == 0 ) {
			lastC = (this->value[this->wordSize-1] & BIG_INT_WORD_HIGHEST_BIT) ? 1 : 0;
		}
		// else: last_c is default set to 0

		// clearing
		//for(uint i = 0 ; i<this->wordSize ; ++i) {
		//	this->value[i] = mask;
		//}
		this->value[0] = mask;
		this->wordSize = 1;

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
		//for( ; first<this->wordSize ; ++first ) {
		//	this->value[first] = mask;
		//}
		this->wordSize = first;
	}
}

BIG_INT_WORD_TYPE UArbBigInt::rcr_moveBits(const uint bits, BIG_INT_WORD_TYPE c) {
	assert ( bits>0 && bits<BIG_INT_BITS_PER_WORD );

	uint move = BIG_INT_BITS_PER_WORD - bits;
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

	if(this->wordSize > 1 && this->value[this->wordSize-1] == 0) {
		this->wordSize--;
	}

	return c;
}

BIG_INT_WORD_TYPE UArbBigInt::rcr(const uint bits, const BIG_INT_WORD_TYPE c) {
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

UArbBigInt UArbBigInt::operator>> (const uint bits) const {
	UArbBigInt res(*this);
	res.rcr(bits);
	return res;
}


// ----- boolean operations -----

void UArbBigInt::boolXor(const UArbBigInt &other) {
	if(this->wordSize < other.wordSize) {
		this->reserveWordsAndInitUnused(other.wordSize, 0);
	}
	
	BIG_INT_WORD_COUNT_TYPE newWordSize = 0;
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i < other.wordSize; i++) {
		this->value[i] = this->value[i] ^ other.value[i];
		if(this->value[i] > 0) {
			newWordSize = i;
		}
	}
	
	// If this is has more word than other:
	// The words with i >= other.wordSize are unchanged because "a xor 0 = a"
	if(this->wordSize <= other.wordSize) {
		this->wordSize = newWordSize + 1;
	}
}

UArbBigInt UArbBigInt::operator^ (const UArbBigInt& other) const {
	UArbBigInt result(*this, std::max(this->wordSize, other.wordSize));
	result.boolXor(other);
	return result;
}

void UArbBigInt::boolAnd(const UArbBigInt &other) {
	BIG_INT_WORD_COUNT_TYPE maxNewWordSize = std::min(this->wordSize, other.wordSize);
	
	BIG_INT_WORD_COUNT_TYPE newWordSize = 0;
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i < maxNewWordSize; i++) {
		this->value[i] = this->value[i] & other.value[i];
		if(this->value[i] > 0) {
			newWordSize = i;
		}
	}
	
	// truncate all my be available words abovenewWordSize by virtualy setting it to zero;
	this->wordSize = newWordSize + 1;
}

UArbBigInt UArbBigInt::operator& (const UArbBigInt& other) const {
	UArbBigInt result(*this);
	result.boolAnd(other);
	return result;
}


// ----- addition -----

void UArbBigInt::addInt(const BIG_INT_WORD_TYPE word) {

	BIG_INT_WORD_TYPE c = BigIntUtil::addInt(word, 0, this->value, this->wordSize);

	// increate the word count in order to add the last carry
	if(c != 0) {
		this->reserveWords(this->wordSize + 1);
		this->value[this->wordSize] = c;
		this->wordSize = this->wordSize + 1;
	}
}

void UArbBigInt::add(const UArbBigInt &other, UArbBigInt &result) const {
	BIG_INT_WORD_TYPE carry = 0;
	BIG_INT_WORD_TYPE a,b;//,c;
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->wordSize, other.wordSize);
	//BIG_INT_WORD_TYPE* resValue = new BIG_INT_WORD_TYPE[maxWordCount+1];
	if(result.wordCapacity < maxWordCount) {
		result.reserveWords(maxWordCount+1); // If we need to resize the storage array than also preserve the space for a possible carry bit
	}
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<maxWordCount; i++) {
		a = this->wordSize > i ? this->value[i] : 0;
		b = other.wordSize > i ? other.value[i] : 0;

		carry = BigIntUtil::addTwoWords(a, b, carry, &result.value[i]);
	}

	result.wordSize = maxWordCount; // net to be set before reserveWords() is called otherwise the new values between result.value[result.wordSize] and result.value[maxWordCount] will not be copied to the new array
	if(carry > 0) {
		result.reserveWords(maxWordCount+1); // reserve space for carry bit

		result.value[maxWordCount] = carry;
		result.wordSize = maxWordCount+1;
	} else {
		//result.wordSize = maxWordCount;
	}
}

void UArbBigInt::add(const UArbBigInt &other) {
	this->add(other, *this);
}

UArbBigInt UArbBigInt::operator+ (const UArbBigInt& other) const {
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->wordSize, other.wordSize);
	UArbBigInt result(0, maxWordCount+1);
	this->add(other, result);
	return result;
}


// ----- substraction -----

BIG_INT_WORD_TYPE UArbBigInt::subInt(const BIG_INT_WORD_TYPE word) {
	BIG_INT_WORD_TYPE c = BigIntUtil::subInt(word, 0, this->value, this->wordSize);

	// reduce word size if a word was truncated
	if(this->value[this->wordSize-1] == 0) {
		this->wordSize = this->wordSize-1;
	}

	return c;
}

BIG_INT_WORD_TYPE UArbBigInt::sub(const UArbBigInt& other, BIG_INT_WORD_TYPE carry, UArbBigInt &result) const {
	BIG_INT_WORD_TYPE a,b,c;
	BIG_INT_WORD_COUNT_TYPE usedWordIndex = 0;
	result.reserveWords(this->wordSize);

	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<this->wordSize; i++) {
		b = other.wordSize > i ? other.value[i] : 0;

		carry = BigIntUtil::subTwoWords(this->value[i], b, carry, &result.value[i]);
		if(result.value[i] > 0) {
			usedWordIndex = i;
		}
	}

	result.wordSize = usedWordIndex+1;
	return carry;
}

BIG_INT_WORD_TYPE UArbBigInt::sub(const UArbBigInt& other) {
	return this->sub(other, 0, *this);
}

UArbBigInt UArbBigInt::operator- (const UArbBigInt& other) const {
	if(other > *this) {
		std::string msg = "ERROR substract UArbBigInt a - b with a < b (a=" + this->toStringDec() + ", b=" + other.toStringDec() + ")!";
		std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	UArbBigInt result(0,this->wordSize);
	this->sub(other, 0, result);
	return result;
}


// ----- multiplication -----

void UArbBigInt::mulInt(BIG_INT_WORD_TYPE ss2, UArbBigInt& result) const {
	if( ss2 == 0 ) {
		result.setZero();
		return;
	}

	// reserve words at the result and inizialize ith with zeros
	result.reserveWords(this->wordSize+1);
	std::fill_n(result.value, this->wordSize+1, 0);

	BIG_INT_WORD_TYPE r2,r1;
	BIG_INT_WORD_COUNT_TYPE x1size=this->wordSize;
	BIG_INT_WORD_COUNT_TYPE x1start=0;

	// try to save some CPU sycles if this contains words with 0 at the start or at the end
	// if( value_size > 2 )
	if( this->wordSize > 2 ) {
		// if the value_size is smaller than or equal to 2
		// there is no sense to set x1size and x1start to another values

		for(x1size=this->wordSize ; x1size>0 && this->value[x1size-1]==0 ; --x1size);

		if( x1size == 0 ) {
			// this is 0: 0*x => 0
			result.setZero();
			return;
		}

		for(x1start=0 ; x1start<x1size && this->value[x1start]==0 ; ++x1start);
	}

	// performe the multiplication
	for(BIG_INT_WORD_COUNT_TYPE x1=x1start ; x1<x1size ; ++x1) {
		BigIntUtil::mulTwoWords(this->value[x1], ss2, &r2, &r1 );
		BigIntUtil::addTwoInts(r2, r1, x1, result.value, result.wordCapacity); // this->wordCapacity is > u.wordSize => there can not be a carry bit!
	}

	// check if the most significant word is > 0 and increase the wordSize if it is.
	// TODO remove this if addTwoInts() can take care of the this->wordSize
	if(result.value[this->wordSize] == 0) {
		result.wordSize = this->wordSize;
	} else {
		result.wordSize = this->wordSize + 1;
	}
}

void UArbBigInt::mulSchool(const UArbBigInt& a, const UArbBigInt& b, UArbBigInt& result) const {
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

	if( aSize==0 || bSize==0 ) {
		result.setZero();
		return;
	}

	BIG_INT_WORD_COUNT_TYPE maxWordCount = aSize + bSize;
	result.reserveWords(maxWordCount);
	std::fill_n(result.value, maxWordCount, 0);

	//if constexpr(true && !BIG_INT_FORCE_SCHOOL && BIG_INT_BITS_PER_WORD <= 32) {
	#if !defined(BIG_INT_FORCE_SCHOOL) && _BIG_INT_WORD_LENGTH_PRESET_ <= 32
		if (bSize == 1) {
			a.mulInt(b.value[0], result);
			return;
		} else if (aSize == 1) {
			b.mulInt(a.value[0], result);
			return;
		}
		
		// from JAVA private static int[] multiplyToLen(int[] x, int xlen, int[] y, int ylen, int[] z) {}
		// https://stackoverflow.com/questions/55778236/explanation-of-biginteger-multiplytolen-function
		bStart = aStart = 0;
		
		// Multiply first word
		/*
		uint64_t carry = 0;
		for (BIG_INT_WORD_COUNT_TYPE j=bStart, k=bStart+aStart; j < bSize; j++, k++) {
			assert( j < b.wordCapacity );
			assert( aStart < a.wordCapacity );
			assert( k < result.wordCapacity );

			uint64_t product =  (uint64_t)(b.value[     j]) *
								(uint64_t)(a.value[aStart]) + carry;
			result.value[k] = (BIG_INT_WORD_TYPE)product;

			carry = product >> BIG_INT_BITS_PER_WORD;
		}
		assert( bSize < result.wordCapacity );
		result.value[bSize] = (BIG_INT_WORD_TYPE)carry;
		*/
		// The last block is algorthmicaly equal to the following two lines. The loop is executed by the method BigIntUtil::mulAdd()
		BIG_INT_WORD_TYPE carry = BigIntUtil::mulAdd(result.value, 0, b.value, bStart, bSize, a.value[0]);
		result.value[bSize] = carry;
	
		// Add in subsequent words, storing the most significant word, which is new each time.
		for (BIG_INT_WORD_COUNT_TYPE i = aStart+1; i < aSize; i++) {
			/*
			carry = 0;
			for (BIG_INT_WORD_COUNT_TYPE j=bStart, k=bStart+i; j < bSize; j++, k++) {
				assert( j < b.wordCapacity );
				assert( i < a.wordCapacity );
				assert( k < result.wordCapacity );
				
				uint64_t product =  (uint64_t)(     b.value[j]) *
									(uint64_t)(     a.value[i]) +
									(uint64_t)(result.value[k]) + carry;
				result.value[k] = (BIG_INT_WORD_TYPE)product;
				
				carry = product >> BIG_INT_BITS_PER_WORD;
			}
			assert( bSize+i < result.wordCapacity );
			result.value[bSize+i] = (BIG_INT_WORD_TYPE)carry;
			*/
			// The last block is algorthmicaly equal to the following two lines. The loop is executed by the method BigIntUtil::mulAdd()
			carry = BigIntUtil::mulAdd(result.value, bStart+i, b.value, bStart, bSize, a.value[i]);
			result.value[bSize+i] = carry;
		}
	//} else {
	#else
		// basic school algorithem
		BIG_INT_WORD_TYPE r2, r1;
		for(BIG_INT_WORD_COUNT_TYPE aI=aStart ; aI<aSize ; ++aI) {
			for(BIG_INT_WORD_COUNT_TYPE bI=bStart ; bI<bSize ; ++bI) {
				BigIntUtil::mulTwoWords(a.value[aI], b.value[bI], &r2, &r1);
				BigIntUtil::addTwoInts(r2, r1, bI+aI, result.value, maxWordCount);
				// here will never be a carry
			}
		}
	//}
	#endif
	
	// optimize word count
	BIG_INT_WORD_COUNT_TYPE usedWordIndex;
	for(usedWordIndex = maxWordCount; usedWordIndex>0 && result.value[usedWordIndex-1] == 0; --usedWordIndex);

	result.wordSize = usedWordIndex;
}

void UArbBigInt::mulSchoolBasic(const UArbBigInt& a, const UArbBigInt& b, UArbBigInt& result) const {
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

	if( aSize==0 || bSize==0 ) {
		result.setZero();
		return;
	}

	BIG_INT_WORD_TYPE r2, r1;

	BIG_INT_WORD_COUNT_TYPE maxWordCount = aSize + bSize;
	result.reserveWords(maxWordCount);
	std::fill_n(result.value, maxWordCount, 0);

		// basic school algorithem
		for(BIG_INT_WORD_COUNT_TYPE aI=aStart ; aI<aSize ; ++aI) {
			for(BIG_INT_WORD_COUNT_TYPE bI=bStart ; bI<bSize ; ++bI) {
				BigIntUtil::mulTwoWords(a.value[aI], b.value[bI], &r2, &r1);
				BigIntUtil::addTwoInts(r2, r1, bI+aI, result.value, maxWordCount);
				// here will never be a carry
			}
		}
	
	// optimize word count
	BIG_INT_WORD_COUNT_TYPE usedWordIndex;
	for(usedWordIndex = maxWordCount; usedWordIndex>0 && result.value[usedWordIndex-1] == 0; --usedWordIndex);

	result.wordSize = usedWordIndex;
}

void UArbBigInt::mul(const UArbBigInt& b, UArbBigInt& result) const {
	this->mulSchool(*this, b, result);
}

void UArbBigInt::mul(const UArbBigInt& b) {
	UArbBigInt result = UArbBigInt(0, this->wordSize + b.wordSize);
	this->mul(b, result);
	*this = result;
}

UArbBigInt UArbBigInt::operator* (const UArbBigInt& other) const {
	UArbBigInt result = UArbBigInt(0, this->wordSize + other.wordSize);
	this->mul(other, result);
	return result;
}

// ----- division -----


// -- divInt

BIG_INT_WORD_TYPE UArbBigInt::divInt(BIG_INT_WORD_TYPE divisor, UArbBigInt& result) const {
	if(divisor == 0) {
		std::string msg = "UArbBigInt devision by (uint)0.";
		std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	if( divisor == 1 ) {
		if(this != &result) {
			result = *this;
		}
		return 0;
	}

	result.reserveWords(this->wordSize);

	//UInt<value_size> dividend(*this);
	const BIG_INT_WORD_TYPE* dividend = this->value;
	//SetZero();
	//BIG_INT_WORD_TYPE *result = new BIG_INT_WORD_TYPE[targetWordCount];
	//std::fill_n(result, targetWordCount, 0);

	int i;  // i must be with a sign
	BIG_INT_WORD_TYPE r = 0;

	BIG_INT_WORD_COUNT_TYPE newWordSize = this->wordSize;
	bool nonZeroWordRes = false;

	// we're looking for the last word in dividend (most significant word that is not null)
	//for(i=targetWordSize-1 ; i>0 && dividend[i]==0 ; --i);
	i = this->wordSize - 1;

	for( ; i>=0 ; --i) {
		BigIntUtil::divTwoWords(r, dividend[i], divisor, &result.value[i], &r);
		// find index+1 of most significant word which is not 0
		if(!nonZeroWordRes && i > 0) {
			if(result.value[i] == 0) {
				newWordSize = i;
			} else {
				nonZeroWordRes = true;
			}
		}
	}


	result.wordSize = newWordSize;
	return r;
}

BIG_INT_WORD_TYPE UArbBigInt::divInt(BIG_INT_WORD_TYPE divisor) {
	return this->divInt(divisor, *this);
}

// -- divKnuth

void UArbBigInt::divKnuth_division(UArbBigInt divisor, UArbBigInt &result, UArbBigInt& remainder, uint m, uint n) const {
	// this: dividend
	assert(n >= 2);
	//assert(this != &remainder);

	BIG_INT_WORD_COUNT_TYPE maxWordCount = this->wordSize;

	remainder = *this;

	//UInt<value_size+1> uu, vv;
	UArbBigInt uu(0, maxWordCount+1);
	//UArbBigInt vv(*this, maxWordCount+1);

	//UInt<value_size> q;
	result.reserveWords(maxWordCount);

	uint d, j=m;
	BIG_INT_WORD_TYPE u_value_size, u0, u1, u2, v1, v0;

	u_value_size = remainder.divKnuth_normalize(divisor, n, d);

	if( j+n == remainder.wordSize ) {
		u2 = u_value_size;
	} else {
		u2 = remainder.value[j+n];
	}

	//Div3_MakeBiggerV(v, vv);
	UArbBigInt vv(divisor, maxWordCount+1);
	//std::copy(&divisor.value[0], (&divisor.value[0] + divisor.wordSize), vv);
	//vv[divisor.wordSize] = 0;

	std::fill_n(result.value, maxWordCount, 0);

	while( true ) {
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

		u2 = remainder.value[j+n];
	}

	BIG_INT_WORD_COUNT_TYPE newWordSize;
	// trim reminder word size
	//for (newWordSize = n; newWordSize>1 && remainder.value[newWordSize-1] == 0; newWordSize--);
	//remainder.wordSize = newWordSize;
	remainder.trimWordSize(n);

	// set new word size of the result
	//for (newWordSize = maxWordCount; newWordSize>1 && result.value[newWordSize-1] == 0; newWordSize--);
	//result.wordSize = newWordSize;
	result.trimWordSize(maxWordCount);

	//if( remainder ) {
		remainder.divKnuth_unnormalize(d);
	//}

	//*this = result;
}

void UArbBigInt::divKnuth_makeNewU(UArbBigInt &uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n, BIG_INT_WORD_TYPE u_max) const {
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
}

void UArbBigInt::divKnuth_copyNewU(const UArbBigInt & uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n) {
	BIG_INT_WORD_COUNT_TYPE i;

	for(i=0 ; i<n ; ++i) {
		this->value[i+j] = uu.value[i];
	}

	if( i+j < this->wordSize ) {
		this->value[i+j] = uu.value[i];
	}
}

BIG_INT_WORD_TYPE UArbBigInt::divKnuth_normalize(UArbBigInt& divisor, uint n, uint & d) {
	// this = dividend, v = divisor
	// v.table[n-1] is != 0

	uint bit  = (uint)BigIntUtil::findHighestSetBitInWord(divisor.value[n-1]); // TODO divisor.value[divisor.wordSize - 1] ?
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

	return res;
}

void UArbBigInt::divKnuth_unnormalize(BIG_INT_WORD_COUNT_TYPE d) {
	this->rcr(d,0);
	//*remainder = *this;
}

BIG_INT_WORD_TYPE UArbBigInt::divKnuth_calculate(BIG_INT_WORD_TYPE u2, BIG_INT_WORD_TYPE u1, BIG_INT_WORD_TYPE u0, BIG_INT_WORD_TYPE v1, BIG_INT_WORD_TYPE v0) const {
	
	BIG_INT_WORD_TYPE rp, c;
	bool next_test;

	assert( v1 != 0 );

	//UInt<2> u_temp;
	// u_temp in qp (quotient) umbenant
	BIG_INT_WORD_COUNT_TYPE qpWordCount = 2;
	BIG_INT_WORD_TYPE qpValue[2];
	UArbBigInt qp(&qpValue[0], qpWordCount, (u2 > 0 ? qpWordCount : qpWordCount-1));
	qp.value[1] = u2;
	qp.value[0] = u1;
	//u_temp.DivInt(v1, &rp);
	rp = qp.divInt(v1);

	//TTMATH_ASSERT( u_temp.table[1]==0 || u_temp.table[1]==1 )
	assert( qp.value[1]==0 || qp.value[1]==1 );

	do {
		bool decrease = false;

		if( qp.value[1] == 1 ) {
			decrease = true;
		} else {
			//UInt<2> temp1, temp2;
			BIG_INT_WORD_TYPE temp1[2], temp2[2];

			//UInt<2>::MulTwoWords(u_temp.table[0], v0, temp1.table+1, temp1.table);
			BigIntUtil::mulTwoWords(qp.value[0], v0, &temp1[1], &temp1[0]);
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
			qp.subInt(1);

			rp += v1;

			if( rp >= v1 ) { // it means that there wasn't a carry (r<b from the book)
				next_test = true;
			}
		}
	}
	while( next_test );

	qp.value = NULL;
	return qpValue[0];
}

void UArbBigInt::divKnuth_multiplySubtract(	UArbBigInt & uu,  const UArbBigInt & vv, BIG_INT_WORD_TYPE & qp) const {
	// D4 (in the book)

	//UInt<value_size+1> vv_temp(vv);
	UArbBigInt vv_temp(0, vv.wordSize+1);
	vv.mulInt(qp, vv_temp);

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
}

void UArbBigInt::divKnuth(const UArbBigInt& divisor, UArbBigInt &result, UArbBigInt& remainder) const {
	const UArbBigInt& dividend = *this;
	if(divisor.isZero()) {
		std::string msg = "UArbBigInt devision by (UArbBigInt)0.";
		std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	if(dividend < divisor) {
		// set the reminder to this value and replace this with "0";
		remainder = *this;
		result.setZero();
		return;
	}
	if(dividend.isZero()) {
		// 0/x => result = 0; remainder = 0
		remainder.setZero();
		result.setZero();
		return;
	}
	if(dividend == divisor) {
		// x/x => result = 1; remainder = 0
		remainder.setZero();
		result.setOne();
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
		r = this->divInt( divisor.value[0], result );
		//if( remainder ) {
			//remainder->SetZero();
			remainder.value[0] = r;
			remainder.wordSize = 1;
		//}
		return;
	}

	// we can only use the third division algorithm when
	// the divisor is greater or equal 2^32 (has more than one 32-bit word)
	++m;
	++n;
	m = m - n;

	this->divKnuth_division(divisor, result, remainder, m, n);
}

void UArbBigInt::div(const UArbBigInt& divisor, UArbBigInt &result, UArbBigInt& remainder) const {
	this->divKnuth(divisor, result, remainder);
}

void UArbBigInt::div(const UArbBigInt& divisor, UArbBigInt& remainder) {
	this->div(divisor, *this, remainder);
	//UArbBigInt result;
	//this->div(divisor, result, *this);
	//*this = result;
}

UArbBigInt UArbBigInt::operator/ (const UArbBigInt& other) const {
	UArbBigInt result(0, this->wordSize), reminder(0, this->wordSize);
	this->div(other, result, reminder);
	return result;
}

UArbBigInt UArbBigInt::operator% (const UArbBigInt& other) const {
	UArbBigInt result(0, this->wordSize), reminder(0, this->wordSize);
	this->div(other, result, reminder);
	return reminder;
}

/*
UArbBigInt UArbBigInt::operator/ (const UArbBigInt& other) const {
	UArbBigInt result(*this); // copy this to new UArbBigInt
	UArbBigInt reminder(0);
	result.div(other, reminder);
	return result;
}


UArbBigInt UArbBigInt::operator% (const UArbBigInt& other) const {
	UArbBigInt result(*this); // copy this to new UArbBigInt
	UArbBigInt reminder(0);
	result.div(other, reminder);
	return reminder;
}
*/


// ----- pow(), sqrt() -----

void UArbBigInt::square(const UArbBigInt& a, UArbBigInt& result) {
	//assert(BIG_INT_BITS_PER_WORD <= 32);
#if !defined(BIG_INT_FORCE_SCHOOL) && _BIG_INT_WORD_LENGTH_PRESET_ <= 32
	/*
	 * The algorithm used here is adapted from Colin Plumb's C library.
	 * see lbn32.c lbnSquare_32(BNWORD32 *prod, BNWORD32 const *num, unsigned len), line 1069
	 *
	 *
	 * Technique: Consider the partial products in the multiplication
	 * of "abcde" by itself:
	 *
	 *               a  b  c  d  e
	 *            *  a  b  c  d  e
	 *          ==================
	 *              ae be ce de ee
	 *           ad bd cd dd de
	 *        ac bc cc cd ce
	 *     ab bb bc bd be
	 *  aa ab ac ad ae
	 *
	 * Note that everything above the main diagonal:
	 *              ae be ce de = (abcd) * e
	 *           ad bd cd       = (abc) * d
	 *        ac bc             = (ab) * c
	 *     ab                   = (a) * b
	 *
	 * is a copy of everything below the main diagonal:
	 *                       de
	 *                 cd ce
	 *           bc bd be
	 *     ab ac ad ae
	 *
	 * Thus, the sum is 2 * (off the diagonal) + diagonal.
	 *
	 * This is accumulated beginning with the diagonal (which
	 * consist of the squares of the digits of the input), which is then
	 * divided by two, the off-diagonal added, and multiplied by two
	 * again.  The low bit is simply a copy of the low bit of the
	 * input, so it doesn't need special care.
	 *
	 */

	BIG_INT_WORD_COUNT_TYPE len = a.wordSize;
	BIG_INT_WORD_COUNT_TYPE resultLen = a.wordSize * 2;
	result.setZero(); result.reserveWords(resultLen); result.initUnusedWords();
	
	// Store the squares, right shifted one bit (i.e., divided by 2)
	BIG_INT_WORD_TYPE lastProductLowWord = 0;
	for (int j=len-1, i=resultLen-1; j >= 0; j--) {
		assert( j >= 0 );
		assert( i-1 >= 0 );
		assert( j < len );
		assert( i < resultLen );
		
		uint64_t piece = (uint64_t)(a.value[j]);
		uint64_t product = piece * piece;
		result.value[i--] = (lastProductLowWord << (BIG_INT_BITS_PER_WORD-1)) | (BIG_INT_WORD_TYPE)(product >> (BIG_INT_BITS_PER_WORD+1)); //z[i++] = (lastProductLowWord << 31) | (int)(product >>> 33);
		result.value[i--] = (BIG_INT_WORD_TYPE)(product >> 1);
		lastProductLowWord = (BIG_INT_WORD_TYPE)product;
	}

	// Add in off-diagonal sums
	for (BIG_INT_WORD_COUNT_TYPE i=0, offset=1; i < len-1; i++, offset+=2) {
		BIG_INT_WORD_COUNT_TYPE lenx = len - i - 1;
		assert( i >= 0 );
		assert( i < len );
		//assert( offset >= 0 );
		//assert( offset < len );
		
		BIG_INT_WORD_TYPE t = a.value[i];
		t = BigIntUtil::mulAdd(result.value, offset, a.value, i+1, lenx, t); //t = mulAdd(z, x, offset, i-1, t);
		BIG_INT_WORD_TYPE cTest = BigIntUtil::addInt(t, offset+lenx, result.value, resultLen); //lbnAdd1_32(BIGLITTLE(prodx-lenx,prodx+lenx), lenx+1, t); //addOne(result.value, offset-1, i, t);
		assert(cTest == 0);
	}

	// Shift the result back up
	result.wordSize = resultLen;
	BIG_INT_WORD_TYPE carry = result.rcl(1, 0, false); //primitiveLeftShift(z, zlen, 1);
	assert( carry == 0 );
	result.trimWordSize(resultLen);
	
	// And set the low bit appropriately
	result.value[0] |= a.value[0] & 1; //result.value[resultLen-1] |= a.value[len-1] & 1;
#else
	a.mul(a, result);
#endif
}

UArbBigInt UArbBigInt::square() const {
	UArbBigInt result = UArbBigInt(0, this->wordSize*2);
	square(*this, result);
	return result;
}

UArbBigInt UArbBigInt::pow(UArbBigInt pow) const {
	//if( IsNan() )
	//	return 1;

	if( this->isZero() ) {
		if( pow.isZero() ) {
			// we don't define zero^zero
			std::string msg = "UArbBigInt zero^zero is not defined.";
			std::cerr << msg << std::endl;
			throw std::invalid_argument(msg);
		}

		// 0^(+something) is zero
		//return 0;
		return *this;
	}

	UArbBigInt start(*this);
	UArbBigInt result(1);
	uint c = 0;
	
	UArbBigInt squereRes{0};

	//while( !c ) {
	while( true ) {
		if( pow.isOdd() ) {//if( pow.value[0] & 1 ) {
			//c += result.mul(start);
			result = result * start;
		}

		pow.rcr(1);

		if( pow.isZero() ) {
			break;
		}

		//c += start.Mul(start);
		square(start, squereRes);
		start = squereRes;
	}

	//*this = result;
	//return CheckCarry(c);
	return result;
}

UArbBigInt UArbBigInt::sqrt() const {
	if( this->isZero() ) {
		return UArbBigInt(0);
	}

	UArbBigInt bit(0, this->wordSize), temp(0, this->wordSize), result(0, this->wordSize);

	UArbBigInt value(*this);

	//this->setZero();
	//bit.SetZero();
	std::fill_n(bit.value, this->wordSize, 0);
	bit.value[this->wordSize-1] = (BIG_INT_WORD_HIGHEST_BIT >> 1);
	bit.wordSize = this->wordSize;

	while( bit > value ) {
		bit.rcr(2);
	}

	while( !bit.isZero() ) {
		temp = result;
		temp.add(bit);

		if( value >= temp ) {
			value.sub(temp);
			result.rcr(1);
			result.add(bit);
		} else {
			result.rcr(1);
		}

		bit.rcr(2);
	}

	return result;
}


// ----- modInverse / gcd -----

// https://www.di-mgt.com.au/euclidean.html
UArbBigInt UArbBigInt::gcd(const UArbBigInt & a, const UArbBigInt & b) {
	if (a.isZero()) {
		return b;
	}
	return gcd(b % a, a);
}

UArbBigInt UArbBigInt::gcd(const UArbBigInt & b) const {
	return gcd(*this, b);
}


/*
uint UArbBigInt::gcdExtended_binaryIterative_removePowersOfTwo(UArbBigInt& a, UArbBigInt& b) {
	uint c = 0;
	// calculated the amount of zeros first
	while (a.isEven() && b.isEven()) {
		a.rcr(c);
		b.rcr(c);
	}
	return c;
}
* /
/ *
void UArbBigInt::gcdExtended_binaryIterative(const UArbBigInt& aIn, const UArbBigInt& bIn, UArbBigInt& u, UArbBigInt& v, UArbBigInt* gcd) {
	// https://github.com/DavidNorman/gcd
	
	UArbBigInt a{aIn};
	UArbBigInt b{bIn};
	
	// Start with 'a' and 'b'
	uint c = gcdExtended_binaryIterative_removePowersOfTwo(a, b); //// Remove common factors of 2 from both and remember how many factors of 2 there were (=c)
	UArbBigInt Rx{a};
	UArbBigInt Ry{b};
	UArbBigInt Sx{1};
	UArbBigInt Sy{0};
	UArbBigInt Tx{0};
	UArbBigInt Ty{1};
	while (Rx != Ry) { // Repeat until Rx==Ry:
		if(Rx.isOdd()) { // If 'Rx' is odd:
			if (Rx > Ry) { //If (Rx > Ry):
				Rx = Rx - Ry; //Rx -> Rx - Ry
				Sx = Sx - Sy; //Sx -> Sx - Sy
				Rx = Tx - Ty; //Tx -> Tx - Ty
			} else { //Else:
				Ry = Ry - Rx; //Ry -> Ry - Rx
				Sy = Sy - Sx; //Sy -> Sy - Sx
				Ty = Ty - Tx; //Ty -> Ty - Tx
			}
		} else {//if(Rx.isEven()) { //Else: (Rx is even)
			Rx = Rx >> 2; //Rx -> Rx / 2
			if(Sx.isEven() &&  Sy.isEven()) { //If Sx==even AND Sy==even:
				Sx = Sx >> 2; //Sx -> Sx / 2
				Rx = Tx >> 2; //Tx -> Tx / 2
			} else { //Else:
				Sx = (Sx + b) >> 2; //Sx -> (Sx + b) / 2
				Tx = (Tx - a) >> 2; //Tx -> (Tx - a) / 2
			}
		}
	}
	// at this point Rx == Ry == GCD without the common powers of 2
	assert( Rx * TWO.pow(UArbBigInt::fromUint64(c)) == UArbBigInt::gcd(aIn, bIn) ); // GCD = Rx * 2^c
	if( gcd != nullptr) {
		*gcd = Rx * TWO.pow(UArbBigInt::fromUint64(c)); // GCD = Rx * 2^c
	}
	
	u = Sx; //S = Sx
	v = Tx; //T = Tx
}
* /
/ *
void UArbBigInt::gcdExtended_binaryIterative(const UArbBigInt& aIn, const UArbBigInt& bIn, UArbBigInt& uOut, UArbBigInt& vOut, UArbBigInt* gcd) {
	// https://www.di-mgt.com.au/euclidean.html
	// https://cs.stackexchange.com/questions/86779/maximum-value-reached-in-extended-binary-gcd
	
	UArbBigInt x, y;
//	if( aIn < bIn ) {
//		x = aIn;
//		y = bIn;
//	} else {
//		throw std::invalid_argument("a must be les then b. Posible solution: calculate a = aIn mod bIn ???");
//	}
	x = aIn;
	y = bIn;
	bool swappedInputVars;
	uint c = gcdExtended_binaryIterative_removePowersOfTwo(x,y);
	
	if( y.isEven() ) {
		//throw std::invalid_argument("bIn need to be an odd prime");
		// posible solution:
		// flip a and b
		// If and are both even, a first step is to factor them both by the greatest power of possible (which boils down to a cheap bit shift), so that one of them necessarily becomes odd.
		
		std::swap(x, y);
		assert(y.isOdd());
		swappedInputVars = true;
	} else {
		swappedInputVars = false;
	}
	
	// # Begin of the actual extended binary euclidean algorithm that does not rquire signed variables
	// Given positive integer inputs x and y, with 0<x<y and y an odd prime
	UArbBigInt A,B,U,V; //d=U, a=V, u=A, v=B
	if(x.isOdd()) {
		A = x;
	} else {
		A = x + y;
	}
	
	B = y;
	U = B - UArbBigInt{1};//A - 1;
	V = UArbBigInt{0};
	
	while (!B.isOne()) {
		// invariant here and at start of the next while loop: u and v are odd and distinct
		while (B < A) {
			A = A - B;
			U = U + V;
			while (A.isEven()) { // that's at least once
				if(U.isOdd()) {
					U = U + y;
				}
				A = A >> 1; //A / TWO;
				U = U >> 1; //U / TWO;
			}
		}
		B = B - A;
		V = V + U;
		while (B.isEven()) { // that's at least once
			if (V.isOdd()) {
				V = V + y;
				// Note: I'm aware that by changing a←a+y to:
				//	if a<y	 then a←a+y; else a←a−y;
				// and same for d←d+y, we keep a and d below 4y; I'm asking what if we do not.
			}
			B = B >> 1; //B / TWO;
			V = V >> 1; //V / TWO;
		}
	}
	//a = a % y; //that's the desired inverse.
	// End of the extenden binary euclidean algorithm
	//uOut = V;
	
	
	// at this point Rx == Ry == GCD without the common powers of 2
	assert( B * TWO.pow(UArbBigInt::fromUint64(0)) == UArbBigInt::gcd(aIn, bIn) ); // GCD = Rx * 2^c
	if( gcd != nullptr) {
		*gcd = B * TWO.pow(UArbBigInt::fromUint64(c)); // GCD = Rx * 2^c
	}
	
	if(swappedInputVars) {
		uOut = U;
		vOut = V;
	} else {
		uOut = V; //S = Sx
		vOut = U; //T = Tx
	}
}
*/

UArbBigInt UArbBigInt::gcdExtended_binaryIterative(const UArbBigInt& aIn, const UArbBigInt& bIn, UArbBigInt& uOut/*, UArbBigInt& vOut*/) {
	
	// Shifting Euclidean algorithm with unsigned arithmetic:
	// SEUinv(a,b) -> inverse of a mod bIn, Shifting Euclidean alg, using Unsigned
	UArbBigInt u, r, v, s, t;
	uint f;
	if (aIn < bIn) {
	   u = bIn; v = aIn;
	   r = 0; s = 1;
	} else {
	   v = bIn; u = aIn;
	   s = 0; r = 1;
	}
	while( v > 1) {
		f = u.bitLength() - v.bitLength();    // U >= V, f >= 0
		if(  u < (v << f)) {
			f = f - 1;
		}
		u = u - (v << f);   // always U >= 0
		t = s;
		for (uint i=0; i<f; i++) { //for i = 1:f
			t = t+t;               // #adds <= bits(U)+bits(V)
			if( t > bIn) {
				t = t - bIn;
			}
		}
		//R = R - t;                // check R < t beforhand
		while( r < t) {
			r = r + bIn; // one of R,S gets large soon
		}
		r = r - t;
		
		if( u < v) {
		  t = u; u = v; v = t;   // swap(U,V)
		  t = r; r = s; s = t;   // swap(R,S)
		}
	}
//	if (V == 0) {
//		S = 0;
//	}
	
	uOut = s;
	//vOut = r;
	
	if( v.isZero() ) {
		assert( u == UArbBigInt::gcd(aIn, bIn) );
		return u;
	} else {
		assert( v == UArbBigInt::gcd(aIn, bIn) );
		return v;
	}
}

UArbBigInt UArbBigInt::modInverse(const UArbBigInt & m) const {
	if (m.isZero()) {
		std::string msg = "ERROR UArbBigInt: modulus not positive!";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	if (m.isOne()) {
		return UArbBigInt(0);
	}

	// all the hard work will be done by gcd.
	UArbBigInt u/*, v*/;
	
//	if(false) {
		UArbBigInt gcd = gcdExtended_binaryIterative(*this, m, u/*, v*/);
		if(!gcd.isOne()) {
			std::string msg = "ERROR UArbBigInt: " + this->toStringDec() + " does not have a multiplicative inverse mod " + m.toStringDec() + " becaus the numbers are not relatively prime to!";
			//std::cerr << msg << std::endl;
			throw NoMultiplicativeInverse(msg);
		}
		
//	}
	
//	if(false) {
//		// TODO The montgcd does not produce the gcd, therefore I can not  throw an exception.
//		// Therefore, I added an assert() with a seperate gcd calculation.
//	//	UArbBigInt gcd = this->gcdExtended(*this, m, u, v);
//	//	if(!gcd.isOne()) {
//	//		std::string msg = "ERROR UArbBigInt: " + this->toStringDec() + " does not have a multiplicative inverse mod " + m.toStringDec() + " becaus the numbers are not relatively prime to!";
//	//		//std::cerr << msg << std::endl;
//	//		throw NoMultiplicativeInverse(msg);
//	//	}
//
//		gcdExtended_binary4mont(*this, m, u, v);
//		assert( !(gcd(m).isOne()) );
//		assert( ( TWO*(*this)*u - m*v).isOne() );
//	}
//
//	if(false) {
//#ifndef NDEBUG
//		// debug build
//		UArbBigInt gcd;
//		gcdExtended_binaryIterative(*this, m, u, v, &gcd);
//		assert( gcd.isOne() );
//#else
//		gcdExtended_binaryIterative(*this, m, u, v);
//#endif
//	}
//
//	if(true) {
//		gcdExtended_binaryIterative(*this % m, m, u, v);
//	}
//
//	if(false) {
//		// ExtendedBinaryGCD(classicalgorithm)
//		// Require: Oddmodulusm(m ≥ 3,m mod 2 = 1)andvaluetoinverty(0 ≤ y < m) Ensure: 1/y mod m (if GCD(y, m) = 1), or zero
//		UArbBigInt a = *this % m; // ensure base < modulus;
//		UArbBigInt b = m;
//		u = ONE;
//		v = ZERO;
//		while (!a.isZero()) {
//			if(a.isEven()) {
//				// a is even, so this division is exact.
//				a = a / TWO;
//				u = u / TWO % m;
//			} else {
//				if( a < b) {
//					// Conditional swap to ensure a ≥ b.
//					std::swap(a, b);
//					std::swap(u, v);
//					//std::swap(b, a);
//					//std::swap(v, u);
//				}
//				a = (a-b) / TWO; // a and b are odd,so this division is exact.
//				u = (u-v) / TWO % m;
//			}
//		}
//		if(!b.isOne()) {
//			// return 0 (value y is not invertible) ⊲ b contains GCD(y, m) at this point.
//
//			std::string msg = "ERROR UArbBigInt: " + this->toStringDec() + " does not have a multiplicative inverse mod " + m.toStringDec() + " becaus the numbers are not relatively prime to!";
//			//std::cerr << msg << std::endl;
//			throw NoMultiplicativeInverse(msg);
//		}
//		return v;
//	}
	
	
	
	//if (u < 0) {
	//	u = u + m;
	//}
	return u % m;
}

// ----- modPow -----

void UArbBigInt::modPow_naiv(UArbBigInt& base, UArbBigInt &exponent, const UArbBigInt &modulus, UArbBigInt& result) {
	result.setOne();
	//Assert :: (modulus - 1) * (modulus - 1) does not overflow base

	// ensure that the base is < modulus
	//SArbBigInt base = (this->signum < 0 || *this >= modulus) ? (*this % modulus) : *this;
	//UArbBigInt baseTmp = (base >= modulus) ? (base % modulus) : base;
	
	UArbBigInt squereRes{0, modulus.wordSize*2};
	
	while ( !exponent.isZero()) {
		if (exponent.isOdd()) {
			result = (result * base) % modulus;
		}
		exponent.rcr(1);
		UArbBigInt::square(base, squereRes);
		base = squereRes % modulus;
	}
}

void UArbBigInt::modPow_montgomery(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result) {
	if (modulus.isOdd()) {
		modPow_montgomeryOdd(base, exponent, modulus, result);
	} else {
		modPow_montgomeryEven(base, exponent, modulus, result);
	}
}

void UArbBigInt::modPow_montgomeryEven(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result) {
	/*
	 * Even modulus.  Tear it into an "odd part" (m1) and power of two
	 * (m2), exponentiate mod m1, manually exponentiate mod m2, and
	 * use Chinese Remainder Theorem to combine results.
	 */
	
	
	// B = base
	// X = exponent
	//
	// C = p
	// M = m1 (= modulus)
	// P = m2
	
	//uint32 R, K, I, P;
	//uint32 X1, X2, Y;
	//size_t C;

	//C = ntz32(M);
	//M >>= C;
	//P = 1lu << C;
	
	// Tear modulus apart into odd part (m1) and power of 2 (m2)
	int p = modulus.findLowestSetBit(); // Max pow of 2 that divides modulus
	UArbBigInt m1 = modulus >> p;  // modulus/2**p
	UArbBigInt m2 = UArbBigInt::ONE << p; // 2**p

	// R = reciprocal
	// K = factor
	UArbBigInt reciprocal, factor;
	
	//montgcd(m2 >> 1, m1, reciprocal, factor);// montgcd(P >> 1, m1, R, K);
	
	//UArbBigInt I = m2 - factor;//I = P - K;

	// Calculate new base from m1
	UArbBigInt base2 = (/*base.signum < 0 ||*/ base >= m1) ? (base % m1) : base;
	
	// X1 = a1
	// X2 = a2
	UArbBigInt a1, a2;
	
	// Caculate (base ** exponent) mod m1.
	if(m1.isOne()) {
		a1.setZero();
	} else {
		modPow_montgomeryOdd(base2, exponent, m1, a1); // X1 = montmodpow_odd(B, X, M);
	}
	// Calculate (this ** exponent) mod m2
	a2 = base.modPow2(exponent, p); // X2 = modpow2x(B, X, P);
/*
	if (X2 < X1)
	{
		Y = (X1 - X2);
		Y &= (P - 1);
		if (Y != 0)
		{
			Y = P - Y;
		}
	}
	else
	{
		Y = (X2 - X1);
		Y &= (P - 1);
	}

	Y *= I;
	Y &= (P - 1);
	X1 += (M * Y);
	return X1;
 */
	// Combine results using Chinese Remainder Theorem
	UArbBigInt y1 = m2.modInverse(m1);
	UArbBigInt y2 = m1.modInverse(m2);

	//if (m.mag.length < MAX_MAG_LENGTH / 2) {
	result = (a1 * m2 * y1 + a2 * m1 * y2) % modulus;
//	} else {
//	MutableBigInteger t1 = new MutableBigInteger();
//	new MutableBigInteger(a1.multiply(m2)).multiply(new MutableBigInteger(y1), t1);
//	MutableBigInteger t2 = new MutableBigInteger();
//	new MutableBigInteger(a2.multiply(m1)).multiply(new MutableBigInteger(y2), t2);
//	t1.add(t2);
//	MutableBigInteger q = new MutableBigInteger();
//	result = t1.divide(new MutableBigInteger(m), q).toBigInteger();
//	}
}

/*
// From Hacker's Delight
// https://github.com/hcs0/Hackers-Delight/blob/master/mont64.c.txt
void UArbBigInt::gcdExtended_binary4mont(UArbBigInt a, UArbBigInt b, UArbBigInt& u, UArbBigInt& v) {
	/ * C program implementing the extended binary GCD algorithm. C.f.
	http://www.ucl.ac.uk/~ucahcjm/combopt/ext_gcd_python_programs.pdf. This
	is a modification of that routine in that we find s and t s.t.
		gcd(a, b) = s*a - t*b,
	rather than the same expression except with a + sign.
	   This routine has been greatly simplified to take advantage of the
	facts that in the MM use, argument a is a power of 2, and b is odd. Thus
	there are no common powers of 2 to eliminate in the beginning. The
	parent routine has two loops. The first drives down argument a until it
	is 1, modifying u and v in the process. The second loop modifies s and
	t, but because a = 1 on entry to the second loop, it can be easily seen
	that the second loop doesn't alter u or v. Hence the result we want is u
	and v from the end of the first loop, and we can delete the second loop.
	   The intermediate and final results are always > 0, so there is no
	trouble with negative quantities. Must have a either 0 or a power of 2
	<= 2**63. A value of 0 for a is treated as 2**64. b can be any 64-bit
	value.
	   Parameter a is half what it "should" be. In other words, this function
	does not find u and v st. u*a - v*b = 1, but rather u*(2a) - v*b = 1.
	* /
	
	u.setOne();
	v.setZero();
	UArbBigInt alpha{a};
	UArbBigInt beta {b};
	UArbBigInt a1{a};
	
	/ * The invariant maintained from here on is:
	   a = u*2*alpha - v*beta. * /

	while (!a1.isZero()) {
		a1.rcr(1); // A >>= 1;
		v.rcr(1); // v >>= 1;

		if (u.isOdd()) { //if ((u & 1) == 1) {
			u = ((u ^ beta) >> 1) + (u & beta);
			v.add(alpha); // v += alpha;
		} else {
			// Delete a common factor of 2 in u and v.
			u.rcr(1); // u >>= 1;
		}
		
		//assert( a == (TWO*alpha*u - beta*v) );
	}

	//R = u;
	//K = v;
	assert( ( TWO*(a)*u - b*v).isOne() );
}
*/

void UArbBigInt::modPow_montgomeryOdd(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result) {
//#if !defined(BIG_INT_NO_MONTGOMERY_WINDOW) && _BIG_INT_WORD_LENGTH_PRESET_ <= 32
//	modPow_montgomeryOdd_window(base, exponent, modulus, result);
//#else
	//modPow_montgomeryOdd_leastToMostSig(base, exponent, modulus, result);
	//modPow_montgomeryOdd_mostToLeastSig(base, exponent, modulus, result);
	modPow_montgomeryOdd_kAry(base, exponent, modulus, result);
//#endif
}

void UArbBigInt::modPow_montgomeryOdd_leastToMostSig(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result) {
	assert( modulus.isOdd() );
	assert( base < modulus );
	
	const MontgomeryReducer<UArbBigInt> mmReducer{modulus};
	
	UArbBigInt b = mmReducer.convertIn(base); // S
	const UArbBigInt e = exponent; // E
	UArbBigInt res = mmReducer.getConvertedOne(); // A
	for (size_t i = 0, len = e.bitLength(); i < len; i++) {
		if (e.testBit(i)) {
			res = mmReducer.multiply(res, b);
		}
		b = mmReducer.square(b);
	}
	result = mmReducer.convertOut(res);
}

void UArbBigInt::modPow_montgomeryOdd_mostToLeastSig(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result) {
	assert( modulus.isOdd() );
	assert( base < modulus );
	
	const MontgomeryReducer<UArbBigInt> mmReducer{modulus};
	
	const UArbBigInt b = mmReducer.convertIn(base);
	const UArbBigInt e = exponent;
	UArbBigInt res = mmReducer.getConvertedOne(); // A
	for (int i = e.bitLength() - 1; i >= 0; i--) {
		res = mmReducer.square(res);
		
		if (e.testBit(i)) {
			res = mmReducer.multiply(res, b);
		}
		
	}
	result = mmReducer.convertOut(res);
}

void UArbBigInt::modPow_montgomeryOdd_kAry(const UArbBigInt& base, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result) {
	assert( modulus.isOdd() );
	assert( base < modulus );
	
	constexpr int k = 6; // 512bit => k=4; 2048bit => k=6
	constexpr int tableSize = (1<<k) - 1; // 2^k - 1;
	assert( k <= BIG_INT_BITS_PER_WORD);
	UArbBigInt table[tableSize];
	
	const MontgomeryReducer<UArbBigInt> mmReducer{modulus};
	const UArbBigInt b = mmReducer.convertIn(base);
	
	// pre calculculate the multiplicators for 2^k bit patterns of the exponent.
	table[0] = b;
	for (int i = 1; i < tableSize; i++) {
		table[i] = mmReducer.multiply(table[i-1], b);
	}
	
	// iterate over the k*x most significant bit of the exponent (k bits per iteration)
	UArbBigInt e = exponent;
	UArbBigInt res = mmReducer.getConvertedOne(); // A
	for (int i = e.bitLength() - 1; i >= (k-1); i -= k) {
		// get the k most significant bit and store it in t
		UArbBigInt t1 = e >> (i-(k-1));
		BIG_INT_WORD_TYPE t = t1.getData()[0] & tableSize; // t <= 2^k-1 // e.getData()[0] = the least segnificant word of e
		
		for (int j = 0; j < k; j++) {
			res = mmReducer.square(res);
		}
		
		if ( t != 0) {
			res = mmReducer.multiply(res, table[t-1]);
		}
	}
	
	// iterate over the remaining least significant bit of the exponent which was not a multiple of k (one bit per iteration)
	int remainingBitsOfExp = e.bitLength() % k;
	if(remainingBitsOfExp > 0) {
		BIG_INT_WORD_TYPE remainingBitsOfExpMask = (1 << remainingBitsOfExp) - 1;
		e.boolAnd(UArbBigInt{remainingBitsOfExpMask});
		
		for (int i = remainingBitsOfExp - 1; i >= 0; i--) {
			res = mmReducer.square(res);
			
			if (e.testBit(i)) {
				res = mmReducer.multiply(res, b);
			}
		}
	}
	result = mmReducer.convertOut(res);
}

UArbBigInt UArbBigInt::modPow2(UArbBigInt exponent, uint p) const {
	/*
	 * Perform exponentiation using repeated squaring trick, chopping off
	 * high order bits as indicated by modulus.
	 */
	UArbBigInt result = UArbBigInt::ONE;
	UArbBigInt baseToPow2 = this->mod2(p);
	int expOffset = 0;

	int limit = exponent.bitLength();

	if (this->isOdd()) {
		limit = ((p-1) < limit) ? (p-1) : limit;
	}
	
	UArbBigInt squareResult;

	while (expOffset < limit) {
		if (exponent.testBit(expOffset)) {
			result = (result * baseToPow2).mod2(p);
		}
		expOffset++;
		if (expOffset < limit) {
			square(baseToPow2, squareResult);
			baseToPow2 = squareResult.mod2(p);
		}
	}

	return result;
}

UArbBigInt UArbBigInt::mod2(uint p) const {
	if (this->bitLength() <= p) {
		return *this;
	}

	// Copy remaining ints of mag
	BIG_INT_WORD_COUNT_TYPE numWords = BIG_INT_BIT_TO_SIZE(p); // (p + (BIG_INT_BITS_PER_WORD-1)) >> 5;
	BIG_INT_WORD_TYPE* mag = new BIG_INT_WORD_TYPE[numWords];
	std::copy_n(&(this->value[0]), numWords, &(mag[0])); //System.arraycopy(this.mag, (this.mag.length - numInts), mag, 0, numInts);

	// Mask out any excess bits
	BIG_INT_WORD_COUNT_TYPE mostSignificantWordIndex = numWords-1;
	int excessBits = (numWords << 5) - p;
	mag[mostSignificantWordIndex] &= (BIG_INT_WORD_TYPE{1} << (BIG_INT_BITS_PER_WORD-excessBits)) - 1;

	//return (mag[mostSignificantWordIndex] == 0 ? new BigInteger(1, mag) : new BigInteger(mag, 1));
	UArbBigInt result{mag, numWords, numWords};
	if(mag[mostSignificantWordIndex] == 0) {
		result.trimWordSize(numWords);
	}
	return result;
}

// ---
/*
void UArbBigInt::modPow_montgomeryOdd_window(const UArbBigInt& baseIn, const UArbBigInt& exponent, const UArbBigInt& modulus, UArbBigInt& result) {
	assert(BIG_INT_BITS_PER_WORD <= 32);
	/ *
	 * The algorithm is adapted from Javas BigInteger class.
	 *
	 * The algorithm is adapted from Colin Plumb's C library.
	 *
	 * The window algorithm:
	 * The idea is to keep a running product of b1 = n^(high-order bits of exp)
	 * and then keep appending exponent bits to it.  The following patterns
	 * apply to a 3-bit window (k = 3):
	 * To append   0: square
	 * To append   1: square, multiply by n^1
	 * To append  10: square, multiply by n^1, square
	 * To append  11: square, square, multiply by n^3
	 * To append 100: square, multiply by n^1, square, square
	 * To append 101: square, square, square, multiply by n^5
	 * To append 110: square, square, multiply by n^3, square
	 * To append 111: square, square, square, multiply by n^7
	 *
	 * Since each pattern involves only one multiply, the longer the pattern
	 * the better, except that a 0 (no multiplies) can be appended directly.
	 * We precompute a table of odd powers of n, up to 2^k, and can then
	 * multiply k bits of exponent at a time.  Actually, assuming random
	 * exponents, there is on average one zero bit between needs to
	 * multiply (1/2 of the time there's none, 1/4 of the time there's 1,
	 * 1/8 of the time, there's 2, 1/32 of the time, there's 3, etc.), so
	 * you have to do one multiply per k+1 bits of exponent.
	 *
	 * The loop walks down the exponent, squaring the result buffer as
	 * it goes.  There is a wbits+1 bit lookahead buffer, buf, that is
	 * filled with the upcoming exponent bits.  (What is read after the
	 * end of the exponent is unimportant, but it is filled with zero here.)
	 * When the most-significant bit of this buffer becomes set, i.e.
	 * (buf & tblmask) != 0, we have to decide what pattern to multiply
	 * by, and when to do it.  We decide, remember to do it in future
	 * after a suitable number of squarings have passed (e.g. a pattern
	 * of "100" in the buffer requires that we multiply by n^1 immediately;
	 * a pattern of "110" calls for multiplying by n^3 after one more
	 * squaring), clear the buffer, and continue.
	 *
	 * When we start, there is one more optimization: the result buffer
	 * is implcitly one, so squaring it or multiplying by it can be
	 * optimized away.  Further, if we start with a pattern like "100"
	 * in the lookahead window, rather than placing n into the buffer
	 * and then starting to square it, we have already computed n^2
	 * to compute the odd-powers table, so we can place that into
	 * the buffer and save a squaring.
	 *
	 * This means that if you have a k-bit window, to compute n^z,
	 * where z is the high k bits of the exponent, 1/2 of the time
	 * it requires no squarings.  1/4 of the time, it requires 1
	 * squaring, ... 1/2^(k-1) of the time, it reqires k-2 squarings.
	 * And the remaining 1/2^(k-1) of the time, the top k bits are a
	 * 1 followed by k-1 0 bits, so it again only requires k-2
	 * squarings, not k-1.  The average of these is 1.  Add that
	 * to the one squaring we have to do to compute the table,
	 * and you'll see that a k-bit window saves k-2 squarings
	 * as well as reducing the multiplies.  (It actually doesn't
	 * hurt in the case k = 1, either.)
	 * /
	// Special case for exponent of one
	//if (exponent.isOne()) {
	//	return base;
	//}

	// Special case for base of zero
	//if (signum == 0)
	//	return ZERO;

	UArbBigInt base{baseIn}; //int[] base =  mag.clone();
	const UArbBigInt *exp = &exponent;	//int[] exp = exponent.mag;
	UArbBigInt mod{modulus}; //int[] mod = modulus.mag;
	BIG_INT_WORD_COUNT_TYPE modLen = modulus.getWordSize(); //int modLen = mod.length;

	// Make modLen even. It is conventional to use a cryptographic
	// modulus that is 512, 768, 1024, or 2048 bits, so this code
	// will not normally be executed. However, it is necessary for
	// the correct functioning of the HotSpot intrinsics.
	if ((modLen & 1) != 0) {
		//int[] x = new int[modLen + 1];
		//System.arraycopy(mod, 0, x, 1, modLen);
		//mod = x;
		mod.reserveWordsAndInitUnused(modLen + 1, 0);
		modLen++;
	}

	// Select an appropriate window size
	uint wbits = 0;
	uint ebits = exponent.bitLength(); //bitLength(exp, exp.length);
	// if exponent is 65537 (0x10001), use minimum window size
	//if ((ebits != 17) || (exp[0] != 65537)) {
		while (ebits > bnExpModThreshTable[wbits]) {
			wbits++;
		}
	//}

	// Calculate appropriate table size
	uint tblmask = 1 << wbits;

	// Allocate table for precomputed odd powers of base in Montgomery form
	UArbBigInt* table = new UArbBigInt[tblmask];//int[][] table = new int[tblmask][];
	for (int i=0; i < tblmask; i++) {
		table[i].reserveWordsAndInitUnused(modLen, 0); //table[i] = new int[modLen];
	}
	
	// Compute the modular inverse of the least significant 64-bit
	// digit of the modulus
	uint64_t n0 = (uint64_t)mod.value[0] + ((uint64_t)mod.value[1] << BIG_INT_BITS_PER_WORD); //(mod[modLen-1] & LONG_MASK) + ((mod[modLen-2] & LONG_MASK) << 32);
	uint64_t inv = BigIntUtil::inverseMod64(n0); //long inv = -MutableBigInteger.inverseMod64(n0);

	// Convert base to Montgomery form
	// Move base up "mlen" words into a
	UArbBigInt a{0, 2*modLen}; a.initUnusedWords(); std::copy_n(&baseIn.value[0], baseIn.wordSize, &a.value[modLen]); a.trimWordSize(2*modLen); //UArbBigInt a{baseIn}; a.rcl(modLen * BIG_INT_BITS_PER_WORD, 0, true); //int[] a = leftShift(base, base.length, modLen << 5);

	UArbBigInt 	q{}, //MutableBigInteger q = new MutableBigInteger(),
				a2{a}, //a2 = new MutableBigInteger(a),
				b2{modulus}; //b2 = new MutableBigInteger(mod);
	//b2.normalize(); // MutableBigInteger.divide() assumes that its
					// divisor is in normal form.

	UArbBigInt r;
	a2.div(b2, q, r); //MutableBigInteger r= a2.divide(b2, q);
	table[0] = r; //table[0] = r.toIntArray();

	// Pad table[0] with leading zeros so its length is at least modLen
	//if (table[0].length < modLen) {
	//   int offset = modLen - table[0].length;
	//   int[] t2 = new int[modLen];
	//   System.arraycopy(table[0], 0, t2, offset, table[0].length);
	//   table[0] = t2;
	//}

	// Set b to the square of the base
	UArbBigInt b{0, modLen}; montgomerySquare(table[0], mod, modLen, inv, b); //int[] b = montgomerySquare(table[0], mod, modLen, inv, null);

	// Set t to high half of b // Use high half of b to initialize the table
	UArbBigInt t{0, modLen}; t.initUnusedWords(); std::copy_n(&b.value[modLen/2], modLen/2, &t.value[0]); t.trimWordSize(modLen/2); //int[] t = Arrays.copyOf(b, modLen);

	// Fill in the table with odd powers of the base
	for (size_t i=1; i < tblmask; i++) { //for (int i=1; i < tblmask; i++) {
		montgomeryMultiply(t, table[i-1], mod, modLen, inv, table[i]); //table[i] = montgomeryMultiply(t, table[i-1], mod, modLen, inv, null);
	}

	// Pre load the window that slides over the exponent
	uint bitpos = 1 << ((ebits-1) & (BIG_INT_BITS_PER_WORD-1)); //int bitpos = 1 << ((ebits-1) & (32-1));

	uint buf = 0; //int buf = 0;
	uint elen = exp->getWordSize(); //int elen = exp.length;
	uint eIndex = 0; //int eIndex = 0;
	for (uint i = 0; i <= wbits; i++) { //for (int i = 0; i <= wbits; i++) {
		buf = (buf << 1) | (((exp[eIndex] & bitpos) != 0)?1:0);
		bitpos >>= 1; //bitpos >>>= 1;
		if (bitpos == 0) {
			eIndex++;
			bitpos = 1 << (BIG_INT_BITS_PER_WORD-1); //bitpos = 1 << (32-1);
			elen--;
		}
	}

	int multpos = ebits;

	// The first iteration, which is hoisted out of the main loop
	ebits--;
	bool isone = true; //boolean isone = true;

	multpos = ebits - wbits;
	while ((buf & 1) == 0) {
		buf >>= 1; //buf >>>= 1;
		multpos++;
	}

	UArbBigInt mult{table[buf >> 1], modLen}; //int[] mult = table[buf >>> 1];  // TODO reference?

	buf = 0;
	if (multpos == ebits) { //if (multpos == ebits)
		isone = false;
	}

	// The main loop
	while (true) {
		ebits--;
		// Advance the window
		buf <<= 1;

		if (elen != 0) {
			buf |= ((exp[eIndex] & bitpos) != 0) ? 1 : 0;
			bitpos >>= 1; //bitpos >>>= 1;
			if (bitpos == 0) {
				eIndex++;
				bitpos = 1 << (BIG_INT_BITS_PER_WORD-1); //bitpos = 1 << (32-1);
				elen--;
			}
		}

		// Examine the window for pending multiplies
		if ((buf & tblmask) != 0) {
			multpos = ebits - wbits;
			while ((buf & 1) == 0) {
				buf >>= 1; //buf >>>= 1;
				multpos++;
			}
			mult = table[buf >> 1]; //mult = table[buf >>> 1]; // TODO reference?
			buf = 0;
		}

		// Perform multiply
		if (ebits == multpos) {
			if (isone) {
				b = mult; //b = mult.clone();
				isone = false;
			} else {
				t = b;
				montgomeryMultiply(t, mult, mod, modLen, inv, a); //a = montgomeryMultiply(t, mult, mod, modLen, inv, a);
				t = a; a = b; b = t;
			}
		}

		// Check if done
		if (ebits == 0) { //if (ebits == 0)
			break;
		}

		// Square the input
		if (!isone) {
			t = b;
			montgomerySquare(t, mod, modLen, inv, a); //a = montgomerySquare(t, mod, modLen, inv, a);
			t = a; a = b; b = t;
		}
	}

	// Convert result out of Montgomery form and return
	UArbBigInt t2{0, (2*modLen)}; //int[] t2 = new int[2*modLen];
	t2.initUnusedWords(); std::copy_n(&b.value[modLen-1], modLen, &t.value[0]); t2.trimWordSize(modLen); //System.arraycopy(b, 0, t2, modLen, modLen);

	montReduce(t2, mod, modLen, (int)inv); //b = montReduce(t2, mod, modLen, (int)inv);

	//t2 = Arrays.copyOf(b, modLen);

	result = t2; //result = new BigInteger(1, t2);
	
	// cleanup
	//delete[] base;
	//delete[] mod;
	delete[] table;
}

void UArbBigInt::montReduce(UArbBigInt& n, const UArbBigInt& mod, BIG_INT_WORD_COUNT_TYPE mlen, BIG_INT_WORD_COUNT_TYPE inv) {
	//Adapted from Colin Plumb's C library.
	int c=0;
	int len = mlen;
	int offset=0;

	do {
		BIG_INT_WORD_TYPE nEnd = n.value[offset]; //int nEnd = n[n.length-1-offset];
		MagnitudeView nMag{n.value, n.wordCapacity};
		BIG_INT_WORD_TYPE carry = mulAdd(nMag, MagnitudeView(mod.value, mod.wordCapacity), offset, mlen, inv * nEnd); // int carry = mulAdd(n, mod, offset, mlen, inv * nEnd);
		c = BigIntUtil::addInt(carry, offset, n.value, mlen); //c += addOne(n, offset, mlen, carry);
		offset++;
	} while (--len > 0);

	while (c > 0) {
		c = n.sub(mod); //c += subN(n, mod, mlen);
	}
	
	while (n >= mod) { //while (intArrayCmpToLen(n, mod, mlen) >= 0) {
		n.sub(mod); //subN(n, mod, mlen);
	}
	
	//return n;
}

void UArbBigInt::montgomeryMultiply(const UArbBigInt& a, const UArbBigInt& b, const UArbBigInt& n, BIG_INT_WORD_COUNT_TYPE len, uint64_t inv, UArbBigInt& product) {
	product.reserveWords(a.wordCapacity * 2); // TODO: wordCapacity
	implMontgomeryMultiplyChecks(a, b, n, len, product);
	
	a.mul(b, product); //product = multiplyToLen(a, len, b, len, product);
	montReduce(product, n, len, (BIG_INT_WORD_COUNT_TYPE)inv); //return montReduce(product, n, len, (int)inv);
}

void UArbBigInt::montgomerySquare(const UArbBigInt& a, const UArbBigInt& n, BIG_INT_WORD_COUNT_TYPE len, uint64_t inv, UArbBigInt& product) {
	product.reserveWords(a.wordCapacity * 2); // TODO: wordCapacity
	implMontgomeryMultiplyChecks(a, a, n, len, product);
	
	a.mul(a, product); //product = squareToLen(a, len, product);
	montReduce(product, n, len, (BIG_INT_WORD_COUNT_TYPE)inv); //return montReduce(product, n, len, (int)inv);
}

void UArbBigInt::implMontgomeryMultiplyChecks(const UArbBigInt& a, const UArbBigInt& b, const UArbBigInt& n, BIG_INT_WORD_COUNT_TYPE len, UArbBigInt& product) {
	if (len % 2 != 0) {
		throw std::invalid_argument("input array length must be even: " + std::to_string(len));
	}

	if (len < 1) {
		throw std::invalid_argument("invalid input length: " + std::to_string(len));
	}

	if (len > a.wordCapacity ||
		len > b.wordCapacity ||
		len > n.wordCapacity ||
		(/ * product != null && * / len > product.wordCapacity)) {
		throw std::invalid_argument("input array length out of bound: " + std::to_string(len));
	}
}

BIG_INT_WORD_TYPE UArbBigInt::mulAdd(MagnitudeView& out, const MagnitudeView& in, BIG_INT_WORD_COUNT_TYPE offset, BIG_INT_WORD_COUNT_TYPE len, BIG_INT_WORD_TYPE k) {
	implMulAddCheck(out, in, offset, len, k);
	throw std::invalid_argument("UArbBigInt::mulAdd not implemented");
	return -1;//BigIntUtil::MulAdd(out.value(), -1, in, offset, len, k);
}

void UArbBigInt::implMulAddCheck(const MagnitudeView& out, const MagnitudeView& in, BIG_INT_WORD_COUNT_TYPE offset, BIG_INT_WORD_COUNT_TYPE len, BIG_INT_WORD_TYPE k) {
	if (len > in.wordCapacity()) {
		throw std::invalid_argument("input length is out of bound: " + std::to_string(len) + " > " + std::to_string(in.wordCapacity()));
	}
	if (offset < 0) {
		throw std::invalid_argument("input offset is invalid: " + std::to_string(offset));
	}
	if (offset > (out.wordCapacity() - 1)) {
		throw std::invalid_argument("input offset is out of bound: " + std::to_string(offset) + " > " + std::to_string(out.wordCapacity() - 1));
	}
	if (len > (out.wordCapacity() - offset)) {
		throw std::invalid_argument("input len is out of bound: " + std::to_string(len) + " > " + std::to_string(out.wordCapacity() - offset));
	}
}
*/
// ---

void UArbBigInt::modPow(UArbBigInt &exponent, const UArbBigInt &modulus, UArbBigInt& result) const {
	if (modulus.isZero()) {
		//throw new ArithmeticException("BigInteger: modulus not positive");
		std::string msg = "ERROR UArbBigInt: modulus not positive!";
		std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	// Trivial cases: exponent = 0
	if (exponent.isZero()) {
		if(modulus.isOne()) {
			result.setZero();
		} else {
			result.setOne();
		}
		return;
	}
	
	// ensure that the base is < modulus
	//SArbBigInt base = (this->signum < 0 || *this >= modulus) ? (*this % modulus) : *this;
	UArbBigInt base = (*this >= modulus) ? (*this % modulus) : *this;

	// Trivial cases: base = 1
	if (base.isOne()) {
		if(modulus.isOne()) {
			result.setZero();
		} else {
			result.setOne();
		}
		return;
	}

	// Trivial cases: base = 0
	if (base.isZero() && !exponent.isZero()) {
		result.setZero();
		return;
	}
	
	// Trivial cases: modulus = 1
	if(modulus.isOne()) {
		result.setOne();
		return;
	}

#ifdef BIG_INT_NO_MONTGOMERY_REDUCTION
	modPow_naiv(base, exponent, modulus, result);
#else
	modPow_montgomery(base, exponent, modulus, result);
#endif
}

UArbBigInt UArbBigInt::modPow(const UArbBigInt &exponent, const UArbBigInt &modulus) const {
	UArbBigInt result{1, modulus.getWordSize()};
	UArbBigInt tmpExponent{exponent};
	this->modPow(tmpExponent, modulus, result);
	return result;
}


// ----- comparisons -----
bool UArbBigInt::operator< (const UArbBigInt& other) const {
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

bool UArbBigInt::operator<= (const UArbBigInt& other) const {
	if (*this < other) {
		return true;
	}

	if (*this == other) {
		return true;
	}

	return false;
}

bool UArbBigInt::operator> (const UArbBigInt& other) const {
	return (!(*this <= other));
}

bool UArbBigInt::operator>= (const UArbBigInt& other) const {
	return (!(*this < other));
}

bool UArbBigInt::operator== (const UArbBigInt& other) const {
	if (*this < other) {
		return false;
	}

	if (other < *this) {
		return false;
	}

	return true;
}

bool UArbBigInt::operator!= (const UArbBigInt& other) const {
	return (!(*this == other));
}



// ----- asignment operator -----

UArbBigInt& UArbBigInt::operator= (const UArbBigInt& other) {
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

UArbBigInt& UArbBigInt::operator= (UArbBigInt&& other) {
	// If we're not trying to move the object into itself...
	if (this != &other) {
		// Delete this original data original data.
		if(this->value != nullptr) {
			delete [] this->value;
		}
		// Copy the other string's data into this string.
		this->value = other.value;
		this->wordCapacity = other.wordCapacity;
		this->wordSize = other.wordSize;
	
		// Finally, reset the other string's data pointer.
		other.value = nullptr;
		other.wordCapacity = 0;
		other.wordSize = 0;
	}
	return *this;
}
