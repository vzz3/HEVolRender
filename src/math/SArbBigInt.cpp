
#include "SArbBigInt.hpp"
#include <cassert>
#include <iostream>
#include <algorithm> // required for std::find_if (trim tring)

using namespace ppvr::math;

// ----- statics -----

const SArbBigInt SArbBigInt::SmallPrimeProduct = SArbBigInt::fromUint64(3L*5*7*11*13*17*19*23*29*31*37*41);

// Pre generated primes
const SArbBigInt SArbBigInt::FirstPrimes[] = {
	SArbBigInt::fromInt64(  2), SArbBigInt::fromInt64(  3), SArbBigInt::fromInt64(  5),
	SArbBigInt::fromInt64(  7), SArbBigInt::fromInt64( 11), SArbBigInt::fromInt64( 13),
	SArbBigInt::fromInt64( 17), SArbBigInt::fromInt64( 19), SArbBigInt::fromInt64( 23),
	SArbBigInt::fromInt64( 29), SArbBigInt::fromInt64( 31), SArbBigInt::fromInt64( 37),
	SArbBigInt::fromInt64( 41), SArbBigInt::fromInt64( 43), SArbBigInt::fromInt64( 47),
	SArbBigInt::fromInt64( 53), SArbBigInt::fromInt64( 59), SArbBigInt::fromInt64( 61),
	SArbBigInt::fromInt64( 67), SArbBigInt::fromInt64( 71), SArbBigInt::fromInt64( 73),
	SArbBigInt::fromInt64( 79), SArbBigInt::fromInt64( 83), SArbBigInt::fromInt64( 89),
	SArbBigInt::fromInt64( 97), SArbBigInt::fromInt64(101), SArbBigInt::fromInt64(103),
	SArbBigInt::fromInt64(107), SArbBigInt::fromInt64(109), SArbBigInt::fromInt64(113),
	SArbBigInt::fromInt64(127), SArbBigInt::fromInt64(131), SArbBigInt::fromInt64(137),
	SArbBigInt::fromInt64(139), SArbBigInt::fromInt64(149), SArbBigInt::fromInt64(151),
	SArbBigInt::fromInt64(157), SArbBigInt::fromInt64(163), SArbBigInt::fromInt64(167),
	SArbBigInt::fromInt64(173), SArbBigInt::fromInt64(179), SArbBigInt::fromInt64(181),
	SArbBigInt::fromInt64(191), SArbBigInt::fromInt64(193), SArbBigInt::fromInt64(197),
	SArbBigInt::fromInt64(199), SArbBigInt::fromInt64(211), SArbBigInt::fromInt64(223),
	SArbBigInt::fromInt64(227), SArbBigInt::fromInt64(229), SArbBigInt::fromInt64(233),
	SArbBigInt::fromInt64(239), SArbBigInt::fromInt64(241), SArbBigInt::fromInt64(251),
	SArbBigInt::fromInt64(257), SArbBigInt::fromInt64(263), SArbBigInt::fromInt64(269),
	SArbBigInt::fromInt64(271), SArbBigInt::fromInt64(277), SArbBigInt::fromInt64(281),
	SArbBigInt::fromInt64(283), SArbBigInt::fromInt64(293), SArbBigInt::fromInt64(307),
	SArbBigInt::fromInt64(311), SArbBigInt::fromInt64(313), SArbBigInt::fromInt64(317),
	SArbBigInt::fromInt64(331), SArbBigInt::fromInt64(337), SArbBigInt::fromInt64(347),
	SArbBigInt::fromInt64(349)
};

SArbBigInt SArbBigInt::fromInt64(const int64_t& int64Val) {
	SArbBigInt res(0);
	SArbBigInt::fromInt64(int64Val, res);
	return res;
}

