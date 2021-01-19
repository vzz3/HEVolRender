#pragma once

#include <vector>
#include "./BigIntTestCase.hpp"

#define BIG_INT_GPU_TEST_OPERATION_copy 1

namespace ppvr {
	namespace rendering {
		namespace test {
			class BigIntTestFactory {
			public:
				static std::vector<BigIntTestCase> createAllTest();
				
			//private:
				static BigIntTestCase createCopyTest();
			};
		}
	}
}
