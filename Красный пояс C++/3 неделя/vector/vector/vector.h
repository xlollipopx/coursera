#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
	SimpleVector() : a(nullptr), size(0), capacity(0) {}
	explicit SimpleVector(size_t _size) {
		a = new T[_size];
		size = _size;
		capacity = _size;
	}
	~SimpleVector() {
		delete[]a;
	}

	T& operator[](size_t index) {
		return a[index];
	}
	const T* begin() const {
		return a;
	}
	const T* end() const {
		return (a + size);
	}
	T* begin() {
		return a;
	}
	T* end() {
		return (a + size);
	}

	size_t Size() const {
		return size;
	}
	size_t Capacity() const {
		return capacity;
	}
	void PushBack(const T& value) {
		if (size == 0) {
			a = new T[1];
			a[0] = value;
			capacity = 1;
		}
		else if (size == capacity) {
			T* tmp = new T[size];
			for (size_t i = 0;i < size;i++) {
				tmp[i] = a[i];
			}
			a = new T[2 * size];
			capacity = 2 * size;
			for (size_t i = 0;i < size;i++) {
				a[i] = tmp[i];
			}
			a[size] = value;
		}
		else {
			a[size] = value;
		}
		size++;
	}

private:
	size_t size;
	size_t capacity;
	T* a;
};