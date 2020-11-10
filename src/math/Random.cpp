
#include "Random.hpp"

using namespace ppvr::math;

Random* Random::fixMe = NULL;

Random& Random::getForLocalThread() {
	if(Random::fixMe == NULL) {
		fixMe = new Random();
	}
	return *fixMe;
}

Random::Random():
	rdev(), // inizialize std::random_device
	randEngine(rdev) // inzialize the isaac64 engine with a seed from the std::random_device
{
}

Random::~Random() {
}

void Random::randomFill(void * buf, std::size_t count) {
	static constexpr std::size_t word_size = sizeof(typename Random::RandomGenerator::result_type);
	unsigned char* p = (unsigned char*)buf;
	unsigned char* limit = p + count;
	while (p < limit) {
		auto word = this->randEngine();
		auto n = std::min(static_cast<std::size_t>(limit - p), word_size);
		std::memcpy(p, &word, n);
		p += n;
	}
}

