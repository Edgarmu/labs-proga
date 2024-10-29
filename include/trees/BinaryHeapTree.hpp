#pragma once

#include <utility>
#include <string>
#include <sstream>

template<class T>
class BinaryHeapTree {
	struct Node {
		// инварианты:
		// parent->element <= element
		// element <= leftChild->element (если leftChild != nullptr)
		// element <= rightChild->element (если rightChild != nullptr)
		Node *parent;
		Node *leftChild;
		Node *rightChild;
		T element;

		Node(const T &element)
			: parent{nullptr}, leftChild{nullptr}, rightChild{nullptr}, element{element} {
		}

		void append(Node *child) {
			if (parent != nullptr) {
				if (parent->rightChild != nullptr) {
					parent->rightChild->append(child);
				}
				return;
			}
			child->parent = this;
			if (leftChild == nullptr) {
				leftChild = child;
				return;
			}
			assert(rightChild == nullptr);
			rightChild = child;
		}

		void sendUp() {
			if (parent == nullptr || parent->element <= element) {
				return;
			}
			std::swap(parent->element, element);
			parent->sendUp();
		}


		void sendDown() {
			if (leftChild == nullptr) {
				return;
			}
			Node *minChild = leftChild;
			if (rightChild != nullptr && rightChild->element < leftChild->element) {
				minChild = rightChild;
			}
			if (element <= minChild->element) {
				return;
			}
			std::swap(element, minChild->element);
			minChild->sendDown();
		}
	};

	Node *root;
	Node *last;
	int size;

	static Node *find(Node *node, const T &element) {
		if (node == nullptr || node->element == element) {
			return node;
		}
		if (element < node->element) {
			return nullptr;
		}
		for (Node *child: {node->leftChild, node->rightChild}) {
			Node *result = find(child, element);
			if (result != nullptr) {
				return result;
			}
		}
		return nullptr;
	}

	static std::string traverse(const Node *node, const char *formatString) {
		if (node == nullptr) {
			return {};
		}
		std::stringstream result;
		auto left = traverse(node->leftChild, formatString);
		auto right = traverse(node->rightChild, formatString);
		while (*formatString != '\0') {
			char c = *formatString;
			switch (c) {
				case 'K':
					result << node->element;
					break;
				case 'L': {
					result << left;
					break;
				}
				case 'R': {
					result << right;
					break;
				}
				default:
					result << c;
			}
			formatString++;
		}
		auto str = result.str();
		str.erase(str.find_last_not_of(' ') + 1);
		str.erase(0, str.find_first_not_of(' '));
		return str;
	}

	static std::string pairList(const Node *node) {
		if (node == nullptr || node->leftChild == nullptr) {
			return {};
		}
		std::stringstream stream;
		const char pairSeparator = ';';
		const char elementsSeparator = '<';
		stream << node->element << elementsSeparator << node->leftChild->element << pairSeparator;
		if (node->rightChild != nullptr) {
			stream << node->element << elementsSeparator << node->rightChild->element << pairSeparator;
		}
		stream << pairList(node->leftChild) << pairList(node->rightChild);
		return stream.str();
	}

	// находит указатель на элемент с заданным индексом (child) вместе с его parent
	// пара parent, child
	std::pair<Node **, Node **> find(int index) {
		int k = 0; // глубина дерева = длина пути
		int path = 0; // биты path кодируют путь от корня
		for (int n = 1 + index; n >= 2; k += 1, n /= 2) {
			path = (path << 1) | (n & 1);
		}
		Node **parent = &root;
		Node **child = &root;
		while (k > 0) {
			parent = child;
			if (path & 1) {
				child = &((*child)->rightChild);
			}
			else {
				child = &((*child)->leftChild);
			}
			path >>= 1;
			k -= 1;
		}
		return {parent, child};
	}

public:

	BinaryHeapTree() : root{nullptr}, last{nullptr}, size{0} {
	}

	T getMin() const {
		if (root == nullptr) {
			throw IndexOutOfRange{"No elements"};
		}
		return root->element;
	}

	bool exist(const T &element) const {
		return find(root, element) != nullptr;
	}

	void eraseMin() {
		if (root == nullptr) {
			throw IndexOutOfRange{"No elements"};
		}
		if (root == last) {
			delete root;
			root = last = nullptr;
			size--;
			return;
		}
		std::swap(root->element, last->element);
		Node *p = last->parent;
		if (p->leftChild == last) {
			p->leftChild = nullptr;
		}
		else {
			assert(p->rightChild == last);
			p->rightChild = nullptr;
		}
		delete last;
		root->sendDown();
		size--;
		last = *find(size - 1).second;
	}

	void erase(const T &element) {
		Node *ptr = find(root, element);
		if (ptr == nullptr) {
			return;
		}
		while (root != ptr) {
			std::swap(ptr->element, ptr->parent->element);
			ptr = ptr->parent;
		}
		eraseMin();
	}

	void add(const T &element) {
		auto [parent, child] = find(size);
		Node *newnode = new Node{element};
		newnode->parent = *parent;
		*child = newnode;
		newnode->sendUp();
		last = newnode;
		size++;
	}

	int getSize() const {
		return size;
	}

	// Сохранение в строку по обходу, задаваемому строкой форматирования (наример: «{K}(L)[R]»)
	std::string traverse(const char *formatString) const {
		return traverse(root, formatString);
	}

	// Сохранение в строку по фиксированному обходу
	std::string traverse() const {
		return traverse("K L R");
	}

// Сохранение в строку в формате списка пар «узел-родитель»
// пары разделяются ';'
// узел и родитель разделяются '<'
	std::string pairList() const {
		std::string result = pairList(root);
		if (!result.empty()) {
			result.pop_back();
		}
		return result;
	}

};
