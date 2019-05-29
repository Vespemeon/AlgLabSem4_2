#include "stdafx.h"
#include "CppUnitTest.h"
#include "c:\Users\Vlast\source\repos\Лабораторная работа 2\Лабораторная работа 2\RedBlackTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Unittestsecondlab
{
	TEST_CLASS(Tree)
	{
	public:

		TEST_METHOD(Insert_test_getKey)
		{
			RedBlackTree<int, char> *tree = new RedBlackTree<int, char>();

			tree->insert(1, 'a');
			tree->insert(2, 'b');
			tree->insert(3, 'c');
			tree->insert(4, 'd');
			tree->insert(5, 'e');
			tree->insert(6, 'f');
			tree->insert(7, 'g');
			tree->insert(8, 'h');
			tree->insert(9, 'i');
			tree->insert(10, 'j');

			RedBlackIterator<int, char> *iterator = new RedBlackIterator<int, char>(tree);
			Assert::AreEqual(iterator->getKey(), 4);
			iterator->goRight();

			Assert::AreEqual(iterator->getKey(), 6);
			iterator->goRight();

			Assert::AreEqual(iterator->getKey(), 8);
			iterator->goRight();

			Assert::AreEqual(iterator->getKey(), 9);
			iterator->goRight();

			Assert::AreEqual(iterator->getKey(), 10);
			iterator->goUpper();
			iterator->goUpper();
			iterator->goLeft();

			Assert::AreEqual(iterator->getKey(), 7);
			iterator->goUpper();
			iterator->goUpper();
			iterator->goLeft();

			Assert::AreEqual(iterator->getKey(), 5);
			iterator->goUpper();
			iterator->goUpper();
			iterator->goLeft();

			Assert::AreEqual(iterator->getKey(), 2);
			iterator->goRight();

			Assert::AreEqual(iterator->getKey(), 3);
			iterator->goUpper();
			iterator->goLeft();

			Assert::AreEqual(iterator->getKey(), 1);

			delete iterator;
			iterator = nullptr;

			delete tree;
			tree = nullptr;
		}

		TEST_METHOD(Insert_test_getValue)
		{
			RedBlackTree<int, char> *tree = new RedBlackTree<int, char>();

			tree->insert(1, 'a');
			tree->insert(2, 'b');
			tree->insert(3, 'c');
			tree->insert(4, 'd');
			tree->insert(5, 'e');
			tree->insert(6, 'f');
			tree->insert(7, 'g');
			tree->insert(8, 'h');
			tree->insert(9, 'i');
			tree->insert(10, 'j');

			RedBlackIterator<int, char> *iterator = new RedBlackIterator<int, char>(tree);
			Assert::AreEqual(iterator->getVal(), 'd');
			iterator->goRight();

			Assert::AreEqual(iterator->getVal(), 'f');
			iterator->goRight();

			Assert::AreEqual(iterator->getVal(), 'h');
			iterator->goRight();

			Assert::AreEqual(iterator->getVal(), 'i');
			iterator->goRight();

			Assert::AreEqual(iterator->getVal(), 'j');
			iterator->goUpper();
			iterator->goUpper();
			iterator->goLeft();

			Assert::AreEqual(iterator->getVal(), 'g');
			iterator->goUpper();
			iterator->goUpper();
			iterator->goLeft();

			Assert::AreEqual(iterator->getVal(), 'e');
			iterator->goUpper();
			iterator->goUpper();
			iterator->goLeft();

			Assert::AreEqual(iterator->getVal(), 'b');
			iterator->goRight();

			Assert::AreEqual(iterator->getVal(), 'c');
			iterator->goUpper();
			iterator->goLeft();

			Assert::AreEqual(iterator->getVal(), 'a');

			delete iterator;
			iterator = nullptr;

			delete tree;
			tree = nullptr;
		}

		TEST_METHOD(Remove_method_test)
		{
			RedBlackTree<int, char> *tree = new RedBlackTree<int, char>();

			tree->insert(1, 'a');
			tree->insert(2, 'b');
			tree->insert(3, 'c');
			tree->insert(4, 'd');
			tree->insert(5, 'e');
			tree->insert(6, 'f');
			tree->insert(7, 'g');
			tree->insert(8, 'h');
			tree->insert(9, 'i');
			tree->insert(10, 'j');

			tree->remove(3);
			tree->remove(2);
			tree->remove(9);
			tree->remove(8);
			tree->remove(6);

			RedBlackIterator<int, char> *it = new RedBlackIterator<int, char>(tree);
			Assert::AreEqual(it->getKey(), 7);
			Assert::AreEqual(it->getVal(), 'g');
			Assert::AreEqual(it->isBlack(), true);
			it->goRight();

			Assert::AreEqual(it->getKey(), 10);
			Assert::AreEqual(it->getVal(), 'j');
			Assert::AreEqual(it->isBlack(), true);
			it->goUpper();
			it->goLeft();

			Assert::AreEqual(it->getKey(), 4);
			Assert::AreEqual(it->getVal(), 'd');
			Assert::AreEqual(it->isBlack(), true);
			it->goRight();

			Assert::AreEqual(it->getKey(), 5);
			Assert::AreEqual(it->getVal(), 'e');
			Assert::AreEqual(it->isBlack(), true);
			it->goUpper();
			it->goLeft();

			Assert::AreEqual(it->getKey(), 1);
			Assert::AreEqual(it->getVal(), 'a');
			Assert::AreEqual(it->isBlack(), true);

			delete it;
			it = nullptr;

			delete tree;
			tree = nullptr;
		}

		TEST_METHOD(Keys) {
			RedBlackTree<int, char> *tree = new RedBlackTree<int, char>();

			tree->insert(1, 'a');
			tree->insert(2, 'b');
			tree->insert(3, 'c');
			tree->insert(4, 'd');
			tree->insert(5, 'e');
			tree->insert(6, 'f');
			tree->insert(7, 'g');
			tree->insert(8, 'h');
			tree->insert(9, 'i');
			tree->insert(10, 'j');

			List<int> *list = nullptr;
			list = tree->get_keys();

			ListIterator<int> *it = new ListIterator<int>(list);
			Assert::AreEqual(it->getData(), 4);
			it->next();
			Assert::AreEqual(it->getData(), 2);
			it->next();
			Assert::AreEqual(it->getData(), 1);
			it->next();
			Assert::AreEqual(it->getData(), 3);
			it->next();
			Assert::AreEqual(it->getData(), 6);
			it->next();
			Assert::AreEqual(it->getData(), 5);
			it->next();
			Assert::AreEqual(it->getData(), 8);
			it->next();
			Assert::AreEqual(it->getData(), 7);
			it->next();
			Assert::AreEqual(it->getData(), 9);
			it->next();
			Assert::AreEqual(it->getData(), 10);

			delete list;
			list = nullptr;

			delete it;
			it = nullptr;

			delete tree;
			tree = nullptr;
		}

		TEST_METHOD(Values) {
			RedBlackTree<int, char> *tree = new RedBlackTree<int, char>();

			tree->insert(1, 'a');
			tree->insert(2, 'b');
			tree->insert(3, 'c');
			tree->insert(4, 'd');
			tree->insert(5, 'e');
			tree->insert(6, 'f');
			tree->insert(7, 'g');
			tree->insert(8, 'h');
			tree->insert(9, 'i');
			tree->insert(10, 'j');

			List<char> *list = nullptr;
			list = tree->get_values();

			ListIterator<char> *it = new ListIterator<char>(list);
			Assert::AreEqual(it->getData(), 'd');
			it->next();
			Assert::AreEqual(it->getData(), 'b');
			it->next();
			Assert::AreEqual(it->getData(), 'a');
			it->next();
			Assert::AreEqual(it->getData(), 'c');
			it->next();
			Assert::AreEqual(it->getData(), 'f');
			it->next();
			Assert::AreEqual(it->getData(), 'e');
			it->next();
			Assert::AreEqual(it->getData(), 'h');
			it->next();
			Assert::AreEqual(it->getData(), 'g');
			it->next();
			Assert::AreEqual(it->getData(), 'i');
			it->next();
			Assert::AreEqual(it->getData(), 'j');

			delete list;
			list = nullptr;

			delete it;
			it = nullptr;

			delete tree;
			tree = nullptr;
		}

		TEST_METHOD(Find) {
			RedBlackTree<int, char> *tree = new RedBlackTree<int, char>();
			RedBlackNode<int, char> *node = nullptr;

			tree->insert(1, 'a');
			tree->insert(2, 'b');
			tree->insert(3, 'c');
			tree->insert(4, 'd');
			tree->insert(5, 'e');
			tree->insert(6, 'f');
			tree->insert(7, 'g');
			tree->insert(8, 'h');
			tree->insert(9, 'i');
			tree->insert(10, 'j');

			node = tree->find(4);
			Assert::AreEqual(node->getKey(), 4);
			Assert::AreEqual(node->getValue(), 'd');
			Assert::AreEqual(node->isBlack(), true);

			node = tree->find(6);
			Assert::AreEqual(node->getKey(), 6);
			Assert::AreEqual(node->getValue(), 'f');
			Assert::AreEqual(node->isBlack(), true);

			node = tree->find(8);
			Assert::AreEqual(node->getKey(), 8);
			Assert::AreEqual(node->getValue(), 'h');
			Assert::AreEqual(node->isBlack(), false);

			node = tree->find(9);
			Assert::AreEqual(node->getKey(), 9);
			Assert::AreEqual(node->getValue(), 'i');
			Assert::AreEqual(node->isBlack(), true);

			node = tree->find(10);
			Assert::AreEqual(node->getKey(), 10);
			Assert::AreEqual(node->getValue(), 'j');
			Assert::AreEqual(node->isBlack(), false);

			node = tree->find(7);
			Assert::AreEqual(node->getKey(), 7);
			Assert::AreEqual(node->getValue(), 'g');
			Assert::AreEqual(node->isBlack(), true);

			node = tree->find(5);
			Assert::AreEqual(node->getKey(), 5);
			Assert::AreEqual(node->getValue(), 'e');
			Assert::AreEqual(node->isBlack(), true);

			node = tree->find(2);
			Assert::AreEqual(node->getKey(), 2);
			Assert::AreEqual(node->getValue(), 'b');
			Assert::AreEqual(node->isBlack(), true);

			node = tree->find(3);
			Assert::AreEqual(node->getKey(), 3);
			Assert::AreEqual(node->getValue(), 'c');

			node = tree->find(1);
			Assert::AreEqual(node->getKey(), 1);
			Assert::AreEqual(node->getValue(), 'a');
			Assert::AreEqual(node->isBlack(), true);

			node = nullptr;

			delete tree;
			tree = nullptr;
		}
	};
}