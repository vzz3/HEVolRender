
#include "BigIntTestFactory.hpp"
#include "BigIntGpuTestOperation_types.hpp"

using namespace ppvr::rendering::test;


std::vector<BigIntTestCase> BigIntTestFactory::createAllTest() {
	std::vector<BigIntTestCase> testCases;
	
	testCases.push_back(createCopyTest());
	testCases.push_back(createMulTest());
	
	return testCases;
}


BigIntTestCase BigIntTestFactory::createCopyTest() {
	size_t s = 13;
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
	
	
	return tc;
}

BigIntTestCase BigIntTestFactory::createMulTest() {
	size_t s = 17;
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
	tc.addAssertion({a,b}, (a*b)); // result: FF
	
	a = PaillierInt::fromString("FF", 16); // 8 bit
	b = PaillierInt::fromString("1", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("80", 16); // 8 bit
	b = PaillierInt::fromString("2", 16);
	tc.addAssertion({a,b}, (a*b)); // result: 100
	
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
	tc.addAssertion({a,b}, (a*b)); // result: 1FE
	
	a = PaillierInt::fromString("FFFFFFFF", 16); // 32 bit
	b = PaillierInt::fromString("FFFFFFFF", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF", 16); // 64 bit
	b = PaillierInt::fromString("FFFFFFFF FFFFFFFF", 16);
	tc.addAssertion({a,b}, (a*b));
	
	// assertion Nr: 15
	a = PaillierInt::fromString("10000000 00000000", 16); // 32 bit
	b = PaillierInt::fromString("12345678 9ABCDEF0", 16);
	tc.addAssertion({a,b}, (a*b));
	
	a = PaillierInt::fromString("FFFFFFFF FFFFFFFF", 16); // 32 bit
	b = PaillierInt::fromString("12345678 9ABCDEF0", 16);
	tc.addAssertion({a,b}, (a*b));
	
	return tc;
}

