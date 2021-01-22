
#include "BigIntTestFactory.hpp"
#include "BigIntGpuTestOperation_types.hpp"

using namespace ppvr::rendering::test;


std::vector<BigIntTestCase> BigIntTestFactory::createAllTest() {
	std::vector<BigIntTestCase> testCases;
	
	testCases.push_back(createCopyTest());
	
	testCases.push_back(createLessThanTest());
	testCases.push_back(createLessThanOrEqualToTest());
	testCases.push_back(createGreaterThanTest());
	testCases.push_back(createGreaterThanOrEqualToTest());
	testCases.push_back(createEqualToTest());
	testCases.push_back(createNotEqualToTest());
	
	testCases.push_back(createMulTest());
	
	return testCases;
}


BigIntTestCase BigIntTestFactory::createCopyTest() {
	size_t s = 15;
	BigIntTestCase tc{"GPU big int copy", BIG_INT_GPU_TEST_OPERATION_copy, s, 1};
	
	// assertion Nr: 0
	tc.addAssertion(
		{{PaillierInt::fromString("0", 10)  }}
		, PaillierInt::fromString("0", 10)
	);
	tc.addAssertion(
		{{PaillierInt::fromString("1", 10)  }}
		, PaillierInt::fromString("1", 10)
	);
	tc.addAssertion(
		{{PaillierInt::fromString("2", 10)  }}
		, PaillierInt::fromString("2", 10)
	);
	tc.addAssertion(
		{{PaillierInt::fromString("255", 10)}}
		, PaillierInt::fromString("255", 10)
	);
	tc.addAssertion(
		{{PaillierInt::fromString("256", 10)}}
		, PaillierInt::fromString("256", 10)
	);
	
	// assertion Nr: 5
	tc.addAssertion(
		{{PaillierInt::fromString("1", 10) << 31}}
		, PaillierInt::fromString("1", 10) << 31
	);
	tc.addAssertion(
		{{PaillierInt::fromString("1", 10) << 32}}
		, PaillierInt::fromString("1", 10) << 32
	);
	tc.addAssertion(
		{{PaillierInt::fromString("1", 10) << 63}}
		, PaillierInt::fromString("1", 10) << 63
	);
	tc.addAssertion(
		{{PaillierInt::fromString("1", 10) << 64}}
		, PaillierInt::fromString("1", 10) << 64
	);
	tc.addAssertion(
		{{PaillierInt::fromString("10101010 01010101 10101010 01010101", 2)}}
		, PaillierInt::fromString("10101010 01010101 10101010 01010101", 2)
	);
	
	// assertion Nr: 10
	tc.addAssertion(
		{{PaillierInt::fromString("1  10101010 01010101 10101010 01010101", 2)}}
		, PaillierInt::fromString("1  10101010 01010101 10101010 01010101", 2)
	);
	tc.addAssertion(
		{{PaillierInt::fromString("10101010 01010101 01010101 01010101  01010101 10101010 01010101 10101010", 2)}}
		, PaillierInt::fromString("10101010 01010101 01010101 01010101  01010101 10101010 01010101 10101010", 2)
	);
	tc.addAssertion(
		{{PaillierInt::fromString("1  10101010 01010101 01010101 01010101  01010101 10101010 01010101 10101010", 2)}}
		, PaillierInt::fromString("1  10101010 01010101 01010101 01010101  01010101 10101010 01010101 10101010", 2)
	);
	tc.addAssertion(
		{{PaillierInt::fromString("1000", 16)}}
		, PaillierInt::fromString("1000", 16)
	);
	tc.addAssertion(
		{{PaillierInt::fromString("1001", 16)}}
		, PaillierInt::fromString("1001", 16)
	);
	
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createLessThanTest() {
	size_t s = 28;
	BigIntTestCase tc{"GPU big int lessThanTest (<)", BIG_INT_GPU_TEST_OPERATION_lessThan, s, 2};
	
	PaillierInt a, b;
	
	// assertion Nr: 0
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 0 < 0
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 1 < 0
	
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 0 < 1
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 1 < 2
	
	a = PaillierInt::fromString("9", 16);
	b = PaillierInt::fromString("A", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 9 < 10
	
	// assertion Nr: 5
	a = PaillierInt::fromString("E", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 14 < 15
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("10", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 15 < 16
	
	a = PaillierInt::fromString("10", 16);
	b = PaillierInt::fromString("0F", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 16 < 15
	
	a = PaillierInt::fromString("FF", 16);
	b = PaillierInt::fromString("FF", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("0FF", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 10
	a = PaillierInt::fromString("0FF", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("0FF", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1001", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 15
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1010", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1100", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000001", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 20
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 25
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16); // 128 bit
	b = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createLessThanOrEqualToTest() {
	size_t s = 33;
	BigIntTestCase tc{"GPU big int lessThanOrEqualTo (<=)", BIG_INT_GPU_TEST_OPERATION_lessThanOrEqualTo, s, 2};
	
	PaillierInt a, b;
	
	// assertion Nr: 0
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 0 <= 0
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 1 <= 0
	
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 0 <= 1
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 1 <= 2
	
	a = PaillierInt::fromString("9", 16);
	b = PaillierInt::fromString("A", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 9 <= 10
	
	// assertion Nr: 5
	a = PaillierInt::fromString("E", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 14 <= 15
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 15 <= 15
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("10", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 15 <= 16
	
	a = PaillierInt::fromString("10", 16);
	b = PaillierInt::fromString("0F", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 16 <= 15
	
	a = PaillierInt::fromString("FF", 16);
	b = PaillierInt::fromString("FF", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 10
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("0FF", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("0FF", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("0FF", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 15
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1001", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1001", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1010", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1100", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 20
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000001", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000001", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 25
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 30
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16); // 128 bit
	b = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createGreaterThanTest() {
	size_t s = 37;
	BigIntTestCase tc{"GPU big int greaterThan (>)", BIG_INT_GPU_TEST_OPERATION_greaterThan, s, 2};
	
	PaillierInt a, b;
	
	// assertion Nr: 0
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 0 > 0
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 1 > 0
	
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 0 > 1
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 1 > 2
	
	a = PaillierInt::fromString("2", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 2 > 1
	
	// assertion Nr: 5
	a = PaillierInt::fromString("9", 16);
	b = PaillierInt::fromString("A", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 9 > 10
	
	a = PaillierInt::fromString("A", 16);
	b = PaillierInt::fromString("9", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 10 > 9
	
	a = PaillierInt::fromString("E", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 14 > 15
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 15 > 15
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("E", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 15 > 14
	
	// assertion Nr: 10
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("10", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 15 > 16
	
	a = PaillierInt::fromString("10", 16);
	b = PaillierInt::fromString("0F", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 16 > 15
	
	a = PaillierInt::fromString("FF", 16);
	b = PaillierInt::fromString("FF", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("0FF", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("0FF", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 15
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1001", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1001", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1010", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 20
	a = PaillierInt::fromString("1010", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1100", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1100", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000001", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 25
	a = PaillierInt::fromString("10000001", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 30
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	b = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 35
	a = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createGreaterThanOrEqualToTest() {
	size_t s = 37;
	BigIntTestCase tc{"GPU big int greaterThanOrEqualTo (>=)", BIG_INT_GPU_TEST_OPERATION_greaterThanOrEqualTo, s, 2};
	
	PaillierInt a, b;
	
	// assertion Nr: 0
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 0 >= 0
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 1 >= 0
	
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 0 >= 1
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 1 >= 2
	
	a = PaillierInt::fromString("2", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 2 >= 1
	
	// assertion Nr: 5
	a = PaillierInt::fromString("9", 16);
	b = PaillierInt::fromString("A", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 9 >= 10
	
	a = PaillierInt::fromString("A", 16);
	b = PaillierInt::fromString("9", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 10 >= 9
	
	a = PaillierInt::fromString("E", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 14 >= 15
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 15 >= 15
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("E", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 15 >= 14
	
	// assertion Nr: 10
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("10", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 15 >= 16
	
	a = PaillierInt::fromString("10", 16);
	b = PaillierInt::fromString("0F", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 16 >= 15
	
	a = PaillierInt::fromString("FF", 16);
	b = PaillierInt::fromString("FF", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("0FF", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("0FF", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 15
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1001", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1001", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1010", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 20
	a = PaillierInt::fromString("1010", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1100", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1100", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000001", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 25
	a = PaillierInt::fromString("10000001", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 30
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	b = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 35
	a = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createEqualToTest() {
	size_t s = 41;
	BigIntTestCase tc{"GPU big int equalTo (==)", BIG_INT_GPU_TEST_OPERATION_equalTo, s, 2};
	
	PaillierInt a, b;
	
	// assertion Nr: 0
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 0 == 0
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 1 == 0
	
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 0 == 1
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 1 == 2
	
	a = PaillierInt::fromString("2", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 2 == 1
	
	// assertion Nr: 5
	a = PaillierInt::fromString("2", 16);
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 2 == 2
	
	a = PaillierInt::fromString("9", 16);
	b = PaillierInt::fromString("A", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 9 == 10
	
	a = PaillierInt::fromString("A", 16);
	b = PaillierInt::fromString("9", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 10 == 9
	
	a = PaillierInt::fromString("E", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 14 == 15
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 15 == 15
	
	// assertion Nr: 10
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("E", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 15 == 14
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("10", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 15 == 16
	
	a = PaillierInt::fromString("10", 16);
	b = PaillierInt::fromString("0F", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 16 == 15
	
	a = PaillierInt::fromString("FF", 16);
	b = PaillierInt::fromString("FF", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("0FF", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 15
	a = PaillierInt::fromString("0FF", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1001", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1001", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 20
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1010", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1010", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1100", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1100", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 25
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000001", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000001", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 30
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 35
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	b = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16); // 128 bit
	b = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("F0E00C00 0000B000 A000D000 12345687", 16); // 128 bit
	b = PaillierInt::fromString("F0E00C00 0000B000 A000D000 12345687", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 40
	a = PaillierInt::fromString("F0E00C00 0000B000 A000D000 12345687", 16); // 128 bit
	b = PaillierInt::fromString("F0E00C00 0000B000 A000D000 12345688", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createNotEqualToTest() {
	size_t s = 41;
	BigIntTestCase tc{"GPU big int notEqualTo (!=)", BIG_INT_GPU_TEST_OPERATION_notEqualTo, s, 2};
	
	PaillierInt a, b;
	
	// assertion Nr: 0
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 0 != 0
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 1 != 0
	
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 0 != 1
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 1 != 2
	
	a = PaillierInt::fromString("2", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 2 != 1
	
	// assertion Nr: 5
	a = PaillierInt::fromString("2", 16);
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 2 != 2
	
	a = PaillierInt::fromString("9", 16);
	b = PaillierInt::fromString("A", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 9 != 10
	
	a = PaillierInt::fromString("A", 16);
	b = PaillierInt::fromString("9", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 10 != 9
	
	a = PaillierInt::fromString("E", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 14 != 15
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("F", 16);
	tc.addAssertion({a,b}, PaillierInt(false)); // 15 != 15
	
	// assertion Nr: 10
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("E", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 15 != 14
	
	a = PaillierInt::fromString("F", 16);
	b = PaillierInt::fromString("10", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 15 != 16
	
	a = PaillierInt::fromString("10", 16);
	b = PaillierInt::fromString("0F", 16);
	tc.addAssertion({a,b}, PaillierInt(true)); // 16 != 15
	
	a = PaillierInt::fromString("FF", 16);
	b = PaillierInt::fromString("FF", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("0FF", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 15
	a = PaillierInt::fromString("0FF", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("100", 16);
	b = PaillierInt::fromString("100", 16);
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1001", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1001", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 20
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1010", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1010", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1000", 16); // 16 bit
	b = PaillierInt::fromString("1100", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("1100", 16); // 16 bit
	b = PaillierInt::fromString("1000", 16); // 16 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 25
	a = PaillierInt::fromString("10000000", 16); // 32 bit
	b = PaillierInt::fromString("10000001", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000001", 16); // 32 bit
	b = PaillierInt::fromString("10000000", 16); // 32 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000001", 16); // 64 bit
	b = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 30
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000001", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("0FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	// assertion Nr: 35
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16); // 128 bit
	b = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16); // 128 bit
	b = PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	a = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	b = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("10000000 00000000 00000000 00000000", 16); // 128 bit
	b = PaillierInt::fromString("00000000 00000000 00000000 10000000", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	a = PaillierInt::fromString("F0E00C00 0000B000 A000D000 12345687", 16); // 128 bit
	b = PaillierInt::fromString("F0E00C00 0000B000 A000D000 12345687", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(false));
	
	// assertion Nr: 40
	a = PaillierInt::fromString("F0E00C00 0000B000 A000D000 12345687", 16); // 128 bit
	b = PaillierInt::fromString("F0E00C00 0000B000 A000D000 12345688", 16); // 128 bit
	tc.addAssertion({a,b}, PaillierInt(true));
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createMulTest() {
	size_t s = 36;
	BigIntTestCase tc{"GPU big int mul", BIG_INT_GPU_TEST_OPERATION_mul, s, 2};
	
	PaillierInt a, b;
	
	// assertion Nr: 0
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("0", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("0", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("1", 16);
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, (a*b));
	
	// assertion Nr: 5
	a = PaillierInt::fromString("7", 10);
	b = PaillierInt::fromString("19", 10);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("7F", 16); // 8 bit
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0xFF
	
	a = PaillierInt::fromString("FF", 16); // 8 bit
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("80", 16); // 8 bit
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0x100
	
	a = PaillierInt::fromString("80", 16); // 8 bit
	b = PaillierInt::fromString("3", 16);
	tc.addAssertion({a,b}, (a*b));
	
	// assertion Nr: 10
	a = PaillierInt::fromString("80", 16); // 8 bit
	b = PaillierInt::fromString("4", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("81", 16); // 8 bit
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 102
	
	a = PaillierInt::fromString("FF", 16); // 8 bit
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0x1FE
	
	a = PaillierInt::fromString("123", 10);
	b = PaillierInt::fromString("532", 10); // 16 bit
	tc.addAssertion({a,b}, (a*b)); // result: 0xFF9C
	
	a = PaillierInt::fromString("98", 10);
	b = PaillierInt::fromString("571", 10); // 16 bit
	tc.addAssertion({a,b}, (a*b)); // result: 0xDA96
	
	// assertion Nr: 15
	a = PaillierInt::fromString("0001 0001", 2);
	b = PaillierInt::fromString("1", 2);
	tc.addAssertion({a,b}, (a*b)); // result: 0001 0001
	
	a = PaillierInt::fromString("0010 0010", 2);
	b = PaillierInt::fromString("10", 2);
	tc.addAssertion({a,b}, (a*b)); // result: 0010 0010
	
	a = PaillierInt::fromString("1000 1000", 2);
	b = PaillierInt::fromString("1", 2);
	tc.addAssertion({a,b}, (a*b)); // result: 1000 1000
	
	a = PaillierInt::fromString("1000 1000", 2);
	b = PaillierInt::fromString("       10", 2);
	tc.addAssertion({a,b}, (a*b)); // result: 1 0001 0000
	
	a = PaillierInt::fromString("100", 16); // 16 bit
	b = PaillierInt::fromString("0FF", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0xFF00
	
	// assertion Nr: 20
	a = PaillierInt::fromString("011", 16); // 16 bit
	b = PaillierInt::fromString("0FF", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0x10EF
	
	a = PaillierInt::fromString("FFFF", 16); // 16 bit
	b = PaillierInt::fromString("FFFF", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0xFFFE0001
	
	a = PaillierInt::fromString("0100", 16); // 16 bit
	b = PaillierInt::fromString("0100", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0x010000
	
	a = PaillierInt::fromString("0100", 16); // 16 bit
	b = PaillierInt::fromString("0F00", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0x0F0000
	
	a = PaillierInt::fromString("55555555", 16);
	b = PaillierInt::fromString("      03", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0xFFFFFFFF
	
	// assertion Nr: 25
	a = PaillierInt::fromString("EFEF", 16); // 16 bit
	b = PaillierInt::fromString("  EF", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0xE00021
	
	a = PaillierInt::fromString("EFEF", 16); // 16 bit
	b = PaillierInt::fromString("EFEF", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0xE0E02121
	
	a = PaillierInt::fromString("ff9C", 16); // 16 bit
	b = PaillierInt::fromString("7B", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0x7ACFF4
	
	a = PaillierInt::fromString("FFFFFFFF", 16); // 32 bit
	b = PaillierInt::fromString("FFFFFFFF", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF", 16); // 64 bit
	b = PaillierInt::fromString("FFFFFFFF FFFFFFFF", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0xFFFFFFFFFFFFFFFE0000000000000001
	
	// assertion Nr: 30
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF", 16); // 64 bit
	b = PaillierInt::fromString("               02", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 0x1FFFFFFFFFFFFFFFE
	
	a = PaillierInt::fromString("FEDCBA98 76543210", 16); // 64 bit
	b = PaillierInt::fromString("12345678 9ABCDEF0", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 24090311171252216041959356964269510400
	
	a = PaillierInt::fromString("10000000 00000000", 16); // 64 bit
	b = PaillierInt::fromString("12345678 9ABCDEF0", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF", 16); // 64 bit
	b = PaillierInt::fromString("12345678 9ABCDEF0", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("10001000 10001000 10001000 10001000 10001000 10001000 10001000 10001000", 2);
	b = PaillierInt::fromString("1", 2);
	tc.addAssertion({a,b}, (a*b)); // result: 10001000 10001000 10001000 10001000 10001000 10001000 10001000 10001000
	
	// assertion Nr: 35
	a = PaillierInt::fromString("10001000 10001000 10001000 10001000 10001000 10001000 10001000 10001000", 2);
	b = PaillierInt::fromString("       10", 2);
	tc.addAssertion({a,b}, (a*b)); // result: 1 00010001 00010001 00010001 00010000 00010000 00010000 00010000 00010000
	
	return tc;
}

