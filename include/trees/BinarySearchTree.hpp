#pragma once

#include <string>
#include <sstream>
#include <cassert>

template<typename T>
class BinarySearchTree {
private:
	struct Node {
		// инварианты:
		// left->value < value (если left != nullptr)
		// right->value >= value (если right != nullptr)
		Node() : Node({}) {
		}

		explicit Node(T item) : left{nullptr}, right{nullptr}, value{item} {
		}

		Node *left;
		Node *right;
		T value;
	};

	Node *root = nullptr;

	static std::string traverse(const Node *node, const char *formatString) {
		if (node == nullptr) {
			return {};
		}

		std::string left = traverse(node->left, formatString);
		std::string right = traverse(node->right, formatString);
		std::stringstream result;
		while (*formatString != '\0') {
			char c = *formatString;
			switch (c) {
				case 'K':
					result << node->value;
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
	};

	static void add(Node *node, Node *element) {
		assert(node != nullptr);
		if (element->value < node->value) {
			if (node->left == nullptr) {
				node->left = element;
			}
			else {
				add(node->left, element);
			}
		}
		else {
			if (node->right == nullptr) {
				node->right = element;
			}
			else {
				add(node->right, element);
			}
		}
	}

	static Node *find(Node *node, const T &value) {
		if (node == nullptr || node->value == value) {
			return node;
		}
		if (value < node->value) {
			return find(node->left, value);
		}
		return find(node->right, value);
	}

	void add(Node *node) {
		if (this->root == nullptr) {
			this->root = node;
		}
		else {
			add(this->root, node);
		}
	}

	// для erase
	static Node *successor(Node *node) {
		node = node->right;
		while (node != nullptr && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	Node *erase(Node *root, const T &element) {
		if (root == nullptr) {
			return nullptr;
		}
		if (root->value > element) {
			root->left = erase(root->left, element);
			return root;
		}
		if (root->value < element) {
			root->right = erase(root->right, element);
			return root;
		}
		// root - лист или есть только right ветка
		if (root->left == nullptr) {
			Node *temp = root->right;
			delete root;
			return temp;
		}

		// есть только left ветка
		if (root->right == nullptr) {
			Node *temp = root->left;
			delete root;
			return temp;
		}

		// когда есть обе ветки
		Node *next = successor(root);
		root->value = next->value;
		root->right = erase(root->right, next->value);
		return root;
	}

	static void deleteNode(Node* root) {
		if (root == nullptr) {
			return;
		}
		deleteNode(root->left);
		deleteNode(root->right);
		delete root;
	}

public:
	BinarySearchTree() : root{nullptr} {}

	// вставка
	void add(const T &element) {
		add(new Node{element});
	}

	// поиск
	bool exist(const T &element) const {
		return find(this->root, element) != nullptr;
	}

	// Сохранение в строку по обходу, задаваемому строкой форматирования (наример: «{K}(L)[R]»)
	std::string traverse(const char *formatString) const {
		return traverse(root, formatString);
	}

	// Сохранение в строку по фиксированному обходу
	std::string traverse() const {
		return traverse("L K R");
	}

	// удаление
	void erase(const T &element) {
		root = erase(root, element);
	}

	~BinarySearchTree() {
		deleteNode(root);
	}
};