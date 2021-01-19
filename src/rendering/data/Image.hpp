#pragma once

#include <vector>

namespace ppvr {
	namespace rendering {
		namespace data {

			template <typename T>
			class Image {
			
			private:
				class SubProxyX {
					Image* pImg;
					size_t pX;
				public:
					SubProxyX(Image* img, size_t x): pImg{img}, pX{x} {}
					
					T&  operator[](size_t y) {
						size_t i = pImg->index(pX, y);
						return pImg->mValues[i];
					}
				};

			public:
				Image();
				Image(size_t yWidth, size_t yHeight);
				Image(size_t yWidth, size_t yHeight, T yVal);
			
				~Image();
				
				void resize(size_t yWidth, size_t yHeight);
				void resize(size_t yWidth, size_t yHeight, T yVal);
				
				size_t width() const {return mWidth;}
				size_t height() const {return mHeight;}
				size_t length() const {return mValues.size();}
				
				size_t index(size_t x, size_t y) const;
				
				void set(size_t x, size_t y, const T& value);
				T& get(size_t x, size_t y);
				const T& get(size_t x, size_t y) const;
				
				void set(size_t index, const T& value);
				T& get(size_t index);
				const T& get(size_t index) const;
				
				//const T& operator[](size_t i) const;
				SubProxyX operator[](size_t x) {
					return SubProxyX(this, x);
				}
			
				T* data();
				const T* data() const;
				
			private:
				size_t mWidth, mHeight;
				
			private:
				std::vector<T> mValues;
			};
		}
	}
}

#include "Image_impl.hpp"
