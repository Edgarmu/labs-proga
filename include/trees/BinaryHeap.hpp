#pragma once

#include "MutableSequence.hpp"
#include "NegativeSize.hpp"
#include "ArraySequence.hpp"

#include <utility>
#include <iostream>
#include <sstream>

template<class T>
class BinaryHeap {
private:
	MutableSequence<T> *elements;
private:

	static constexpr int ELEMENT_NOT_FOUND_INDEX = -1;

	static constexpr int leftChild(int index) {
		return 2 * index + 1;
	}

	static constexpr int rightChild(int index) {
		return 2 * index + 2;
	}

	static constexpr int parent(int index) {
		return (index - 1) / 2;
	}

	void sendUp(int index) {
		int i = index;
		while ((*elements)[parent(i)] > (*elements)[i]) {
			std::swap((*elements)[parent(i)], (*elements)[i]);
			i = parent(i);
		}
	}

	void sendDown(int index) {
		int i = index;
		while (leftChild(i) < getSize()) {
			int minChild = leftChild(i);
			if (rightChild(i) < getSize() && (*elements)[rightChild(i)] < (*elements)[leftChild(i)]) {
				minChild = rightChild(i);
			}
			if ((*elements)[i] <= (*elements)[minChild]) {
				break;
			}

			std::swap((*elements)[i], (*elements)[minChild]);
			i = minChild;
		}
	}

	// returns ELEMENT_NOT_FOUND_INDEX if not found
	int find(const T &element) const {
		for (int i = 0; i < getSize(); i++) {
			if ((*elements)[i] == element) {
				return i;
			}
		}
		return ELEMENT_NOT_FOUND_INDEX;
	}

	std::string traverse(int i, const char* formatString) const {
		if (i >= getSize()) {
			return {};
		}
		auto left = traverse(leftChild(i), formatString);
		auto right = traverse(rightChild(i), formatString);
		std::stringstream result;
		while (*formatString != '\0') {
			char c = *formatString;
			switch (c) {
				case 'K':
					result << (*elements)[i];
					break;
				case 'L':
					result << left;
					break;
				case 'R':
					result << right;
					break;
				default: {
					result << c;
				}
			}
			formatString++;
		}
		auto str = result.str();
		str.erase(str.find_last_not_of(' ')+1);
		str.erase(0, str.find_first_not_of(' '));
		return str;
	}

public:
	BinaryHeap()
		: elements{new ArraySequence<T>{}} {
	}

	~BinaryHeap() {
		delete elements;
		elements = nullptr;
	}

	int getSize() const {
		return elements->getLength();
	}

	T getMin() const {
		if (elements->getLength() == 0) {
			throw IndexOutOfRange{"heap is empty"};
		}
		return (*elements)[0];
	}

	// Вставка
	void add(const T& element) {
		elements->append(element);
		sendUp(getSize() - 1);
	}

	// Поиск
	bool exist(const T &element) const {
		return find(element) != ELEMENT_NOT_FOUND_INDEX;
	}

	// удаление
	void erase(const T &element) {
		int i = find(element);
		if (i == ELEMENT_NOT_FOUND_INDEX) {
			return;
		}
		while (i != 0) {
			std::swap((*elements)[parent(i)], (*elements)[i]);
			i = parent(i);
		}
		eraseMin();
	}

	void eraseMin() {
		if (getSize() == 0) {
			throw IndexOutOfRange{"heap is empty"};
		}
		std::swap((*elements)[0], (*elements)[getSize() - 1]);
		elements->dropLast();
		sendDown(0);
	}

	// Сохранение в строку по обходу, задаваемому строкой форматирования (наример: «{K}(L)[R]»)
	std::string traverse(const char* formatString) const {
		return traverse(0, formatString);
	}

	// Сохранение в строку по фиксированному обходу
	std::string traverse() const {
		return traverse("K L R");
	}

	// Сохранение в строку в формате списка пар «узел-родитель»
	// пары разделяются ';'
	// узел и родитель разделяются '<'
	std::string pairList() {
		std::stringstream stream;
		for (int i = 0; leftChild(i) < getSize(); ++i) {
			const char pairSeparator = ';';
			const char elementsSeparator = '<';
			stream << (*elements)[i] << elementsSeparator << (*elements)[leftChild(i)] << pairSeparator;
			if (rightChild(i) >= getSize()) {
				break;
			}
			stream << (*elements)[i] << elementsSeparator << (*elements)[rightChild(i)] << pairSeparator;
		}
		auto result = stream.str();
		if (!result.empty()) {
			result.pop_back();
		}
		return result;
	}
};