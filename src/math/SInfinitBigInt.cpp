
#include "SInfinitBigInt.h"
#include <iostream>

using namespace ppvr::math;

// ----- statics -----


SInfinitBigInt SInfinitBigInt::fromInt64(const int64_t& uint64Val) {
	SInfinitBigInt res(0);
	SInfinitBigInt::fromInt64(uint64Val, res);
	return res;
}

SInfinitBigInt& SInfinitBigInt::fromInt64(const int64_t& uint64Val, SInfinitBigInt &target ) {
	BigInt::fromUint64(abs(uint64Val), target);
	if(target.isMagnitudeZero()) {
		target.signum = 0;
	} else {
		if(uint64Val > 0) {
			target.signum = 1;
		} else if(uint64Val < 0) {
			target.signum = -1;
		}
	}
	return target;
}

SInfinitBigInt SInfinitBigInt::fromString(const std::string& str, const BIG_INT_WORD_TYPE base) {
	SInfinitBigInt res(0);
	SInfinitBigInt::fromString(str, base, res);
	return res;
}

SInfinitBigInt& SInfinitBigInt::fromString(std::string str, const BIG_INT_WORD_TYPE base, SInfinitBigInt &target ) {
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
	BigInt::fromString(str, base, target);
	
	// set sign
	if( target.isMagnitudeZero() ) {
		target.signum = 0;
	} else {
		target.signum = negative ? -1 : +1;
	}
	
	return target;
}

SInfinitBigInt SInfinitBigInt::randomNumber(const uint& sizeInBit) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BigInt::requiredWords(sizeInBit);
	SInfinitBigInt res(0, requiredWords);
	SInfinitBigInt::randomNumber(sizeInBit, res);
	return res;
}

SInfinitBigInt SInfinitBigInt::randomNumber(const SInfinitBigInt& upperBound) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BigInt::requiredWords(upperBound.bitLength());
	SInfinitBigInt res(0, requiredWords);
	SInfinitBigInt::randomNumber(upperBound, res);
	return res;
}

SInfinitBigInt& SInfinitBigInt::randomNumber(const uint& sizeInBit, SInfinitBigInt &target) {
	BigInt::randomNumber(sizeInBit, target);
	return target;
}

