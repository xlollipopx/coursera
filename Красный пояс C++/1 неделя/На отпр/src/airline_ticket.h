
#pragma once
#include <iostream>
#include<vector>
using namespace std;

template<typename T>
class Deque {
private: 
	vector<T> beg;
	vector<T> en;

public:
	Deque() {};

	bool Empty() {
		return (beg.size() == 0 && en.size() == 0);
	}
	int Size() { return (beg.size() + en.size()); }
	T& operator[] (size_t index) {
		return At(index);
	}

	const T& operator[] (size_t index)  const {
		return At(index);
	}
	T& At(size_t index) {
		try {
			if (index >= beg.size()) {
				return en[index - beg.size()];
			}
			else {
				return beg[beg.size() - index];
			}
		}
		catch(...){
			cerr << "out_of_range";
		}
	}

	const T& At(size_t index) const {
		try {
			if (index >= beg.size()) {
				return en[index - beg.size()];
			}
			else {
				return beg[beg.size() - index];
			}
		}
		catch(...){
			cerr << "out_of_range";
		}
	}

	T& Front() {
		return At(0);
	}

	const T& Front() const {
		return At(0);
	}

	T& Back() {
		return At(Size() - 1);
	}

	const T& Back() const {
		return At(Size() - 1);
	}
	void PushBack(T value) {
		en.push_back(value);
	}
	void PushFront(T value) {
		beg.push_back(value);
	}

};
