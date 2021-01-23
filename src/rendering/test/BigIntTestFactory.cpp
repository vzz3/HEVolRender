
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
	
	testCases.push_back(createShiftLeft());
	testCases.push_back(createShiftRight());
	
	testCases.push_back(createAddTest());
	testCases.push_back(createSubTest());
	testCases.push_back(createMulTest());
	
	return testCases;
}


BigIntTestCase BigIntTestFactory::createCopyTest() {
	BigIntTestCase tc{"GPU big int copy", BIG_INT_GPU_TEST_OPERATION_copy, 1};
	
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
	BigIntTestCase tc{"GPU big int lessThanTest (<)", BIG_INT_GPU_TEST_OPERATION_lessThan, 2};
	
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
	BigIntTestCase tc{"GPU big int lessThanOrEqualTo (<=)", BIG_INT_GPU_TEST_OPERATION_lessThanOrEqualTo, 2};
	
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
	BigIntTestCase tc{"GPU big int greaterThan (>)", BIG_INT_GPU_TEST_OPERATION_greaterThan, 2};
	
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
	BigIntTestCase tc{"GPU big int greaterThanOrEqualTo (>=)", BIG_INT_GPU_TEST_OPERATION_greaterThanOrEqualTo, 2};
	
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
	BigIntTestCase tc{"GPU big int equalTo (==)", BIG_INT_GPU_TEST_OPERATION_equalTo, 2};
	
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
	BigIntTestCase tc{"GPU big int notEqualTo (!=)", BIG_INT_GPU_TEST_OPERATION_notEqualTo, 2};
	
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

BigIntTestCase BigIntTestFactory::createShiftLeft() {
	BigIntTestCase tc{"GPU big int shiftLeft", BIG_INT_GPU_TEST_OPERATION_shiftLeft, 2};
	
	PaillierInt a, b;
	

	// 1 Byte (8bit)
	// assertion Nr: 0
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 0)}, PaillierInt::fromString("1", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 1)}, PaillierInt::fromString("10", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 2)}, PaillierInt::fromString("100", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 3)}, PaillierInt::fromString("1000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 4)}, PaillierInt::fromString("10000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 5)}, PaillierInt::fromString("100000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 6)}, PaillierInt::fromString("1000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 7)}, PaillierInt::fromString("10000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 8)}, PaillierInt::fromString(" 0000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 8)}, PaillierInt::fromString("10000000 0", 2) );
//	}

	// 2 Byte (16bit)
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 8)}, PaillierInt::fromString("10000000 0", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt( 9)}, PaillierInt::fromString("10000000 00", 2) );
	// assertion Nr: 10
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(10)}, PaillierInt::fromString("10000000 000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(11)}, PaillierInt::fromString("10000000 0000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(12)}, PaillierInt::fromString("10000000 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(13)}, PaillierInt::fromString("10000000 000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(14)}, PaillierInt::fromString("10000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(15)}, PaillierInt::fromString("10000000 00000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t)) {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(16)}, PaillierInt::fromString(" 0000000 00000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(16)}, PaillierInt::fromString("10000000 00000000 0", 2) );
//	}

	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 0)}, PaillierInt::fromString("10000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 1)}, PaillierInt::fromString("10000000 0", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 2)}, PaillierInt::fromString("10000000 00", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 3)}, PaillierInt::fromString("10000000 000", 2) );
	// assertion Nr: 20
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 4)}, PaillierInt::fromString("10000000 0000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 5)}, PaillierInt::fromString("10000000 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 6)}, PaillierInt::fromString("10000000 000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 7)}, PaillierInt::fromString("10000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 8)}, PaillierInt::fromString("10000000 00000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t)) {
//		tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 9)}, PaillierInt::fromString(" 0000000 00000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 9)}, PaillierInt::fromString("10000000 00000000 0", 2) );
//	}

	// 3 Byte (24bit)
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(16)}, PaillierInt::fromString("10000000 00000000 0", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(17)}, PaillierInt::fromString("10000000 00000000 00", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(18)}, PaillierInt::fromString("10000000 00000000 000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(19)}, PaillierInt::fromString("10000000 00000000 0000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(20)}, PaillierInt::fromString("10000000 00000000 00000", 2) );
	// assertion Nr: 30
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(21)}, PaillierInt::fromString("10000000 00000000 000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(22)}, PaillierInt::fromString("10000000 00000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(23)}, PaillierInt::fromString("10000000 00000000 00000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(24)}, PaillierInt::fromString(" 0000000 00000000 00000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(24)}, PaillierInt::fromString("10000000 00000000 00000000 0", 2) );
//	}

	tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 0)}, PaillierInt::fromString("10000000 00000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 1)}, PaillierInt::fromString("10000000 00000000 0", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 2)}, PaillierInt::fromString("10000000 00000000 00", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 3)}, PaillierInt::fromString("10000000 00000000 000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 4)}, PaillierInt::fromString("10000000 00000000 0000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 5)}, PaillierInt::fromString("10000000 00000000 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 6)}, PaillierInt::fromString("10000000 00000000 000000", 2) );
	// assertion Nr: 40
	tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 7)}, PaillierInt::fromString("10000000 00000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 8)}, PaillierInt::fromString("10000000 00000000 00000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
//		tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 9)}, PaillierInt::fromString(" 0000000 00000000 00000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("10000000 00000000", 2), PaillierInt( 9)}, PaillierInt::fromString("10000000 00000000 00000000 0", 2) );
//	}

	// 4 Byte (32bit)
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(24)}, PaillierInt::fromString("10000000 00000000 00000000 0", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(25)}, PaillierInt::fromString("10000000 00000000 00000000 00", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(26)}, PaillierInt::fromString("10000000 00000000 00000000 000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(27)}, PaillierInt::fromString("10000000 00000000 00000000 0000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(28)}, PaillierInt::fromString("10000000 00000000 00000000 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(29)}, PaillierInt::fromString("10000000 00000000 00000000 000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(30)}, PaillierInt::fromString("10000000 00000000 00000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(31)}, PaillierInt::fromString("10000000 00000000 00000000 00000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t)) {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(32)}, PaillierInt::fromString(" 0000000 00000000 00000000 00000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(32)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 0", 2) );
//	}

	// assertion Nr: 50
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 0)}, PaillierInt::fromString("10000000 00000000 00000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 1)}, PaillierInt::fromString("10000000 00000000 00000000 0", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 2)}, PaillierInt::fromString("10000000 00000000 00000000 00", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 3)}, PaillierInt::fromString("10000000 00000000 00000000 000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 4)}, PaillierInt::fromString("10000000 00000000 00000000 0000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 5)}, PaillierInt::fromString("10000000 00000000 00000000 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 6)}, PaillierInt::fromString("10000000 00000000 00000000 000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 7)}, PaillierInt::fromString("10000000 00000000 00000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 8)}, PaillierInt::fromString("10000000 00000000 00000000 00000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint16_t) || typeid(BIG_INT_WORD_TYPE) == typeid(uint32_t)) {
//		tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 9)}, PaillierInt::fromString(" 0000000 00000000 00000000 00000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("10000000 00000000 00000000", 2), PaillierInt( 9)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 0", 2) );
//	}

	// 5 Byte (40bit)
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(32)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 0", 2) );
	// assertion Nr: 60
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(33)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(34)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(35)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 0000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(36)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(37)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(38)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(39)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(40)}, PaillierInt::fromString(" 0000000 00000000 00000000 00000000 00000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(40)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 0", 2) );
//	}

	tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 0)}, PaillierInt::fromString("10000000 00000000 10110111 00000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 1)}, PaillierInt::fromString("10000000 00000000 10110111 00000000 0", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 2)}, PaillierInt::fromString("10000000 00000000 10110111 00000000 00", 2) );
	// assertion Nr: 70
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 3)}, PaillierInt::fromString("10000000 00000000 10110111 00000000 000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 4)}, PaillierInt::fromString("10000000 00000000 10110111 00000000 0000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 5)}, PaillierInt::fromString("10000000 00000000 10110111 00000000 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 6)}, PaillierInt::fromString("10000000 00000000 10110111 00000000 000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 7)}, PaillierInt::fromString("10000000 00000000 10110111 00000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 8)}, PaillierInt::fromString("10000000 00000000 10110111 00000000 00000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
//		tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 9)}, PaillierInt::fromString(" 0000000 00000000 10110111 00000000 00000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("10000000 00000000 10110111 00000000", 2), PaillierInt( 9)}, PaillierInt::fromString("10000000 00000000 10110111 00000000 00000000 0", 2) );
//	}

	// 8 Byte (64bit)
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(56)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(57)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(58)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(59)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 0000", 2) );
	// assertion Nr: 80
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(60)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(61)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(62)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(63)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2) );
	//tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(64)}, PaillierInt::fromString(" 0000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );

	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2), PaillierInt( 0)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2), PaillierInt( 1)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 0", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2), PaillierInt( 2)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 00", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2), PaillierInt( 3)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2), PaillierInt( 4)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 0000", 2) );
	// assertion Nr: 90
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2), PaillierInt( 5)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2), PaillierInt( 6)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2), PaillierInt( 7)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2), PaillierInt( 8)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 00000000", 2) );
	//tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000", 2), PaillierInt( 9)}, PaillierInt::fromString(" 0000000 01010101 00000000 10110111 00000000 11111101 00000000 00000000 0", 2) );

	// 9 Byte (72bit)
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(64)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(65)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(66)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(67)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(68)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(69)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 000000", 2) );
	// assertion Nr: 100
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(70)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000000", 2) );
	tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(71)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(72)}, PaillierInt::fromString(" 0000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(72)}, PaillierInt::fromString("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0", 2) );
//	}

	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 0)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 1)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 2)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 3)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 4)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 5)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 6)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 7)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 0000000", 2) );
	// assertion Nr: 110
	tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 8)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000000", 2) );
