
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

