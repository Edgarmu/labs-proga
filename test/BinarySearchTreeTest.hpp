#pragma once

#include <cassert>

#include "BinarySearchTree.hpp"

class BinarySearchTreeTest {
	using T = BinarySearchTree<char>;
public:
	BinarySearchTreeTest() {
		add();
		exist();
		existEmptyThrows();
		erase();
		eraseEmpty();
		traverseFormat();
		traverseFormatEmpty();
		traverse();
		traverseEmpty();
	}

	T create() const {
		T tree{};
		tree.add('b');
		tree.add('a');
		tree.add('f');
		tree.add('e');
		tree.add('h');
		tree.add('g');
		tree.add('c');
		tree.add('d');
		return tree;
	}

	void add() {
		T tree = create();
		tree.add('0');
		assert(tree.exist('0'));
	}

	void exist() {
		T tree = create();
		assert(tree.exist('a'));
		assert(!tree.exist('*'));
	}

	void existEmptyThrows() {
		T empty{};
		assert(!empty.exist('a'));
	}

	void erase() {
		T tree = create();
		tree.erase('*');
		assert(!tree.exist('*'));
		tree.erase('a');
		assert(!tree.exist('a'));
		for (char c = 'h'; c >= 'b'; c--) {
			tree.erase(c);
			assert(!tree.exist(c));
		}
	}

	void eraseEmpty() {
		T empty{};
		empty.erase('a');
		assert(!empty.exist('a'));
	}

	void traverse() {
		T tree = create();
		std::string s = tree.traverse();
		auto expected = "a b c d e f g h";
		assert(s == expected);
	}

	void traverseEmpty() {
		T empty{};
		std::string s = empty.traverse();
		assert(s.empty());
	}

	void traverseFormat() {
		T tree = create();
		std::string s = tree.traverse("{K}(L)[R]");
		auto expected = "{b}({a}()[])[{f}({e}({c}()[{d}()[]])[])[{h}({g}()[])[]]]";
		assert(s == expected);
	}

	void traverseFormatEmpty() {
		T empty{};
		std::string s = empty.traverse("{K}(L)[R]");
		assert(s.empty());
	}
};