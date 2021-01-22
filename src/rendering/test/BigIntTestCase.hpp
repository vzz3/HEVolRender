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
			private:
				struct Assertion {
					Assertion(const std::vector<PaillierInt>& yInputVars, const PaillierInt& yResult);
					const std::vector<PaillierInt> inputVars;
					const PaillierInt result;
				};
		
			public:
				BigIntTestCase(const std::string yName, const uint32_t yGpuOperationType
					, const size_t yMaxInputVarsPerOperation = 2);
				~BigIntTestCase();
			
				void addAssertion(const std::vector<PaillierInt>& yInputVars, const PaillierInt& yResult);
				//void setAssertion(const size_t yAssertionIndex, const std::vector<PaillierInt>& yInputVars, const PaillierInt& yResult);
				
				QSize getRequiredFboSize() const;
				const Volume<PaillierInt>& getSrcVolume();
				const Image<PaillierInt>& getRefImage();
				
			private:
				void checkAssertion(const Assertion& yAssertion);
				void buildTextures();
			
			public:
				const uint32_t gpuOperationType;
				const std::string name;//{"GPU big int copy"};
			
			private:
				//size_t assertionCount = 0;
				bool texturesRequireUpdate = true;
				size_t maxInputVarsPerOperation;
				std::vector<Assertion> assertions;
				Volume<PaillierInt> srcVolume;
				Image<PaillierInt> refImage;
			};
		}
	}
}
