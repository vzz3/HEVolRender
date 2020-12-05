
#include "SInfinitBigInt.hpp"
#include <iostream>

using namespace ppvr::math;

// ----- statics -----

const SInfinitBigInt SInfinitBigInt::SmallPrimeProduct = SInfinitBigInt::fromUint64(3L*5*7*11*13*17*19*23*29*31*37*41);

// Pre generated primes
const SInfinitBigInt SInfinitBigInt::FirstPrimes[] = {
	SInfinitBigInt::fromInt64(  2), SInfinitBigInt::fromInt64(  3), SInfinitBigInt::fromInt64(  5),
	SInfinitBigInt::fromInt64(  7), SInfinitBigInt::fromInt64( 11), SInfinitBigInt::fromInt64( 13),
	SInfinitBigInt::fromInt64( 17), SInfinitBigInt::fromInt64( 19), SInfinitBigInt::fromInt64( 23),
	SInfinitBigInt::fromInt64( 29), SInfinitBigInt::fromInt64( 31), SInfinitBigInt::fromInt64( 37),
	SInfinitBigInt::fromInt64( 41), SInfinitBigInt::fromInt64( 43), SInfinitBigInt::fromInt64( 47),
	SInfinitBigInt::fromInt64( 53), SInfinitBigInt::fromInt64( 59), SInfinitBigInt::fromInt64( 61),
	SInfinitBigInt::fromInt64( 67), SInfinitBigInt::fromInt64( 71), SInfinitBigInt::fromInt64( 73),
	SInfinitBigInt::fromInt64( 79), SInfinitBigInt::fromInt64( 83), SInfinitBigInt::fromInt64( 89),
	SInfinitBigInt::fromInt64( 97), SInfinitBigInt::fromInt64(101), SInfinitBigInt::fromInt64(103),
	SInfinitBigInt::fromInt64(107), SInfinitBigInt::fromInt64(109), SInfinitBigInt::fromInt64(113),
	SInfinitBigInt::fromInt64(127), SInfinitBigInt::fromInt64(131), SInfinitBigInt::fromInt64(137),
	SInfinitBigInt::fromInt64(139), SInfinitBigInt::fromInt64(149), SInfinitBigInt::fromInt64(151),
	SInfinitBigInt::fromInt64(157), SInfinitBigInt::fromInt64(163), SInfinitBigInt::fromInt64(167),
	SInfinitBigInt::fromInt64(173), SInfinitBigInt::fromInt64(179), SInfinitBigInt::fromInt64(181),
	SInfinitBigInt::fromInt64(191), SInfinitBigInt::fromInt64(193), SInfinitBigInt::fromInt64(197),
	SInfinitBigInt::fromInt64(199), SInfinitBigInt::fromInt64(211), SInfinitBigInt::fromInt64(223),
	SInfinitBigInt::fromInt64(227), SInfinitBigInt::fromInt64(229), SInfinitBigInt::fromInt64(233),
	SInfinitBigInt::fromInt64(239), SInfinitBigInt::fromInt64(241), SInfinitBigInt::fromInt64(251),
	SInfinitBigInt::fromInt64(257), SInfinitBigInt::fromInt64(263), SInfinitBigInt::fromInt64(269),
	SInfinitBigInt::fromInt64(271), SInfinitBigInt::fromInt64(277), SInfinitBigInt::fromInt64(281),
	SInfinitBigInt::fromInt64(283), SInfinitBigInt::fromInt64(293), SInfinitBigInt::fromInt64(307),
	SInfinitBigInt::fromInt64(311), SInfinitBigInt::fromInt64(313), SInfinitBigInt::fromInt64(317),
	SInfinitBigInt::fromInt64(331), SInfinitBigInt::fromInt64(337), SInfinitBigInt::fromInt64(347),
	SInfinitBigInt::fromInt64(349)
};

SInfinitBigInt SInfinitBigInt::fromInt64(const int64_t& int64Val) {
	SInfinitBigInt res(0);
	SInfinitBigInt::fromInt64(int64Val, res);
	return res;
}

