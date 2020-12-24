// main
#include <iostream>
#include <string>
#include "../src/math/PerformanceTest.hpp"
#include <chrono>

using namespace ppvr;

int main (int argc, char *argv[]) {
	std::cout << "main function\n";
	
	math::PerformanceTest::fromString();
	math::PerformanceTest::createPrime();
	
	return 0;
}
