
#include <cassert>

using ppvr::rendering::data::Image;

template <typename T>
Image<T>::Image()
	: mWidth(0), mHeight(0) {
}

template <typename T>
Image<T>::Image(size_t yWidth, size_t yHeight) {
	this->resize(yWidth, yHeight);
}

template <typename T>
Image<T>::Image(size_t yWidth, size_t yHeight, T yVal) {
  	this->resize(yWidth, yHeight, yVal);
}

template <typename T>
Image<T>::~Image() {}

template <typename T>
void Image<T>::resize(size_t yWidth, size_t yHeight) {
		this->resize(yWidth, yHeight, T{});
}

template <typename T>
void Image<T>::resize(size_t yWidth, size_t yHeight, T yVal) {
	//assert(yWidth >= 1);
	//assert(yHeight >= 1);
	//assert(yDepth >= 1);
	
	mWidth = yWidth;
	mHeight = yHeight;
	mValues.resize(yWidth * yHeight, yVal);
}

template <typename T>
size_t Image<T>::index(size_t x, size_t y) const {
	assert(x < mWidth);
	assert(y < mHeight);
	
	size_t index = y * mWidth + x;
	return index;
}

template <typename T>
void Image<T>::set(size_t x, size_t y, const T& value)  {
	size_t i = index(x, y);
	mValues[i] = value;
	//resetCaches();
}

template <typename T>
T& Image<T>::get(size_t x, size_t y) {
	size_t i = index(x, y);
	return mValues[i];
}

template <typename T>
const T& Image<T>::get(size_t x, size_t y) const {
	size_t i = index(x, y);
	return mValues[i];
}

template <typename T>
void Image<T>::set(size_t index, const T& value) {
	assert(index < length());
	
	mValues[index] = value;
}

template <typename T>
T& Image<T>::get(size_t index) {
	assert(index < length());
	
	return mValues[index];
}

template <typename T>
const T& Image<T>::get(size_t index) const {
	assert(index < length());
	
	return mValues[index];
}




template <typename T>
T* Image<T>::data() {
	return mValues.data();
}

template <typename T>
const T* Image<T>::data() const {
	return mValues.data();
}