SArbBigInt& SArbBigInt::fromInt64(const int64_t& int64Val, SArbBigInt &target ) {
	UArbBigInt::fromUint64(std::abs(int64Val), target);
	if(target.isMagnitudeZero()) {
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

SArbBigInt SArbBigInt::fromString(const std::string& str, const BIG_INT_WORD_TYPE base) {
	SArbBigInt res(0);
	SArbBigInt::fromString(str, base, res);
	return res;
}

SArbBigInt& SArbBigInt::fromString(std::string str, const BIG_INT_WORD_TYPE base, SArbBigInt &target ) {
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
	UArbBigInt::fromString(str, base, target);

	// set sign
	if( target.isMagnitudeZero() ) {
		target.signum = 0;
	} else {
		target.signum = negative ? -1 : +1;
	}

	return target;
}

SArbBigInt SArbBigInt::randomNumber(const uint& sizeInBit, Random& rnd) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BIG_INT_REQUIRED_WORDS(sizeInBit);
	SArbBigInt res(0, requiredWords);
	SArbBigInt::randomNumber(sizeInBit, rnd, res);
	return res;
}

SArbBigInt SArbBigInt::randomNumber(const SArbBigInt& upperBound, Random& rnd) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BIG_INT_REQUIRED_WORDS(upperBound.bitLength());
	SArbBigInt res(0, requiredWords);
	SArbBigInt::randomNumber(upperBound, rnd, res);
	return res;
}

SArbBigInt& SArbBigInt::randomNumber(const uint& sizeInBit, Random& rnd, SArbBigInt &target) {
	UArbBigInt::randomNumber(sizeInBit, rnd, target);
	if(target.isMagnitudeZero()) {
		target.signum = 0;
	} else {
		target.signum = 1;
	}
	return target;
}

