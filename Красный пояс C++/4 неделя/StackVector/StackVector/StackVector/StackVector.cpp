// StackVector.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<array>
#include "test_runner.h"
#include "profile.h"

#include <random>
#include <stdexcept>
#include "test_runner.h"
#include "StackVector.h"
using namespace std;
#include <assert.h>

template<typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0): capacity_(N) {
		if (a_size > capacity_) {
			throw invalid_argument("");
		}
		size_ = a_size;
	}

	T& operator[](size_t index) {
		return data_[index];
	}
	const T& operator[](size_t index) const {
		return data_[index];
	}

	auto begin() {
		return data_.begin();
	}
	auto end() {
		return data_.end() + size_;
	}
	const auto begin() const {
		return data_.begin();
	}
	const auto end() const {
		return data_.end() + size_;
	}

	size_t Size() const {
		return size_;
	}
	size_t Capacity() const {
		return capacity_;
	}

	void PushBack(const T& value) {
		if (size_ == capacity_) {
			throw overflow_error("");
		}
		data_[size_] = value;
		size_++;
	}
	T PopBack() {
		if (size_ == 0) {
			throw underflow_error("");
		}
		return data_[--size_];
	}

private:
	array<T, N> data_;
	size_t size_=0;
	size_t capacity_;

};
void TestConstruction() {
	StackVector<int, 10> v;
	ASSERT_EQUAL(v.Size(), 0u);
	ASSERT_EQUAL(v.Capacity(), 10u);

	StackVector<int, 8> u(5);
	ASSERT_EQUAL(u.Size(), 5u);
	ASSERT_EQUAL(u.Capacity(), 8u);

	try {
		StackVector<int, 10> u(50);
		Assert(false, "Expect invalid_argument for too large size");
	}
	catch (invalid_argument&) {
	}
	catch (...) {
		Assert(false, "Unexpected exception for too large size");
	}
}

void TestPushBack() {
	StackVector<int, 5> v;
	for (size_t i = 0; i < v.Capacity(); ++i) {
		v.PushBack(i);
	}

	try {
		v.PushBack(0);
		Assert(false, "Expect overflow_error for PushBack in full vector");
	}
	catch (overflow_error&) {
	}
	catch (...) {
		Assert(false, "Unexpected exception for PushBack in full vector");
	}
}

void TestPopBack() {
	StackVector<int, 5> v;
	for (size_t i = 1; i <= v.Capacity(); ++i) {
		v.PushBack(i);
	}
	for (int i = v.Size(); i > 0; --i) {
		ASSERT_EQUAL(v.PopBack(), i);
	}

	try {
		v.PopBack();
		Assert(false, "Expect underflow_error for PopBack from empty vector");
	}
	catch (underflow_error&) {
	}
	catch (...) {
		Assert(false, "Unexpected exception for PopBack from empty vector");
	}
}

int main() {
	{
		TestRunner tr;
		RUN_TEST(tr, TestConstruction);
		RUN_TEST(tr, TestPushBack);
		RUN_TEST(tr, TestPopBack);
	}

	cerr << "Running benchmark..." << endl;
	const size_t max_size = 2500;

	default_random_engine re;
	uniform_int_distribution<int> value_gen(1, max_size);

	vector<vector<int>> test_data(50000);
	for (auto& cur_vec : test_data) {
		cur_vec.resize(value_gen(re));
		for (int& x : cur_vec) {
			x = value_gen(re);
		}
	}

	{
		LOG_DURATION("vector w/o reserve");
		for (auto& cur_vec : test_data) {
			vector<int> v;
			for (int x : cur_vec) {
				v.push_back(x);
			}
		}
	}
	{
		LOG_DURATION("vector with reserve");
		for (auto& cur_vec : test_data) {
			vector<int> v;
			v.reserve(cur_vec.size());
			for (int x : cur_vec) {
				v.push_back(x);
			}
		}
	}
	{
		LOG_DURATION("StackVector");
		for (auto& cur_vec : test_data) {
			StackVector<int, max_size> v;
			for (int x : cur_vec) {
				v.PushBack(x);
			}
		}
	}
	cerr << "Done" << endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
