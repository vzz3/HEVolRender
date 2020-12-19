#pragma once

//#define USE_ISAAC_RANDOM_NUMBER_ENGINE

#include <random>

#ifdef USE_ISAAC_RANDOM_NUMBER_ENGINE
	#include "../../include/isaac-engine/isaac.h"
#else
	#include "../../include/cpp_isaac64/isaac64_engine.h"
	//class isaac64_engine;
#endif
/*
namespace utils {
	template<std::size_t Alpha = 8>
	class isaac64;
}
*/

// https://burtleburtle.net/bob/rand/isaacafa.html
// https://github.com/edgeofmagic/ISAAC-engine/blob/master/isaac.h
// https://github.com/sjinks/cpp_isaac64/blob/master/isaac64_engine.h
// http://www.cplusplus.com/forum/beginner/37298/

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
			
			#ifdef USE_ISAAC_RANDOM_NUMBER_ENGINE
				// Alpha determines the size (in elements of result_type) of the
				// internal state, and the size of the initial state for seeding.
			
				// Alpha should (generally) either be 8 for crypto use, or 4 for non-crypto use.
				// If not provided, it defaults to 8
				static constexpr std::size_t isaacAlpha = 8;
			
				typedef utils::isaac64<isaacAlpha> RandomGenerator;
			#else
				typedef isaac64_engine RandomGenerator;
			#endif
			
			RandomGenerator randEngine;
			
			/*
			#ifndef USE_ISAAC_RANDOM_NUMBER_ENGINE
			void seed(std::random_device& dev)
			{
				std::vector<typename isaac64_engine::result_type> seed_vec;
				seed_vec.reserve(isaac64_engine::randsiz());
				for (auto i = 0; i < isaac64_engine::randsiz(); ++i)
				{
					isaac64_engine::result_type value;
					value = dev();
					std::size_t bytes_filled{sizeof(std::random_device::result_type)};
					while(bytes_filled < sizeof(isaac64_engine::result_type))
					{
						value <<= (sizeof(std::random_device::result_type) * 8);
						value |= dev();
						bytes_filled += sizeof(std::random_device::result_type);
					}
					seed_vec.push_back(value);
				}
				randEngine.seed(seed_vec.begin(), seed_vec.end());
			}
			
			template<class Iter>
			void seed(Iter begin, Iter end)
			{
				Iter it = begin;
				for (std::size_t i = 0; i < isaac64_engine::randsiz(); ++i)
				{
					if (it == end)
					{
						it = begin;
					}
					result_[i] = *it;
					++it;
				}
				init();
			}
			#endif
			 */
		
		public:
			void randomFill(void * buf, std::size_t count);
		};
	}
}
