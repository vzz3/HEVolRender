

#include "UFixBigInt.hpp"

using ppvr::math::UArbBigInt;
using ppvr::math::UFixBigInt;

template <BIG_INT_WORD_COUNT_TYPE S>
UArbBigInt UArbBigInt::fromUFixBigInt(const UFixBigInt<S>& src) {
	UArbBigInt res{0, src.getWordSize()};
	UArbBigInt::fromUFixBigInt(src, res);
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
UArbBigInt& UArbBigInt::fromUFixBigInt(const UFixBigInt<S>& src, UArbBigInt &target) {
	BIG_INT_WORD_COUNT_TYPE srcWordCount = src.getWordSize();
	/*
	if(srcWordCount > S ) {
		std::string msg = "overflow error, provided UArbBigInt (" + std::to_string(srcWordCount) +  " wordes) does not fit  not the target UFixBigInt<S> (" + std::to_string(S) +  " wordes).";
		//std::cerr << msg << std::endl;
		throw std::invalid_argument(msg);
	}
	*/
	target.reserveWords(srcWordCount);
	target.wordSize = srcWordCount;
	
	const BIG_INT_WORD_TYPE (&srcData)[S] = src.getData(); // const referenc to array (yes, I need to lookop the C++ reference to get that syntax right...)
	//BIG_INT_WORD_TYPE test = srcData[0]; // OK
	//BIG_INT_WORD_TYPE test2 = srcData[1]; // Warning, if S=1:  Array index 1 is past the end of the array (which contains 1 element)
	//srcData[0] = 99; // Error: readonly
	
	std::copy_n(srcData, srcWordCount, target.value);
	//std::fill_n(&(target.value[srcWordCount]), S - srcWordCount, 0);
	return target;
}