SInfinitBigInt& SInfinitBigInt::fromInt64(const int64_t& int64Val, SInfinitBigInt &target ) {
	BigInt::fromUint64(std::abs(int64Val), target);
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

SInfinitBigInt SInfinitBigInt::randomNumber(const uint& sizeInBit, Random& rnd) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BigInt::requiredWords(sizeInBit);
	SInfinitBigInt res(0, requiredWords);
	SInfinitBigInt::randomNumber(sizeInBit, rnd, res);
	return res;
}

SInfinitBigInt SInfinitBigInt::randomNumber(const SInfinitBigInt& upperBound, Random& rnd) {
	BIG_INT_WORD_COUNT_TYPE requiredWords = BigInt::requiredWords(upperBound.bitLength());
	SInfinitBigInt res(0, requiredWords);
	SInfinitBigInt::randomNumber(upperBound, rnd, res);
	return res;
}

SInfinitBigInt& SInfinitBigInt::randomNumber(const uint& sizeInBit, Random& rnd, SInfinitBigInt &target) {
	BigInt::randomNumber(sizeInBit, rnd, target);
	if(target.isMagnitudeZero()) {
		target.signum = 0;
	} else {
		target.signum = 1;
	}
	return target;
}

SInfinitBigInt& SInfinitBigInt::randomNumber(const SInfinitBigInt& upperBound, Random& rnd, SInfinitBigInt &target) {
	if(upperBound.signum < 0) {
		std::string msg = "ERROR upperBound: must be strictly greater than one";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	
	BigInt::randomNumber(upperBound, rnd, target);
	if(target.isMagnitudeZero()) {
		target.signum = 0;
	} else {
		target.signum = 1;
	}
	return target;
}



SInfinitBigInt SInfinitBigInt::probablePrime(const uint& bitLength, Random& rnd) {
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

SInfinitBigInt SInfinitBigInt::smallPrime(const uint& bitLength, const uint& certainty, Random& rnd) {
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
	
	BIG_INT_WORD_COUNT_TYPE requiredWords = BigInt::requiredWords(bitLength);
	SInfinitBigInt p(0, requiredWords);
	
	while (true) {
		SInfinitBigInt::randomNumber(bitLength, rnd, p);
		p.setBit(bitLength-1); // Ensure exact length
		
		if (bitLength > 2) {
			p.setBit(0); //p.value[0] |= 1;  // Make odd if bitlen > 2
		}
		
		// Do cheap "pre-test" if applicable
		if (bitLength > 6) {
			int64_t r = (p % SInfinitBigInt::SmallPrimeProduct).toUint64();
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

SInfinitBigInt SInfinitBigInt::largePrime(const uint& bitLength, const uint& certainty, Random& rnd) {
	// A search with a BitSieve is  faster. (The java BigInt class uses such a surch algorithem.)
	// However, a test for random numers should do it for the moment (it is simpler to implement).
	// https://stackoverflow.com/questions/13665443/generate-random-prime-number-in-c-c-between-2-limits
	// https://crypto.stackexchange.com/questions/1812/how-to-better-generate-large-primes-sieving-and-then-random-picking-or-random-p
	 
	// Algorithm and comments adapted from https://www.geeksforgeeks.org/how-to-generate-large-prime-numbers-for-rsa-algorithm/
	SInfinitBigInt primeCandidate(0, requiredWords(bitLength));
	while(true) {
		SInfinitBigInt::lowLevelPrime(bitLength, rnd, primeCandidate);
		if (primeCandidate.primeToCertainty(certainty, rnd)) {
			return primeCandidate;
		}
	}
}

void SInfinitBigInt::lowLevelPrime(const uint& bitLength, Random& rnd, SInfinitBigInt &target) {
	// Algorithm and comments adapted from https://www.geeksforgeeks.org/how-to-generate-large-prime-numbers-for-rsa-algorithm/
	// Generate a prime candidate divisible by first primes
	bool isLowLevelPrime(false);
	while(!isLowLevelPrime) {
		// Obtain a random number
		SInfinitBigInt::randomNumber(bitLength, rnd, target);
	
		// Test divisibility by pre-generated primes
		isLowLevelPrime = true;
		for(SInfinitBigInt divisor : SInfinitBigInt::FirstPrimes) {
			if ((target % divisor).isZero() && divisor.pow(2) <= target) {
				isLowLevelPrime = false;
				break; // early exit
			}
		}
	}
}
 
bool SInfinitBigInt::primeToCertainty(const uint certainty, Random& rnd) {
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

bool SInfinitBigInt::passesLucasLehmer() {
	// Algorithm and comments adapted from Java java.math.BigInteger
	
	SInfinitBigInt thisPlusOne= *this + BigInt::ONE;
	
	// Step 1
	int d = 5;
	while (jacobiSymbol(d, *this) != -1) {
		// 5, -7, 9, -11, ...
		d = (d < 0) ? std::abs(d)+2 : -(d+2);
	}
	
	// Step 2
	SInfinitBigInt u = lucasLehmerSequence(d, thisPlusOne, *this);
	
	// Step 3
	return (u % *this).isZero();
}

int SInfinitBigInt::jacobiSymbol(int16_t p, const SInfinitBigInt& n) {
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
	u = (n % SInfinitBigInt(p)).getLeastSignificantWord(); // getLeastSignificantWord() is save because p must fit into BIG_INT_WORD_TYPE and therfore the reminder of X/p must fit into BIG_INT_WORD_TYPE.
	
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

SInfinitBigInt SInfinitBigInt::lucasLehmerSequence(int z, const SInfinitBigInt& k, const SInfinitBigInt& n) {
	// Algorithm and comments adapted from Java java.math.BigInteger
	
	SInfinitBigInt d = SInfinitBigInt::fromInt64(z);
	SInfinitBigInt u = ONE; SInfinitBigInt u2;
	SInfinitBigInt v = ONE; SInfinitBigInt v2;
	
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

bool SInfinitBigInt::passesMillerRabin(int iterations, Random& rnd) {
	// Algorithm and comments adapted from Java java.math.BigInteger
	
	// Find a and m such that m is odd and this == 1 + 2**a * m
	SInfinitBigInt thisMinusOne = *this - BigInt::ONE;
	SInfinitBigInt m = thisMinusOne;
	int a = m.findLowestSetBit();
	m = m >> a;
	
	// Do the tests
	//if (rnd == null) {
	//	rnd = ThreadLocalRandom.current();
	//}
	for (int i=0; i < iterations; i++) {
		// Generate a uniform random on (1, this)
		SInfinitBigInt b(0, this->getWordSize());
		do {
			SInfinitBigInt::randomNumber(this->bitLength(), rnd, b);
		} while (b <= SInfinitBigInt::ONE || b >= *this);
		
		int j = 0;
		SInfinitBigInt z = b.modPow(m, *this);
		while (!((j == 0 && z.isOne()) || z == thisMinusOne)) {
			if ((j > 0 && z.isOne()) || ++j == a) {
				return false;
			}
			z = z.modPow(TWO, *this);
		}
	}
	return true;
}

bool SInfinitBigInt::isProbablePrime(const uint certainty, Random& rnd) {
	// Algorithm and comments adapted from Java java.math.BigInteger
	if (certainty <= 0) {
		return true;
	}
	SInfinitBigInt w(*this); w.setAbs(); // TODO Speed: is this copy of the magnitud realy required? is it ok to set and reset just the signum?
	if (w == TWO) {
		return true;
	}
	if (!w.testBit(0) || w.isOne()) {
		return false;
	}
	
	return w.primeToCertainty(certainty, rnd);
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

SInfinitBigInt SInfinitBigInt::abs() const {
	SInfinitBigInt res(*this);
	res.setAbs();
	return res;
}

SInfinitBigInt SInfinitBigInt::negate() const {
	SInfinitBigInt res(*this);
	res.setNegate();
	return res;
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
		throw std::invalid_argument(msg);
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
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
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
	// https://jeffhurchalla.com/2018/10/09/analysis-of-bounds-in-the-extended-euclidean-algorithm/
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
		throw std::invalid_argument(msg);
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
		/ *
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
	/ *
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

/ **
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
bool SInfinitBigInt::operator< (const SInfinitBigInt& other) const {
	if(this->signum < other.signum) {
		return true;
	}
	
	if(this->signum > other.signum) {
		return false;
	}
	
	if(this->signum < 0) {
		return !(BigInt::operator<=(other));
	} else {
		return BigInt::operator<(other);
	}
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

