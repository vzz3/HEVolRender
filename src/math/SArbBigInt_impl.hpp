

#include "SFixBigInt.hpp"

using ppvr::math::SArbBigInt;
using ppvr::math::SFixBigInt;

template <BIG_INT_WORD_COUNT_TYPE S>
SArbBigInt SArbBigInt::fromSFixBigInt(const SFixBigInt<S>& src) {
	SArbBigInt res{0, src.getWordSize()};
	SArbBigInt::fromSFixBigInt(src, res);
	return res;
}

template <BIG_INT_WORD_COUNT_TYPE S>
SArbBigInt& SArbBigInt::fromSFixBigInt(const SFixBigInt<S>& src, SArbBigInt &target) {
	BIG_INT_WORD_COUNT_TYPE srcWordCount = src.getWordSize();
	UArbBigInt::fromUFixBigInt(src.asUnsigned(), target);
	target.signum = src.getSignum();
	return target;
}
