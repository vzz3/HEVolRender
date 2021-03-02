
#include <cassert>

using ppvr::rendering::data::Volume;

template <typename T>
Volume<T>::Volume()
	: mWidth(0), mHeight(0), mDepth(0) {
}

template <typename T>
Volume<T>::Volume(size_t yWidth, size_t yHeight, size_t yDepth) {
	this->resize(yWidth, yHeight, yDepth);
}

template <typename T>
Volume<T>::Volume(size_t yWidth, size_t yHeight, size_t yDepth, T yVal) {
  	this->resize(yWidth, yHeight, yDepth, yVal);
}

template <typename T>
Volume<T>::~Volume() {}

template <typename T>
void Volume<T>::resize(size_t yWidth, size_t yHeight, size_t yDepth) {
		this->resize(yWidth, yHeight, yDepth, T{});
}

template <typename T>
void Volume<T>::resize(size_t yWidth, size_t yHeight, size_t yDepth, T yVal) {
	//assert(yWidth >= 1);
	//assert(yHeight >= 1);
	//assert(yDepth >= 1);
	
	mWidth = yWidth;
	mHeight = yHeight;
	mDepth = yDepth;
	mValues.resize(yWidth * yHeight * yDepth, yVal);
}

template <typename T>
size_t Volume<T>::index(size_t x, size_t y, size_t z) const {
	assert(x < mWidth);
	assert(y < mHeight);
	assert(z < mDepth);
	
	size_t index = z * mHeight * mWidth + y * mWidth + x;
	return index;
}

template <typename T>
void Volume<T>::set(size_t x, size_t y, size_t z, const T& value)  {
	size_t i = index(x, y, z);
	mValues[i] = value;
	//resetCaches();
}

template <typename T>
const T& Volume<T>::get(size_t x, size_t y, size_t z) const {
	size_t i = index(x, y, z);
	return mValues[i];
}

template <typename T>
T& Volume<T>::get(size_t x, size_t y, size_t z) {
	size_t i = index(x, y, z);
	return mValues[i];
}

template <typename T>
void Volume<T>::set(size_t index, const T& value) {
	assert(index < length());
	
	mValues[index] = value;
}

template <typename T>
const T& Volume<T>::get(size_t index) const {
	assert(index < length());
	
	return mValues[index];
}

template <typename T>
T& Volume<T>::get(size_t index) {
	assert(index < length());
	
	return mValues[index];
}



template <typename T>
T* Volume<T>::data() {
	return mValues.data();
}

template <typename T>
const T* Volume<T>::data() const {
	return mValues.data();
}
