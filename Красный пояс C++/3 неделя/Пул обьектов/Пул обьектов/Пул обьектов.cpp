#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include "test_runner.h"
using namespace std;

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <set>


template <class T>
class ObjectPool {
public:
	T* Allocate() {
		if (free_objects.empty()) {
			T* new_object = new T;
			detached_objects.insert(new_object);
			return new_object;
		}
		else {
			T* old_object = free_objects.front();
			free_objects.pop();
			detached_objects.insert(old_object);
			return old_object;
		}
	}

	T* TryAllocate() {
		if (free_objects.empty()) {
			return nullptr;
		}
		else {
			T* old_object = free_objects.front();
			free_objects.pop();
			detached_objects.insert(old_object);
			return old_object;
		}
	}

	void Deallocate(T* object) {
		auto find = detached_objects.find(object);
		if (find == detached_objects.end()) {
			throw std::invalid_argument("");
		}
		free_objects.push(*find);
		detached_objects.erase(find);
	}

	~ObjectPool() {
		for (auto i = detached_objects.begin(); i != detached_objects.end();) {
			T* ptr = *i;
			i = detached_objects.erase(i);
			delete ptr;
		}
		while (!free_objects.empty()) {
			T* ptr = free_objects.front();
			free_objects.pop();
			delete ptr;
		}
	}

private:
	std::set<T*> detached_objects;
	std::queue<T*> free_objects;
};

void TestObjectPool() {
	ObjectPool<string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}
