
#include <algorithm>
#include <iostream>
#include "BigIntUtil.hpp"
#include "exceptions.hpp"

using ppvr::math::UFixBigInt;

// ----- statics -----
template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S> UFixBigInt<S>::fromUint64(const uint64_t& uint64Val) {
	UFixBigInt<S> res(0);
	UFixBigInt<S>::fromUint64(uint64Val, res);
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S>& UFixBigInt<S>::fromUint64(const uint64_t& uint64Val, UFixBigInt<S> &target ) {
	size_t wordsFor64Bit = (sizeof(uint64_t) * CHAR_BIT) / BIG_INT_BITS_PER_WORD;
	
	// copy bits from uint64 into words
	for(BIG_INT_WORD_COUNT_TYPE i = 0; i < wordsFor64Bit && i < S; i++) {
		target.value[i] = (BIG_INT_WORD_TYPE)(uint64Val >> (i * BIG_INT_BITS_PER_WORD));
	}
	
	return target;
}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S> UFixBigInt<S>::fromString(const std::string& str, const BIG_INT_WORD_TYPE base) {
	UFixBigInt<S> res(0);
	UFixBigInt<S>::fromString(str, base, res);
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S>& UFixBigInt<S>::fromString(const std::string& str, const BIG_INT_WORD_TYPE base, UFixBigInt<S> &target ) {
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
	//double sizeInBit = (double)str.length() * (log2((double)base));
	//uint wordSize = std::ceil(sizeInBit / (double)BIG_INT_BITS_PER_WORD);
	//if(wordSize > S) {
	//	throw FixBigIntOverflow(std::string("The number from the string ") + str + std::string(" can not be stored within ") + std::to_string(S) + std::string(" words."));
	//}
	
	UFixBigInt<S> pow(1);
	UFixBigInt<S> powTmp(0);
	BIG_INT_WORD_TYPE d;
	BIG_INT_WORD_TYPE carry;
	UFixBigInt<S> dPow(0);
	size_t strlen = str.length();
	size_t leadingZeroCount = 0;
	
	try {
		for(size_t i = strlen; i>0; i--) {
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
			
			if(d > 0) {
				//if(i != strlen) { // pow need to be zero at the first iteration
				for(size_t n = 0; n < leadingZeroCount; n++) {
					// pow = pow * base
					powTmp = pow;
					powTmp.mulInt(base, pow);
				}
				
				// target = target + pow * t
				pow.mulInt(d, dPow); // trows FixBigIntOverflow
				carry = target.add(dPow);
				if(carry > 0) {
					throw FixBigIntOverflow("temp");
				}
				
				leadingZeroCount = 0;
			}
			leadingZeroCount++;
		}
	} catch (const FixBigIntOverflow& e) {
		throw FixBigIntOverflow(std::string("The number from the string ") + str + std::string(" can not be stored within ") + std::to_string(S) + std::string(" words."));
	}
	
	return target;
}

// ----- constructors -----

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S>::UFixBigInt() {}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S>::UFixBigInt(const BIG_INT_WORD_TYPE& value) {
	this->initWords(0);
	this->value[0] = value;
}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S>::UFixBigInt(const UFixBigInt &src) {
	std::copy(&src.value[0], &src.value[0] + S, this->value);
}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S>::~UFixBigInt() {}

template <BIG_INT_WORD_COUNT_TYPE S>
void UFixBigInt<S>::initWords(const BIG_INT_WORD_TYPE initValue) {
	std::fill_n(&this->value[0], S, initValue);
}

// ----- value export - toString / toUint64 -----

template <BIG_INT_WORD_COUNT_TYPE S>
uint64_t UFixBigInt<S>::toUint64() const {
	uint64_t res = 0;
	uint64_t tmp;
	size_t wordsFor64Bit = (sizeof(uint64_t) * CHAR_BIT) / BIG_INT_BITS_PER_WORD;
	for( size_t i=0; i<S && i<wordsFor64Bit; i++) {
		tmp = this->value[i];
		res = res | (tmp << (i * BIG_INT_BITS_PER_WORD));
	}
	
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
std::string UFixBigInt<S>::toStringHex() const {
	static const char* digits = "0123456789ABCDEF";
	
	size_t bitPerHexDidigit = 4;
	size_t hexDigitsPerWord = BIG_INT_BITS_PER_WORD / bitPerHexDidigit ;
	std::string ret = "";
	size_t zeroBuffer = 0;
	for (BIG_INT_WORD_COUNT_TYPE wordIndex = 0; wordIndex < S; wordIndex++) {
		BIG_INT_WORD_TYPE word = this->value[wordIndex];
		for (size_t hexDigitIndex=0; hexDigitIndex < hexDigitsPerWord; hexDigitIndex++) {
			BIG_INT_WORD_TYPE digit = word & 0x0F;
			word = word >> bitPerHexDidigit;
			if(digit > 0) { // prevent leading zeros
				if(zeroBuffer > 0) {
					ret = std::string(zeroBuffer, '0') + ret;
					zeroBuffer = 0;
				}
				ret = digits[digit] + ret;
			} else {
				zeroBuffer++;
			}
		}
	}
	
	if(ret.length() == 0) {
		ret = "0";
	}
	
	return ret;
}

template <BIG_INT_WORD_COUNT_TYPE S>
std::string UFixBigInt<S>::toStringDec() const {
	static const char* digits = "0123456789";
	
	std::string ret = "";
	UFixBigInt<S> tmp = *this;
	BIG_INT_WORD_TYPE decDigit;
	while (!tmp.isZero()) {
		decDigit = tmp.divInt( 10 );
		ret = digits[decDigit] + ret;
	}
	
	if(ret.length() == 0) {
		ret = "0";
	}
	
	return ret;
}

// ----- bit utilities -----

template <BIG_INT_WORD_COUNT_TYPE S>
int UFixBigInt<S>::bitLength() const {
	return findHighestSetBit()+1;
}


template <BIG_INT_WORD_COUNT_TYPE S>
void UFixBigInt<S>::setZero() {
	initWords(0);
}

template <BIG_INT_WORD_COUNT_TYPE S>
void UFixBigInt<S>::setOne() {
	initWords(0);
	this->wordSize = 1;
}

template <BIG_INT_WORD_COUNT_TYPE S>
void UFixBigInt<S>::setBit(const uint n) {
	uint restBits   = n % BIG_INT_BITS_PER_WORD;
	uint allWords 	= n / BIG_INT_BITS_PER_WORD;
	
	if(allWords >= S) {
		throw FixBigIntOverflow("Can not set Bit " + std::to_string(n) + " because it is not within "  + std::to_string(S) + " words.");
	}
	
	this->value[allWords] |= (BIG_INT_WORD_TYPE(1) << restBits);
}

template <BIG_INT_WORD_COUNT_TYPE S>
void UFixBigInt<S>::clearBit(const uint n) {
	uint restBits   = n % BIG_INT_BITS_PER_WORD;
	uint allWords 	= n / BIG_INT_BITS_PER_WORD;
	
	if(allWords >= S) {
		throw FixBigIntOverflow("Can not clear Bit " + std::to_string(n) + " because it is not within "  + std::to_string(S) + " words.");
	}
		
	this->value[allWords] &= ~(BIG_INT_WORD_TYPE(1) << restBits);
}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S> UFixBigInt<S>::withBit(const uint n) {
	UFixBigInt<S> res(*this);
	res.setBit(n);
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S> UFixBigInt<S>::withoutBit(const uint n) {
	UFixBigInt<S> res(*this);
	res.clearBit(n);
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::isZero() const {
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<S; i++) {
		if(this->value[i] != 0) {
			return false;
		}
	}
	return true;
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::isOne() const {
	if(this->value[0] != 1) {
		return false;
	}
	for (BIG_INT_WORD_COUNT_TYPE i = 1; i<S; i++) {
		if(this->value[i] != 0) {
			return false;
		}
	}
	return true;
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::isEven() const {
	return !(this->testBit(0));
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::isOdd() const {
	return this->testBit(0);
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::testBit(uint n) const {
	uint restBits   = n % BIG_INT_BITS_PER_WORD;
	uint allWords 	= n / BIG_INT_BITS_PER_WORD;
	
	if(allWords >= S) {
		throw FixBigIntOverflow("Can not test Bit " + std::to_string(n) + " because it is not within "  + std::to_string(S) + " words.");
	}
	
	return ((this->value[allWords] >> restBits) & 1);
}

template <BIG_INT_WORD_COUNT_TYPE S>
int UFixBigInt<S>::findHighestSetBit() const {
	//if(this->isZero()) { // Does not have an advantage for a fixed with integer, because we need to loop over all words anyway.
	//	return -1;
	//}
	
	int wordIndex;
	for(wordIndex=S-1; wordIndex > 0 && this->value[wordIndex] == 0; wordIndex--);
	
	BIG_INT_WORD_TYPE word = this->value[wordIndex];
	int bit = BigIntUtil::findHighestSetBitInWord(word);
	
	if(bit < 0) {
		return -1;
	}
	
	return wordIndex * BIG_INT_BITS_PER_WORD + bit;
}

template <BIG_INT_WORD_COUNT_TYPE S>
int UFixBigInt<S>::findLowestSetBit() const {
	//if(this->isZero()) { // Does not have an advantage for a fixed with integer, because we need to loop over all words anyway.
	//	return -1;
	//}
	
	int wordIndex=0;
	for(wordIndex=0; wordIndex < S-1 && this->value[wordIndex] == 0; wordIndex++);
	
	BIG_INT_WORD_TYPE word = this->value[wordIndex];
	int bit = BigIntUtil::findLowestSetBitInWord(word);
	
	if(bit < 0) {
		return -1;
	}
	
	return wordIndex * BIG_INT_BITS_PER_WORD + bit;
}


// ----- shift left -----

template <BIG_INT_WORD_COUNT_TYPE S>
void UFixBigInt<S>::rcl_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, const uint bits, BIG_INT_WORD_TYPE c) {
	restBits      = bits % BIG_INT_BITS_PER_WORD;
	uint allWords = bits / BIG_INT_BITS_PER_WORD;
	BIG_INT_WORD_TYPE mask      = ( c ) ? BIG_INT_WORD_MAX_VALUE : 0;
	
	
	if( allWords >= S ) {
		if( allWords == S && restBits == 0 ) {
			lastC = this->value[0] & 1;
		}
		// else: last_c is default set to 0
		
		// clearing
		for(uint i = 0 ; i<S ; ++i) {
			this->value[i] = mask;
		}
		
		restBits = 0;
	} else {
		if( allWords > 0 ) {
			// 0 < all_words < value_size
			
			int first, second;
			lastC = this->value[S - allWords] & 1; // all_words is greater than 0
			
			// copying the first part of the value
			for(first = S-1, second=first-allWords ; second>=0 ; --first, --second) {
				this->value[first] = this->value[second];
			}
			
			// setting the rest to 'c'
			for( ; first>=0 ; --first ) {
				this->value[first] = mask;
			}
		}
	}
}

template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::rcl_moveBits(const uint bits, BIG_INT_WORD_TYPE c) {
	assert( bits>0 && bits<BIG_INT_BITS_PER_WORD );
	
	uint move = BIG_INT_BITS_PER_WORD - bits;
	BIG_INT_WORD_COUNT_TYPE i;
	BIG_INT_WORD_TYPE newC;
	
	if( c != 0 ) {
		c = BIG_INT_BITS_PER_WORD >> move;
	}
	
	for(i=0 ; i<S ; ++i) {
		newC    = this->value[i] >> move;
		this->value[i] = (this->value[i] << bits) | c;
		c        = newC;
	}
	
	return (c & 1);
}

template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::rcl(const uint bits, const BIG_INT_WORD_TYPE c) {
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

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S> UFixBigInt<S>::operator<< (const uint bits) const {
	UFixBigInt<S> res(*this);
	res.rcl(bits, 0);
	return res;
}


// ----- shift right -----

template <BIG_INT_WORD_COUNT_TYPE S>
void UFixBigInt<S>::rcr_moveWords(uint &restBits, BIG_INT_WORD_TYPE &lastC, const uint bits, BIG_INT_WORD_TYPE c) {
	restBits      = bits % BIG_INT_BITS_PER_WORD;
	uint allWords = bits / BIG_INT_BITS_PER_WORD;
	BIG_INT_WORD_TYPE mask      = ( c ) ? BIG_INT_WORD_MAX_VALUE : 0;
	
	
	if( allWords >= S ) {
		if( allWords == S && restBits == 0 ) {
			lastC = (this->value[S-1] & BIG_INT_WORD_HIGHEST_BIT) ? 1 : 0;
		}
		// else: last_c is default set to 0
		
		// clearing
		for(uint i = 0 ; i<S ; ++i) {
			this->value[i] = mask;
		}
		//this->value[0] = mask;
		//this->wordSize = 1;
		
		restBits = 0;
	} else if( allWords > 0 ) {
		// 0 < all_words < value_size
		
		uint first, second;
		lastC = (this->value[allWords - 1] & BIG_INT_WORD_HIGHEST_BIT) ? 1 : 0; // all_words is > 0
		
		// copying the first part of the value
		for(first=0, second=allWords ; second<S ; ++first, ++second) {
			this->value[first] = this->value[second];
		}
		
		// setting the rest to 'c'
		for( ; first<S ; ++first ) {
			this->value[first] = mask;
		}
		//this->wordSize = first;
	}
}

template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::rcr_moveBits(const uint bits, BIG_INT_WORD_TYPE c) {
	assert ( bits>0 && bits<BIG_INT_BITS_PER_WORD );
	
	uint move = BIG_INT_BITS_PER_WORD - bits;
	int i; // signed
	BIG_INT_WORD_TYPE newC;
	
	if( c != 0 ) {
		c = BIG_INT_WORD_MAX_VALUE << move;
	}
	
	for(i=S-1 ; i>=0 ; --i) {
		newC    = this->value[i] << move;
		this->value[i] = (this->value[i] >> bits) | c;
		c        = newC;
	}
	
	c = (c & BIG_INT_WORD_HIGHEST_BIT) ? 1 : 0;
	
	//if(this->wordSize > 1 && this->value[this->wordSize-1] == 0) {
	//	this->wordSize--;
	//}
	
	return c;
}

template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::rcr(const uint bits, const BIG_INT_WORD_TYPE c) {
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

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S> UFixBigInt<S>::operator>> (const uint bits) const {
	UFixBigInt<S> res(*this);
	res.rcr(bits);
	return res;
}




// ----- addition -----
/*
template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::addInt(const BIG_INT_WORD_TYPE word) {
	
	BIG_INT_WORD_TYPE c = BigIntUtil::addInt(word, 0, this->value, this->wordSize);
	
	// increate the word count in order to add the last carry
	if(c != 0) {
		this->reserveWords(this->wordSize + 1);
		this->value[this->wordSize] = c;
		this->wordSize = this->wordSize + 1;
	}
}
*/
template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::add(const UFixBigInt<S> &other, UFixBigInt<S> &result) const {
	BIG_INT_WORD_TYPE carry = 0;
	BIG_INT_WORD_TYPE a,b;//,c;
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<S; i++) {
		a = this->value[i];
		b = other.value[i];
		
		carry = BigIntUtil::addTwoWords(a, b, carry, &result.value[i]);
	}
	
	return carry;
}

template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::add(const UFixBigInt<S> &other) {
	return this->add(other, *this);
}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S> UFixBigInt<S>::operator+ (const UFixBigInt<S>& other) const {
	UFixBigInt<S> result(0);
	BIG_INT_WORD_TYPE carry = this->add(other, result);
	if(carry > 0) {
		throw FixBigIntOverflow("add() returned a carry");
	}
	return result;
}

// ----- substraction -----

template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::subInt(const BIG_INT_WORD_TYPE word) {
	BIG_INT_WORD_TYPE c = BigIntUtil::subInt(word, 0, this->value, this->wordSize);
	
	// reduce word size if a word was truncated
	if(this->value[this->wordSize-1] == 0) {
		this->wordSize = this->wordSize-1;
	}
	
	return c;
}

template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::sub(const UFixBigInt<S>& other, BIG_INT_WORD_TYPE carry, UFixBigInt<S> &result) const {
	for (BIG_INT_WORD_COUNT_TYPE i = 0; i<S; i++) {
		carry = BigIntUtil::subTwoWords(this->value[i], other.value[i], carry, &result.value[i]);
	}
	return carry;
}

template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::sub(const UFixBigInt<S>& other) {
	return this->sub(other, 0, *this);
}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S> UFixBigInt<S>::operator- (const UFixBigInt<S>& other) const {
	if(other > *this) {
		std::string msg = "ERROR substract UArbBigInt a - b with a < b (a=";// + this->toStringDec() + ", b=" + other.toStringDec() + ")!"; // TODO reenable this!!!!!
		std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	UFixBigInt<S> result(0);
	this->sub(other, 0, result);
	return result;
}



// ----- multiplication -----

template <BIG_INT_WORD_COUNT_TYPE S>
//template <BIG_INT_WORD_COUNT_TYPE R>
void UFixBigInt<S>::mulInt(BIG_INT_WORD_TYPE ss2, UFixBigInt<S>& result) const {
	//assert(S < R);
	result.setZero();
	
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
		
		for(x1size=S ; x1size>0 && this->value[x1size-1]==0 ; --x1size);
		
		if( x1size == 0 ) {
			// this is 0: 0*x => 0
			result.setZero();
			return;
		}
		
		for(x1start=0 ; x1start<x1size && this->value[x1start]==0 ; ++x1start);
	}
	
	// performe the multiplication
	//for(BIG_INT_WORD_COUNT_TYPE x1=x1start ; x1<x1size ; ++x1) {
	for(BIG_INT_WORD_COUNT_TYPE x1=x1start ; x1<x1size && x1 < (S-1); ++x1) {
		BigIntUtil::mulTwoWords(this->value[x1], ss2, &r2, &r1 );
		BigIntUtil::addTwoInts(r2, r1, x1, result.value, S); // this->wordCapacity is > u.wordSize => there can not be a carry bit!
	}
	
	// multiply with last word if required
	if(x1size == S) {
		BIG_INT_WORD_TYPE carry;
		
		BigIntUtil::mulTwoWords(this->value[S-1], ss2, &r2, &r1);
		carry = r2;
		if(carry > 0) {
			throw FixBigIntOverflow(std::string("mulInt not posible without overflow (r2)"));
		}
		
		carry = BigIntUtil::addInt(r1, S-1, result.value, S);
		if(carry > 0) {
			throw FixBigIntOverflow(std::string("mulInt not posible without overflow (r1)"));
		}
	}
	
	
}

template <BIG_INT_WORD_COUNT_TYPE S>
void UFixBigInt<S>::mulSchool(const UFixBigInt<S>& a, const UFixBigInt<S>& b, UFixBigInt<S>& result) const {
	BIG_INT_WORD_COUNT_TYPE aSize  = S, 	bSize  = S;
	BIG_INT_WORD_COUNT_TYPE aStart = 0,     bStart = 0;
	
	//if( aSize > 2 ) {
		// if the wordCount is smaller than or equal to 2
		// there is no sense to set aSize (and others) to another values
		
		for( ; aSize>0 && a.value[aSize-1]==0 ; --aSize);
		for(aStart=0 ; aStart<aSize && a.value[aStart]==0 ; ++aStart);
	//}
	//if( bSize > 2 ) {
		// if the wordCount is smaller than or equal to 2
		// there is no sense to set bSize (and others) to another values
		
		for( ; bSize>0 && b.value[bSize-1]==0 ; --bSize);
		for(bStart=0 ; bStart<bSize && b.value[bStart]==0 ; ++bStart);
	//}
	
	result.setZero();
	if( aSize==0 || bSize==0 ) {
		return;
	}
	
	if((aSize + bSize - 1) > S) {
		throw FixBigIntOverflow(std::string("mulSchool not posible without overflow (aSize + bSize >= S)"));
	}
	
	BIG_INT_WORD_TYPE r2, r1, carry = 0;
	
	for(uint aI=aStart ; aI<aSize ; ++aI) {
		//for(uint bI=bStart ; bI<bSize ; ++bI) {
		for(uint bI=bStart ; bI<bSize && bI+aI < (S-1) ; ++bI) {
			BigIntUtil::mulTwoWords(a.value[aI], b.value[bI], &r2, &r1);
			carry += BigIntUtil::addTwoInts(r2, r1, bI+aI, result.value, S); // there can be a carry during the last iteration of the outer loop here will never be a carry
			
		}
	}
	
	if(carry > 0) {
		throw FixBigIntOverflow(std::string("mulSchool not posible without overflow (loop)"));
	}
	
	// multiply with last word if required
	if( (aSize + bSize - 1) == S ) {
		BigIntUtil::mulTwoWords(a.value[aSize-1], b.value[bSize-1], &r2, &r1);
		carry = r2;
		if(carry > 0) {
			throw FixBigIntOverflow(std::string("mulSchool not posible without overflow (r2)"));
		}
		
		carry = BigIntUtil::addInt(r1, S-1, result.value, S);
		if(carry > 0) {
			throw FixBigIntOverflow(std::string("mulSchool not posible without overflow (r1)"));
		}
	}
	
	// optimize word count
	//BIG_INT_WORD_COUNT_TYPE usedWordIndex;
	//for(usedWordIndex = maxWordCount; usedWordIndex>0 && result.value[usedWordIndex-1] == 0; --usedWordIndex);
	//
	//result.wordSize = usedWordIndex;
}

template <BIG_INT_WORD_COUNT_TYPE S>
void UFixBigInt<S>::mul(const UFixBigInt<S>& b, UFixBigInt<S>& result) const {
	this->mulSchool(*this, b, result);
}

template <BIG_INT_WORD_COUNT_TYPE S>
void UFixBigInt<S>::mul(const UFixBigInt<S>& b) {
	UArbBigInt result;
	this->mul(b, result);
	*this = result;
}

template <BIG_INT_WORD_COUNT_TYPE S>
UFixBigInt<S> UFixBigInt<S>::operator* (const UFixBigInt<S>& other) const {
	UFixBigInt<S> result;
	this->mul(other, result);
	return result;
}






// ----- division -----


// -- divInt

template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::divInt(BIG_INT_WORD_TYPE divisor, UFixBigInt<S>& result) const {
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
	
	//UInt<value_size> dividend(*this);
	const BIG_INT_WORD_TYPE* dividend = this->value;
	
	int i;  // i must be with a sign
	BIG_INT_WORD_TYPE r = 0;
	
	// we're looking for the last word in dividend (most significant word that is not null)
	//result.setZero();
	//for(i=S-1 ; i>0 && dividend[i]==0 ; --i);
	i = S - 1;
	
	for( ; i>=0 ; --i) {
		BigIntUtil::divTwoWords(r, dividend[i], divisor, &result.value[i], &r);
	}
	
	return r;
}

template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE UFixBigInt<S>::divInt(BIG_INT_WORD_TYPE divisor) {
	return this->divInt(divisor, *this);
}







/* ---------- comparisons ---------- */

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::operator< (const UFixBigInt<S>& other) const {
	for (BIG_INT_WORD_COUNT_TYPE i = (S - 1); i > 0; i--) {
		if (this->value[i] < other.value[i]) {
			return true;
		}
		
		if (this->value[i] > other.value[i]) {
			return false;
		}
	}
	return (this->value[0] < other.value[0]);
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::operator<= (const UFixBigInt<S>& other) const {
	if (*this < other) {
		return true;
	}
	
	if (*this == other) {
		return true;
	}
	
	return false;
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::operator> (const UFixBigInt<S>& other) const {
	return (!(*this <= other));
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::operator>= (const UFixBigInt<S>& other) const {
	return (!(*this < other));
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::operator== (const UFixBigInt<S>& other) const {
	if (*this < other) {
		return false;
	}
	
	if (other < *this) {
		return false;
	}
	
	return true;
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool UFixBigInt<S>::operator!= (const UFixBigInt<S>& other) const {
	return (!(*this == other));
}
