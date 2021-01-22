
#include "BigIntTestCase.hpp"



using namespace ppvr::rendering::test;


BigIntTestCase::Assertion::Assertion(const std::vector<PaillierInt>& yInputVars, const PaillierInt& yResult)
	: inputVars(yInputVars), result(yResult) {
}


BigIntTestCase::BigIntTestCase(const std::string yName, const uint32_t yGpuOperationType, const size_t yMaxInputVarsPerOperation)
	: name{yName}
	, gpuOperationType{yGpuOperationType}
	, maxInputVarsPerOperation{yMaxInputVarsPerOperation}
{
	
}

BigIntTestCase::~BigIntTestCase() {

}


void BigIntTestCase::addAssertion(const std::vector<PaillierInt>& yInputVars, const PaillierInt& yResult) {
	Assertion assertion{yInputVars, yResult};
	checkAssertion(assertion);
	assertions.push_back(assertion);
	texturesRequireUpdate = true;
}

/*
void BigIntTestCase::setAssertion(const size_t yAssertionIndex, const std::vector<PaillierInt>& yInputVars, const PaillierInt& yResult) {
//	if(yAssertionIndex >= srcVolume.height()) {
//		std::string msg = "The TestCase \"" + name + "\" supports only " + std::to_string(srcVolume.height()) + " assertions.";
//		throw std::logic_error(msg);
//	}
//	if(yInputVars.size() > srcVolume.width()) {
//		std::string msg = "This TestCase \"" + name + "\" supports only " + std::to_string(srcVolume.width()) + " input vars.";
//		throw std::logic_error(msg);
//	}

	Assertion assertion{yInputVars, yResult};
	checkAssertion(assertion);
	assertions[yAssertionIndex] = assertion;
	texturesRequireUpdate = true;
}
*/

QSize BigIntTestCase::getRequiredFboSize() const {
	return QSize{static_cast<int>(1), static_cast<int>(assertions.size())};
}

const Volume<PaillierInt>& BigIntTestCase::getSrcVolume() {
	if(texturesRequireUpdate) {
		buildTextures();
	}
	return srcVolume;
}

const Image<PaillierInt>& BigIntTestCase::getRefImage() {
	if(texturesRequireUpdate) {
		buildTextures();
	}
	return refImage;
}

void BigIntTestCase::checkAssertion(const Assertion& yAssertion) {
	if(yAssertion.inputVars.size() > maxInputVarsPerOperation) {
		std::string msg = "This TestCase \"" + name + "\" supports only " + std::to_string(maxInputVarsPerOperation) + " input vars.";
		throw std::logic_error(msg);
	}
}

void BigIntTestCase::buildTextures() {
	srcVolume.resize(maxInputVarsPerOperation, assertions.size(), 1, PaillierInt(0));
	refImage.resize (1,                        assertions.size(),    PaillierInt(0));
	
	for(size_t row = 0; row < assertions.size(); row++) {
		Assertion assertion = assertions[row];
		refImage[0][row] = assertion.result;
		for(size_t i = 0; i < maxInputVarsPerOperation; i++) {
			srcVolume[i][row][0] = assertion.inputVars[i];
		}
	}
	
	texturesRequireUpdate = false;
}
