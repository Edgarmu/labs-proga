#pragma once

#include "LinkedList.hpp"

template<class T>
class ListSequence : public MutableSequence<T> {
private:
    LinkedList<T> delegate;
public:
    ListSequence(T *items, int count) : delegate{items, count} {
    }

    ListSequence() : delegate{} {
    }

    explicit ListSequence(const LinkedList<T> &list) : delegate{list} {
    }

    ListSequence(const ListSequence<T> &) = default;

    ListSequence(ListSequence<T> &&) = default;

    ~ListSequence() = default;

public:
    const T &getFirst() const override {
        return delegate.getFirst();
    }

    const T &getLast() const override {
        return delegate.getLast();
    }

    const T &get(int index) const override {
        return (delegate.get(index));
    }

    // delete выполняет вызывающая функция
    ListSequence<T> *getSubsequence(int startIndex, int endIndex) const override {
        //используется move-конструктор
        return new ListSequence<T>{delegate.getSubList(startIndex, endIndex)};
    }

    int getLength() const override {
        return delegate.getLength();
    }

public:
    ListSequence<T> *append(const T &item) override {
        delegate.append(item);
        return this;
    }

    ListSequence<T> *prepend(const T &item) override {
        delegate.prepend(item);
        return this;
    }

    ListSequence<T> *insertAt(const T &item, int index) override {
        delegate.insertAt(item, index);
        return this;
    }

    ListSequence<T> *concat(const Sequence<T> &other) override {
        if (other.getLength() == 0) {
            return this;
        }
        // если передали ListSequence можем пользоваться LinkedList::concat
        auto ptr = dynamic_cast<const ListSequence<T> *>(&other);
        if (ptr != nullptr) {
            delegate.concat(LinkedList<T>{ptr->delegate});
            return this;
        }

        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
        return this;
    }

	T &operator[](int index) override
	{
		return delegate[index];
	}

	ListSequence<T>* dropLast() override {
		return nullptr;
	}
};
