#pragma once
#include "RedBlackNode.h"
#include "List.h"
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <class Key, class Value>
class RedBlackTree {
private:
	RedBlackNode<Key, Value> *root = nullptr;
	template <class Key, class Value> friend class RedBlackIterator;


	void leftRotate(RedBlackNode<Key, Value> *x) {
		RedBlackNode<Key, Value> *y = x->right;

		//y's left child now belongs to x's right
		x->right = y->left;
		if (y->left)
			y->left->upper = x;

		//now x's parent becomes an y's parent
		y->upper = x->upper;

		//if x is not root, basically
		if (x->upper) {
			if (x->isLeft()) {
				y->upper->left = y;
			}
			else if (x->isRight()) {
				y->upper->right = y;
			}
		}

		//now x becomes y's left child
		x->upper = y;
		y->left = x;

		//if x was a root, now it's y
		if (x == root) {
			root = y;
		}
	}

	void rightRotate(RedBlackNode<Key, Value> *x) {
		RedBlackNode<Key, Value> *y = x->left;

		//y's right child now belongs to x's left
		x->left = y->right;
		if (y->right)
			y->right->upper = x;

		//now x's parent becomes an y's parent
		y->upper = x->upper;

		//if x is not root, basically
		if (x->upper) {
			if (x->isLeft()) {
				y->upper->left = y;
			}
			else if (x->isRight()) {
				y->upper->right = y;
			}
		}

		//now x becomes y's right child
		x->upper = y;
		y->right = x;

		//if x was a root, now it's y
		if (x == root) {
			root = y;
		}
	}

	//find the node to insert new node after it
	//used in insert
	RedBlackNode<Key, Value> *findToInsert(Key key) {
		RedBlackNode<Key, Value> *node = root;
		bool found = false;

		while (!found) {
			if (key > node->key) {
				if (node->right)
					node = node->right;
				else
					found = true;
			}
			else if (key < node->key) {
				if (node->left)
					node = node->left;
				else
					found = true;
			}
			else if (key == node->key)
				//no 2 matching keys could be in an one tree
				return nullptr;
		}

		return node;
	}

	//fix the tree after we add a new node
	//used in insert
	void fixTreeAfterInsert(RedBlackNode<Key, Value> *node) {
		RedBlackNode<Key, Value>
			*grandpa = nullptr,
			*uncle = nullptr;

		//black parent means it's ok, check if it's red
		//stop fixing if root, no parent or parent is black
		while (node != root && node->upper && !node->upper->black) {
			//the fresh added node is red
			grandpa = node->grandpa();
			uncle = node->uncle();

			if (!grandpa)
				return;

			//check for uncle color
			//if red, paint parent black, grandpa red, uncle black

			//if black, perform a rotation to make child and parent both left or right
			//then perfom a rotation again

			//if no uncle is like uncle is black
			if (!uncle || uncle->black) {
				if (node->upper->isRight() && node->isLeft()) {
					rightRotate(node->upper);
					node = node->right;
				}
				else if (node->upper->isLeft() && node->isRight()) {
					leftRotate(node->upper);
					node = node->left;
				}

				node->upper->black = true;
				grandpa->black = false;

				if (node->upper->isRight())
					leftRotate(grandpa);
				else
					rightRotate(grandpa);
			}
			else if (!uncle->black) {
				node->upper->black = true;
				grandpa->black = false;
				uncle->black = true;
			}

			node = grandpa;
		}

		root->black = true;
	}

