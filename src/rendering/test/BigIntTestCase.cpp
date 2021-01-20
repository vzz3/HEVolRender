
#include "BigIntTestCase.hpp"



using namespace ppvr::rendering::test;



BigIntTestCase::BigIntTestCase(const std::string yName, const uint32_t yGpuOperationType
			, const size_t yAssertionCount, const size_t yMaxInputVarsPerOperation)
	: 	  name{yName}
		, gpuOperationType{yGpuOperationType}
		, srcVolume{yMaxInputVarsPerOperation, yAssertionCount, 1, PaillierInt(0)}
		, refImage {1,                         yAssertionCount,    PaillierInt(0)}
{
	
}

BigIntTestCase::~BigIntTestCase() {

}


void BigIntTestCase::addAssertion(const std::vector<PaillierInt>& yInputVars, const PaillierInt& yResult) {
	size_t c = this->assertionCount;
	this->setAssertion(c, yInputVars, yResult);
	this->assertionCount++;
}

void BigIntTestCase::setAssertion(const size_t yAssertionIndex, const std::vector<PaillierInt>& yInputVars, const PaillierInt& yResult) {
	if(yAssertionIndex >= srcVolume.height()) {
		std::string msg = "The TestCase \"" + name + "\" supports only " + std::to_string(srcVolume.height()) + " assertions.";
		throw std::logic_error(msg);
	}
	if(yInputVars.size() > srcVolume.width()) {
		std::string msg = "This TestCase \"" + name + "\" supports only " + std::to_string(srcVolume.width()) + " input vars.";
		throw std::logic_error(msg);
	}

	refImage [0][yAssertionIndex] = yResult;
	for(size_t i = 0; i < yInputVars.size(); i++) {
		srcVolume[i][yAssertionIndex][0] = yInputVars[i];
	}
}

QSize BigIntTestCase::getRequiredFboSize() const {
	return QSize{static_cast<int>(refImage.width()), static_cast<int>(refImage.height())};
}
