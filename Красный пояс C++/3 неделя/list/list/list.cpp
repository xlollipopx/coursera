﻿#include "test_runner.h"
#include<iostream>
#include <vector>
#include "test_runner.h"
using namespace std;

template <typename T>
class LinkedList {
public:
	struct Node {
		T value;
		Node* next = nullptr;
		Node(T _value) : value(_value) {}
		Node(){}
	};

	~LinkedList();
	LinkedList() { size = 0; }
	void PushFront(const T& value);
	void InsertAfter(Node* node, const T& value);
	void RemoveAfter(Node* node);
	void PopFront();

	Node* GetHead() { return head; }
	const Node* GetHead() const { return head; }

private:
	Node* head = nullptr;
	size_t size;
};
template <typename T>
LinkedList<T>::~LinkedList() {
	Node* current = head;
	Node* next;
	while (current != nullptr) {
		next = current->next;
		delete current;
		current = next;
	}
}

template <typename T>
void LinkedList<T>::PushFront(const T& value) {
	if (head == nullptr) {
		head = new Node(value);

	}
	else {
		Node* current = new Node(value);
		current->next = head;
		head = current;
	}
	size++;
}

template <typename T>
void LinkedList<T>::PopFront() {
	if (!head) {
		return;
	}
	Node* temp_node = head;
	head = temp_node->next;
	delete temp_node;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& value) {
	if (!node) {
		PushFront(value);
		return;
	}
	Node* new_node = new Node;
	new_node->value = value;
	new_node->next = node->next;
	node->next = new_node;
}

template <typename T>
void LinkedList<T>::RemoveAfter(Node* node) {
	if (!node) {
		PopFront();
		return;
	}
	if (!node->next) {
		return;
	}
	Node* temp_node = node->next;
	node->next = temp_node->next;
	delete temp_node;
}
template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
	vector<T> result;
	for (auto node = list.GetHead(); node; node = node->next) {
		result.push_back(node->value);
	}
	return result;
}

void TestPushFront() {
	LinkedList<int> list;

	list.PushFront(1);
	ASSERT_EQUAL(list.GetHead()->value, 1);
	list.PushFront(2);
	ASSERT_EQUAL(list.GetHead()->value, 2);
	list.PushFront(3);
	ASSERT_EQUAL(list.GetHead()->value, 3);

	const vector<int> expected = { 3, 2, 1 };
	ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
	LinkedList<string> list;

	list.PushFront("a");
	auto head = list.GetHead();
	ASSERT(head);
	ASSERT_EQUAL(head->value, "a");

	list.InsertAfter(head, "b");
	const vector<string> expected1 = { "a", "b" };
	ASSERT_EQUAL(ToVector(list), expected1);

	list.InsertAfter(head, "c");
	const vector<string> expected2 = { "a", "c", "b" };
	ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
	LinkedList<int> list;
	for (int i = 1; i <= 5; ++i) {
		list.PushFront(i);
	}

	const vector<int> expected = { 5, 4, 3, 2, 1 };
	ASSERT_EQUAL(ToVector(list), expected);

	auto next_to_head = list.GetHead()->next;
	list.RemoveAfter(next_to_head); // ÑƒÐ´Ð°Ð»ÑÐµÐ¼ 3
	list.RemoveAfter(next_to_head); // ÑƒÐ´Ð°Ð»ÑÐµÐ¼ 2

	const vector<int> expected1 = { 5, 4, 1 };
	ASSERT_EQUAL(ToVector(list), expected1);

	while (list.GetHead()->next) {
		list.RemoveAfter(list.GetHead());
	}
	ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
	LinkedList<int> list;

	for (int i = 1; i <= 5; ++i) {
		list.PushFront(i);
	}
	for (int i = 1; i <= 5; ++i) {
		list.PopFront();
	}
	ASSERT(list.GetHead() == nullptr);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestPushFront);
	RUN_TEST(tr, TestInsertAfter);
	RUN_TEST(tr, TestRemoveAfter);
	RUN_TEST(tr, TestPopFront);
	
	return 0;
}