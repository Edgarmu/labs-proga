#pragma once
#include "Sequence.hpp"

// Все методы ImmutableSequence возвращают новый список, не изменяют текущий
template <class T>
class ImmutableSequence : public Sequence<T> {
public:
    // Получить список из всех элементов, начиная с startIndex и заканчивая endIndex.
    virtual ImmutableSequence<T>* getSubsequence(int startIndex, int endIndex) const = 0;
    // Добавляет элемент в конец списка
    virtual ImmutableSequence<T>* append(const T& item) const = 0;
    // Добавляет элемент в начало списка
    virtual ImmutableSequence<T>* prepend(const T& item) const = 0;
    // Вставляет элемент в заданную позицию
    virtual ImmutableSequence<T>* insertAt(const T& item, int index) const = 0;
    // Сцепляет два списка
    virtual ImmutableSequence<T>* concat(const Sequence<T>& list) const = 0;

    virtual ~ImmutableSequence() = default;
};
