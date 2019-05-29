#pragma once
#include <iostream>

template <class Key, class Value>
class RedBlackNode {
public:
	RedBlackNode() {
		//no def constructor because key and value should exist
	}
	RedBlackNode(Key key, Value val) {
		this->key = key;
		this->val = val;
	}
	~RedBlackNode() {
		//no need to delete family members
		//(it would screw everything up)
	}

	Key getKey() {
		return key;
	}

	Value getValue() {
		return val;
	}

	bool isBlack() {
		return black;
	}

	template <class Key, class Value>
	friend std::ostream& operator<<(std::ostream& stream, RedBlackNode<Key, Value>& node) {
		stream << "Key: " << node.key << ", Value: " << node.val;
		if (node.black)
			stream << ", Color: black\n";
		else
			stream << ", Color: red\n";

		return stream;
	}

private:
	template <class Key, class Value> friend class RedBlackTree;
	template <class Key, class Value> friend class RedBlackIterator;

	Key key;
	Value val;
	RedBlackNode<Key, Value> *left = nullptr;
	RedBlackNode<Key, Value> *right = nullptr;
	RedBlackNode<Key, Value> *upper = nullptr;
	bool black = false;	//new node is red, the root is black

	bool isLeft() {
		if (!upper)
			return false;

		if (upper->left == this)
			return true;
		else
			return false;
	}

	bool isRight() {
		if (!upper)
			return false;

		if (upper->right == this)
			return true;
		else
			return false;
	}

	RedBlackNode<Key, Value> *grandpa() {
		//no parent(root) no grandpa
		if (!upper)
			return nullptr;

		return upper->upper;
	}

	RedBlackNode<Key, Value> *uncle() {
		RedBlackNode<Key, Value> *node = grandpa();

		//no grandpa no uncle
		if (!node)
			return nullptr;

		if (node->left == upper)
			return node->right;
		else
			return node->left;
	}
};