	void fixTreeAfterRemove(RedBlackNode<Key, Value> *node) {
		while (node != root && node->black == true) {
			if (node == node->upper->left) {
				RedBlackNode<Key, Value> *bro = node->upper->right;
				if (bro->black == false) {
					bro->black = true;
					node->upper->black = false;
					leftRotate(node->upper);
					bro = node->upper->right;
				}
				if (bro->left->black == true && bro->right->black == true) {
					bro->black = false;
					node = node->upper;
				}
				else {
					if (bro->right->black == true) {
						bro->left->black = true;
						bro->black = false;
						rightRotate(bro);
						bro = node->upper->right;
					}
					bro->black = node->upper->black;
					node->upper->black = true;
					bro->right->black = true;
					leftRotate(node->upper);
					node = root;
				}
			}
			else {
				RedBlackNode<Key, Value> *bro = node->upper->left;
				if (bro->black == false) {
					bro->black = true;
					node->upper->black = false;
					rightRotate(node->upper);
					bro = node->upper->left;
				}
				if (bro->right->black == true && bro->left->black == true) {
					bro->black = false;
					node = node->upper;
				}
				else {
					if (bro->left->black == true) {
						bro->right->black = true;
						bro->black = false;
						leftRotate(bro);
						bro = node->upper->left;
					}
					bro->black = node->upper->black;
					node->upper->black = true;
					bro->left->black = true;
					rightRotate(node->upper);
					node = root;
				}
			}
		}
		node->black = true;
	}

	void printFromNode(RedBlackNode<Key, Value> *node, size_t level, bool left_or_right) {
		if (node != nullptr) {
			printFromNode(node->left, level + 3, true);

			bool strokes = false;

			for (size_t i = 0; i < level; ++i) {
				if (i + 2 == level) {
					strokes = true;
				}

				if (strokes) {
					std::cout << "---";
				}
				else {
					std::cout << "   ";
				}
			}


			if (left_or_right && node != root) {
				std::cout << "L, ";

			}
			else if (node != root) {
				std::cout << "R, ";
			}

			if (node->black) {
				std::cout << "Blk:";
			}
			else {
				std::cout << "Red:";
			}

			std::cout << node->key << ", " << node->val << std::endl;
			printFromNode(node->right, level + 3, false);
		}
	}

	//recursive delete all the tree
	void postorderDelete(RedBlackNode<Key, Value> *node) {
		if (!node)
			return;

		postorderDelete(node->left);
		postorderDelete(node->right);

		delete node;
		node = nullptr;

		root = nullptr;
	}

	//to fill the list of keys
	void preorderKey(List<Key> *list, RedBlackNode<Key, Value> *node) {
		if (!node)
			return;

		list->push_back(node->key);
		preorderKey(list, node->left);
		preorderKey(list, node->right);
	}

	//to fill the list of values
	void preorderValue(List<Value> *list, RedBlackNode<Key, Value> *node) {
		if (!node)
			return;

		list->push_back(node->val);

		preorderValue(list, node->left);
		preorderValue(list, node->right);
	}

public:
	RedBlackTree() {

	}

	~RedBlackTree() {
		//clear();
	}

	//fast init with init list of keys as arg
	RedBlackTree(std::initializer_list<Key> list, Value val) {
		for (auto elem : list) {
			this->push_back(elem, val);
		}
	}

	//fast init with LIST_H list of keys
	RedBlackTree(List<Key> *list, Value val) {
		ListIterator<Key> *it = new ListIterator<Key>(list);

		while (it->notNul()) {
			this->insert(it->getData(), val);
			it->next();
		}

		delete it;
		it = nullptr;
	}

	template <class Key, class Value>
	friend std::ostream& operator<<(std::ostream& stream, RedBlackTree<Key, Value>& tree) {
		RedBlackNode<Key, Value> *node = tree.root;
		if (!node) {
			std::cout << "An empty tree.\n";
			return stream;
		}

		tree.printFromNode(tree.root, 0, true);
		return stream;
	}

	void insert(Key key, Value val) {
		//adding the first elem is easy
		if (!root) {
			root = new RedBlackNode<Key, Value>(key, val);
			root->black = true;
			return;
		}

		RedBlackNode<Key, Value> *toInsert = findToInsert(key);

		//if key is already exists
		if (!toInsert)
			return;

		RedBlackNode<Key, Value> *newNode = new RedBlackNode<Key, Value>(key, val);

		if (key > toInsert->key)
			toInsert->right = newNode;
		else
			toInsert->left = newNode;

		newNode->upper = toInsert;

		fixTreeAfterInsert(newNode);
	}

