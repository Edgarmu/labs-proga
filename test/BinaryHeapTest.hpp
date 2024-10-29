#pragma once

#include <cassert>

template<class T>
class BinaryHeapTest {

public:
	BinaryHeapTest() {
		getSize();
		getSizeEmpty();
		getMin();
		getMinEmptyThrows();
		add();
		exists();
		existsEmptyThrows();
		erase();
		eraseEmpty();
		eraseMin();
		eraseMinEmpty();
		pairList();
		pairListEmpty();
		traverseFormat();
		traverseFormatEmpty();
		traverse();
		traverseEmpty();
	}

	T create() const {
		T heap{};
		heap.add('b');
		heap.add('a');
		heap.add('f');
		heap.add('e');
		heap.add('h');
		heap.add('g');
		heap.add('c');
		heap.add('d');
		return heap;
	}

	void getSize() {
		T heap = create();
		assert(heap.getSize() == 8);
	}

	void getSizeEmpty() {
		T empty{};
		assert(empty.getSize() == 0);
	}

	void getMin() {
		T heap = create();
		assert(heap.getMin() == 'a');
	}

	void getMinEmptyThrows() {
		T empty{};
		try {
			empty.getMin();
		} catch (const IndexOutOfRange &) { return; }
		assert(false);
	}

	void add() {
		T heap = create();
		heap.add('0');
		assert(heap.getSize() == 9);
	}

	void exists() {
		T heap = create();
		assert(heap.exist('a'));
		assert(!heap.exist('*'));
	}

	void existsEmptyThrows() {
		T empty{};
		assert(!empty.exist('a'));
	}

	void erase() {
		T heap = create();
		heap.erase('*');
		assert(heap.getSize() == 8);
		heap.erase('a');
		int elements = 7;
		assert(heap.getSize() == elements);
		for (char c = 'h'; c >= 'b'; c--) {
			heap.erase(c);
			elements--;
			assert(heap.getSize() == elements);
		}
	}

	void eraseEmpty() {
		T empty{};
		empty.erase('a');
		assert(empty.getSize() == 0);
	}

	void eraseMin() {
		T heap = create();
		heap.eraseMin();
		assert(!heap.exist('a'));
	}

	void eraseMinEmpty() {
		T empty{};
		try {
			empty.eraseMin();
		} catch (const IndexOutOfRange &) { return; }
		assert(false);

	}

	void traverse() {
		T heap = create();
		std::string s = heap.traverse();
		auto expected = "a b d e h c g f";
		assert(s == expected);
	}

	void traverseEmpty() {
		T empty{};
		std::string s = empty.traverse();
		assert(s.empty());
	}

	void pairList() {
		T heap = create();
		std::string s = heap.pairList();
		auto expected = "a<b;a<c;b<d;b<h;c<g;c<f;d<e";
		auto expected2 = "a<b;a<c;b<d;b<h;d<e;c<g;c<f";
		assert(s == expected || s == expected2);

	}

	void pairListEmpty() {
		T empty{};
		std::string s = empty.pairList();
		assert(s.empty());
	}

	void traverseFormat() {
		T heap = create();
		std::string s = heap.traverse("{K}(L)[R]");
		auto expected = "{a}({b}({d}({e}()[])[])[{h}()[]])[{c}({g}()[])[{f}()[]]]";
		assert(s == expected);
	}

	void traverseFormatEmpty() {
		T empty{};
		std::string s = empty.traverse("{K}(L)[R]");
		assert(s.empty());
	}
};