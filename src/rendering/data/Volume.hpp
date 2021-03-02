#pragma once

#include <vector>

namespace ppvr {
	namespace rendering {
		namespace data {

			template <typename T>
			class Volume {
			
			private:
				class SubProxyXY {
					Volume* pV;
					size_t pX;
					size_t pY;
				public:
					SubProxyXY(Volume* v, size_t x, size_t y):  pV{v}, pX{x}, pY{y} {}
					
					T& operator[](size_t z) {
						size_t i = pV->index(pX, pY, z);
						return pV->mValues[i];
					}
					/*
					const T& operator[](size_t z) const {
						size_t i = pV->index(pX, pY, z);
						return pV->values[i];
					}
					*/
				};
				
				class SubProxyX {
					Volume* pV;
					size_t pX;
				public:
					SubProxyX(Volume* v, size_t x): pV{v}, pX{x} {}
					
					SubProxyXY operator[](size_t y) {
						return SubProxyXY(pV, pX, y);
					}
				};

			public:
				Volume();
				Volume(size_t yWidth, size_t yHeight, size_t yDepth);
				Volume(size_t yWidth, size_t yHeight, size_t yDepth, T yVal);
			
				~Volume();
				
				void resize(size_t yWidth, size_t yHeight, size_t yDepth);
				void resize(size_t yWidth, size_t yHeight, size_t yDepth, T yVal);
				
				size_t width() const {return mWidth;}
				size_t height() const {return mHeight;}
				size_t depth() const {return mDepth;}
				size_t length() const {return mValues.size();}
				
				size_t index(size_t x, size_t y, size_t z) const;
				
				void set(size_t x, size_t y, size_t z, const T& value);
				const T& get(size_t x, size_t y, size_t z) const;
				T& get(size_t x, size_t y, size_t z);
				
				void set(size_t index, const T& value);
				const T& get(size_t index) const;
				T& get(size_t index);
				
				//const T& operator[](size_t i) const;
				SubProxyX operator[](size_t x) {
					return SubProxyX(this, x);
				}
			
				T* data();
				const T* data() const;
				
			private:
				size_t mWidth, mHeight, mDepth;
				
			private:
				std::vector<T> mValues;
			};
		}
	}
}

#include "Volume_impl.hpp"