//	if (typeid(BIG_INT_WORD_TYPE) == typeid(uint8_t)) {
//		tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 9)}, PaillierInt::fromString(" 0000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000000 0", 2) );
//	} else {
//		tc.addAssertion({PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101", 2), PaillierInt( 9)}, PaillierInt::fromString("10000000 01010101 00000000 10110111 00000000 11111101 00000000 10111101 00000000 0", 2) );
//	}

	// 12 Byte (96bit)
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  0)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("      1", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  1)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("      2", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  2)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("      4", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  3)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("      8", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  4)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("     16", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  5)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("     32", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  6)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("     64", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  7)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("    128", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  8)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("    256", 10) );
	// assertion Nr: 120
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  9)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("    512", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 10)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("   1024", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 11)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("   2048", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 12)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("   4096", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 13)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("   8192", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 14)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("  16384", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 15)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("  32768", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 16)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("  65536", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 17)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString(" 131072", 10) );

	if(PAILLIER_INT_STORAGE_BIT_LENGTH >= 192) {
		// 24 Byte (192bit)
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 63)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("    9223372036854775808", 10) );
		// assertion Nr: 130
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 64)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("   18446744073709551616", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 65)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("   36893488147419103232", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 66)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("   73786976294838206464", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 67)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("  147573952589676412928", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 68)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("  295147905179352825856", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 69)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("  590295810358705651712", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 70)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString(" 1180591620717411303424", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 71)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString(" 2361183241434822606848", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 72)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString(" 4722366482869645213696", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 73)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString(" 9444732965739290427392", 10) );
	}
	
	if(PAILLIER_INT_STORAGE_BIT_LENGTH >= 208) {
		// 26 Byte (208bit)
		// assertion Nr: 140
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(127)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("170141183460469231731687303715884105728", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(128)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("340282366920938463463374607431768211456", 10) );
		tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(129)}, PaillierInt::fromString("3529260907631713815077", 10) * PaillierInt::fromString("680564733841876926926749214863536422912", 10) );
	}
	
	if(PAILLIER_INT_STORAGE_BIT_LENGTH <= 256) {
		tc.addAssertion({PaillierInt::fromString("1", 2), PaillierInt(PAILLIER_INT_STORAGE_BIT_LENGTH)}, PaillierInt::fromString("0", 2) );
	}
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createShiftRight() {
	BigIntTestCase tc{"GPU big int shiftRight", BIG_INT_GPU_TEST_OPERATION_shiftRight, 2};
	
	PaillierInt a, b;
	

	// 1 Byte (8bit)
	// assertion Nr: 0
	//tc.addAssertion({PaillierInt(  0), PaillierInt(  0)}, PaillierInt(  0 ));
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 0)}, PaillierInt::fromString("10000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 1)}, PaillierInt::fromString( "1000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 2)}, PaillierInt::fromString(  "100000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 3)}, PaillierInt::fromString(   "10000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 4)}, PaillierInt::fromString(    "1000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 5)}, PaillierInt::fromString(     "100", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 6)}, PaillierInt::fromString(      "10", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 7)}, PaillierInt::fromString(       "1", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 8)}, PaillierInt::fromString(       "0", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt( 9)}, PaillierInt::fromString(       "0", 2) );
	tc.addAssertion({PaillierInt::fromString("10000000", 2), PaillierInt(16)}, PaillierInt::fromString(       "0", 2) );

	// 2 Byte (16bit)
	// assertion Nr: 11
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt( 0)}, PaillierInt::fromString("1000001100101101", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt( 1)}, PaillierInt::fromString("0100000110010110", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt( 2)}, PaillierInt::fromString("0010000011001011", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt( 3)}, PaillierInt::fromString("0001000001100101", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt( 4)}, PaillierInt::fromString("0000100000110010", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt( 5)}, PaillierInt::fromString("0000010000011001", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt( 6)}, PaillierInt::fromString("0000001000001100", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt( 7)}, PaillierInt::fromString("0000000100000110", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt( 8)}, PaillierInt::fromString("0000000010000011", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt( 9)}, PaillierInt::fromString("0000000001000001", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt(10)}, PaillierInt::fromString("0000000000100000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt(11)}, PaillierInt::fromString("0000000000010000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt(12)}, PaillierInt::fromString("0000000000001000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt(13)}, PaillierInt::fromString("0000000000000100", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt(14)}, PaillierInt::fromString("0000000000000010", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt(15)}, PaillierInt::fromString("0000000000000001", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt(16)}, PaillierInt::fromString("0000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt(17)}, PaillierInt::fromString("0000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("10000011 00101101", 2), PaillierInt(32)}, PaillierInt::fromString("0000000000000000", 2) );

	// 8 Byte (64bit)
	// assertion Nr: 30
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(  0)}, PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(  1)}, PaillierInt::fromString("0000000010000110110000000101010100101010100011000100100111000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(  2)}, PaillierInt::fromString("0000000001000011011000000010101010010101010001100010010011100000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(  3)}, PaillierInt::fromString("0000000000100001101100000001010101001010101000110001001001110000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(  4)}, PaillierInt::fromString("0000000000010000110110000000101010100101010100011000100100111000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(  5)}, PaillierInt::fromString("0000000000001000011011000000010101010010101010001100010010011100", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(  6)}, PaillierInt::fromString("0000000000000100001101100000001010101001010101000110001001001110", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(  7)}, PaillierInt::fromString("0000000000000010000110110000000101010100101010100011000100100111", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(  8)}, PaillierInt::fromString("0000000000000001000011011000000010101010010101010001100010010011", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(  9)}, PaillierInt::fromString("0000000000000000100001101100000001010101001010101000110001001001", 2) );
	// assertion Nr: 40
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 10)}, PaillierInt::fromString("0000000000000000010000110110000000101010100101010100011000100100", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 11)}, PaillierInt::fromString("0000000000000000001000011011000000010101010010101010001100010010", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 12)}, PaillierInt::fromString("0000000000000000000100001101100000001010101001010101000110001001", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 13)}, PaillierInt::fromString("0000000000000000000010000110110000000101010100101010100011000100", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 14)}, PaillierInt::fromString("0000000000000000000001000011011000000010101010010101010001100010", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 15)}, PaillierInt::fromString("0000000000000000000000100001101100000001010101001010101000110001", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 16)}, PaillierInt::fromString("0000000000000000000000010000110110000000101010100101010100011000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 17)}, PaillierInt::fromString("0000000000000000000000001000011011000000010101010010101010001100", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 18)}, PaillierInt::fromString("0000000000000000000000000100001101100000001010101001010101000110", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 19)}, PaillierInt::fromString("0000000000000000000000000010000110110000000101010100101010100011", 2) );
	// assertion Nr: 50
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 20)}, PaillierInt::fromString("0000000000000000000000000001000011011000000010101010010101010001", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 21)}, PaillierInt::fromString("0000000000000000000000000000100001101100000001010101001010101000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 22)}, PaillierInt::fromString("0000000000000000000000000000010000110110000000101010100101010100", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 23)}, PaillierInt::fromString("0000000000000000000000000000001000011011000000010101010010101010", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 24)}, PaillierInt::fromString("0000000000000000000000000000000100001101100000001010101001010101", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 25)}, PaillierInt::fromString("0000000000000000000000000000000010000110110000000101010100101010", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 26)}, PaillierInt::fromString("0000000000000000000000000000000001000011011000000010101010010101", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 27)}, PaillierInt::fromString("0000000000000000000000000000000000100001101100000001010101001010", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 28)}, PaillierInt::fromString("0000000000000000000000000000000000010000110110000000101010100101", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 29)}, PaillierInt::fromString("0000000000000000000000000000000000001000011011000000010101010010", 2) );
	// assertion Nr: 60
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 30)}, PaillierInt::fromString("0000000000000000000000000000000000000100001101100000001010101001", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 31)}, PaillierInt::fromString("0000000000000000000000000000000000000010000110110000000101010100", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 32)}, PaillierInt::fromString("0000000000000000000000000000000000000001000011011000000010101010", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 33)}, PaillierInt::fromString("0000000000000000000000000000000000000000100001101100000001010101", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 34)}, PaillierInt::fromString("0000000000000000000000000000000000000000010000110110000000101010", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 35)}, PaillierInt::fromString("0000000000000000000000000000000000000000001000011011000000010101", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 36)}, PaillierInt::fromString("0000000000000000000000000000000000000000000100001101100000001010", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 37)}, PaillierInt::fromString("0000000000000000000000000000000000000000000010000110110000000101", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 38)}, PaillierInt::fromString("0000000000000000000000000000000000000000000001000011011000000010", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 39)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000100001101100000001", 2) );
	// assertion Nr: 70
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 40)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000010000110110000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 41)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000001000011011000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 42)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000100001101100000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 43)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000010000110110000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 44)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000001000011011000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 45)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000100001101100", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 46)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000010000110110", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 47)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000001000011011", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 48)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000100001101", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 49)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000010000110", 2) );
	// assertion Nr: 80
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 50)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000001000011", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 51)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000100001", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 52)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000010000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 53)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000001000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 54)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000100", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 55)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000010", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 56)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000001", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 57)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 58)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 59)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 60)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 61)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 62)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 63)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 64)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 65)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 66)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt( 67)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );
	tc.addAssertion({PaillierInt::fromString("00000001 00001101 10000000 10101010 01010101 00011000 10010011 10000001", 2), PaillierInt(127)}, PaillierInt::fromString("0000000000000000000000000000000000000000000000000000000000000000", 2) );


	// 9 Byte (72bit)
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  0)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                      1", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  1)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                      2", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  2)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                      4", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  3)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                      8", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  4)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                     16", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  5)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                     32", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  6)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                     64", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  7)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                    128", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  8)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                    256", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(  9)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                    512", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 10)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                   1024", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 11)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                   2048", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 12)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                   4096", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 13)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                   8192", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 14)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                  16384", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 15)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                  32768", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 16)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("                  65536", 10) );

	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 63)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("    9223372036854775808", 10) );
	
	// divKnuth_multiplySubtract not poible without FIX_BIG_INT_AUTO_SIZE_TEMP_VARS
	// => 10 Byte (80bit)
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 64)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString(  "18446744073709551616", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 65)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString(  "36893488147419103232", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 66)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString(  "73786976294838206464", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 67)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString( "147573952589676412928", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 68)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString( "295147905179352825856", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 69)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString( "590295810358705651712", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 70)}, PaillierInt::fromString("3529260907631713815077", 10) / PaillierInt::fromString("1180591620717411303424", 10) );
	
	// 9 Byte (72bit)
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 71)}, PaillierInt::fromString("1", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 72)}, PaillierInt::fromString("0", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt( 73)}, PaillierInt::fromString("0", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(127)}, PaillierInt::fromString("0", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(128)}, PaillierInt::fromString("0", 10) );
	tc.addAssertion({PaillierInt::fromString("10111111 01010010 01010101 10000000 10101010 01010101 00000001 10001010 00100101", 2), PaillierInt(129)}, PaillierInt::fromString("0", 10) );
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createAddTest() {
	BigIntTestCase tc{"GPU big int add", BIG_INT_GPU_TEST_OPERATION_add, 2};
	
	PaillierInt a, b;
	

	// 1 Byte (8bit)
	// assertion Nr: 0
	tc.addAssertion({PaillierInt(  0), PaillierInt(  0)}, PaillierInt(  0 ));
	tc.addAssertion({PaillierInt(  1), PaillierInt(  0)}, PaillierInt(  1 ));
	tc.addAssertion({PaillierInt(  0), PaillierInt(  1)}, PaillierInt(  1 ));
	tc.addAssertion({PaillierInt(  1), PaillierInt(  1)}, PaillierInt(  2 ));
	tc.addAssertion({PaillierInt(  2), PaillierInt(  1)}, PaillierInt(  3 ));
	// assertion Nr: 5
	tc.addAssertion({PaillierInt(  1), PaillierInt(  2)}, PaillierInt(  3 ));
	tc.addAssertion({PaillierInt( 10), PaillierInt(  1)}, PaillierInt( 11 ));
	tc.addAssertion({PaillierInt(128), PaillierInt(127)}, PaillierInt(255 ));

	// 2 Bytes (16 bit)
	tc.addAssertion({PaillierInt(128), PaillierInt(128)}, PaillierInt::fromString("0100", 16) );
	tc.addAssertion({PaillierInt(255), PaillierInt(  1)}, PaillierInt::fromString("0100", 16) );
	// assertion Nr: 10
	tc.addAssertion({PaillierInt(  1), PaillierInt(255)}, PaillierInt::fromString("0100", 16) );
	tc.addAssertion({PaillierInt(255), PaillierInt(255)}, PaillierInt::fromString("01FE", 16) );
	
	tc.addAssertion({PaillierInt::fromString("7FFF", 16), PaillierInt::fromString("7FFF", 16)}, PaillierInt::fromString("FFFE", 16) );
	tc.addAssertion({PaillierInt::fromString("7FFF", 16), PaillierInt::fromString("8000", 16)}, PaillierInt::fromString("FFFF", 16) );
	tc.addAssertion({PaillierInt::fromString("8000", 16), PaillierInt::fromString("7FFF", 16)}, PaillierInt::fromString("FFFF", 16) );

	// 4 Bytes (32bit)
	// assertion Nr: 15
	tc.addAssertion({PaillierInt::fromString("8000", 16), PaillierInt::fromString("8000", 16)}, PaillierInt::fromString("010000", 16) );
	tc.addAssertion({PaillierInt::fromString("FFFF", 16), PaillierInt::fromString(  "01", 16)}, PaillierInt::fromString("010000", 16) );
	tc.addAssertion({PaillierInt::fromString(  "01", 16), PaillierInt::fromString("FFFF", 16)}, PaillierInt::fromString("010000", 16) );
	tc.addAssertion({PaillierInt::fromString("FFFF", 16), PaillierInt::fromString("FFFF", 16)}, PaillierInt::fromString("01FFFE", 16) );

	tc.addAssertion({PaillierInt::fromString("7FFFFFFF", 16), PaillierInt::fromString("7FFFFFFF", 16)}, PaillierInt::fromString("FFFFFFFE", 16) );
	// assertion Nr: 20
	tc.addAssertion({PaillierInt::fromString("7FFFFFFF", 16), PaillierInt::fromString("80000000", 16)}, PaillierInt::fromString("FFFFFFFF", 16) );
	tc.addAssertion({PaillierInt::fromString("80000000", 16), PaillierInt::fromString("7FFFFFFF", 16)}, PaillierInt::fromString("FFFFFFFF", 16) );

	// 8 Bytes (64bit)
	tc.addAssertion({PaillierInt::fromString("80000000", 16), PaillierInt::fromString("80000000", 16)}, PaillierInt::fromString("0100000000", 16) );
	tc.addAssertion({PaillierInt::fromString("FFFFFFFF", 16), PaillierInt::fromString(      "01", 16)}, PaillierInt::fromString("0100000000", 16) );
	tc.addAssertion({PaillierInt::fromString(      "01", 16), PaillierInt::fromString("FFFFFFFF", 16)}, PaillierInt::fromString("0100000000", 16) );
	// assertion Nr: 25
	tc.addAssertion({PaillierInt::fromString("FFFFFFFF", 16), PaillierInt::fromString("FFFFFFFF", 16)}, PaillierInt::fromString("01FFFFFFFE", 16) );

	tc.addAssertion({PaillierInt::fromString("7FFFFFFFFFFFFFFF", 16), PaillierInt::fromString("7FFFFFFFFFFFFFFF", 16)}, PaillierInt::fromString("FFFFFFFFFFFFFFFE", 16) );
	tc.addAssertion({PaillierInt::fromString("7FFFFFFFFFFFFFFF", 16), PaillierInt::fromString("8000000000000000", 16)}, PaillierInt::fromString("FFFFFFFFFFFFFFFF", 16) );
	tc.addAssertion({PaillierInt::fromString("8000000000000000", 16), PaillierInt::fromString("7FFFFFFFFFFFFFFF", 16)}, PaillierInt::fromString("FFFFFFFFFFFFFFFF", 16) );

	// 16 Bytes (128bit)
	// assertion Nr: 30
	tc.addAssertion({PaillierInt::fromString("FFFFFFFFFFFFFFFF", 16), PaillierInt(1)}, PaillierInt::fromString("18446744073709551616", 10) ); // 2^64

	tc.addAssertion({PaillierInt::fromString("8000000000000000", 16), PaillierInt::fromString("8000000000000000", 16)}, PaillierInt::fromString("18446744073709551616", 10) ); // 2^64
	tc.addAssertion({PaillierInt::fromString("FFFFFFFFFFFFFFFF", 16), PaillierInt::fromString(              "01", 16)}, PaillierInt::fromString("010000000000000000", 16) ); // 2^64
	tc.addAssertion({PaillierInt::fromString(              "01", 16), PaillierInt::fromString("FFFFFFFFFFFFFFFF", 16)}, PaillierInt::fromString("010000000000000000", 16) ); // 2^64
	tc.addAssertion({PaillierInt::fromString("FFFFFFFFFFFFFFFF", 16), PaillierInt::fromString("FFFFFFFFFFFFFFFF", 16)}, PaillierInt::fromString("01FFFFFFFFFFFFFFFE", 16) );

	// assertion Nr: 35
	tc.addAssertion({PaillierInt::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16), PaillierInt::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16)}, PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFE", 16) );
	tc.addAssertion({PaillierInt::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16), PaillierInt::fromString("80000000 00000000 00000000 00000000", 16)}, PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) );
	tc.addAssertion({PaillierInt::fromString("80000000 00000000 00000000 00000000", 16), PaillierInt::fromString("7FFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16)}, PaillierInt::fromString("FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF", 16) );

	if(PAILLIER_INT_STORAGE_BIT_LENGTH >= 192) {
		tc.addAssertion({PaillierInt::fromString("123456 789abcde f0000000 00000000 12345678 9abcdef0", 16), PaillierInt::fromString("fedcba9 87654321 00000000 00000000 fedcba98 76543210", 16)}, PaillierInt::fromString("fffffff ffffffff f0000000 00000001 11111111 11111100", 16) );
		tc.addAssertion({PaillierInt::fromString("fedcba9 87654321 00000000 00000000 fedcba98 76543210", 16), PaillierInt::fromString("123456 789abcde f0000000 00000000 12345678 9abcdef0", 16)}, PaillierInt::fromString("FFFFFFF FFFFFFFF F0000000 00000001 11111111 11111100", 16) );

		// assertion Nr: 40
		tc.addAssertion({PaillierInt::fromString("123456789000000000000000000000000000001234567890", 10), PaillierInt::fromString("987654321000000000000000000000000000009876543210", 10)}, PaillierInt::fromString("1111111110000000000000000000000000000011111111100", 10) );
		tc.addAssertion({PaillierInt::fromString("987654321000000000000000000000000000009876543210", 10), PaillierInt::fromString("123456789000000000000000000000000000001234567890", 10)}, PaillierInt::fromString("1111111110000000000000000000000000000011111111100", 10) );
	}
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createSubTest() {
	BigIntTestCase tc{"GPU big int sub", BIG_INT_GPU_TEST_OPERATION_sub, 2};
	
	PaillierInt a, b;
	
	// assertion Nr: 0
	// 1 Byte (8bit)
	tc.addAssertion({PaillierInt(  0), PaillierInt(  0)}, PaillierInt(0)); // 0 - 0 = 0
	tc.addAssertion({PaillierInt(  1), PaillierInt(  0)}, PaillierInt(1)); // 1 - 0 = 1
	tc.addAssertion({PaillierInt(  1), PaillierInt(  1)}, PaillierInt(0)); // 1 - 1 = 0

	tc.addAssertion({PaillierInt(  9), PaillierInt(  1)}, PaillierInt(  8 )); // 9 - 1 = 8
	tc.addAssertion({PaillierInt(  9), PaillierInt(  9)}, PaillierInt(  0 ));
	// assertion Nr: 5
	tc.addAssertion({PaillierInt( 10), PaillierInt(  9)}, PaillierInt(  1 ));
	tc.addAssertion({PaillierInt(255), PaillierInt(  0)}, PaillierInt(255 ));
	tc.addAssertion({PaillierInt(255), PaillierInt(255)}, PaillierInt(  0 ));
	tc.addAssertion({PaillierInt(255), PaillierInt(  1)}, PaillierInt(254 ));

	// 2 Bytes (16 bit)
	tc.addAssertion({PaillierInt::fromString("0100", 16), PaillierInt::fromString("0100", 16)}, PaillierInt::fromString("00", 16)); // 256 - 256 = 0
	// assertion Nr: 10
	tc.addAssertion({PaillierInt::fromString("0101", 16), PaillierInt::fromString("0100", 16)}, PaillierInt::fromString("01", 16)); // 257 - 256 = 1
	tc.addAssertion({PaillierInt::fromString("0101", 16), PaillierInt::fromString("  01", 16)}, PaillierInt::fromString("0100", 16)); // 257 - 1 = 256
	tc.addAssertion({PaillierInt::fromString("0101", 16), PaillierInt::fromString("  02", 16)}, PaillierInt::fromString("FF", 16)); // 257 - 2 = 255

	// 4 Bytes (32bit)
	tc.addAssertion({PaillierInt::fromString("010000", 16), PaillierInt::fromString("010000", 16)}, PaillierInt::fromString("00", 16)); // 2^16 - 2^16 = 0
	tc.addAssertion({PaillierInt::fromString("010001", 16), PaillierInt::fromString("010000", 16)}, PaillierInt::fromString("01", 16)); // (2^16 + 1) - 2^16 = 1
	// assertion Nr: 15
	tc.addAssertion({PaillierInt::fromString("010001", 16), PaillierInt::fromString("    01", 16)}, PaillierInt::fromString("010000", 16)); // (2^16 + 1) - 1 = 2^16
	tc.addAssertion({PaillierInt::fromString("010001", 16), PaillierInt::fromString("    02", 16)}, PaillierInt::fromString("00FFFF", 16)); // (2^16 + 1) - 2 = 2^16 - 1

	// 8 Bytes (64bit)
	tc.addAssertion({PaillierInt::fromString("0100000000", 16), PaillierInt::fromString("0100000000", 16)}, PaillierInt::fromString("00", 16)); // 2^32 - 2^32 = 0
	tc.addAssertion({PaillierInt::fromString("0100000001", 16), PaillierInt::fromString("0100000000", 16)}, PaillierInt::fromString("01", 16)); // (2^32 + 1) - 2^32 = 1
	tc.addAssertion({PaillierInt::fromString("0100000001", 16), PaillierInt::fromString("01", 16)}, PaillierInt::fromString("0100000000", 16)); // (2^32 + 1) - 1 = 2^32
	// assertion Nr: 20
	tc.addAssertion({PaillierInt::fromString("0100000001", 16), PaillierInt::fromString("02", 16)}, PaillierInt::fromString("00FFFFFFFF", 16)); // (2^32 + 1) - 2 = 2^32 - 1

	// 16 Bytes (128bit)
	tc.addAssertion({PaillierInt::fromString("010000000000000000", 16), PaillierInt::fromString("010000000000000000", 16)}, PaillierInt::fromString("00", 16)      ); // 2^64 - 2^64 = 0
	tc.addAssertion({PaillierInt::fromString("010000000000000001", 16), PaillierInt::fromString("010000000000000000", 16)}, PaillierInt::fromString("01", 16)      ); // (2^64 + 1) - 2^64 = 1
	tc.addAssertion({PaillierInt::fromString("010000000000000001", 16), PaillierInt::fromString("01", 16)}, PaillierInt::fromString("010000000000000000", 16) ); // (2^64 + 1) - 1 = 2^64
	tc.addAssertion({PaillierInt::fromString("010000000000000001", 16), PaillierInt::fromString("02", 16)}, PaillierInt::fromString("FFFFFFFFFFFFFFFF", 16)   ); // (2^64 + 1) - 2 = 2^64 - 1

	if(PAILLIER_INT_STORAGE_BIT_LENGTH >= 192) {
		// assertion Nr: 25
		tc.addAssertion({PaillierInt::fromString(" fedcba9 87654321 00000000 00000000 fedcba98 76543210", 16), PaillierInt::fromString("  123456 789abcde f0000000 00000000 12345678 9abcdef0", 16)}, PaillierInt::fromString("  fdb9753 0eca8642 10000000 00000000 eca8641f db975320", 16) );
		tc.addAssertion({PaillierInt::fromString("987 654 321 000 000 000 000 000 000 000 000 000 009 876 543 210", 10), PaillierInt::fromString("123 456 789 000 000 000 000 000 000 000 000 000 001 234 567 890", 10)}, PaillierInt::fromString("864 197 532 000 000 000 000 000 000 000 000 000 008 641 975 320", 10) );
	
	}
	return tc;
}

BigIntTestCase BigIntTestFactory::createMulTest() {
	BigIntTestCase tc{"GPU big int mul", BIG_INT_GPU_TEST_OPERATION_mul, 2};
	
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

