#pragma once

#include "IndexOutOfRange.hpp"
#include "NegativeSize.hpp"

template<class T>
class DynamicArray {
private:
    T* array; // != nullptr если непустой
    int size;
public:
    // копирует элементы из переданного массива
    // items - указатель на константу
    DynamicArray(const T* items, int count) : DynamicArray{count} {
        for (int i = 0; i < count; ++i) {
            array[i] = items[i];
        }
    }

    // Создать массив заданной длины
    explicit DynamicArray(int size)
        : array{size < 0 ? throw NegativeSize{"'size'"} : size == 0 ? nullptr : new T[size]{}}
        , size{size} {
    }

    // Копирующий конструктор
    DynamicArray(const DynamicArray<T> &other)
        : DynamicArray{other.array, other.size} {
    }

    // move-конструктор
    DynamicArray(DynamicArray<T> &&other) : DynamicArray{} {
        std::swap(array, other.array);
        std::swap(size, other.size);
    }


    DynamicArray& operator=(DynamicArray&& other) {
        std::swap(array, other.array);
        std::swap(size, other.size);
        return *this;
    }

	DynamicArray& operator=(const DynamicArray& other) {
		if (this == &other) {
			return *this;
		}
        *this = DynamicArray{other};
        return *this;
    }

    // создает массив размера newSize
    DynamicArray(const DynamicArray<T> &other, int newSize)
        : DynamicArray(newSize) {

        for (int i = std::min(other.size, newSize) - 1; i >= 0; --i) {
            array[i] = other.array[i];
        }
    }

    // пустой массив
    DynamicArray() : array{nullptr}, size{0} {
    }

    // Декомпозиция //

    // Получить элемент по индексу
    // может выбрасывать исключения:
    // - IndexOutOfRange (если индекс отрицательный, больше/равен числу элементов)
    const T &get(int index) const {
        if (index < 0 || index >= size) {
            throw IndexOutOfRange{"'index' is out of range"};
        }
        return array[index];
    }

    // Получить размер массива
    int getSize() const {
        return size;
    }

    // Задать элемент по индексу.
    // Может выбросить IndexOutOfRange
    void set(int index, const T &value) {
        if (index < 0 || index >= size) {
            throw IndexOutOfRange{"'index' is out of range"};
        }
        array[index] = value;
    }

    T& operator[](int index) {
        return array[index];
    };

    ~DynamicArray() {
        delete[] array;
    }
};