#pragma once

template <class T>
class Sequence {
public:
    // Декомпозиция //
    // Получить первый элемент в списке
    virtual const T& getFirst() const = 0;
    // Получить последний элемент в списке
    virtual const T& getLast() const = 0;
    // Получить элемент по индексу
    virtual const T& get(int index) const = 0;
    // Получить длину списка
    virtual int getLength() const = 0;

    virtual ~Sequence() = default;
};
