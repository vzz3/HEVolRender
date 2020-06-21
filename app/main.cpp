// main
#include <iostream>
#include <string>
#include "math/BigInt.h"

using namespace ppvr;

int main (int argc, char *argv[]) {
	std::cout << "main function\n";
	
	std::string numStrIn("1234");
	math::BigInt a = math::BigInt::fromString(numStrIn, 10);
	std::string numStrOut = a.toStringDec();
	std::cout << "In: " << numStrIn << ", out: " << numStrOut << std::endl;
	
	return 0;
}
