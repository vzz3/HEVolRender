
#include "BigInt.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>		/* ciel */
#include <math.h>       /* log2 */
//#include <Security/Security.h>



using namespace ppvr::math;

// ----- statics -----

const BigInt BigInt::ZERO(0);
const BigInt BigInt::ONE(1);
const BigInt BigInt::TWO(2);
const BigInt BigInt::TEN(10);

BigInt BigInt::fromUint64(const uint64_t& uint64Val) {
	BigInt res(0);
	BigInt::fromUint64(uint64Val, res);
	return res;
}

BigInt& BigInt::fromUint64(const uint64_t& uint64Val, BigInt &target ) {
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
	target.reserveWords(requiredWords);
	
	// copy bits from uint64 into words
	for(BIG_INT_WORD_COUNT_TYPE i = 0; i < requiredWords; i++) {
		target.value[i] = (BIG_INT_WORD_TYPE)(uint64Val >> (i * BIG_INT_BITS_PER_WORD));
	}
	
	//BigInt res(value, requiredWords, requiredWords);
	target.wordSize = requiredWords;
	return target;
}

BigInt BigInt::fromString(const std::string& str, const BIG_INT_WORD_TYPE base) {
	BigInt res(0);
	BigInt::fromString(str, base, res);
	return res;
}

BigInt& BigInt::fromString(const std::string& str, const BIG_INT_WORD_TYPE base, BigInt &target ) {
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
	//BigInt val(0, wordSize);
	target.reserveWords(wordSize);
	
	//BigInt val(0);
	BigInt pow(1, wordSize);
	BigInt powTmp(0, wordSize);
	//BigInt bigBase(base);
	//BigInt t(0, 1);
	BIG_INT_WORD_TYPE t;
	BigInt tPow(0, wordSize);
	for(size_t i = str.length(); i>0; i--) {
		char c = str[i-1];
		if(c >= '0' &&  c <= '9') {
			t = c - '0';
		} else if( base > 10 && c >= 'A' &&  c <= 'F') {
			t = 10 + c - 'A';
		} else if( base > 10 && c >= 'a' &&  c <= 'f') {
			t = 10 + c - 'a';
		} else {
			continue;
		}
		
		powTmp = pow;
		
		pow.mulInt(t, tPow);
		target.add(tPow);
		
		powTmp = pow;
		powTmp.mulInt(base, pow);
	}
	
	return target;
}

// ----- statics rendome -----

BigInt BigInt::randomNumber(const uint& sizeInBit, Random& rnd) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BigInt::requiredWords(sizeInBit);
	BigInt res(0, requiredWords);
	BigInt::randomNumber(sizeInBit, rnd, res);
	return res;
}

BigInt BigInt::randomNumber(const BigInt& upperBound, Random& rnd) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BigInt::requiredWords(upperBound.bitLength());
	BigInt res(0, requiredWords);
	BigInt::randomNumber(upperBound, rnd, res);
	return res;
}

BigInt& BigInt::randomNumber(const uint& sizeInBit, Random& rnd, BigInt &target) {
	if(sizeInBit < 1) {
		std::string msg = "ERROR randomNumber: the sizeInBit parameter must be greater then 0 ";
		//std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	
	// reserve required words
	BIG_INT_WORD_COUNT_TYPE requiredWords = BigInt::requiredWords(sizeInBit);
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

BigInt& BigInt::randomNumber(const BigInt& upperBound, Random& rnd, BigInt &target) {
	if(upperBound.isZero()) {
		std::string msg = "ERROR upperBound: must be strictly greater than one";
		//std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	
	uint bits = upperBound.bitLength();
	do {
		BigInt::randomNumber(bits, rnd, target);
		// make sure r <= upperBound (modulus)
	} while (target >= upperBound);
	return target;
}





BIG_INT_WORD_COUNT_TYPE BigInt::requiredWords(const uint& sizeInBit) {
	return (sizeInBit + (BIG_INT_BITS_PER_WORD - 1)) / BIG_INT_BITS_PER_WORD;
}

// ----- constructors -----

BigInt::BigInt(): BigInt(0, 0) {}

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
	if(this->value != NULL) {
		delete [] this->value;
	}
}

// ----- value export - toString / toUint64 -----

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
		decDigit = tmp.divInt( 10 );
		ret = digits[decDigit] + ret;
	}
	
	return ret;
}

