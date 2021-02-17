#pragma once

#include <vector>
#include "./BigIntTestCase.hpp"
#include <array>


namespace ppvr {
	namespace rendering {
		namespace test {
			class BigIntTestFactory {
			public:
				static std::vector<BigIntTestCase> createAllTest();
				
			//private:
				static BigIntTestCase createCopyTest();
				
				static BigIntTestCase createLessThanTest();
				static BigIntTestCase createLessThanOrEqualToTest();
				static BigIntTestCase createGreaterThanTest();
				static BigIntTestCase createGreaterThanOrEqualToTest();
				static BigIntTestCase createEqualToTest();
				static BigIntTestCase createNotEqualToTest();
				
				static BigIntTestCase createShiftLeftTest();
				static BigIntTestCase createShiftRightTest();
				
				static BigIntTestCase createXorTest();
				static BigIntTestCase createAndTest();
				
				static BigIntTestCase createAddTest();
				static BigIntTestCase createSubTest();
				static BigIntTestCase createMulTest();
				static std::array<BigIntTestCase,2> createDivAndModTest();
			};
		}
	}
}
