// main
#include <iostream>
#include <string>
#include "../src/math/BigInt.h"

using namespace ppvr;

int main (int argc, char *argv[]) {
	std::cout << "main function\n";
	
	/*
	std::string numStrIn("1234");
	math::BigInt a = math::BigInt::fromString(numStrIn, 10);
	std::string numStrOut = a.toStringDec();
	std::cout << "In: " << numStrIn << ", out: " << numStrOut << std::endl;
	*/
	
	math::BigInt test(0);
	uint8_t result, rest;
	test.divTwoWords(0x36, 0xa5, 0x8e, &result, &rest);
	std::cout << "0x36a5 / 0x8e = result: " << std::to_string(result) << " (expected: 98 / 0x62) , rest: " << std::to_string(rest) << " (expected: 73 / 0x49)" << std::endl;
	
	uint64_t bigIntRes = (math::BigInt::fromUint64(0xDA96ull) / math::BigInt::fromUint64(  571)).toUint64();
	std::cout << "result: " << std::to_string(bigIntRes) << " (expected: 98)" << std::endl;
	
	return 0;
}
