#pragma once

#include "IndexOutOfRange.hpp"
#include "InconsistentBounds.hpp"

template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };
    
    Node* first;
    Node* last;
    int size;
public:
    // Создание объекта //

    LinkedList(const T* items, int count) : LinkedList() {
        if (count <= 0) {
            return;
        }
        first = new Node { items[0], nullptr, nullptr };
        Node* elem = first;
        for (int i = 1;i < count;i++) {
            elem->next = new Node {items[i], elem, nullptr};
            elem = elem->next;
        }
        last = elem;
        size = count;

    }

    // Создать пустой список
    LinkedList()
        : first{nullptr}
        , last{nullptr}
        , size{0} {
    }

    // Копирующий конструктор
    LinkedList(const LinkedList<T>& other) : LinkedList{} {
        if (other.size == 0) {
            return;
        }
        first = new Node { other.first->data, nullptr, nullptr };
        Node* elem = first;
        Node* otherElem = other.first->next;
        while (otherElem != nullptr) {
            elem->next = new Node {otherElem->data, elem, nullptr};
            otherElem = otherElem->next;
            elem = elem->next;
        }
        last = elem;
        size = other.size;
    };

    LinkedList(LinkedList&& other) : LinkedList{} {
        std::swap(first, other.first);
        std::swap(last, other.last);
        std::swap(size, other.size);
    }

    ~LinkedList() {
        Node* node = first;
        while (node != last) {
            Node* tempNode = node->next;
            delete node;
            node = tempNode;
        }
    }
public:

    // Декомпозиция //

    // Получить первый элемент в списке.
    // Может выбрасывать исключения:
    // − IndexOutOfRange (если список пуст)
    const T& getFirst() const {
        if (first == nullptr) {
            throw IndexOutOfRange{ "list is empty" };
        }
        return first->data;
    }

    // Получить последний элемент в списке.
    // Может выбрасывать исключения:
    // − IndexOutOfRange (если список пуст)
    const T& getLast() const {
        if (last == nullptr) {
            throw IndexOutOfRange{ "list is empty" };
        }
        return last->data;
    }

    // Получить элемент по индексу. O(index)
    // Может выбрасывать исключения:
    // − IndexOutOfRange (если индекс отрицательный или больше/равен числу элементов)
    const T& get(int index) const {
        return getNode(index)->data;
    }

    // Получить список из всех элементов, начиная с startIndex
    // и заканчивая endIndex (включительно).
    // Изменение полученного списка *не повлечет* изменение исходного списка.
    // Может выбрасывать исключения:
    // − IndexOutOfRange (если хотя бы один из индексов отрицательный или больше/равен числу элементов)
    LinkedList<T> getSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || startIndex >= size) {
            throw IndexOutOfRange{"'startIndex' is out of range"};
        }
        if (endIndex < 0 || endIndex >= size) {
            throw IndexOutOfRange{"'endIndex' is out of range"};
        }
        if (endIndex < startIndex) {
            throw InconsistentBounds{"endIndex should be >= startIndex"};
        }
        int subListSize = endIndex + 1 - startIndex;
        LinkedList subList{};
        if (subListSize == 0) {
            return subList;
        }
        Node* myFirst = getNode(startIndex);
        subList.first = new Node { myFirst->data, nullptr, nullptr };
        Node* elem = subList.first;
        Node* otherElem = myFirst->next;
        while (otherElem != nullptr) {
            elem->next = new Node {otherElem->data, elem, nullptr};
            otherElem = otherElem->next;
            elem = elem->next;
        }
        subList.last = elem;
        subList.size = subListSize;
        return subList;
    }

    // Получить длину списка
    int getLength() const {
        return size;
    }

    // Операции //

    // Добавляет элемент в конец списка
    void append(const T& item) {
        Node* newLast = new Node {item, last, nullptr };
        if (last == nullptr) {
            first = newLast;
        } else {
            last->next = newLast;
        }
        last = newLast;
        size++;
    }

    // Добавляет элемент в начало списка
    void prepend(const T& item) {
        Node* newFirst = new Node {item, nullptr, first };
        if (first == nullptr) {
            last = newFirst;
        } else {
            first->prev = newFirst;
        }
        first = newFirst;
        size++;
    }

    // Вставляет элемент в заданную позицию
    // index -- индекс вставленного элемента в измененном списке.
    // Может выбрасывать исключения:
    // − IndexOutOfRange (если индекс отрицательный или больше числа элементов)
    void insertAt(const T& item, int index) {
        if (index < 0 || index > size) {
            throw IndexOutOfRange{"'index' is out of range"};
        }
        if (index == 0) {
            prepend(item);
            return;
        }
        if (index == size) {
            append(item);
            return;
        }
        // было:  [prev_node]-1->  <-4-[the_node]
        // стало: [prev_node]-1->  <-2-[new_node]-3->  <-4-[the_node]
        Node* the_node = getNode(index);
        Node* prev_node = the_node->prev;
        Node* new_node = new Node { item, prev_node, the_node }; // указатели 2, 3
        prev_node->next = new_node; // указатель 1
        the_node->prev = new_node; // указатель 4
        size++;
    }

    // Сцепляет два списка: прицепляет к списку (*this) список list.
    // После выполнения операции list пуст!
    LinkedList<T>& concat(LinkedList<T>&& list) {
        if (list.first == nullptr) {
            return *this;
        }
        if (first == nullptr) {
            first = list.first;
        } else {
        // было:   [last]-1-?  ?-2-[list.first]
        // стало:  [last]-1->  <-2-[list.first]
            last->next = list.first;
            list.first->prev = last;
        }
        last = list.last;
        size += list.size;

        list.first = nullptr;
        list.last = nullptr;
        list.size = 0;
        return *this;
    }

    private:
    Node* getNode(int index) const {
        if (index < 0 || index >= size) {
            throw IndexOutOfRange{"'index' is out of range"};
        }
        Node* element = this->first;
        for (int i = 0; i < index; ++i) {
            element = element->next;
        }
        return element;
    }
public:
	T& operator[](int index) {
		return getNode(index)->data;
	}
};