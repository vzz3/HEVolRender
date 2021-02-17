

//#include "SFixBigInt.hpp"

using namespace ppvr::math;

#include "SArbBigInt.hpp"

// ----- statics -----

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::fromInt64(const int64_t& int64Val) {
	SFixBigInt<S> res(0);
	SFixBigInt<S>::fromInt64(int64Val, res);
	return res;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>& SFixBigInt<S>::fromInt64(const int64_t& int64Val, SFixBigInt<S> &target ) {
	UFixBigInt<S>::fromUint64(std::abs(int64Val), target);
	target.fixSignumAfterUnsafeOperation(int64Val < 0);
	return target;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::fromString(const std::string& str, const BIG_INT_WORD_TYPE base) {
	SFixBigInt<S> res(0);
	SFixBigInt<S>::fromString(str, base, res);
	return res;
}

template<BIG_INT_WORD_COUNT_TYPE S>
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
	target.fixSignumAfterUnsafeOperation(negative);

	return target;
}


template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::fromSArbBigInt(const SArbBigInt& src) {
	SFixBigInt<S> res{};
	SFixBigInt<S>::fromSArbBigInt(src, res);
	return res;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>& SFixBigInt<S>::fromSArbBigInt(const SArbBigInt& src, SFixBigInt<S> &target) {
	UFixBigInt<S>::fromUArbBigInt(src.asUnsigned(), target);
	target.signum = src.getSignum();
	return target;
}


template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::randomNumber(const uint& sizeInBit, Random& rnd) {
	SFixBigInt<S> res(0);
	SFixBigInt<S>::randomNumber(sizeInBit, rnd, res);
	return res;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::randomNumber(const SFixBigInt<S>& upperBound, Random& rnd) {
	SFixBigInt<S> res(0);
	SFixBigInt<S>::randomNumber(upperBound, rnd, res);
	return res;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>& SFixBigInt<S>::randomNumber(const uint& sizeInBit, Random& rnd, SFixBigInt<S> &target) {
	UFixBigInt<S>::randomNumber(sizeInBit, rnd, target);
	target.fixSignumAfterUnsafeOperation(false);
	return target;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>& SFixBigInt<S>::randomNumber(const SFixBigInt<S>& upperBound, Random& rnd, SFixBigInt<S> &target) {
	if(upperBound.signum < 0) {
		std::string msg = "ERROR upperBound: must be strictly greater than one";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	UFixBigInt<S>::randomNumber(upperBound, rnd, target);
	target.fixSignumAfterUnsafeOperation(false);
	return target;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::probablePrime(const uint& bitLength, Random& rnd) {
	if(bitLength > (S * BIG_INT_BITS_PER_WORD) ) {
		std::string msg = "ERROR probablePrime: the bitLength can not be greater then the bit length of the magnitude store (S * BIG_INT_BITS_PER_WORD).";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	
	const SArbBigInt arbPrime = SArbBigInt::probablePrime(bitLength, rnd);
	const SFixBigInt fixPrim = SFixBigInt<S>::fromSArbBigInt(arbPrime);
	return fixPrim;
}

// ----- constructors -----

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>::SFixBigInt(): SFixBigInt<S>(0, false) {}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>::SFixBigInt(const BIG_INT_WORD_TYPE& value, bool negative): UFixBigInt<S>(value) {
	if(UFixBigInt<S>::isZero()) {
		this->signum = 0;
	} else if(negative) {
		this->signum = -1;
	} else {
		this->signum = +1;
	}
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>::SFixBigInt(const UFixBigInt<S>& value, bool negative): UFixBigInt<S>(value) {
	if(UFixBigInt<S>::isZero()) {
		this->signum = 0;
	} else if(negative) {
		this->signum = -1;
	} else {
		this->signum = +1;
	}
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>::SFixBigInt(const SFixBigInt<S>& value): UFixBigInt<S>(value), signum(value.signum) {}

template<BIG_INT_WORD_COUNT_TYPE S>
template<BIG_INT_WORD_COUNT_TYPE OS>
SFixBigInt<S>::SFixBigInt(const SFixBigInt<OS>& src): UFixBigInt<S>(src), signum(src.signum) {}

template <BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S>::~SFixBigInt() {

}

// ----- value export - toString / toUint64 -----

template<BIG_INT_WORD_COUNT_TYPE S>
int64_t SFixBigInt<S>::toInt64() const {
	int64_t res = UFixBigInt<S>::toUint64();
	if(this->signum < 0) {
		res *= -1;
	}
	return res;
}

template<BIG_INT_WORD_COUNT_TYPE S>
std::string SFixBigInt<S>::toStringHex() const {
	std::string res = UFixBigInt<S>::toStringHex();
	if(this->signum < 0) {
		res = "-" + res;
	}
	return res;
}

template<BIG_INT_WORD_COUNT_TYPE S>
std::string SFixBigInt<S>::toStringDec() const {
	std::string res = UFixBigInt<S>::toStringDec();
	if(this->signum < 0) {
		res = "-" + res;
	}
	return res;
}

// ----- word utilities -----
template<BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_COUNT_TYPE SFixBigInt<S>::getWordSize() const {
	return UFixBigInt<S>::getWordSize();
}


// ----- bit utilities -----

template<BIG_INT_WORD_COUNT_TYPE S>
int SFixBigInt<S>::bitLength() const {
	return UFixBigInt<S>::bitLength();
}

template<BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::setZero() {
	UFixBigInt<S>::setZero();
	this->signum = 0;
}

template<BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::setOne() {
	UFixBigInt<S>::setOne();
	this->signum = +1;
}

template<BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::setAbs() {
	this->signum = this->signum * this->signum;
}


template<BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::setNegate() {
	this->signum = this->signum * -1;
}

template<BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::isMagnitudeZero() const {
	return UFixBigInt<S>::isZero();
}

template<BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::isMagnitudeOne() const {
	return UFixBigInt<S>::isOne();
}

template<BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::isZero() const {
	return this->signum == 0;
}

template<BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::isOne() const {
	if(this->signum <= 0) {
		return false;
	}
	return UFixBigInt<S>::isOne();
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::abs() const {
	SFixBigInt<S> res(*this);
	res.setAbs();
	return res;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::negate() const {
	SFixBigInt<S> res(*this);
	res.setNegate();
	return res;
}


// ----- shift left -----

template<BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE SFixBigInt<S>::rcl(const uint bits, const BIG_INT_WORD_TYPE c) {
	return UFixBigInt<S>::rcl(bits, c);
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::operator<< (const uint bits) const {
	// copy tha magnitude array 2 times
	//return SArbBigInt(BigInt::operator<<(bits), this->signum < 0);

	// copy the magnitude array only once
	SFixBigInt<S> res(*this);
	res.rcl(bits, 0);
	return res;
}


// ----- shift right -----

template<BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE SFixBigInt<S>::rcr(const uint bits, const BIG_INT_WORD_TYPE c) {
	return UFixBigInt<S>::rcr(bits, c);
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::operator>> (const uint bits) const {
	// copy tha magnitude array 2 times
	//return SArbBigInt(BigInt::operator>>(bits), this->signum < 0);

	// copy the magnitude array only once
	SFixBigInt<S> res(*this);
	res.rcr(bits, 0);
	if(res.isMagnitudeZero()) {
		res.signum = 0;
	}
	return res;
}


// ----- addition -----

template<BIG_INT_WORD_COUNT_TYPE S>
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
		UFixBigInt<S>::add(other, result);
		result.signum = +1;
		return;
	}
	if(this->signum < 0 && other.signum < 0) {
		// -x + -y = -(+x + +y)
		UFixBigInt<S>::add(other, result);
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

template<BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::add(const SFixBigInt<S> &other) {
	this->add(other, *this);
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::operator+ (const SFixBigInt<S>& other) const {
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->getWordSize(), other.getWordSize());
	SFixBigInt<S> result(0);
	this->add(other, result);
	return result;
}


// ----- substraction -----

template<BIG_INT_WORD_COUNT_TYPE S>
BIG_INT_WORD_TYPE SFixBigInt<S>::subUFixBigInt(const SFixBigInt<S>& b, SFixBigInt<S>& restul) const {
	return UFixBigInt<S>::sub(b, 0, restul);
}

template<BIG_INT_WORD_COUNT_TYPE S>
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

template<BIG_INT_WORD_COUNT_TYPE S>
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

template<BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::sub(const SFixBigInt<S>& other) {
	this->sub(other, *this);
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::operator- (const SFixBigInt<S>& other) const {
	SFixBigInt<S> result(0);
	this->sub(other, result);
	return result;
}


// ----- multiplication -----

template<BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::mul(const SFixBigInt<S>& b, SFixBigInt<S>& result) const {
	if(this->isZero() || b.isZero()) {
		result.setZero();
		return;
	}

	UFixBigInt<S>::mul(b, result);
	result.signum = ((this->signum < 0) ^ (b.signum < 0)) ? -1 : +1;
}

template<BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::mul(const SFixBigInt<S>& b) {
	SFixBigInt result{0};
	this->mul(b, result);
	*this = result;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::operator* (const SFixBigInt<S>& other) const {
	SFixBigInt<S> result{0};
	this->mul(other, result);
	return result;
}


// ----- division -----

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::operator/ (const SFixBigInt<S>& other) const {
	SFixBigInt<S> res(UFixBigInt<S>::operator/(other), (this->signum < 0) ^ (other.signum < 0) );
	//if(res.isZero()) {
	//	res.signum = 0;
	//}
	return res;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::operator% (const SFixBigInt<S>& other) const {
	SFixBigInt<S> res(UFixBigInt<S>::operator%(other), false);

	if(!res.isZero()) {
		if(this->signum >= 0 && other.signum >= 0) {
			res.signum = +1;
		} else if(this->signum < 0 && other.signum < 0) {
			res.signum = -1;
		} else if(this->signum >= 0 && other.signum < 0) {
			res = res + other; // 1 mod -5 = -4 => +1 + -5
		} else if (this->signum < 0 && other.signum >= 0) {
			res = other - res; // -1 mod 5 = 4 => +5 - +1
		} else {
			std::string msg = "ERROR mod SFixBigInt unexpected case!";
			std::cerr << msg << std::endl;
			throw std::runtime_error(msg);
		}
	}
	return res;
}


// ----- pow(), sqrt() -----

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::pow(SFixBigInt<S> pow) const {
	return SFixBigInt<S>(UFixBigInt<S>::pow(pow), pow.isOdd() && this->signum < 0);
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::sqrt() const {
	if (this->signum < 0) {
		//throw new ArithmeticException("BigInteger: modulus not positive");
		std::string msg = "ERROR SFixBigInt: can not claculate sqrt from negative number (no imaginary suport)!";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	return SFixBigInt<S>(UFixBigInt<S>::sqrt(), false);
}


/* ---------- modInverse / gcd ---------- */

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::gcd(const SFixBigInt<S> & a, const SFixBigInt<S> & b) {
	if (a.isZero()) {
		return b;
	}
	return gcd(b % a, a);
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::gcd(const SFixBigInt<S> & b) const {
	return SFixBigInt<S>::gcd(*this, b);
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::gcdExtended(const SFixBigInt<S> &a, const SFixBigInt<S> &b, SFixBigInt<S> &u, SFixBigInt<S> &v) const {
	// https://math.stackexchange.com/questions/37806/extended-euclidean-algorithm-with-negative-numbers
	//  |𝑎|𝑥+|𝑏|𝑦=1 => 𝑎(sign(𝑎)⋅𝑥)+𝑏(sign(𝑏)⋅𝑦)=1.

	// Implementing the Extended Euclidean Algorithm with Unsigned Inputs
	// https://jeffhurchalla.com/2018/10/09/analysis-of-bounds-in-the-extended-euclidean-algorithm/
	// https://jeffhurchalla.com/2018/10/13/implementing-the-extended-euclidean-algorithm-with-unsigned-inputs/

	int_fast8_t signumA = a.signum;
	int_fast8_t signumB = b.signum;

	SFixBigInt<S> absA = a;
	SFixBigInt<S> absB = b;
	absA.setAbs();
	absB.setAbs();

	//SFixBigInt<S> gcd = this->gcdExtended_internRecursive(absA, absB, u, v);
	SFixBigInt<S> gcd = this->gcdExtended_internIterative(absA, absB, u, v);

	u.signum = u.signum * signumA;
	v.signum = v.signum * signumB;

	//assert((a*u + b*v) == gcd);
	assert((SFixBigInt<FBI_WC_Sm2>(a)*SFixBigInt<FBI_WC_Sm2>(u) + SFixBigInt<FBI_WC_Sm2>(b)*SFixBigInt<FBI_WC_Sm2>(v)) == SFixBigInt<FBI_WC_Sm2>(gcd));

	return gcd;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::gcdExtended_internRecursive(const SFixBigInt<S> &a, const SFixBigInt<S> &b, SFixBigInt<S> &u, SFixBigInt<S> &v) const {
	// Base Case
	if (a.isZero()) {
		u.setZero();
		v.setOne();
		return b;
	}

	SFixBigInt<S> u1(0, u.getWordSize()), v1(0, v.getWordSize()); // To store results of recursive call
	//SFixBigInt<S> gcd = gcdExtended(b % a, a, u1, v1);
	SFixBigInt<S> gcd = gcdExtended_internRecursive(b % a, a, u1, v1);

	// Update u and v using results of recursive call
	u = v1 - (b/a) * u1;
	v = u1;

	return gcd;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::gcdExtended_internIterative(const SFixBigInt<S> &a, const SFixBigInt<S> &b, SFixBigInt<S> &u, SFixBigInt<S> &v) const {
	// https://rosettacode.org/wiki/Modular_inverse#C.2B.2B

	// https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
	/*
	u.setOne();
	v.setZero();
	SArbBigInt u1(0), v1(1), a1(a), b1(b);
	while (!b1.isZero()) {
		SArbBigInt q = a1 / b1;
		//tie(u, u1) = make_tuple(u1, u - q * u1);
		u = u1, u1 = u - q * u1;
		//tie(v, v1) = make_tuple(v1, v - q * v1);
		v = v1, v1 = v - q * v1;
		//tie(a1, b1) = make_tuple(b1, a1 - q * b1);
		a1 = b1, b1 = a1 - q * b1;

		assert((a*u  + b*v ) == SArbBigInt(a1));
		assert((a*u1 + b*v1) == SArbBigInt(b1));
	}
	return a1;
	 */

	// https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
	if( a.isZero()) {
		u.setZero();
		v.setOne();
		return b;
	}

	u.setOne();
	v.setZero();
	SFixBigInt<S> unCur(0);
	SFixBigInt<S> vnCur(1);
	SFixBigInt<S> a1(a);
	SFixBigInt<S> b1(b);

	SFixBigInt<S> q, newB, unNew, vnNew;

	while( !b1.isZero() ) {
		q = a1 / b1;
		newB = a1 % b1;
		a1 = b1;
		b1 = newB;

		// Update coefficients
		unNew = u - q * unCur;
		vnNew = v - q * vnCur;

		// Shift coefficients
		u = unCur;
		v = vnCur;
		unCur = unNew;
		vnCur = vnNew;
	}
	return a1;
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::modInverse(const SFixBigInt<S> & m) const {
	if (m.isZero()) {
		std::string msg = "ERROR BigInt: modulus not positive!";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	if (m.isOne()) {
		return SFixBigInt<S>(0);
	}

	// all the hard work will be done by gcd.
	SFixBigInt<S> u, v;
	SFixBigInt<S> gcd = this->gcdExtended(*this, m, u, v);
	if(!gcd.isOne()) {
		std::string msg = "ERROR BigInt: " + this->toStringDec() + " does not have a multiplicative inverse mod " + m.toStringDec() + " becaus the numbers are not relatively prime to!";
		//std::cerr << msg << std::endl;
		throw NoMultiplicativeInverse(msg);
	}

	//if (u < 0) {
	//	u = u + m;
	//}
	return u % m;
}


/* ---------- modPow ---------- */

template<BIG_INT_WORD_COUNT_TYPE S>
void SFixBigInt<S>::modPow(const SFixBigInt<S> &exponent, const SFixBigInt<S> &modulus, SFixBigInt<FBI_WC_Sm2>& result) const {
	if (modulus.signum <= 0) {
		//throw new ArithmeticException("BigInteger: modulus not positive");
		std::string msg = "ERROR SFixBigInt: modulus not positive!";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	
	// Trivial cases: base = -1 && (exponent % 2 = 0)
	if ( (this->isMagnitudeOne() && this->signum < 0) && exponent.isEven()) {
		if(modulus.isOne()) {
			result.setZero();
		} else {
			result.setOne();
		}
		return;
	}
	
	SFixBigInt<S> base = (this->signum < 0 || *this >= modulus) ? (*this % modulus) : *this;

	bool invertResult = exponent.signum < 0;
	SFixBigInt<S> absExponent(exponent);
	if (invertResult) {
		absExponent.setAbs();
	}

	base.UFixBigInt<S>::modPow(absExponent, modulus, result); // This methods call does the actual work! All other lines in the method are just checks / fixes for negative numbers
	result.fixSignumAfterUnsafeOperation(false);

	
	if(invertResult) {
		result = result.modInverse(modulus);
	}
}

template<BIG_INT_WORD_COUNT_TYPE S>
SFixBigInt<S> SFixBigInt<S>::modPow(const SFixBigInt<S> &exponent, const SFixBigInt<S> &modulus) const {
	SFixBigInt<FBI_WC_Sm2> result{1};
	SFixBigInt<S> tmpExponent{exponent};
	this->modPow(tmpExponent, modulus, result);
	return result;
}



/* ---------- comparisons ---------- */
template<BIG_INT_WORD_COUNT_TYPE S>
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

template<BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator<= (const SFixBigInt<S>& other) const {
	if (*this < other) {
		return true;
	}

	if (*this == other) {
		return true;
	}

	return false;
}

template<BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator> (const SFixBigInt<S>& other) const {
	return (!(*this <= other));
}

template<BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator>= (const SFixBigInt<S>& other) const {
	return (!(*this < other));
}

template<BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator== (const SFixBigInt<S>& other) const {
	if (*this < other) {
		return false;
	}

	if (other < *this) {
		return false;
	}

	return true;
}

template<BIG_INT_WORD_COUNT_TYPE S>
bool SFixBigInt<S>::operator!= (const SFixBigInt<S>& other) const {
	return (!(*this == other));
}