// ----- memory managment -----

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

void BigInt::reserveWords( const BIG_INT_WORD_COUNT_TYPE newCapacity ) {
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

void BigInt::reserveWordsAndInitUnused( const BIG_INT_WORD_COUNT_TYPE newCapacity, const BIG_INT_WORD_TYPE initValue ) {
	this->reserveWords(newCapacity);
	
	// inizialize all words with an index >= this->wordSize (all alocated but not used words. this can be more then the (newCapacity - this->wordSize) because this->this->wordCapacity can be > then newCapacity)
	this->initUnusedWords();
}

void BigInt::initUnusedWords(const BIG_INT_WORD_TYPE initValue) {
	std::fill_n(&this->value[this->wordSize], this->wordCapacity - this->wordSize, initValue);
}

// ----- bit utilities -----

int BigInt::bitLength() const {
	return findHighestSetBit()+1;
}

void BigInt::setZero() {
	this->value[0] = 0;
	this->wordSize = 1;
}

void BigInt::setOne() {
	this->value[0] = 1;
	this->wordSize = 1;
}

bool BigInt::isZero() const {
	return (this->wordSize == 1 && this->value[0] == 0);
}

void BigInt::setBit(const uint n) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BigInt::requiredWords(n);
	this->reserveWordsAndInitUnused(requiredWords);
	
	uint restBits   = n % BIG_INT_BITS_PER_WORD;
	uint allWords 	= n / BIG_INT_BITS_PER_WORD;
	
	this->value[allWords] |= (1 << restBits);
	
	this->wordSize = std::max(this->wordSize, allWords + 1);
}

void BigInt::clearBit(int n) {
	uint oldBitLength = this->bitLength();
	if(n <= oldBitLength) {
		uint restBits   = n % BIG_INT_BITS_PER_WORD;
		uint allWords 	= n / BIG_INT_BITS_PER_WORD;
		
		this->value[allWords] &= ~(1 << restBits);
		
		// if the higest bit was cleard, the word count could have changed
		if(n == oldBitLength) {
			this->trimWordSize(this->wordSize);
		}
	}
}

BigInt BigInt::withBit(const uint n) {
	BigInt res(*this);
	res.setBit(n);
	return res;
}

BigInt BigInt::withoutBit(int n) {
	BigInt res(*this);
	res.clearBit(n);
	return res;
}

bool BigInt::isOne() const {
	return (this->wordSize == 1 && this->value[0] == 1);
}

bool BigInt::isEven() const {
	return !(this->testBit(0));
}

bool BigInt::isOdd() const {
	return this->testBit(0);
}

bool BigInt::testBit(uint n) const {
	uint restBits   = n % BIG_INT_BITS_PER_WORD;
	uint allWords 	= n / BIG_INT_BITS_PER_WORD;
	
	return ((this->value[allWords] >> restBits) & 1);
}

int BigInt::findHighestSetBitInWord(BIG_INT_WORD_TYPE word) const {
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

int BigInt::findLowestSetBitInWord(BIG_INT_WORD_TYPE word) const {
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

int BigInt::findHighestSetBit() const {
	if(this->isZero()) {
		return -1;
	}
	
	int wordIndex = this->wordSize-1;
	
	BIG_INT_WORD_TYPE word = this->value[wordIndex];
	int bit = this->findHighestSetBitInWord(word);
	
	return wordIndex * BIG_INT_BITS_PER_WORD + bit;
}

int BigInt::findLowestSetBit() const {
	if(this->isZero()) {
		return -1;
	}
	
	int wordIndex=0;
	for(wordIndex=0; wordIndex < this->wordSize && this->value[wordIndex] == 0; wordIndex++);
	
	BIG_INT_WORD_TYPE word = this->value[wordIndex];
	int bit = this->findLowestSetBitInWord(word);
	
	return wordIndex * BIG_INT_BITS_PER_WORD + bit;
}

// ----- word utilities -----

inline void BigInt::trimWordSize(BIG_INT_WORD_COUNT_TYPE newMaxWordSize) {
	assert(newMaxWordSize <= this->wordCapacity);
	BIG_INT_WORD_COUNT_TYPE newWordSize;// = std::min(newMaxWordSize, this->wordCapacity); disable this min check for performance resons
	for (newWordSize = newMaxWordSize; newWordSize>1 && this->value[newWordSize-1] == 0; newWordSize--);
	this->wordSize = newWordSize;
}

inline BIG_INT_WORD_TYPE BigInt::setLowFromLowBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res =
		// set low bits to 0 and keep the high bits
		this->getHighAsHighBits(target)
		|
		// set high bits to 0 and keep the low bits
		this->getLowAsLowBits(src)
	;
	
	return res;
}

inline BIG_INT_WORD_TYPE BigInt::setLowFromHighBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) const {
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

inline BIG_INT_WORD_TYPE BigInt::setHighFromHighBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res =
		// set high bits to 0 and keep the low bits
		this->getLowAsLowBits(target)
		|
		// set low bits to 0 and keep the high bits
		this->getHighAsHighBits(src)
	;
	
	return res;
}