SArbBigInt& SArbBigInt::randomNumber(const SArbBigInt& upperBound, Random& rnd, SArbBigInt &target) {
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



SArbBigInt SArbBigInt::probablePrime(const uint& bitLength, Random& rnd) {
	if (bitLength < 2) {
		std::string msg = "ERROR probablePrime: bitLength < 2";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	return (bitLength < BIG_INT_SMALL_PRIME_THRESHOLD ?
			smallPrime(bitLength, BIG_INT_DEFAULT_PRIME_CERTAINTY, rnd) :
			largePrime(bitLength, BIG_INT_DEFAULT_PRIME_CERTAINTY, rnd)
			);
}

SArbBigInt SArbBigInt::smallPrime(const uint& bitLength, const uint& certainty, Random& rnd) {
	// Algorithm and comments adapted from Java java.math.BigInteger

	/*
	 uint magLen = (bitLength + 31) >> 5;
	 uint temp[magLen];
	 uint highBit = 1 << ((bitLength+31) & 0x1f);  // High bit of high int
	 uint highMask = (highBit << 1) - 1;  // Bits to keep in high int

	 while (true) {
	 // Construct a candidate
	 for (int i=0; i < magLen; i++) {
	 temp[i] = rnd.nextInt();
	 }
	 temp[0] = (temp[0] & highMask) | highBit;  // Ensure exact length
	 if (bitLength > 2)
	 temp[magLen-1] |= 1;  // Make odd if bitlen > 2

	 BigInteger p = new BigInteger(temp, 1);

	 // Do cheap "pre-test" if applicable
	 if (bitLength > 6) {
	 long r = p.remainder(SMALL_PRIME_PRODUCT).longValue();
	 if ((r%3==0)  || (r%5==0)  || (r%7==0)  || (r%11==0) ||
	 (r%13==0) || (r%17==0) || (r%19==0) || (r%23==0) ||
	 (r%29==0) || (r%31==0) || (r%37==0) || (r%41==0))
	 continue; // Candidate is composite; try another
	 }

	 // All candidates of bitLength 2 and 3 are prime by this point
	 if (bitLength < 4)
	 return p;

	 // Do expensive test if we survive pre-test (or it's inapplicable)
	 if (p.primeToCertainty(certainty, rnd))
	 return p;
	 }
	 */

	BIG_INT_WORD_COUNT_TYPE requiredWords = BIG_INT_REQUIRED_WORDS(bitLength);
	SArbBigInt p(0, requiredWords);

	while (true) {
		SArbBigInt::randomNumber(bitLength, rnd, p);
		p.setBit(bitLength-1); // Ensure exact length

		if (bitLength > 2) {
			p.setBit(0); //p.value[0] |= 1;  // Make odd if bitlen > 2
		}

		// Do cheap "pre-test" if applicable
		if (bitLength > 6) {
			int64_t r = (p % SArbBigInt::SmallPrimeProduct).toUint64();
			if ((r%3==0)  || (r%5==0)  || (r%7==0)  || (r%11==0) ||
				(r%13==0) || (r%17==0) || (r%19==0) || (r%23==0) ||
				(r%29==0) || (r%31==0) || (r%37==0) || (r%41==0))
			continue; // Candidate is composite; try another
		}

		// All candidates of bitLength 2 and 3 are prime by this point
		if (bitLength < 4) {
			return p;
		}

		// Do expensive test if we survive pre-test (or it's inapplicable)
		if (p.primeToCertainty(certainty, rnd)) {
			return p;
		}
	}
}

SArbBigInt SArbBigInt::largePrime(const uint& bitLength, const uint& certainty, Random& rnd) {
	// A search with a BitSieve is  faster. (The java BigInt class uses such a surch algorithem.)
	// However, a test for random numers should do it for the moment (it is simpler to implement).
	// https://stackoverflow.com/questions/13665443/generate-random-prime-number-in-c-c-between-2-limits
	// https://crypto.stackexchange.com/questions/1812/how-to-better-generate-large-primes-sieving-and-then-random-picking-or-random-p

	// Algorithm and comments adapted from https://www.geeksforgeeks.org/how-to-generate-large-prime-numbers-for-rsa-algorithm/
	SArbBigInt primeCandidate(0, BIG_INT_REQUIRED_WORDS(bitLength));
	while(true) {
		SArbBigInt::lowLevelPrime(bitLength, rnd, primeCandidate);
		if (primeCandidate.primeToCertainty(certainty, rnd)) {
			return primeCandidate;
		}
	}
}

void SArbBigInt::lowLevelPrime(const uint& bitLength, Random& rnd, SArbBigInt &target) {
	// Algorithm and comments adapted from https://www.geeksforgeeks.org/how-to-generate-large-prime-numbers-for-rsa-algorithm/
	// Generate a prime candidate divisible by first primes
	bool isLowLevelPrime(false);
	while(!isLowLevelPrime) {
		// Obtain a random number
		SArbBigInt::randomNumber(bitLength, rnd, target);

		// Test divisibility by pre-generated primes
		isLowLevelPrime = true;
		for(SArbBigInt divisor : SArbBigInt::FirstPrimes) {
			if ((target % divisor).isZero() && divisor.pow(2) <= target) {
				isLowLevelPrime = false;
				break; // early exit
			}
		}
	}
}

bool SArbBigInt::primeToCertainty(const uint certainty, Random& rnd) {
	// Algorithm and comments adapted from Java java.math.BigInteger

	uint rounds = 0;
	uint n = (std::min(certainty, uint(-1ll)-1)+1)/2;

	// The relationship between the certainty and the number of rounds
	// we perform is given in the draft standard ANSI X9.80, "PRIME
	// NUMBER GENERATION, PRIMALITY TESTING, AND PRIMALITY CERTIFICATES".
	uint sizeInBits = this->bitLength();
	if (sizeInBits < 100) {
		rounds = 50;
		rounds = n < rounds ? n : rounds;
		return passesMillerRabin(rounds, rnd);
	}

	if (sizeInBits < 256) {
		rounds = 27;
	} else if (sizeInBits < 512) {
		rounds = 15;
	} else if (sizeInBits < 768) {
		rounds = 8;
	} else if (sizeInBits < 1024) {
		rounds = 4;
	} else {
		rounds = 2;
	}
	rounds = n < rounds ? n : rounds;

	return passesMillerRabin(rounds, rnd) && passesLucasLehmer();
}

bool SArbBigInt::passesLucasLehmer() {
	// Algorithm and comments adapted from Java java.math.BigInteger

	SArbBigInt thisPlusOne= *this + UArbBigInt::ONE;

	// Step 1
	int d = 5;
	while (jacobiSymbol(d, *this) != -1) {
		// 5, -7, 9, -11, ...
		d = (d < 0) ? std::abs(d)+2 : -(d+2);
	}

	// Step 2
	SArbBigInt u = lucasLehmerSequence(d, thisPlusOne, *this);

	// Step 3
	return (u % *this).isZero();
}

int SArbBigInt::jacobiSymbol(int16_t p, const SArbBigInt& n) {
	if (p == 0) {
		return 0;
	}

	// Algorithm and comments adapted from Colin Plumb's C library.
	// https://github.com/wernerd/ZRTPCPP/blob/master/bnlib/jacobi.c

	int j = 1;
	BIG_INT_WORD_TYPE u = n.getLeastSignificantWord();

	// Make p positive
	if (p < 0) {
		p = -p;
		int n8 = u & 7;
		if ((n8 == 3) || (n8 == 7))
		j = -j; // 3 (011) or 7 (111) mod 8
	}

	// Get rid of factors of 2 in p
	while ((p & 3) == 0) {
		p >>= 2;
	}
	if ((p & 1) == 0) {
		p >>= 1;
		if (((u ^ (u>>1)) & 2) != 0) {
			j = -j; // 3 (011) or 5 (101) mod 8
		}
	}
	if (p == 1) {
		return j;
	}
	// Then, apply quadratic reciprocity
	if ((p & u & 2) != 0) {   // p = u = 3 (mod 4)?
		j = -j;
	}
	// And reduce u mod p
	//u = n.mod(BigInteger.valueOf(p)).intValue();
	u = (n % SArbBigInt(p)).getLeastSignificantWord(); // getLeastSignificantWord() is save because p must fit into BIG_INT_WORD_TYPE and therfore the reminder of X/p must fit into BIG_INT_WORD_TYPE.

	// Now compute Jacobi(u,p), u < p
	while (u != 0) {
		while ((u & 3) == 0) {
			u >>= 2;
		}
		if ((u & 1) == 0) {
			u >>= 1;
			if (((p ^ (p>>1)) & 2) != 0) {
				j = -j;     // 3 (011) or 5 (101) mod 8
			}
		}
		if (u == 1) {
			return j;
		}
		// Now both u and p are odd, so use quadratic reciprocity
		assert (u < p);
		BIG_INT_WORD_TYPE t = u; u = p; p = t;
		if ((u & p & 2) != 0) { // u = p = 3 (mod 4)?
			j = -j;
		}
		// Now u >= p, so it can be reduced
		u %= p;
	}
	return 0;
}

SArbBigInt SArbBigInt::lucasLehmerSequence(int z, const SArbBigInt& k, const SArbBigInt& n) {
	// Algorithm and comments adapted from Java java.math.BigInteger

	SArbBigInt d = SArbBigInt::fromInt64(z);
	SArbBigInt u = ONE; SArbBigInt u2;
	SArbBigInt v = ONE; SArbBigInt v2;

	for (int i=k.bitLength()-2; i >= 0; i--) {
		u2 = (u * v) % n;

		v2 = (v.pow(2) + (d * u.pow(2))) % n;
		if (v2.testBit(0))
		v2 = v2 - n;

		v2 = v2 >> 1;

		u = u2; v = v2;
		if (k.testBit(i)) {
			u2 = (u + v) % n;
			if (u2.testBit(0)) {
				u2 = u2 - n;
			}

			u2 = u2 >> 1;
			v2 = ( v + (d * u)) % n;
			if (v2.testBit(0)) {
				v2 = v2 - n;
			}
			v2 = v2 >> 1;

			u = u2; v = v2;
		}
	}
	return u;
}

bool SArbBigInt::passesMillerRabin(int iterations, Random& rnd) {
	// Algorithm and comments adapted from Java java.math.BigInteger

	// Find a and m such that m is odd and this == 1 + 2**a * m
	SArbBigInt thisMinusOne = *this - UArbBigInt::ONE;
	SArbBigInt m = thisMinusOne;
	int a = m.findLowestSetBit();
	m = m >> a;

	// Do the tests
	//if (rnd == null) {
	//	rnd = ThreadLocalRandom.current();
	//}
	for (int i=0; i < iterations; i++) {
		// Generate a uniform random on (1, this)
		SArbBigInt b(0, this->getWordSize());
		do {
			SArbBigInt::randomNumber(this->bitLength(), rnd, b);
		} while (b <= SArbBigInt::ONE || b >= *this);

		int j = 0;
		SArbBigInt z = b.modPow(m, *this);
		while (!((j == 0 && z.isOne()) || z == thisMinusOne)) {
			if ((j > 0 && z.isOne()) || ++j == a) {
				return false;
			}
			z = z.modPow(TWO, *this);
		}
	}
	return true;
}

bool SArbBigInt::isProbablePrime(const uint certainty, Random& rnd) {
	// Algorithm and comments adapted from Java java.math.BigInteger
	if (certainty <= 0) {
		return true;
	}
	SArbBigInt w(*this); w.setAbs(); // TODO Speed: is this copy of the magnitud realy required? is it ok to set and reset just the signum?
	if (w == TWO) {
		return true;
	}
	if (!w.testBit(0) || w.isOne()) {
		return false;
	}

	return w.primeToCertainty(certainty, rnd);
}



// ----- constructors -----

SArbBigInt::SArbBigInt(): SArbBigInt(0, 0, false) {}

SArbBigInt::SArbBigInt(const BIG_INT_WORD_TYPE& value, bool negative): SArbBigInt(value, 0, negative) {}

SArbBigInt::SArbBigInt(const BIG_INT_WORD_TYPE& value, BIG_INT_WORD_COUNT_TYPE minCapacity, bool negative): UArbBigInt(value, minCapacity) {
	if(UArbBigInt::isZero()) {
		this->signum = 0;
	} else if(negative) {
		this->signum = -1;
	} else {
		this->signum = +1;
	}
}

SArbBigInt::SArbBigInt(const UArbBigInt& value, bool negative): UArbBigInt(value) {
	if(UArbBigInt::isZero()) {
		this->signum = 0;
	} else if(negative) {
		this->signum = -1;
	} else {
		this->signum = +1;
	}
}

SArbBigInt::SArbBigInt(const SArbBigInt& value): UArbBigInt(value), signum(value.signum) {}

SArbBigInt::~SArbBigInt() {

}

// ----- value export - toString / toUint64 -----

int64_t SArbBigInt::toInt64() const {
	int64_t res = UArbBigInt::toUint64();
	if(this->signum < 0) {
		res *= -1;
	}
	return res;
}

std::string SArbBigInt::toStringHex() const {
	std::string res = UArbBigInt::toStringHex();
	if(this->signum < 0) {
		res = "-" + res;
	}
	return res;
}

std::string SArbBigInt::toStringDec() const {
	std::string res = UArbBigInt::toStringDec();
	if(this->signum < 0) {
		res = "-" + res;
	}
	return res;
}

// ----- memory managment -----

SArbBigInt& SArbBigInt::operator= (const SArbBigInt& other) {
	// check for self-assignment
	if(&other == this) {
		return *this;
	}

	UArbBigInt::operator=(other);
	this->signum = other.signum;

	return *this;
}

// ----- bit utilities -----

int SArbBigInt::bitLength() const {
	return UArbBigInt::bitLength();
}

void SArbBigInt::setZero() {
	UArbBigInt::setZero();
	this->signum = 0;
}

void SArbBigInt::setOne() {
	UArbBigInt::setOne();
	this->signum = +1;
}

void SArbBigInt::setAbs() {
	this->signum = this->signum * this->signum;
}

void SArbBigInt::setNegate() {
	this->signum = this->signum * -1;
}

bool SArbBigInt::isMagnitudeZero() const {
	return UArbBigInt::isZero();
}

bool SArbBigInt::isMagnitudeOne() const {
	return UArbBigInt::isOne();
}

bool SArbBigInt::isZero() const {
	return this->signum == 0;
}

bool SArbBigInt::isOne() const {
	if(this->signum <= 0) {
		return false;
	}
	return UArbBigInt::isOne();
}

SArbBigInt SArbBigInt::abs() const {
	SArbBigInt res(*this);
	res.setAbs();
	return res;
}

SArbBigInt SArbBigInt::negate() const {
	SArbBigInt res(*this);
	res.setNegate();
	return res;
}

// ----- shift left -----
BIG_INT_WORD_TYPE SArbBigInt::rcl(const uint bits, const BIG_INT_WORD_TYPE c, const bool resize) {
	return UArbBigInt::rcl(bits, c, resize);
}

SArbBigInt SArbBigInt::operator<< (const uint bits) const {
	// copy tha magnitude array 2 times
	//return SArbBigInt(BigInt::operator<<(bits), this->signum < 0);

	// copy the magnitude array only once
	SArbBigInt res(*this);
	res.rcl(bits, 0, true);
	return res;
}

// ----- shift right -----
BIG_INT_WORD_TYPE SArbBigInt::rcr(const uint bits, const BIG_INT_WORD_TYPE c) {
	return UArbBigInt::rcr(bits, c);
}

SArbBigInt SArbBigInt::operator>> (const uint bits) const {
	// copy tha magnitude array 2 times
	//return SArbBigInt(BigInt::operator>>(bits), this->signum < 0);

	// copy the magnitude array only once
	SArbBigInt res(*this);
	res.rcr(bits, 0);
	if(res.isMagnitudeZero()) {
		res.signum = 0;
	}
	return res;
}

// ----- addition -----

void SArbBigInt::add(const SArbBigInt &other, SArbBigInt &result) const {
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

void SArbBigInt::add(const SArbBigInt &other) {
	this->add(other, *this);
}

SArbBigInt SArbBigInt::operator+ (const SArbBigInt& other) const {
	BIG_INT_WORD_COUNT_TYPE maxWordCount = std::max(this->getWordSize(), other.getWordSize());
	SArbBigInt result(0, maxWordCount+1);
	this->add(other, result);
	return result;
}

// ----- substraction -----
BIG_INT_WORD_TYPE SArbBigInt::subInfUInt(const SArbBigInt& b, SArbBigInt& restul) const {
	return UArbBigInt::sub(b, 0, restul);
}

void SArbBigInt::subAsPositive(const SArbBigInt& a, const SArbBigInt& b, SArbBigInt& restul) const {
	// more readable version but requires a comparision of the magnitudes and therfore two casts.... probably slow

	//if( (BigInt)b < (BigInt)a ) { // only compare the magnitude
	if(static_cast<const UArbBigInt&>(b) < static_cast<const UArbBigInt&>(a)  ) { // only compare the magnitude (ignore the sign); static_cast<const BigInt&>(X): cast without calling the copy constructor
		//restul = SArbBigInt(a - b, false);
		a.subInfUInt(b, restul);
		restul.signum = restul.isMagnitudeZero() ? 0 : +1;
	} else {
		//restul = SArbBigInt(b - a, true);
		b.subInfUInt(a, restul);
		restul.signum = restul.isMagnitudeZero() ? 0 : -1;
	}

}

void SArbBigInt::sub(const SArbBigInt& other, SArbBigInt &result) const {
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
		UArbBigInt::add(other, result);
		result.signum = +1;
		return;
	}

	if(this->signum < 0 && other.signum > 0) {
		// -a - +b = -(+a + +b)
		UArbBigInt::add(other, result);
		result.signum = -1;
		return;
	}

	std::string msg = "ERROR substract SArbBigInt unexpected case!";
	std::cerr << msg << std::endl;
	throw std::runtime_error(msg);
}

void SArbBigInt::sub(const SArbBigInt& other) {
	this->sub(other, *this);
}

SArbBigInt SArbBigInt::operator- (const SArbBigInt& other) const {
	SArbBigInt result(0, this->getWordSize());
	this->sub(other, result);
	return result;
}

// ----- multiplication -----

void SArbBigInt::mul(const SArbBigInt& b, SArbBigInt& result) const {
	if(this->isZero() || b.isZero()) {
		result.setZero();
		return;
	}

	UArbBigInt::mul(b, result);
	result.signum = ((this->signum < 0) ^ (b.signum < 0)) ? -1 : +1;
}

void SArbBigInt::mul(const SArbBigInt& b) {
	SArbBigInt result = UArbBigInt(0, this->getWordSize() + b.getWordSize());
	this->mul(b, result);
	*this = result;
}

SArbBigInt SArbBigInt::operator* (const SArbBigInt& other) const {
	SArbBigInt result = UArbBigInt(0, this->getWordSize() + other.getWordSize());
	this->mul(other, result);
	return result;
}

SArbBigInt SArbBigInt::operator/ (const SArbBigInt& other) const {
	SArbBigInt res(UArbBigInt::operator/(other), (this->signum < 0) ^ (other.signum < 0) );
	//if(res.isZero()) {
	//	res.signum = 0;
	//}
	return res;
}

SArbBigInt SArbBigInt::operator% (const SArbBigInt& other) const {
	SArbBigInt res(UArbBigInt::operator%(other), false);

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
			std::string msg = "ERROR mod SArbBigInt unexpected case!";
			std::cerr << msg << std::endl;
			throw std::runtime_error(msg);
		}
	}
	return res;
}

