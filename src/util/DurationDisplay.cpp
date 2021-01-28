
#include "DurationDisplay.hpp"

#include <iostream>
#include <chrono>

using namespace ppvr::util;

DurationDisplay::Task DurationDisplay::beginTask(const std::string& yTaskName) {
	DurationDisplay::Task t1 = std::chrono::high_resolution_clock::now();
	std::cout << "Begin Task " << yTaskName << " ...";
	return t1;
}

void DurationDisplay::endTask(const Task& yTaskBegin) {
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - yTaskBegin ).count();
	std::cout << " time required: " << duration << "ms" << std::endl;
}