inline BIG_INT_WORD_TYPE BigInt::setHighFromLowBits(const BIG_INT_WORD_TYPE target, const BIG_INT_WORD_TYPE src) const {
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

inline BIG_INT_WORD_TYPE BigInt::getHighAsHighBits(const BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res = (src & BIG_INT_WORD_HIGH_BIT_MASK);
	return res;
}

inline BIG_INT_WORD_TYPE BigInt::getHighAsLowBits(const BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res = (src >> (BIG_INT_BITS_PER_WORD/2));
	return res;
}

inline BIG_INT_WORD_TYPE BigInt::getLowAsLowBits(const BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res = (src & BIG_INT_WORD_LOW_BIT_MASK);
	return res;
}

inline BIG_INT_WORD_TYPE BigInt::getLowAsHighBits(const BIG_INT_WORD_TYPE src) const {
	BIG_INT_WORD_TYPE res = (src << (BIG_INT_BITS_PER_WORD/2));
	return res;
}

// ----- shift left -----

void BigInt::rcl_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, const uint bits, BIG_INT_WORD_TYPE c) {
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

BIG_INT_WORD_TYPE BigInt::rcl_moveBits(const uint bits, BIG_INT_WORD_TYPE c) {
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

BIG_INT_WORD_TYPE BigInt::rcl(const uint bits, const BIG_INT_WORD_TYPE c, const bool resize) {
	BIG_INT_WORD_TYPE lastC    = 0;
	uint restBits = bits;
	if(resize) {
		// calculate required word size
		BIG_INT_WORD_TYPE curLasWordIndex = this->wordSize - 1;
		uint newTotalBits = (curLasWordIndex) * BIG_INT_BITS_PER_WORD // currently total bits used
			+ this->findHighestSetBitInWord(this->value[curLasWordIndex]) + 1 // bits used in the current word (if findLeadingSetBitInWord() returns -1 the "this->wordSize" is already wrong!)
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

BigInt BigInt::operator<< (const uint bits) const {
	BigInt res(*this);
	res.rcl(bits, 0, true);
	return res;
}

// ----- shift right -----

void BigInt::rcr_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, const uint bits, BIG_INT_WORD_TYPE c) {
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

BIG_INT_WORD_TYPE BigInt::rcr_moveBits(const uint bits, BIG_INT_WORD_TYPE c) {
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

BIG_INT_WORD_TYPE BigInt::rcr(const uint bits, const BIG_INT_WORD_TYPE c) {
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

BigInt BigInt::operator>> (const uint bits) const {
	BigInt res(*this);
	res.rcr(bits);
	return res;
}

// ----- addition -----

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

BIG_INT_WORD_TYPE BigInt::addTwoInts(const BIG_INT_WORD_TYPE wordHigh, const BIG_INT_WORD_TYPE wordLow, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const {
	assert( index < (targetWordCount - 1) ); // TODO
	
	BIG_INT_WORD_TYPE c;
	
	c = addTwoWords(targetArray[index],   wordLow, 0, &targetArray[index]);
	c = addTwoWords(targetArray[index+1], wordHigh, c, &targetArray[index+1]);
	
	for(BIG_INT_WORD_COUNT_TYPE i=index+2 ; i < targetWordCount && c ; ++i) { // TODO
		c = addTwoWords(targetArray[i], 0, c, &targetArray[i]);
	}
	return c;
}

/*
void BigInt::addTwoInts(const BIG_INT_WORD_TYPE wordHigh, const BIG_INT_WORD_TYPE wordLow, const BIG_INT_WORD_COUNT_TYPE index) {
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

BIG_INT_WORD_TYPE BigInt::addInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const {
	assert( index < targetWordCount );
	
	BIG_INT_WORD_TYPE c;
	c = addTwoWords(targetArray[index], word, 0, &targetArray[index]);
	
	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c ; ++i) {
		c = addTwoWords(targetArray[i], 0, c, &targetArray[i]);
	}
	
	return c;
}

void BigInt::addInt(const BIG_INT_WORD_TYPE word) {
	
	BIG_INT_WORD_TYPE c = this->addInt(word, 0, this->value, this->wordSize);
	
	// increate the word count in order to add the last carry
	if(c != 0) {
		this->reserveWords(this->wordSize + 1);
		this->value[this->wordSize] = c;
		this->wordSize = this->wordSize + 1;
	}
}

void BigInt::add(const BigInt &other, BigInt &result) const {
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
		
		carry = addTwoWords(a, b, carry, &result.value[i]);
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

void BigInt::add(const BigInt &other) {
	this->add(other, *this);
}

BigInt BigInt::operator+ (const BigInt& other) const {
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->wordSize, other.wordSize);
	BigInt result(0, maxWordCount+1);
	this->add(other, result);
	return result;
}

// ----- substraction -----

BIG_INT_WORD_TYPE BigInt::subTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE carry, BIG_INT_WORD_TYPE* result) const {
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

BIG_INT_WORD_TYPE BigInt::subInt(const BIG_INT_WORD_TYPE word, const BIG_INT_WORD_COUNT_TYPE index, BIG_INT_WORD_TYPE* targetArray, BIG_INT_WORD_COUNT_TYPE targetWordCount) const {
	assert( index < targetWordCount );
	
	BIG_INT_WORD_TYPE c;
	c = subTwoWords(targetArray[index], word, 0, &targetArray[index]);
	
	for(BIG_INT_WORD_COUNT_TYPE i=index+1 ; i<targetWordCount && c ; ++i) {
		c = subTwoWords(targetArray[i], 0, c, &targetArray[i]);
	}
	
	return c;
}

BIG_INT_WORD_TYPE BigInt::subInt(const BIG_INT_WORD_TYPE word) {
	BIG_INT_WORD_TYPE c = this->subInt(word, 0, this->value, this->wordSize);
	
	// reduce word size if a word was truncated
	if(this->value[this->wordSize-1] == 0) {
		this->wordSize = this->wordSize-1;
	}
	
	return c;
}

BIG_INT_WORD_TYPE BigInt::sub(const BigInt& other, BIG_INT_WORD_TYPE carry, BigInt &result) const {
	BIG_INT_WORD_TYPE a,b,c;
	BIG_INT_WORD_COUNT_TYPE usedWordIndex = 0;
	result.reserveWords(this->wordSize);
	
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<this->wordSize; i++) {
		b = other.wordSize > i ? other.value[i] : 0;
		
		carry = subTwoWords(this->value[i], b, carry, &result.value[i]);
		if(result.value[i] > 0) {
			usedWordIndex = i;
		}
	}
	
	result.wordSize = usedWordIndex+1;
	return carry;
}

BIG_INT_WORD_TYPE BigInt::sub(const BigInt& other) {
	return this->sub(other, 0, *this);
}

BigInt BigInt::operator- (const BigInt& other) const {
	if(other > *this) {
		std::string msg = "ERROR substract BigInt a - b with a < b (a=" + this->toStringDec() + ", b=" + other.toStringDec() + ")!";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	BigInt result(0,this->wordSize);
	this->sub(other, 0, result);
	return result;
}

// ----- multiplication -----

void BigInt::mulTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE* resultHigh, BIG_INT_WORD_TYPE* resultLow) const {
	/*
		expect BIG_INT_WORD_TYPE to be a 64 bits variable:
		we don't have a native type which has 128 bits
		then we're splitting 'a' and 'b' to 4 parts (high and low halves)
		and using 4 multiplications (with additions and carry correctness)
	 */
	
	BIG_INT_WORD_TYPE aLow = this->getLowAsLowBits(a); 		// aLow = a.low;
	BIG_INT_WORD_TYPE bLow = this->getLowAsLowBits(b); 		// aLow = b.low;
	BIG_INT_WORD_TYPE aHigh = this->getHighAsLowBits(a); 	// aHigh = a.high;
	BIG_INT_WORD_TYPE bHigh = this->getHighAsLowBits(b); 	// bHigh = b.high;
	
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
	temp 	  = this->getHighAsLowBits(res_low1) + bLow * aHigh;	// temp = res_low1.high + b.low * a.high
	res_low1  = this->setHighFromLowBits(res_low1, temp); 			// res_low1.high = temp.low
	res_high1 = this->setLowFromHighBits(res_high1, temp); 			// res_high1.low = temp.high
	res_high1 = this->getLowAsLowBits(res_high1); 					// res_high1.high = 0
	
	res_low2  = this->getHighAsHighBits(res_low2); 					// res_low2.low = 0
	temp	  = bHigh * aLow; 										// b.high * a.low
	res_low2  = this->setHighFromLowBits(res_low2, temp); 			// res_low2.high = temp.low
	
	res_high2 = bHigh * aHigh + this->getHighAsLowBits(temp); 		// res_high2 = b.high * a.high + temp.high
	
	BIG_INT_WORD_TYPE c = this->addTwoWords( res_low1,  res_low2, 0,  resultLow); // c = this->addTwoWords(res_low1, res_low2, 0, &res_low2)
						  this->addTwoWords(res_high1, res_high2, c, resultHigh); // there is no carry from here
}

void BigInt::mulInt(BIG_INT_WORD_TYPE ss2, BigInt& result) const {
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
		this->mulTwoWords(this->value[x1], ss2, &r2, &r1 );
		this->addTwoInts(r2, r1, x1, result.value, result.wordCapacity); // this->wordCapacity is > u.wordSize => there can not be a carry bit!
	}
	
	// check if the most significant word is > 0 and increase the wordSize if it is.
	// TODO remove this if addTwoInts() can take care of the this->wordSize
	if(result.value[this->wordSize] == 0) {
		result.wordSize = this->wordSize;
	} else {
		result.wordSize = this->wordSize + 1;
	}
}

void BigInt::mulSchool(const BigInt& a, const BigInt& b, BigInt& result) const {
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
	}
	
	BIG_INT_WORD_TYPE r2, r1;
	
	BIG_INT_WORD_COUNT_TYPE maxWordCount = aSize + bSize;
	result.reserveWords(maxWordCount);
	std::fill_n(result.value, maxWordCount, 0);
	
	for(uint aI=aStart ; aI<aSize ; ++aI)
	{
		for(uint bI=bStart ; bI<bSize ; ++bI)
		{
			mulTwoWords(a.value[aI], b.value[bI], &r2, &r1);
			addTwoInts(r2, r1, bI+aI, result.value, maxWordCount);
			// here will never be a carry
		}
	}
	
	// optimize word count
	BIG_INT_WORD_COUNT_TYPE usedWordIndex;
	for(usedWordIndex = maxWordCount; usedWordIndex>0 && result.value[usedWordIndex-1] == 0; --usedWordIndex);
	
	result.wordSize = usedWordIndex;
}

void BigInt::mul(const BigInt& b, BigInt& result) const {
	this->mulSchool(*this, b, result);
}

void BigInt::mul(const BigInt& b) {
	BigInt result = BigInt(0, this->wordSize + b.wordSize);
	this->mul(b, result);
	*this = result;
}

BigInt BigInt::operator* (const BigInt& other) const {
	BigInt result = BigInt(0, this->wordSize + other.wordSize);
	this->mul(other, result);
	return result;
}

// ----- division -----

// -- divTwoWords

void BigInt::divTwoWords(const BIG_INT_WORD_TYPE a, const BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE divisor, BIG_INT_WORD_TYPE* result, BIG_INT_WORD_TYPE* remainder) const {
	// c = divisor
	// (a < c ) for the result to be one word
	assert( divisor != 0 && a < divisor );
	
	if( a == 0 ) {
		*result    = b / divisor;
		if(remainder != NULL) {
			*remainder = b % divisor;
		}
	} else {
		if( this->getHighAsLowBits(divisor) == 0 ) {
			// higher half of 'divisor' is zero
			// then higher half of 'a' is zero too (look at the asserts at the beginning - 'a' is smaller than 'divisor')
			BIG_INT_WORD_TYPE res, temp1, temp2;
			
			temp1 = this->getLowAsHighBits(a); // this->setHighFromLowBits(temp1, a); 	// temp1.high 	= a.low
			temp1 = this->setLowFromHighBits(temp1, b); 								// temp1.low 	= b.high
			res = this->setHighFromLowBits(res, (temp1 / divisor)); 					// res_.high 	= (temp1.u / c).low
			temp2 = this->setHighFromLowBits(temp2, (temp1 % divisor)); 				// temp2.high 	= (temp1.u % c).low
			temp2 = this->setLowFromLowBits(temp2, b); 									// temp2.low 	= b.low
			res = this->setLowFromLowBits(res, (temp2 / divisor)); 						// res_.low 	= (temp2.u / c).low
			*result = res;
			
			if(remainder != NULL) {
				*remainder = temp2 % divisor;
			}
		} else {
			this->divTwoWordsKnuth(a, b, divisor,  result,  remainder);
		}
	}
}

// -- divTwoWordsKnuth

void BigInt::divTwoWordsKnuth(BIG_INT_WORD_TYPE a, BIG_INT_WORD_TYPE b, BIG_INT_WORD_TYPE c, BIG_INT_WORD_TYPE* result, BIG_INT_WORD_TYPE* remainder ) const {
	// a is not zero
	// c.high is not zero
	
	BIG_INT_WORD_TYPE u, q, u3;
	BIG_INT_WORD_TYPE temp_qLow, temp_qHigh;
	
	// normalizing
	BIG_INT_WORD_TYPE d = this->divTwoWordsKnuth_normalize(a, b, c);
	
	u = a;
	
	u3 = this->getHighAsLowBits(b); // u3 = b.high
	q = this->setHighFromLowBits(q, this->divTwoWordsKnuth_calculate(u, u3, c)); // q.high = this->divTwoWordsCalculate(u, u3, c)
	
	temp_qHigh = this->getHighAsLowBits(q);
	this->divTwoWordsKnuth_multiplySubtract(u, u3, temp_qHigh, c); // this->divTwoWordsMultiplySubtract(u, u3, q.high, c)
	q = this->setHighFromLowBits(q, temp_qHigh);
	
	u = this->setHighFromLowBits(u, u); // u.high = u.low
	u = this->setLowFromLowBits(u, u3); // u.low = u3
	u3 = this->getLowAsLowBits(b); // u3 = b.low
	q = this->setLowFromLowBits(q, this->divTwoWordsKnuth_calculate(u, u3, c)); // q.low = this->divTwoWordsCalculate(u, u3, c)
	
	temp_qLow = this->getLowAsLowBits(q);
	this->divTwoWordsKnuth_multiplySubtract(u, u3, temp_qLow, c); // this->divTwoWordsMultiplySubtract(u_, u3, q_.u_.low, c_);
	q = this->setLowFromLowBits(q, temp_qLow);
	
	*result = q;
	
	if(remainder != NULL) {
		// unnormalizing for the remainder
		u = this->getLowAsHighBits(u); // this->setHighFromLowBits(u, u); // u.high = u.low
		u = this->setLowFromLowBits(u, u3); // u.low = u3;
		*remainder = this->divTwoWordsKnuth_unnormalize(u, d);
	}
}

BIG_INT_WORD_TYPE BigInt::divTwoWordsKnuth_normalize(BIG_INT_WORD_TYPE &a, BIG_INT_WORD_TYPE &b, BIG_INT_WORD_TYPE &c) const {
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

BIG_INT_WORD_TYPE BigInt::divTwoWordsKnuth_unnormalize(BIG_INT_WORD_TYPE u, BIG_INT_WORD_TYPE d) const {
	if( d == 0 ) {
		return u;
	}
	
	u = u >> d;
	
	return u;
}

unsigned int BigInt::divTwoWordsKnuth_calculate(BIG_INT_WORD_TYPE u, BIG_INT_WORD_TYPE u3, BIG_INT_WORD_TYPE v) const {
	bool nextTest;
	BIG_INT_WORD_TYPE qp, rp, temp;
	
	qp = u / this->getHighAsLowBits(v); // qp = u / v.high
	rp = u % this->getHighAsLowBits(v); // rp = u % v.high
	
	assert( this->getHighAsLowBits(qp) == 0 || this->getHighAsLowBits(qp) == 1); // assert( qp.hight == 0 || qp.high == 1);
	
	do {
		bool decrease = false;
		if( this->getHighAsLowBits(qp) == 1 ) { // if( qp.high == 1)
			decrease = true;
		} else {
			temp = this->setHighFromLowBits(temp, rp); // temp.hight = rp.low
			temp = this->setLowFromLowBits(temp, u3); // temp.low = u3.low
			
			if( qp * this->getLowAsLowBits(v) > temp) { // if( qp * v.low > temp )
				decrease = true;
			}
		}
		
		nextTest = false;
		
		if( decrease ) {
			--qp;
			rp += this->getHighAsLowBits(v); // rp += v.high
			
			if( this->getHighAsLowBits(rp) == 0) { // if( rp.high == 0 )
				nextTest = true;
			}
		}
	}
	while( nextTest );
	
	return this->getLowAsLowBits(qp); // return qp.low
}

void BigInt::divTwoWordsKnuth_multiplySubtract(BIG_INT_WORD_TYPE &u, BIG_INT_WORD_TYPE & u3, BIG_INT_WORD_TYPE & q, BIG_INT_WORD_TYPE v) const {
	BIG_INT_WORD_TYPE temp, res_high, res_low;
	this->mulTwoWords(v, q,  &res_high, &res_low);
	
	BIG_INT_WORD_TYPE sub_res_high, sub_res_low;
	
	temp = this->setHighFromLowBits(temp, u); // temp.high = u.low
	temp = this->setLowFromLowBits(temp, u3); // temp.low = u3.low
	
	BIG_INT_WORD_TYPE c = this->subTwoWords(temp, res_low, 0, &sub_res_low);
	
	temp = this->setHighFromLowBits(temp, 0); // temp.high = 0
	temp = this->setLowFromHighBits(temp, u); // temp.low = u.high
	c = this->subTwoWords(temp, res_high, c, &sub_res_high);
	
	if( c ) {
		--q;
		
		c = this->addTwoWords(sub_res_low, v, 0, &sub_res_low);
		this->addTwoWords(sub_res_high, 0, c, &sub_res_high);
	}
	
	u = this->setHighFromLowBits(u, sub_res_high); // u.high = sub_res_high.low
	u = this->setLowFromHighBits(u, sub_res_low); // u.low = sub_res_low.high
	u3 = this->getLowAsLowBits(sub_res_low); // u3 = sub_res_low.low;
}

// -- divInt

BIG_INT_WORD_TYPE BigInt::divInt(BIG_INT_WORD_TYPE divisor, BigInt& result) const {
	if(divisor == 0) {
		std::string msg = "BigInt devision by (uint)0.";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
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
		this->divTwoWords(r, dividend[i], divisor, &result.value[i], &r);
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

BIG_INT_WORD_TYPE BigInt::divInt(BIG_INT_WORD_TYPE divisor) {
	return this->divInt(divisor, *this);
}

// -- divKnuth

void BigInt::divKnuth_division(BigInt divisor, BigInt &result, BigInt& remainder, uint m, uint n) const {
	// this: dividend
	assert(n >= 2);
	//assert(this != &remainder);
	
	BIG_INT_WORD_COUNT_TYPE maxWordCount = this->wordSize;
	
	remainder = *this;
	
	//UInt<value_size+1> uu, vv;
	BigInt uu(0, maxWordCount+1);
	//BigInt vv(*this, maxWordCount+1);
	
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
	BigInt vv(divisor, maxWordCount+1);
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

void BigInt::divKnuth_makeNewU(BigInt &uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n, BIG_INT_WORD_TYPE u_max) const {
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

void BigInt::divKnuth_copyNewU(const BigInt & uu, BIG_INT_WORD_COUNT_TYPE j, BIG_INT_WORD_COUNT_TYPE n) {
	BIG_INT_WORD_COUNT_TYPE i;
	
	for(i=0 ; i<n ; ++i) {
		this->value[i+j] = uu.value[i];
	}
	
	if( i+j < this->wordSize ) {
		this->value[i+j] = uu.value[i];
	}
}

BIG_INT_WORD_TYPE BigInt::divKnuth_normalize(BigInt& divisor, uint n, uint & d) {
	// this = dividend, v = divisor
	// v.table[n-1] is != 0
	
	uint bit  = (uint)this->findHighestSetBitInWord(divisor.value[n-1]); // TODO divisor.value[divisor.wordSize - 1] ?
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

void BigInt::divKnuth_unnormalize(BIG_INT_WORD_COUNT_TYPE d) {
	this->rcr(d,0);
	//*remainder = *this;
}

BIG_INT_WORD_TYPE BigInt::divKnuth_calculate(BIG_INT_WORD_TYPE u2, BIG_INT_WORD_TYPE u1, BIG_INT_WORD_TYPE u0, BIG_INT_WORD_TYPE v1, BIG_INT_WORD_TYPE v0) const {
	//UInt<2> u_temp;
	// u_temp in qp (quotient) umbenant
	BIG_INT_WORD_COUNT_TYPE qpWordCount = 2;
	BIG_INT_WORD_TYPE qpValue[2];
	BigInt qp(&qpValue[0], qpWordCount, (u2 > 0 ? qpWordCount : qpWordCount-1));
	
	BIG_INT_WORD_TYPE rp, c;
	bool next_test;
	
	assert( v1 != 0 );

	
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
			this->mulTwoWords(qp.value[0], v0, &temp1[1], &temp1[0]);
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

void BigInt::divKnuth_multiplySubtract(	BigInt & uu,  const BigInt & vv, BIG_INT_WORD_TYPE & qp) const {
	// D4 (in the book)
	
	//UInt<value_size+1> vv_temp(vv);
	BigInt vv_temp(vv);
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

void BigInt::divKnuth(const BigInt& divisor, BigInt &result, BigInt& remainder) const {
	const BigInt& dividend = *this;
	if(divisor == BigInt::ZERO) {
		std::string msg = "BigInt devision by (BigInt)0.";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	if(dividend < divisor) {
		// set the reminder to this value and replace this with "0";
		remainder = *this;
		result.setZero();
		return;
	}
	if(dividend == BigInt::ZERO) {
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

void BigInt::div(const BigInt& divisor, BigInt &result, BigInt& remainder) const {
	this->divKnuth(divisor, result, remainder);
}

void BigInt::div(const BigInt& divisor, BigInt& remainder) {
	this->div(divisor, *this, remainder);
	//BigInt result;
	//this->div(divisor, result, *this);
	//*this = result;
}
BigInt BigInt::operator/ (const BigInt& other) const {
	BigInt result(0, this->wordSize), reminder(0, this->wordSize);
	this->div(other, result, reminder);
	return result;
}

BigInt BigInt::operator% (const BigInt& other) const {
	BigInt result(0, this->wordSize), reminder(0, this->wordSize);
	this->div(other, result, reminder);
	return reminder;
}
/*
BigInt BigInt::operator/ (const BigInt& other) const {
	BigInt result(*this); // copy this to new BigInt
	BigInt reminder(0);
	result.div(other, reminder);
	return result;
}


BigInt BigInt::operator% (const BigInt& other) const {
	BigInt result(*this); // copy this to new BigInt
	BigInt reminder(0);
	result.div(other, reminder);
	return reminder;
}
*/

// ----- pow(), sqrt() -----

BigInt BigInt::pow(BigInt pow) const {
	//if( IsNan() )
	//	return 1;
	
	if( this->isZero() ) {
		if( pow.isZero() ) {
			// we don't define zero^zero
			std::string msg = "BigInt zero^zero is not defined.";
			std::cerr << msg << std::endl;
			throw std::runtime_error(msg);
		}
		
		// 0^(+something) is zero
		//return 0;
		return *this;
	}
	
	BigInt start(*this);
	BigInt result(1);
	uint c = 0;
	
	//while( !c ) {
	while( true ) {
		if( pow.value[0] & 1 ) {
			//c += result.mul(start);
			result = result * start;
		}
		
		pow.rcr(1);
		
		if( pow.isZero() ) {
			break;
		}
		
		//c += start.Mul(start);
		start = start * start;
	}
	
	//*this = result;
	//return CheckCarry(c);
	return result;
}

BigInt BigInt::sqrt() const {
	if( this->isZero() ) {
		return BigInt(0);
	}
	
	BigInt bit(0, this->wordSize), temp(0, this->wordSize), result(0, this->wordSize);
	
	BigInt value(*this);
	
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

/* ---------- comparisons ---------- */
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


