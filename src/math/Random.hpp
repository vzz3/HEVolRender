#pragma once

#include "../../include/isaac-engine/isaac.h"
#include <random>
/*
namespace utils {
	template<std::size_t Alpha = 8>
	class isaac64;
}
*/

namespace ppvr {
	namespace math {
		/**
		 * This class is not thread save => every thread need its own Random instance!
		 */
		class Random {
		
		public:
			static Random* fixMe;
			static Random& getForLocalThread(); // something like this could be very helpfule for a multi threaded program
		
		// ----- constructors -----
		public:
			Random();
			~Random();
			
		private:
			std::random_device rdev;
			
			// Alpha should (generally) either be 8 for crypto use, or 4 for non-crypto use.
			// If not provided, it defaults to 8
			static constexpr std::size_t isaacAlpha = 8;
			
			typedef utils::isaac64<isaacAlpha> RandomGenerator;
			
			// Alpha determines the size (in elements of result_type) of the
			// internal state, and the size of the initial state for seeding.
			RandomGenerator randEngine;
		
		public:
			void randomFill(void * buf, std::size_t count);
		};
	}
}