SInfinitBigInt& SInfinitBigInt::randomNumber(const SInfinitBigInt& upperBound, SInfinitBigInt &target) {
	if(upperBound.signum < 0) {
		std::string msg = "ERROR upperBound: must be strictly greater than one";
		//std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	
	BigInt::randomNumber(upperBound, target);
	return target;
}

// ----- constructors -----

SInfinitBigInt::SInfinitBigInt(): SInfinitBigInt(0, 0, false) {}

SInfinitBigInt::SInfinitBigInt(const BIG_INT_WORD_TYPE& value, bool negative): SInfinitBigInt(value, 0, negative) {}

SInfinitBigInt::SInfinitBigInt(const BIG_INT_WORD_TYPE& value, BIG_INT_WORD_COUNT_TYPE minCapacity, bool negative): BigInt(value, minCapacity) {
	if(BigInt::isZero()) {
		this->signum = 0;
	} else if(negative) {
		this->signum = -1;
	} else {
		this->signum = +1;
	}
}

SInfinitBigInt::SInfinitBigInt(const BigInt& value, bool negative): BigInt(value) {
	if(BigInt::isZero()) {
		this->signum = 0;
	} else if(negative) {
		this->signum = -1;
	} else {
		this->signum = +1;
	}
}

SInfinitBigInt::SInfinitBigInt(const SInfinitBigInt& value): BigInt(value), signum(value.signum) {}

SInfinitBigInt::~SInfinitBigInt() {
	
}

// ----- value export - toString / toUint64 -----

int64_t SInfinitBigInt::toInt64() const {
	int64_t res = BigInt::toUint64();
	if(this->signum < 0) {
		res *= -1;
	}
	return res;
}

std::string SInfinitBigInt::toStringHex() const {
	std::string res = BigInt::toStringHex();
	if(this->signum < 0) {
		res = "-" + res;
	}
	return res;
}

std::string SInfinitBigInt::toStringDec() const {
	std::string res = BigInt::toStringDec();
	if(this->signum < 0) {
		res = "-" + res;
	}
	return res;
}

// ----- memory managment -----

SInfinitBigInt& SInfinitBigInt::operator= (const SInfinitBigInt& other) {
	// check for self-assignment
	if(&other == this) {
		return *this;
	}
	
	BigInt::operator=(other);
	this->signum = other.signum;
	
	return *this;
}

// ----- bit utilities -----

int SInfinitBigInt::bitLength() const {
	return BigInt::bitLength();
}

void SInfinitBigInt::setZero() {
	BigInt::setZero();
	this->signum = 0;
}

void SInfinitBigInt::setOne() {
	BigInt::setOne();
	this->signum = +1;
}

void SInfinitBigInt::setAbs() {
	this->signum = this->signum * this->signum;
}

void SInfinitBigInt::setNegate() {
	this->signum = this->signum * -1;
}

bool SInfinitBigInt::isMagnitudeZero() const {
	return BigInt::isZero();
}

bool SInfinitBigInt::isMagnitudeOne() const {
	return BigInt::isOne();
}

bool SInfinitBigInt::isZero() const {
	return this->signum == 0;
}

bool SInfinitBigInt::isOne() const {
	if(this->signum <= 0) {
		return false;
	}
	return BigInt::isOne();
}

// ----- shift left -----
BIG_INT_WORD_TYPE SInfinitBigInt::rcl(const uint bits, const BIG_INT_WORD_TYPE c, const bool resize) {
	return BigInt::rcl(bits, c, resize);
}

SInfinitBigInt SInfinitBigInt::operator<< (const uint bits) const {
	// copy tha magnitude array 2 times
	//return SInfinitBigInt(BigInt::operator<<(bits), this->signum < 0);
	
	// copy the magnitude array only once
	SInfinitBigInt res(*this);
	res.rcl(bits, 0, true);
	return res;
}

// ----- shift right -----
BIG_INT_WORD_TYPE SInfinitBigInt::rcr(const uint bits, const BIG_INT_WORD_TYPE c) {
	return BigInt::rcr(bits, c);
}

SInfinitBigInt SInfinitBigInt::operator>> (const uint bits) const {
	// copy tha magnitude array 2 times
	//return SInfinitBigInt(BigInt::operator>>(bits), this->signum < 0);
	
	// copy the magnitude array only once
	SInfinitBigInt res(*this);
	res.rcr(bits, 0);
	if(res.isMagnitudeZero()) {
		res.signum = 0;
	}
	return res;
}

// ----- addition -----

void SInfinitBigInt::add(const SInfinitBigInt &other, SInfinitBigInt &result) const {
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
		BigInt::add(other, result);
		result.signum = +1;
		return;
	}
	if(this->signum < 0 && other.signum < 0) {
		// -x + -y = -(+x + +y)
		BigInt::add(other, result);
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
	
	std::string msg = "ERROR add SInfinitBigInt unexpected case!";
	std::cerr << msg << std::endl;
	throw std::runtime_error(msg);
}

void SInfinitBigInt::add(const SInfinitBigInt &other) {
	this->add(other, *this);
}

SInfinitBigInt SInfinitBigInt::operator+ (const SInfinitBigInt& other) const {
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->getWordSize(), other.getWordSize());
	SInfinitBigInt result(0, maxWordCount+1);
	this->add(other, result);
	return result;
}

// ----- substraction -----
BIG_INT_WORD_TYPE SInfinitBigInt::subInfUInt(const SInfinitBigInt& b, SInfinitBigInt& restul) const {
	return BigInt::sub(b, 0, restul);
}

void SInfinitBigInt::subAsPositive(const SInfinitBigInt& a, const SInfinitBigInt& b, SInfinitBigInt& restul) const {
	// more readable version but requires a comparision of the magnitudes and therfore two casts.... probably slow
	
	//if( (BigInt)b < (BigInt)a ) { // only compare the magnitude
	if(static_cast<const BigInt&>(b) < static_cast<const BigInt&>(a)  ) { // only compare the magnitude (ignore the sign); static_cast<const BigInt&>(X): cast without calling the copy constructor
		//restul = SInfinitBigInt(a - b, false);
		a.subInfUInt(b, restul);
		restul.signum = restul.isMagnitudeZero() ? 0 : +1;
	} else {
		//restul = SInfinitBigInt(b - a, true);
		b.subInfUInt(a, restul);
		restul.signum = restul.isMagnitudeZero() ? 0 : -1;
	}
	
}