	RedBlackNode<Key, Value> *find(Key key) {
		RedBlackNode<Key, Value> *node = root;
		bool found = false;

		while (!found) {
			if (key > node->key) {
				if (node->right)
					node = node->right;
				else
					return nullptr;
			}
			else if (key < node->key) {
				if (node->left)
					node = node->left;
				else
					return nullptr;
			}
			else if (key == node->key)
				found = true;
		}

		return node;
	}

	void remove(Key key) {
		RedBlackNode<Key, Value> *toRemove = find(key);
		RedBlackNode<Key, Value> *fixNode = nullptr;

		//if node to remove wasn't found - return
		if (!toRemove) {
			return;
		}

		bool blackWasDeleted = toRemove->black;

		//if no children simply delete the node
		if (!toRemove->left && !toRemove->right) {
			if (toRemove->isLeft())
				toRemove->upper->left = nullptr;
			else if (toRemove->isRight())
				toRemove->upper->right = nullptr;

			delete toRemove;
			toRemove = nullptr;

			//if root was deleted
			if (!root) {
				return;
			}
		}

		//only right child
		else if (!toRemove->left && toRemove->right) {
			if (toRemove->isLeft())
				toRemove->upper->left = toRemove->right;
			else if (toRemove->isRight())
				toRemove->upper->right = toRemove->right;

			toRemove->right->upper = toRemove->upper;

			fixNode = toRemove->right;
			delete toRemove;
			toRemove = nullptr;

			if (!root) {
				root = fixNode;
			}
		}

		//only left child
		else if (toRemove->left && !toRemove->right) {
			if (toRemove->isLeft())
				toRemove->upper->left = toRemove->left;
			else if (toRemove->isRight())
				toRemove->upper->right = toRemove->left;

			toRemove->left->upper = toRemove->upper;

			fixNode = toRemove->left;
			delete toRemove;
			toRemove = nullptr;

			if (!root) {
				root = fixNode;
			}
		}

		//both children
		else if (toRemove->left && toRemove->right) {
			auto *nextToRemove = toRemove->right;

			while (nextToRemove->left)
				nextToRemove = nextToRemove->left;

			toRemove->key = nextToRemove->key;
			toRemove->val = nextToRemove->val;

			if (nextToRemove->isLeft())
				nextToRemove->upper->left = nextToRemove->right;
			else if (toRemove->isRight())
				nextToRemove->upper->right = nextToRemove->right;

			if (nextToRemove->right)
				nextToRemove->right->upper = nextToRemove->upper;

			fixNode = nextToRemove->right;

			if (nextToRemove->black)
				blackWasDeleted = true;
			else
				blackWasDeleted = false;

			delete nextToRemove;
			nextToRemove = nullptr;
		}

		root->black = true;

		//no need to balance if red was deleted
		if (blackWasDeleted && fixNode)
			fixTreeAfterRemove(fixNode);
	}

	void clear() {
		postorderDelete(root);
	}

	List<Key> *get_keys() {
		List<Key> *list = new List<Key>();

		preorderKey(list, root);
		return list;
	}

	List<Value> *get_values() {
		List <Value> *list = new List<Value>();

		preorderValue(list, root);
		return list;
	}
};

template <class Key, class Value>
class RedBlackIterator {
private:
	RedBlackNode<Key, Value> *curr = nullptr;

public:
	RedBlackIterator() {

	}
	RedBlackIterator(RedBlackTree<Key, Value> *tree) {
		curr = tree->root;
	}
	~RedBlackIterator() {

	}
	bool notNul() {
		if (curr)
			return true;
		else
			return false;
	}
	Key getKey() {
		if (notNul())
			return curr->key;
		else
			return (Key)0;
	}
	Value getVal() {
		if (notNul())
			return curr->val;
		else
			return (Value)0;
	}
	bool isBlack() {
		if (notNul())
			return curr->black;
	}
	void goLeft() {
		if (notNul())
			curr = curr->left;
	}
	void goRight() {
		if (notNul())
			curr = curr->right;
	}
	void goUpper() {
		if (notNul())
			curr = curr->upper;
	}
};