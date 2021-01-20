#pragma once

#include <vector>
#include "../data/Volume.hpp"
#include "../data/Image.hpp"

#include "../../paillier/Paillier_typeDev.h"
#include <QSize>

namespace ppvr {
	namespace rendering {
		namespace test {
			class BigIntTestCase {
		
			public:
				BigIntTestCase(const std::string yName, const uint32_t yGpuOperationType
					, const size_t yAssertionCount, const size_t yMaxInputVarsPerOperation = 2);
				~BigIntTestCase();
			
				void addAssertion(const std::vector<PaillierInt>& yInputVars, const PaillierInt& yResult);
				void setAssertion(const size_t yAssertionIndex, const std::vector<PaillierInt>& yInputVars, const PaillierInt& yResult);
				
				QSize getRequiredFboSize() const;
				
			
				Volume<PaillierInt> srcVolume;
				Image<PaillierInt> refImage;
			
				const uint32_t gpuOperationType;
				const std::string name;//{"GPU big int copy"};
			
			private:
				size_t assertionCount = 0;
			};
		}
	}
}
