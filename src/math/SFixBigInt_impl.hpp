

//#include "SFixBigInt.hpp"

using namespace ppvr::math;

// ----- statics -----

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::fromInt64(const int64_t& int64Val) {
	SFixBigInt<S> res(0);
	SFixBigInt<S>::fromInt64(int64Val, res);
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>& SFixBigInt<S>::fromInt64(const int64_t& int64Val, SFixBigInt<S> &target ) {
	UFixBigInt<S>::fromUint64(std::abs(int64Val), target);
	if(target.isMagnitudeZero() ) {
		target.signum = 0;
	} else {
		if(int64Val > 0) {
			target.signum = 1;
		} else if(int64Val < 0) {
			target.signum = -1;
		}
	}
	return target;
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::fromString(const std::string& str, const BIG_INT_WORD_TYPE base) {
	SFixBigInt<S> res(0);
	SFixBigInt<S>::fromString(str, base, res);
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>& SFixBigInt<S>::fromString(std::string str, const BIG_INT_WORD_TYPE base, SFixBigInt<S> &target ) {
	// trim space on the left side
	auto nonSpaceBegin = std::find_if(str.begin(), str.end(), [](int ch) {
		return !std::isspace(ch);
	});

	if(nonSpaceBegin == str.end()) {
		// string contains only emty chars
		target.setZero();
		return target;
	}

	bool negative;
	if(*nonSpaceBegin == '-') {
		nonSpaceBegin = nonSpaceBegin+1;
		negative = true;
	} else {
		if(*nonSpaceBegin == '+') {
			nonSpaceBegin = nonSpaceBegin+1;
		}
		negative = false;
	}
	// trim string
	str.erase(str.begin(), nonSpaceBegin);

	// pars unsigned string
	UFixBigInt<S>::fromString(str, base, target);

	// set sign
	if( target.isMagnitudeZero() ) {
		target.signum = 0;
	} else {
		target.signum = negative ? -1 : +1;
	}

	return target;
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::randomNumber(const uint& sizeInBit, Random& rnd) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BIG_INT_REQUIRED_WORDS(sizeInBit);
	SFixBigInt<S> res(0, requiredWords);
	SFixBigInt<S>::randomNumber(sizeInBit, rnd, res);
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::randomNumber(const SFixBigInt<S>& upperBound, Random& rnd) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BIG_INT_REQUIRED_WORDS(upperBound.bitLength());
	SFixBigInt<S> res(0, requiredWords);
	SFixBigInt<S>::randomNumber(upperBound, rnd, res);
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>& SFixBigInt<S>::randomNumber(const uint& sizeInBit, Random& rnd, SFixBigInt<S> &target) {
	UArbBigInt::randomNumber(sizeInBit, rnd, target);
	if(target.isMagnitudeZero()) {
		target.signum = 0;
	} else {
		target.signum = 1;
	}
	return target;
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>& SFixBigInt<S>::randomNumber(const SFixBigInt<S>& upperBound, Random& rnd, SFixBigInt<S> &target) {
	if(upperBound.signum < 0) {
		std::string msg = "ERROR upperBound: must be strictly greater than one";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	UArbBigInt::randomNumber(upperBound, rnd, target);
	if(target.isMagnitudeZero()) {
		target.signum = 0;
	} else {
		target.signum = 1;
	}
	return target;
}


// ----- constructors -----

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>::SFixBigInt(): SFixBigInt(0, 0, false) {}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>::SFixBigInt(const BIG_INT_WORD_TYPE& value, bool negative): UFixBigInt<S>(value) {
	if(UFixBigInt<S>::isZero()) {
		this->signum = 0;
	} else if(negative) {
		this->signum = -1;
	} else {
		this->signum = +1;
	}
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>::SFixBigInt(const UFixBigInt<S>& value, bool negative): UFixBigInt<S>(value) {
	if(UFixBigInt<S>::isZero()) {
		this->signum = 0;
	} else if(negative) {
		this->signum = -1;
	} else {
		this->signum = +1;
	}
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>::SFixBigInt(const SFixBigInt<S>& value): UFixBigInt<S>(value), signum(value.signum) {}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>::~SFixBigInt() {

}

// ----- value export - toString / toUint64 -----

template <BIG_INT_WORD_COUNT_TYPE S>
int64_t SFixBigInt<S>::toInt64() const {
	int64_t res = UFixBigInt<S>::toUint64();
	if(this->signum < 0) {
		res *= -1;
	}
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
std::string SFixBigInt<S>::toStringHex() const {
	std::string res = UFixBigInt<S>::toStringHex();
	if(this->signum < 0) {
		res = "-" + res;
	}
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
std::string SFixBigInt<S>::toStringDec() const {
	std::string res = UFixBigInt<S>::toStringDec();
	if(this->signum < 0) {
		res = "-" + res;
	}
	return res;
}

// ----- bit utilities -----


template <BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::setNegate() {
	this->signum = this->signum * -1;
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::isMagnitudeZero() const {
	return UFixBigInt<S>::isZero();
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::isMagnitudeOne() const {
	return UFixBigInt<S>::isOne();
}

// ----- addition -----

template <BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::add(const SFixBigInt<S> &other, SFixBigInt<S> &result) const {
	if(this->isZero()) {
		result = other;
		return;
	}
	if(other.isZero()) {
		result = *this;
		return;
	}
	if(this->signum > 0 && other.signum > 0) {
		// +x + +y = +(+x + +y)
		UArbBigInt::add(other, result);
		result.signum = +1;
		return;
	}
	if(this->signum < 0 && other.signum < 0) {
		// -x + -y = -(+x + +y)
		UArbBigInt::add(other, result);
		result.signum = -1;
		return;
	}
	if(this->signum < 0) {
		// -x + +y = +y - +x
		subAsPositive(other, *this, result);
		return;
	}
	if(other.signum < 0) {
		// +x + -y = +x - +y
		subAsPositive(*this, other, result);
		return;
	}

	std::string msg = "ERROR add SArbBigInt unexpected case!";
	std::cerr << msg << std::endl;
	throw std::runtime_error(msg);
}

template <BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::add(const SFixBigInt<S> &other) {
	this->add(other, *this);
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::operator+ (const SFixBigInt<S>& other) const {
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->getWordSize(), other.getWordSize());
	SFixBigInt<S> result(0);
	this->add(other, result);
	return result;
}

// ----- substraction -----
template <BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE SFixBigInt<S>::subUFixBigInt(const SFixBigInt<S>& b, SFixBigInt<S>& restul) const {
	return UFixBigInt<S>::sub(b, 0, restul);
}

template <BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::subAsPositive(const SFixBigInt<S>& a, const SFixBigInt<S>& b, SFixBigInt<S>& restul) const {
	// more readable version but requires a comparision of the magnitudes and therfore two casts.... probably slow

	//if( (BigInt)b < (BigInt)a ) { // only compare the magnitude
	if(static_cast<const UFixBigInt<S>&>(b) < static_cast<const UFixBigInt<S>&>(a)  ) { // only compare the magnitude (ignore the sign); static_cast<const BigInt&>(X): cast without calling the copy constructor
		//restul = SArbBigInt(a - b, false);
		a.subUFixBigInt(b, restul);
		restul.signum = restul.isMagnitudeZero() ? 0 : +1;
	} else {
		//restul = SArbBigInt(b - a, true);
		b.subUFixBigInt(a, restul);
		restul.signum = restul.isMagnitudeZero() ? 0 : -1;
	}

}

template <BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::sub(const SFixBigInt<S>& other, SFixBigInt<S> &result) const {
	if(this->isZero()) {
		result = other;
		result.setNegate(); // invert sign
		return;
	}
	if(other.isZero()) {
		result = *this;
		return;
	}

	if(this->signum > 0 && other.signum > 0) {
		// +a - +b
		subAsPositive(*this, other, result);
		return;
	}

	if(this->signum < 0 && other.signum < 0) {
		// -a - -b = -a + +b = +b - +a
		subAsPositive(other, *this, result);
		return;
	}

	if(this->signum > 0 && other.signum < 0) {
		// +a - -b = +a + +b
		UFixBigInt<S>::add(other, result);
		result.signum = +1;
		return;
	}

	if(this->signum < 0 && other.signum > 0) {
		// -a - +b = -(+a + +b)
		UFixBigInt<S>::add(other, result);
		result.signum = -1;
		return;
	}

	std::string msg = "ERROR substract SFixBigInt unexpected case!";
	std::cerr << msg << std::endl;
	throw std::runtime_error(msg);
}

template <BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::sub(const SFixBigInt<S>& other) {
	this->sub(other, *this);
}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::operator- (const SFixBigInt<S>& other) const {
	SFixBigInt<S> result(0);
	this->sub(other, result);
	return result;
}







/* ---------- comparisons ---------- */
template <BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator< (const SFixBigInt<S>& other) const {
	if(this->signum < other.signum) {
		return true;
	}

	if(this->signum > other.signum) {
		return false;
	}

	if(this->signum < 0) {
		return !(UFixBigInt<S>::operator<=(other));
	} else {
		return UFixBigInt<S>::operator<(other);
	}
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator<= (const SFixBigInt<S>& other) const {
	if (*this < other) {
		return true;
	}

	if (*this == other) {
		return true;
	}

	return false;
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator> (const SFixBigInt<S>& other) const {
	return (!(*this <= other));
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator>= (const SFixBigInt<S>& other) const {
	return (!(*this < other));
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator== (const SFixBigInt<S>& other) const {
	if (*this < other) {
		return false;
	}

	if (other < *this) {
		return false;
	}

	return true;
}

template <BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator!= (const SFixBigInt<S>& other) const {
	return (!(*this == other));
}

