#pragma once

#include <stdexcept>

namespace ppvr {
	namespace math {
		struct FixBigIntOverflow : public std::logic_error {
			FixBigIntOverflow( const std::string& what_arg ): std::logic_error(what_arg) {}
			FixBigIntOverflow( const char* what_arg ): std::logic_error(what_arg) {}
			FixBigIntOverflow( const logic_error& other ): std::logic_error(other) {}
			//FixBigIntOverflow( const logic_error& other ) noexcept: std::logic_error(other) {}

		};
	}
}
