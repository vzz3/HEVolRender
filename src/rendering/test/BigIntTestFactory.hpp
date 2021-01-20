#pragma once

#include <vector>
#include "./BigIntTestCase.hpp"


namespace ppvr {
	namespace rendering {
		namespace test {
			class BigIntTestFactory {
			public:
				static std::vector<BigIntTestCase> createAllTest();
				
			//private:
				static BigIntTestCase createCopyTest();
				static BigIntTestCase createMulTest();
			};
		}
	}
}