void SInfinitBigInt::sub(const SInfinitBigInt& other, SInfinitBigInt &result) const {
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
		BigInt::add(other, result);
		result.signum = +1;
		return;
	}
	
	if(this->signum < 0 && other.signum > 0) {
		// -a - +b = -(+a + +b)
		BigInt::add(other, result);
		result.signum = -1;
		return;
	}
	
	std::string msg = "ERROR substract SInfinitBigInt unexpected case!";
	std::cerr << msg << std::endl;
	throw std::runtime_error(msg);
}

void SInfinitBigInt::sub(const SInfinitBigInt& other) {
	this->sub(other, *this);
}

SInfinitBigInt SInfinitBigInt::operator- (const SInfinitBigInt& other) const {
	SInfinitBigInt result(0, this->getWordSize());
	this->sub(other, result);
	return result;
}

// ----- multiplication -----

void SInfinitBigInt::mul(const SInfinitBigInt& b, SInfinitBigInt& result) const {
	if(this->isZero() || b.isZero()) {
		result.setZero();
		return;
	}
	
	BigInt::mul(b, result);
	result.signum = ((this->signum < 0) ^ (b.signum < 0)) ? -1 : +1;
}

void SInfinitBigInt::mul(const SInfinitBigInt& b) {
	SInfinitBigInt result = BigInt(0, this->getWordSize() + b.getWordSize());
	this->mul(b, result);
	*this = result;
}

SInfinitBigInt SInfinitBigInt::operator* (const SInfinitBigInt& other) const {
	SInfinitBigInt result = BigInt(0, this->getWordSize() + other.getWordSize());
	this->mul(other, result);
	return result;
}

SInfinitBigInt SInfinitBigInt::operator/ (const SInfinitBigInt& other) const {
	SInfinitBigInt res(BigInt::operator/(other), (this->signum < 0) ^ (other.signum < 0) );
	//if(res.isZero()) {
	//	res.signum = 0;
	//}
	return res;
}

SInfinitBigInt SInfinitBigInt::operator% (const SInfinitBigInt& other) const {
	SInfinitBigInt res(BigInt::operator%(other), false);
	
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
			std::string msg = "ERROR mod SInfinitBigInt unexpected case!";
			std::cerr << msg << std::endl;
			throw std::runtime_error(msg);
		}
	}
	return res;
}

SInfinitBigInt SInfinitBigInt::pow(SInfinitBigInt pow) const {
	return SInfinitBigInt(BigInt::pow(pow), pow.isOdd() && this->signum < 0);
}

