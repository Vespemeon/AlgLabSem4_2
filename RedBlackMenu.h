#pragma once
#include "RedBlackTree.h"

void menu() {
	RedBlackTree<int, char> *tree = new RedBlackTree<int, char>();
	char ch = 'a';
	int key;
	char val;

	while (ch != 'q') {
		std::cout << "\n0: Fast tree init:\n1: Insert\n2: Remove\n3: Find\n4: Print\n5: Clear\n6: Get keys\n7: Get values\nq: Quit\n\n";

		std::cin >> ch;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		RedBlackNode<int, char> *node = nullptr;
		List<int> *listKey = nullptr;
		List<char> *listVal = nullptr;

		char ch2 = 'a';

		switch (ch) {
		case '0':
			std::cout << "Enter keys (type two same keys to end):\n";
			listKey = new List<int>();

			int oldKey;
			std::cin >> oldKey;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			listKey->push_back(oldKey);
			key = oldKey;

			while (key) {
				std::cin >> key;
				if (key == oldKey) {
					break;
				}
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				listKey->push_back(key);
				oldKey = key;
			}

			delete tree;
			tree = new RedBlackTree<int, char>(listKey, 'a');

			delete listKey;
			listKey = nullptr;

			break;
		case '1':
			std::cout << "Enter key, then value:\n";
			std::cin >> key >> val;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			tree->insert(key, val);
			break;
		case '2':
			std::cout << "Enter key:\n";
			std::cin >> key;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			tree->remove(key);
			break;
		case '3':
			std::cout << "Enter key:\n";
			std::cin >> key;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			node = tree->find(key);
			if (!node) {
				std::cout << "There is no such node.\n";
			}
			else {
				std::cout << *node << std::endl;
			}
			delete node;
			node = nullptr;
			break;
		case '4':
			std::cout << *tree;
			break;
		case '5':
			tree->clear();
			break;
		case '6':
			listKey = tree->get_keys();
			std::cout << *listKey;
			delete listKey;
			listKey = nullptr;
			break;
		case '7':
			listVal = tree->get_values();
			std::cout << *listVal;
			delete listVal;
			listVal = nullptr;
			break;
		}
	}

	std::cin.get();
}