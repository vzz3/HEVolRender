#pragma once

#include <stdexcept>

namespace ppvr {
	namespace paillier {
		namespace math {
			struct EncodeException : public std::logic_error {
				EncodeException( const std::string& what_arg ): std::logic_error(what_arg) {}
				EncodeException( const char* what_arg ): std::logic_error(what_arg) {}
				EncodeException( const logic_error& other ): std::logic_error(other) {}
				//EncodeException( const logic_error& other ) noexcept: std::logic_error(other) {}

			};
			
			struct DecodeException : public std::logic_error {
				DecodeException( const std::string& what_arg ): std::logic_error(what_arg) {}
				DecodeException( const char* what_arg ): std::logic_error(what_arg) {}
				DecodeException( const logic_error& other ): std::logic_error(other) {}
				//DecodeException( const logic_error& other ) noexcept: std::logic_error(other) {}
				
			};
			
			struct PaillierKeyMismatchException: public std::logic_error {
				PaillierKeyMismatchException( const std::string& what_arg ): std::logic_error(what_arg) {}
				PaillierKeyMismatchException( const char* what_arg ): std::logic_error(what_arg) {}
				PaillierKeyMismatchException( const logic_error& other ): std::logic_error(other) {}
				//DecodeException( const logic_error& other ) noexcept: std::logic_error(other) {}
				
			};
		}
	}
}
