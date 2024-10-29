#pragma once

#include "Sequence.hpp"

template <class T>
class MutableSequence : public Sequence<T> {
public:
    // Получить список из всех элементов, начиная с startIndex и заканчивая endIndex.
    virtual MutableSequence<T>* getSubsequence(int startIndex, int endIndex) const = 0;
    // Добавляет элемент в конец списка
    virtual MutableSequence<T>* append(const T& item) = 0;
    // Добавляет элемент в начало списка
    virtual MutableSequence<T>* prepend(const T& item) = 0;
    // Вставляет элемент в заданную позицию
    virtual MutableSequence<T>* insertAt(const T& item, int index) = 0;
    // Прицепляет переданный список к концу текущего
    virtual MutableSequence<T>* concat(const Sequence<T>& list) = 0; //const параметр

//	virtual MutableSequence<T>* set(const T& item, int index) = 0;

	virtual T& operator[](int index) = 0;

	virtual MutableSequence<T>* dropLast() = 0;

    virtual ~MutableSequence() {};
};
 
