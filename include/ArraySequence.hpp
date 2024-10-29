#pragma once
#include "DynamicArray.hpp"
#include "MutableSequence.hpp"
#include "InconsistentBounds.hpp"
#include "ImmutableSequence.hpp"

template <class T>
class ArraySequence : public MutableSequence<T> {
private:
    // items.getSize() = вместимость, [0, actualSize) -- диапазон верных индексов.
    // Всегда: items.getSize() >= actualSize
    DynamicArray<T> items;
    // количество адресуемых элементов
    int actualSize;
public:
    // Копировать элементы из переданного массива (первые count)
    ArraySequence(const T* items, int count)
        : items{items, count}, actualSize{count} {
    }

	ArraySequence(int count)
        : items{count}, actualSize{count} {
    }

    // Создать пустой список
    explicit ArraySequence() : items{}, actualSize{0} {
    }

    explicit ArraySequence(const DynamicArray<T>& items)
        : items{items}, actualSize{items.getSize()} {
    };

    ArraySequence(const ArraySequence<T>&) = default;
    ArraySequence(ArraySequence<T>&&) = default;

	ArraySequence& operator=(ArraySequence<T>&& other) {
		std::swap(actualSize, other.actualSize);
		std::swap(items, other.items);
		return *this;
	}

	ArraySequence& operator=(const ArraySequence<T>& other) {
		if (this == &other) {
			return *this;
		}
		*this = ArraySequence{other};
		return *this;
	}

public:
    const T& getFirst() const override {
        if (actualSize <= 0) {
            throw IndexOutOfRange{"sequence is empty"};
        }
        return get(0);
    }

    const T& getLast() const override {
        if (actualSize <= 0) {
            throw IndexOutOfRange{"sequence is empty"};
        }
        return get(actualSize - 1);
    }

    const T& get(int index) const override {
        if (index < 0 || index >= actualSize) {
            throw IndexOutOfRange{"'index' is out of range"};
        }
        return items.get(index);
    }

	T& operator[](int index) override {
        if (index < 0 || index >= actualSize) {
            throw IndexOutOfRange{"'index' is out of range"};
        }
        return items[index];
    }
	const T& operator[](int index) const {
        if (index < 0 || index >= actualSize) {
            throw IndexOutOfRange{"'index' is out of range"};
        }
        return items.get(index);
    }

    ArraySequence<T>* getSubsequence(int startIndex, int endIndex) const override {
        if (endIndex < 0 || endIndex >= actualSize) {
            throw IndexOutOfRange{"'endIndex' is out of range"};
        }
        if (startIndex < 0 || startIndex >= actualSize) {
            throw IndexOutOfRange{"'startIndex' is out of range"};
        }
        if (endIndex < startIndex) {
            throw InconsistentBounds{"endIndex should be >= startIndex"};
        }

        auto subArray = DynamicArray<T>(endIndex - startIndex + 1);
        const int size = subArray.getSize();
        for (int i = 0; i < size; ++i) {
            subArray.set(i, items.get(startIndex + i));
        }
        return new ArraySequence<T>{subArray};
    }

    int getLength() const override {
        return actualSize;
    }
public:
    ArraySequence<T>* append(const T& item) override {
        ensureCapacityGreaterThanSizeBy(1);
        items.set(actualSize, item);
        actualSize++;
        return this;
    }

	ArraySequence<T>* dropLast() override {
        if (actualSize <= 0) {
			throw IndexOutOfRange{"sequence is empty"};
		}
		actualSize--;
        return this;
    }

    ArraySequence<T>* prepend(const T& item) override {
        ensureCapacityGreaterThanSizeBy(1);
        for (int i = actualSize - 1; i > 0; --i) {
            items.set(i, items.get(i - 1));
        }
        items.set(0, item);
        actualSize++;
        return this;
    }

    ArraySequence<T>* insertAt(const T& item, int index) override {
        if (index < 0 || index > actualSize) {
            throw IndexOutOfRange{"'index' is out of range"};
        }
        ensureCapacityGreaterThanSizeBy(1);
        for (int i = actualSize; i > index; --i) {
            items.set(i, items.get(i - 1));
        }
        items.set(index, item);
        actualSize++;
        return this;
    }

    ArraySequence<T>* concat(const Sequence<T>& other) override {
        ensureCapacityGreaterThanSizeBy(other.getLength());
        for (int i = 0; i < other.getLength(); ++i) {
            items.set(actualSize + i, other.get(i));
        }
        actualSize += other.getLength();
        return this;
    }

private:
    // гарантирует, что можно вместить еще delta элементов в массив
    void ensureCapacityGreaterThanSizeBy(int delta) {
        int capacity = items.getSize();
        if (capacity >= actualSize + delta) {
            return;
        }
        items = {items, actualSize + actualSize + delta};
    }
};
