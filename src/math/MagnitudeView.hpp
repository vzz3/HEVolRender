#pragma once
#include "BigInt_wordDef.h"
#include <cassert>


namespace ppvr {
	namespace math {
	
		class MagnitudeView {
			
		// ----- members -----
		private:
			BIG_INT_WORD_COUNT_TYPE _wordCapacity; // length of the value array
			BIG_INT_WORD_TYPE *_value;
			
		// ----- data access -----
		public:
			inline const BIG_INT_WORD_COUNT_TYPE wordCapacity() const {
				return this->_wordCapacity;
			}
			
			inline const BIG_INT_WORD_TYPE* value() const {
				return this->_value;
			}
			
			//inline BIG_INT_WORD_TYPE* value() {
			//	return this->_value;
			//}
			
			const BIG_INT_WORD_TYPE& operator[](const BIG_INT_WORD_COUNT_TYPE i) const {
				assert(i<_wordCapacity);
				return _value[i];
			}
			
			BIG_INT_WORD_TYPE& operator[](const BIG_INT_WORD_COUNT_TYPE i) {
				assert(i<_wordCapacity);
				return _value[i];
			}
			
		// ----- constructors -----
		public:
			/**
			 * Copy constructor
			 */
			//UArbBigInt(const UArbBigInt& src);
			//UArbBigInt(const UArbBigInt& src, BIG_INT_WORD_COUNT_TYPE minCapacity);
			
			/**
			 * Move constructor
			 */
			//UArbBigInt(UArbBigInt&& src);
		//private:
			inline MagnitudeView(BIG_INT_WORD_TYPE* yValue, BIG_INT_WORD_COUNT_TYPE yWordCapacity)
				: _value{yValue}, _wordCapacity{yWordCapacity}
			{
				assert( yValue != nullptr);
			}
		public:
			//~UArbBigInt();

		

		// ----- memory managment -----
		public:
			/**
			 * Copy assignment operator
			 */
			//UArbBigInt& operator= (const UArbBigInt& other);

			/**
			 * Move assignment operator
			 */
			//UArbBigInt& operator= (UArbBigInt&& other);

		
		};
	}
}