SInfinitBigInt SInfinitBigInt::sqrt() const {
	if (this->signum <= 0) {
		//throw new ArithmeticException("BigInteger: modulus not positive");
		std::string msg = "ERROR SInfinitBigInt: can not claculate sqrt from negative number (no imaginary suport)!";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	
	return SInfinitBigInt(BigInt::sqrt(), false);
}

/* ---------- modInverse / gcd ---------- */
/**
 * Returns a BigInteger whose value is {@code (this}<sup>-1</sup> {@code mod m)}.
 *
 * @param  m the modulus.
 * @return {@code this}<sup>-1</sup> {@code mod m}.
 * @throws ArithmeticException {@code  m} &le; 0, or this BigInteger
 *         has no multiplicative inverse mod m (that is, this BigInteger
 *         is not <i>relatively prime</i> to m).
 */
SInfinitBigInt SInfinitBigInt::modInverse(const SInfinitBigInt & m) const {
	if (m.isZero()) {
		std::string msg = "ERROR BigInt: modulus not positive!";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	
	if (m.isOne()) {
		return SInfinitBigInt(0);
	}
	
	// all the hard work will be done by gcd.
	SInfinitBigInt u, v;
	SInfinitBigInt gcd = this->gcdExtended(*this, m, u, v);
	if(!gcd.isOne()) {
		std::string msg = "ERROR BigInt: " + this->toStringDec() + " does not have a multiplicative inverse mod " + m.toStringDec() + " becaus the numbers are not relatively prime to!";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	
	//if (u < 0) {
	//	u = u + m;
	//}
	return u % m;
}

/**
 * Function for extended Euclidean Algorithm
 * return gcd of b and a.
 *  also returns the Bézout coefficients, u and v, which satisfy: a.*u + b.*v = gcd.
 *	The Bézout coefficients are useful for solving Diophantine equations.
 * https://www.mathworks.com/help/matlab/ref/gcd.html
 * https://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/
 */
SInfinitBigInt SInfinitBigInt::gcdExtended(const SInfinitBigInt &a, const SInfinitBigInt &b, SInfinitBigInt &u, SInfinitBigInt &v) const {
	// https://math.stackexchange.com/questions/37806/extended-euclidean-algorithm-with-negative-numbers
	//  |𝑎|𝑥+|𝑏|𝑦=1 => 𝑎(sign(𝑎)⋅𝑥)+𝑏(sign(𝑏)⋅𝑦)=1.
	
	// Implementing the Extended Euclidean Algorithm with Unsigned Inputs
	// https://jeffhurchalla.com/2018/10/13/implementing-the-extended-euclidean-algorithm-with-unsigned-inputs/
	
	int_fast8_t signumA = a.signum;
	int_fast8_t signumB = b.signum;
	
	SInfinitBigInt absA = a;
	SInfinitBigInt absB = b;
	absA.setAbs();
	absB.setAbs();
	
	//SInfinitBigInt gcd = this->gcdExtended_internRecursive(absA, absB, u, v);
	SInfinitBigInt gcd = this->gcdExtended_internIterative(absA, absB, u, v);
	
	u.signum = u.signum * signumA;
	v.signum = v.signum * signumB;
	
	assert((a*u + b*v) == gcd);
	
	return gcd;
}

SInfinitBigInt SInfinitBigInt::gcdExtended_internRecursive(const SInfinitBigInt &a, const SInfinitBigInt &b, SInfinitBigInt &u, SInfinitBigInt &v) const {
	// Base Case
	if (a.isZero()) {
		u.setZero();
		v.setOne();
		return b;
	}
	
	SInfinitBigInt u1(0, u.getWordSize()), v1(0, v.getWordSize()); // To store results of recursive call
	SInfinitBigInt gcd = gcdExtended(b % a, a, u1, v1);
	
	// Update u and v using results of recursive call
	u = v1 - (b/a) * u1;
	v = u1;
	
	return gcd;
}

SInfinitBigInt SInfinitBigInt::gcdExtended_internIterative(const SInfinitBigInt &a, const SInfinitBigInt &b, SInfinitBigInt &u, SInfinitBigInt &v) const {
	// https://rosettacode.org/wiki/Modular_inverse#C.2B.2B
	
	// https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
	/*
	u.setOne();
	v.setZero();
	SInfinitBigInt u1(0), v1(1), a1(a), b1(b);
	while (!b1.isZero()) {
		SInfinitBigInt q = a1 / b1;
		//tie(u, u1) = make_tuple(u1, u - q * u1);
		u = u1, u1 = u - q * u1;
		//tie(v, v1) = make_tuple(v1, v - q * v1);
		v = v1, v1 = v - q * v1;
		//tie(a1, b1) = make_tuple(b1, a1 - q * b1);
		a1 = b1, b1 = a1 - q * b1;
		
		assert((a*u  + b*v ) == SInfinitBigInt(a1));
		assert((a*u1 + b*v1) == SInfinitBigInt(b1));
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
	SInfinitBigInt unCur(0);
	SInfinitBigInt vnCur(1);
	SInfinitBigInt a1(a);
	SInfinitBigInt b1(b);
	
	SInfinitBigInt q, newB, unNew, vnNew;
		
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

/**
 * Basic Euclidean Algorithm
 * returns the gcd of a and b
 */
SInfinitBigInt SInfinitBigInt::gcd(const SInfinitBigInt & a, const SInfinitBigInt & b) const {
	if (a.isZero()) {
		return b;
	}
	return gcd(b % a, a);
}

/* ---------- modPow ---------- */


/**
 * Returns a BigInteger whose value is
 * <code>(this<sup>exponent</sup> mod m)</code>.  (Unlike {@code pow}, this
 * method permits negative exponents.)
 *
 * @param  exponent the exponent.
 * @param  m the modulus.
 * @return <code>this<sup>exponent</sup> mod m</code>
 * @throws ArithmeticException {@code m} &le; 0 or the exponent is
 *         negative and this BigInteger is not <i>relatively
 *         prime</i> to {@code m}.
 * @see    #modInverse
 */
SInfinitBigInt SInfinitBigInt::modPow(const SInfinitBigInt &exponent, const SInfinitBigInt &m) const {
	if (m.signum <= 0) {
		//throw new ArithmeticException("BigInteger: modulus not positive");
		std::string msg = "ERROR SInfinitBigInt: modulus not positive!";
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
	
	// Trivial cases: exponent = 0
	if (exponent.isZero()) {
		return (m.isOne() ? SInfinitBigInt(0) : SInfinitBigInt(1));
	}
	
	// Trivial cases: base = 1
	if (this->isOne()) {
		return (m.isOne() ? SInfinitBigInt(0) : SInfinitBigInt(1));
	}
	
	// Trivial cases: base = 0
	if (this->isZero() &&  exponent.signum >= 0) {
		return SInfinitBigInt(0);
	}
	
	// Trivial cases: base = -1 && (exponent % 2 = 0)
	if (*this == SInfinitBigInt(1, true) && exponent.isEven()) {
		return (m.isOne() ? SInfinitBigInt(0) : SInfinitBigInt(1));
	}
	
	
	return this->modPow_naiv(exponent, m);
	
	// faster version from java BigInt ....
	/*
	bool invertResult = exponent.signum < 0;
	SInfinitBigInt absExponent(exponent); // TODO performance, unessesery copy if exponent is positive
	if (invertResult) {
		absExponent.setAbs();
	}
	
	//BigInteger base = (this.signum < 0 || this.compareTo(m) >= 0
	//				   ? this.mod(m) : this);
	SInfinitBigInt base = (this->signum < 0 || *this >= m) ? *this % m : *this;
	
	SInfinitBigInt result(0);
	if(m.isOdd()) { // odd modulus
		result = base.oddModPow(exponent, m);
	} else {
		/*
		 * Even modulus.  Tear it into an "odd part" (m1) and power of two
		 * (m2), exponentiate mod m1, manually exponentiate mod m2, and
		 * use Chinese Remainder Theorem to combine results.
		 * /
		
		// Tear m apart into odd part (m1) and power of 2 (m2)
		int p = m.findLowestSetBit();   // Max pow of 2 that divides m
		
		//BigInteger m1 = m .shiftRight(p);  // m/2**p
		SInfinitBigInt m1 = m >> p; // m/2**p
		//BigInteger m2 = ONE.shiftLeft(p); // 2**p
		SInfinitBigInt m2 = SInfinitBigInt(1) << p; // 2**p
		
		// Calculate new base from m1
		//BigInteger base2 = (this.signum < 0 || this.compareTo(m1) >= 0 ? this.mod(m1) : this);
		SInfinitBigInt base2 = (this->signum < 0 || *this >= m1) ? *this % m1 : *this;
		
		// Caculate (base ** exponent) mod m1.
		//BigInteger a1 = (m1.equals(ONE) ? ZERO : base2.oddModPow(exponent, m1));
		SInfinitBigInt a1 = m1.isOne() ? BigInt(0) : base2.oddModPow(exponent, m1);
		
		// Calculate (this ** exponent) mod m2
		SInfinitBigInt a2 = base.modPow2(exponent, p);
		
		// Combine results using Chinese Remainder Theorem
		SInfinitBigInt y1 = m2.modInverse(m1);
		SInfinitBigInt y2 = m1.modInverse(m2);
		
		//if (m.mag.length < MAX_MAG_LENGTH / 2) {
			// result = a1.multiply(m2).multiply(y1).add(a2.multiply(m1).multiply(y2)).mod(m);
			result = (a1 * m2 * y1 + a2 * m1 * y2) % m;
		//} else {
		//	MutableBigInteger t1 = new MutableBigInteger();
		//	new MutableBigInteger(a1.multiply(m2)).multiply(new MutableBigInteger(y1), t1);
		//	MutableBigInteger t2 = new MutableBigInteger();
		//	new MutableBigInteger(a2.multiply(m1)).multiply(new MutableBigInteger(y2), t2);
		//	t1.add(t2);
		//	MutableBigInteger q = new MutableBigInteger();
		//	result = t1.divide(new MutableBigInteger(m), q).toBigInteger();
		//}
	}
	
	return (invertResult ? result.modInverse(m) : result);
	 */
}

SInfinitBigInt SInfinitBigInt::modPow_naiv(const SInfinitBigInt &exponent, const BigInt &modulus) const {
	if(modulus.BigInt::isOne()) {
		return SInfinitBigInt(1);
	}
	
	//Assert :: (modulus - 1) * (modulus - 1) does not overflow base
	
	// ensure that the base is < modulus
	SInfinitBigInt base = (this->signum < 0 || *this >= modulus) ? (*this % modulus) : *this;
	
	bool invertResult = exponent.signum < 0;
	SInfinitBigInt absExponent(exponent);
	if (invertResult) {
		absExponent.setAbs();
	}
	
	SInfinitBigInt result(1);
	while ( !absExponent.isZero() > 0) {
		if (absExponent.isOdd()) {
			result = (result * base) % modulus;
		}
		absExponent = absExponent >> 1;
		base = base.pow(2) % modulus;
	}
	
	return (invertResult ? result.modInverse(modulus) : result);
}

/**
 * Returns a BigInteger whose value is (this ** exponent) mod (2**p)
 * /
SInfinitBigInt SInfinitBigInt::modPow2(SInfinitBigInt exponent, int p) const {
	/*
	 * Perform exponentiation using repeated squaring trick, chopping off
	 * high order bits as indicated by modulus.
	 * /
	SInfinitBigInt result(1);
	SInfinitBigInt baseToPow2 = this->mod2(p);
	int expOffset = 0;
	
	int limit = exponent.bitLength();
	
	if (this->testBit(0)) {
		limit = (p-1) < limit ? (p-1) : limit;
	}
	
	while (expOffset < limit) {
		if (exponent.testBit(expOffset)) {
			//result = result.multiply(baseToPow2).mod2(p);
			result = (result * baseToPow2).mod2(p);
		}
		expOffset++;
		if (expOffset < limit) {
			baseToPow2 = baseToPow2.sqrt().mod2(p);
		}
	}
	
	return result;
}

/**
 * Returns a BigInteger whose value is this mod(2**p).
 * Assumes that this {@code BigInteger >= 0} and {@code p > 0}.
 * /
SInfinitBigInt SInfinitBigInt::mod2(int p) const {
	if (this->bitLength() <= p) {
		return *this;
	}
	
	// simple but slow!
	BigInt q = *this >> p; // q = this / 2**p
	return *this - q;
	
	// TODO performance! can be done by bitshifting and masking only!
	/*
	 // Copy remaining ints of mag
	 int numInts = (p + 31) >>> 5;
	 int[] mag = new int[numInts];
	 System.arraycopy(this.mag, (this.mag.length - numInts), mag, 0, numInts);
	 
	 // Mask out any excess bits
	 int excessBits = (numInts << 5) - p;
	 mag[0] &= (1L << (32-excessBits)) - 1;
	 
	 return (mag[0] == 0 ? new BigInteger(1, mag) : new BigInteger(mag, 1));
	 * /
}
*/


/* ---------- comparisons ---------- */
bool SInfinitBigInt::operator< (const SInfinitBigInt& other) const {
	if(this->signum < other.signum) {
		return true;
	}
	
	if(this->signum > other.signum) {
		return false;
	}
	
	return BigInt::operator<(other);
}

bool SInfinitBigInt::operator<= (const SInfinitBigInt& other) const {
	if (*this < other) {
		return true;
	}
	
	if (*this == other) {
		return true;
	}
	
	return false;
}

bool SInfinitBigInt::operator> (const SInfinitBigInt& other) const {
	return (!(*this <= other));
}

bool SInfinitBigInt::operator>= (const SInfinitBigInt& other) const {
	return (!(*this < other));
}

bool SInfinitBigInt::operator== (const SInfinitBigInt& other) const {
	if (*this < other) {
		return false;
	}
	
	if (other < *this) {
		return false;
	}
	
	return true;
}

bool SInfinitBigInt::operator!= (const SInfinitBigInt& other) const {
	return (!(*this == other));
}

