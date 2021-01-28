#pragma once

#include <string>
#include <chrono>

using std::chrono::high_resolution_clock;


#define PRINT_DURATION(f, name) {									\
	auto t1 = ppvr::util::DurationDisplay::beginTask(name);			\
	f;																\
	ppvr::util::DurationDisplay::endTask(t1);						\
}

namespace ppvr {
	namespace util {
		class DurationDisplay {
		public:
			typedef std::chrono::high_resolution_clock::time_point Task;
		
			
			/**
			 * Displays the begin of a new Task and returns the task begin.
			 */
			static Task beginTask(const std::string& yTaskName);
			
			/**
			 * Prints the duration of the task.
			 */
			static void endTask(const Task& yTaskBegin);
			
			
		};
	}
}
