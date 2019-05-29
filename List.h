#pragma once

#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <class Data>
class ListNode {
public:
	template <class Data> friend class List;
	
	ListNode() {

	}

	ListNode(Data data) {
		this->data = data;
	}

	~ListNode() {
		prev = nullptr;
		next = nullptr;
	}

	ListNode<Data> *prev = nullptr;
	ListNode<Data> *next = nullptr;
	Data data;
};

template <class Data>
class List {
private:
	ListNode<Data> *head = nullptr;
	ListNode<Data> *tail = nullptr;

public:
	template <class Data> friend class ListIterator;
	List() {

	}

	//fast list initialization
	List(std::initializer_list<Data> list) {
		this->head = nullptr;
		this->tail = nullptr;

		for (auto elem : list) {
			this->push_back(elem);
		}
	}

	~List() {
		clear();
	};

	void push_back(Data data) {
		ListNode<Data> *node = new ListNode<Data>(data);
		
		if (head == nullptr) {
			head = node;
			tail = node;
		}
		else {
			node->prev = tail;
			tail->next = node;
			tail = node;
		}
	}

	void push_front(Data data) {
		if (head == nullptr) {
			push_back(data);
		}
		else {
			ListNode<Data> *node = new ListNode<Data>(data);
			head->prev = node;
			node->next = head;
			head = node;
		}
	}

	Data pop_back() {
		if (tail == nullptr) {
			throw(std::out_of_range("Pop back empty list"));
		}

		ListNode<Data> *node = tail->prev;

		//check if list has only one elem 
		if (node != nullptr) {
			node->next = nullptr;
		}
		else {
			head = nullptr;
		}

		Data delData = tail->data;

		delete tail;
		tail = node;

		return delData;
	}

	Data pop_front() {
		if (head == nullptr) {
			throw(std::out_of_range("Pop front empty list"));
		}

		ListNode<Data> *node = head->next;

		//check if list has only one elem
		if (node != nullptr) {
			node->prev = nullptr;
		}
		else {
			tail = nullptr;
		}

		Data delData = head->data;

		delete head;
		head = node;

		return delData;
	}

	size_t get_size() {
		size_t size = 0;
		ListNode<Data> *node = head;
		while (node != nullptr) {
			node = node->next;
			++size;
		}
		return size;
	}

	void insert(Data data, size_t index) {
		if (head == nullptr) {
			throw(std::out_of_range("Insert empty list"));
		}
		if (int(index) < 0) {
			throw(std::invalid_argument("Insert negative argument"));
		}
		if (index + 1 > get_size()) {
			throw(std::out_of_range("Insert nonexistent index"));
		}

		ListNode<Data> *node = head;
		for (size_t currInd = 0; currInd < index; ++currInd) {
			node = node->next;
		}

		ListNode<Data> *addNode = new ListNode<Data>(data);

		addNode->next = node;
		addNode->prev = node->prev;

		if (node->next == nullptr) {
			tail = addNode;
		}
		else if (node->prev == nullptr) {
			head = addNode;
		}
		if (node->prev != nullptr) {
			node->prev->next = addNode;
		}

		node->prev = addNode;
	}

	Data at(size_t index) {
		if (head == nullptr) {
			throw(std::out_of_range("At empty list"));
		}
		if (int(index) < 0) {
			throw(std::invalid_argument("At negative argument"));
		}
		if (index + 1 > get_size()) {
			throw(std::out_of_range("At nonexistent index"));
		}

		ListNode<Data> *node = head;
		for (size_t currInd = 0; currInd < index; ++currInd) {
			node = node->next;
		}

		return node->data;
	}

	Data remove(size_t index) {
		if (head == nullptr) {
			throw(std::out_of_range("Remove empty list"));
		}
		if (int(index) < 0) {
			throw(std::invalid_argument("Remove negative argument"));
		}
		if (index + 1 > get_size()) {
			throw(std::out_of_range("Remove nonexistent index"));
		}

		if (index == get_size()) {
			pop_back();
		}
		else if (index == 0) {
			pop_front();
		}
		else {
			ListNode<Data> *node = head;
			for (size_t currInd = 0; currInd < index; ++currInd) {
				node = node->next;
			}
			node->prev->next = node->next;
			if (node->next != nullptr) {
				node->next->prev = node->prev;
			}

			delete node;
		}
	}

	void clear() {
		if (head == nullptr) {
			return;
		}

		ListNode<Data> *node = head;
		ListNode<Data> *toDelete = head;

		while (node != nullptr) {
			node = node->next;
			delete toDelete;
			toDelete = node;
		}
	}

	void set(Data data, size_t index) {
		if (head == nullptr) {
			throw(std::out_of_range("Set empty list"));
		}
		if (int(index) < 0) {
			throw(std::invalid_argument("Set negative argument"));
		}
		if (index + 1 > get_size()) {
			throw(std::out_of_range("Set nonexistent index"));
		}

		ListNode<Data> *node = head;
		for (size_t currInd = 0; currInd < index; ++currInd) {
			node = node->next;
		}
		node->data = data;
	}

	bool isEmpty() {
		if (head == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	friend std::ostream& operator<< (std::ostream &out, const List<Data> &list) {
		ListNode<Data> *node = list.head;

		if (!node) {
			out << "An empty list.\n";
			return out;
		}

		while (node != nullptr) {
			out << node->data;
			node = node->next;
			if (node != nullptr) {
				out << ", ";
			}
		}

		return out;
	}
};

template <class Data>

class ListIterator {
private:
	ListNode<Data> *curr = nullptr;
public:
	ListIterator() {

	}

	ListIterator(List<Data>* list) {
		curr = list->head;
	}

	~ListIterator() {

	}

	bool notNul() {
		return (curr ? true : false);
	}

	void next() {
		if (notNul()) 
			curr = curr->next;
	}

	void prev() {
		if (notNul())
			curr = curr->prev;
	}

	Data getData() {
		if (notNul())
			return curr->data;
		else
			return (Data)0;
	}
};