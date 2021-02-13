
#include "Random.hpp"

#include <QThread>

using namespace ppvr::math;

//Random* Random::fixMe = nullptr;
QMutex Random::PerThreadMapMutex{};
std::unordered_map<Qt::HANDLE, Random*> Random::PerThreadMap{};

Random* Random::getForLocalThread() {
	Qt::HANDLE threadId = QThread::currentThreadId();
	PerThreadMapMutex.lock();
	if (PerThreadMap.find(threadId) == PerThreadMap.end()) {
		PerThreadMap.insert({threadId,  new Random{}});
	}
	Random* res = PerThreadMap[threadId];
	PerThreadMapMutex.unlock();
	return res;
}

Random::Random():
	rdev(), // inizialize std::random_device
	//randEngine() // insecure!!!!! but nice for testing, seed is zero! produces always the same squence of pseudo random numbers!
	randEngine(rdev) // inzialize the isaac64 engine with a seed from the std::random_device
{
}

Random::~Random() {
}

void Random::randomFill(void * buf, std::size_t count) {
	#ifdef USE_ISAAC_RANDOM_NUMBER_ENGINE
		static constexpr std::size_t word_size = sizeof(typename Random::RandomGenerator::result_type);
	#else
		static constexpr std::size_t word_size = sizeof(typename isaac64_engine::result_type);
	#endif
	
	unsigned char* p = (unsigned char*)buf;
	unsigned char* limit = p + count;
	while (p < limit) {
		auto word = this->randEngine();
		auto n = std::min(static_cast<std::size_t>(limit - p), word_size);
		std::memcpy(p, &word, n);
		p += n;
	}
}

