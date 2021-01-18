
#include <cassert>

using ppvr::rendering::data::Volume;

template <typename T>
Volume<T>::Volume()
	: mWidth(0), mHeight(0) {
}

template <typename T>
Volume<T>::Volume(size_t yWidth, size_t yHeight) {
	this->resize(yWidth, yHeight);
}

template <typename T>
Volume<T>::Volume(size_t yWidth, size_t yHeight, T yVal) {
  	this->resize(yWidth, yHeight, yVal);
}

template <typename T>
Volume<T>::~Volume() {}

template <typename T>
void Volume<T>::resize(size_t yWidth, size_t yHeight) {
		this->resize(yWidth, yHeight, T{});
}

template <typename T>
void Volume<T>::resize(size_t yWidth, size_t yHeight, T yVal) {
	//assert(yWidth >= 1);
	//assert(yHeight >= 1);
	//assert(yDepth >= 1);
	
	mWidth = yWidth;
	mHeight = yHeight;
	mValues.resize(yWidth * yHeight, yVal);
}

template <typename T>
size_t Volume<T>::index(size_t x, size_t y, size_t z) const {
	size_t index = y * mWidth + x;
	return index;
}

template <typename T>
void Volume<T>::set(size_t x, size_t y, const T& value)  {
	size_t i = index(x, y);
	mValues[i] = value;
	//resetCaches();
}

template <typename T>
const T& Volume<T>::get(size_t x, size_t y) const {
	size_t i = index(x, y);
	return mValues[i];
}

template <typename T>
void Volume<T>::set(size_t index, const T& value) {
	mValues[index] = value;
}

template <typename T>
const T& Volume<T>::get(size_t index) const {
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