SArbBigInt SArbBigInt::pow(SArbBigInt pow) const {
	return SArbBigInt(UArbBigInt::pow(pow), pow.isOdd() && this->signum < 0);
}

SArbBigInt SArbBigInt::sqrt() const {
	if (this->signum <= 0) {
		//throw new ArithmeticException("BigInteger: modulus not positive");
		std::string msg = "ERROR SArbBigInt: can not claculate sqrt from negative number (no imaginary suport)!";
		std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	return SArbBigInt(UArbBigInt::sqrt(), false);
}

/* ---------- modInverse / gcd ---------- */

SArbBigInt SArbBigInt::modInverse(const SArbBigInt & m) const {
	if (m.isZero()) {
		std::string msg = "ERROR BigInt: modulus not positive!";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	if (m.isOne()) {
		return SArbBigInt(0);
	}

	// all the hard work will be done by gcd.
	SArbBigInt u, v;
	SArbBigInt gcd = this->gcdExtended(*this, m, u, v);
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


SArbBigInt SArbBigInt::gcdExtended(const SArbBigInt &a, const SArbBigInt &b, SArbBigInt &u, SArbBigInt &v) const {
	// https://math.stackexchange.com/questions/37806/extended-euclidean-algorithm-with-negative-numbers
	//  |𝑎|𝑥+|𝑏|𝑦=1 => 𝑎(sign(𝑎)⋅𝑥)+𝑏(sign(𝑏)⋅𝑦)=1.

	// Implementing the Extended Euclidean Algorithm with Unsigned Inputs
	// https://jeffhurchalla.com/2018/10/09/analysis-of-bounds-in-the-extended-euclidean-algorithm/
	// https://jeffhurchalla.com/2018/10/13/implementing-the-extended-euclidean-algorithm-with-unsigned-inputs/

	int_fast8_t signumA = a.signum;
	int_fast8_t signumB = b.signum;

	SArbBigInt absA = a;
	SArbBigInt absB = b;
	absA.setAbs();
	absB.setAbs();

	//SArbBigInt gcd = this->gcdExtended_internRecursive(absA, absB, u, v);
	SArbBigInt gcd = this->gcdExtended_internIterative(absA, absB, u, v);

	u.signum = u.signum * signumA;
	v.signum = v.signum * signumB;

	assert((a*u + b*v) == gcd);

	return gcd;
}

SArbBigInt SArbBigInt::gcdExtended_internRecursive(const SArbBigInt &a, const SArbBigInt &b, SArbBigInt &u, SArbBigInt &v) const {
	// Base Case
	if (a.isZero()) {
		u.setZero();
		v.setOne();
		return b;
	}

	SArbBigInt u1(0, u.getWordSize()), v1(0, v.getWordSize()); // To store results of recursive call
	SArbBigInt gcd = gcdExtended(b % a, a, u1, v1);

	// Update u and v using results of recursive call
	u = v1 - (b/a) * u1;
	v = u1;

	return gcd;
}

SArbBigInt SArbBigInt::gcdExtended_internIterative(const SArbBigInt &a, const SArbBigInt &b, SArbBigInt &u, SArbBigInt &v) const {
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
	SArbBigInt unCur(0);
	SArbBigInt vnCur(1);
	SArbBigInt a1(a);
	SArbBigInt b1(b);

	SArbBigInt q, newB, unNew, vnNew;

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

SArbBigInt SArbBigInt::gcd(const SArbBigInt & a, const SArbBigInt & b) const {
	if (a.isZero()) {
		return b;
	}
	return gcd(b % a, a);
}

/* ---------- modPow ---------- */

SArbBigInt SArbBigInt::modPow(const SArbBigInt &exponent, const SArbBigInt &m) const {
	if (m.signum <= 0) {
		//throw new ArithmeticException("BigInteger: modulus not positive");
		std::string msg = "ERROR SArbBigInt: modulus not positive!";
		std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}

	// Trivial cases: exponent = 0
	if (exponent.isZero()) {
		return (m.isOne() ? SArbBigInt(0) : SArbBigInt(1));
	}

	// Trivial cases: base = 1
	if (this->isOne()) {
		return (m.isOne() ? SArbBigInt(0) : SArbBigInt(1));
	}

	// Trivial cases: base = 0
	if (this->isZero() &&  exponent.signum >= 0) {
		return SArbBigInt(0);
	}

	// Trivial cases: base = -1 && (exponent % 2 = 0)
	if (*this == SArbBigInt(1, true) && exponent.isEven()) {
		return (m.isOne() ? SArbBigInt(0) : SArbBigInt(1));
	}


	return this->modPow_naiv(exponent, m);

	// faster version from java BigInt ....
	/*
	bool invertResult = exponent.signum < 0;
	SArbBigInt absExponent(exponent); // TODO performance, unessesery copy if exponent is positive
	if (invertResult) {
		absExponent.setAbs();
	}

	//BigInteger base = (this.signum < 0 || this.compareTo(m) >= 0
	//				   ? this.mod(m) : this);
	SArbBigInt base = (this->signum < 0 || *this >= m) ? *this % m : *this;

	SArbBigInt result(0);
	if(m.isOdd()) { // odd modulus
		result = base.oddModPow(exponent, m);
	} else {
		/ *
		 * Even modulus.  Tear it into an "odd part" (m1) and power of two
		 * (m2), exponentiate mod m1, manually exponentiate mod m2, and
		 * use Chinese Remainder Theorem to combine results.
		 * /

		// Tear m apart into odd part (m1) and power of 2 (m2)
		int p = m.findLowestSetBit();   // Max pow of 2 that divides m

		//BigInteger m1 = m .shiftRight(p);  // m/2**p
		SArbBigInt m1 = m >> p; // m/2**p
		//BigInteger m2 = ONE.shiftLeft(p); // 2**p
		SArbBigInt m2 = SArbBigInt(1) << p; // 2**p

		// Calculate new base from m1
		//BigInteger base2 = (this.signum < 0 || this.compareTo(m1) >= 0 ? this.mod(m1) : this);
		SArbBigInt base2 = (this->signum < 0 || *this >= m1) ? *this % m1 : *this;

		// Caculate (base ** exponent) mod m1.
		//BigInteger a1 = (m1.equals(ONE) ? ZERO : base2.oddModPow(exponent, m1));
		SArbBigInt a1 = m1.isOne() ? BigInt(0) : base2.oddModPow(exponent, m1);

		// Calculate (this ** exponent) mod m2
		SArbBigInt a2 = base.modPow2(exponent, p);

		// Combine results using Chinese Remainder Theorem
		SArbBigInt y1 = m2.modInverse(m1);
		SArbBigInt y2 = m1.modInverse(m2);

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

SArbBigInt SArbBigInt::modPow_naiv(const SArbBigInt &exponent, const UArbBigInt &modulus) const {
	if(modulus.UArbBigInt::isOne()) {
		return SArbBigInt(1);
	}

	//Assert :: (modulus - 1) * (modulus - 1) does not overflow base

	// ensure that the base is < modulus
	SArbBigInt base = (this->signum < 0 || *this >= modulus) ? (*this % modulus) : *this;

	bool invertResult = exponent.signum < 0;
	SArbBigInt absExponent(exponent);
	if (invertResult) {
		absExponent.setAbs();
	}

	SArbBigInt result(1);
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
SArbBigInt SArbBigInt::modPow2(SArbBigInt exponent, int p) const {
	/ *
	 * Perform exponentiation using repeated squaring trick, chopping off
	 * high order bits as indicated by modulus.
	 * /
	SArbBigInt result(1);
	SArbBigInt baseToPow2 = this->mod2(p);
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

/ **
 * Returns a BigInteger whose value is this mod(2**p).
 * Assumes that this {@code BigInteger >= 0} and {@code p > 0}.
 * /
SArbBigInt SArbBigInt::mod2(int p) const {
	if (this->bitLength() <= p) {
		return *this;
	}

	// simple but slow!
	BigInt q = *this >> p; // q = this / 2**p
	return *this - q;

	// TODO performance! can be done by bitshifting and masking only!
	/ *
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
bool SArbBigInt::operator< (const SArbBigInt& other) const {
	if(this->signum < other.signum) {
		return true;
	}

	if(this->signum > other.signum) {
		return false;
	}

	if(this->signum < 0) {
		return !(UArbBigInt::operator<=(other));
	} else {
		return UArbBigInt::operator<(other);
	}
}

bool SArbBigInt::operator<= (const SArbBigInt& other) const {
	if (*this < other) {
		return true;
	}

	if (*this == other) {
		return true;
	}

	return false;
}

bool SArbBigInt::operator> (const SArbBigInt& other) const {
	return (!(*this <= other));
}

bool SArbBigInt::operator>= (const SArbBigInt& other) const {
	return (!(*this < other));
}

bool SArbBigInt::operator== (const SArbBigInt& other) const {
	if (*this < other) {
		return false;
	}

	if (other < *this) {
		return false;
	}

	return true;
}

bool SArbBigInt::operator!= (const SArbBigInt& other) const {
	return (!(*this == other));
}
