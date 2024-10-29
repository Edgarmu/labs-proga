#pragma once
#include "ArraySequence.hpp"

template <class T>
class ImmutableArraySequence : public ImmutableSequence<T> {
private:
    const ArraySequence<T> delegate;

    explicit ImmutableArraySequence(ArraySequence<T>&& delegate) : delegate{delegate} {
    }
public:
    ImmutableArraySequence(const T* items, int count) : delegate(items, count) {
    }

    explicit ImmutableArraySequence() : delegate{} {
    }

    explicit ImmutableArraySequence(const DynamicArray<T>& dynamicArray)
        : delegate{dynamicArray} {
    }

    // Не нужно копировать ImmutableArraySequence, т.к. он неизменяемый
    ImmutableArraySequence(const ImmutableArraySequence<T>&) = delete;
    ~ImmutableArraySequence() = default;

public:
    const T& getFirst() const override {
        return delegate.getFirst();
    }

    const T& getLast() const override {
        return delegate.getLast();
    }

    const T& get(int index) const override {
        return delegate.get(index);
    }

    // delete выполняет вызывающая сторона
    ImmutableArraySequence<T>* getSubsequence(int startIndex, int endIndex) const override {
        auto* sub = delegate.getSubsequence(startIndex, endIndex);
        auto* result = new ImmutableArraySequence{std::move(*sub)};
        delete sub;
        return result;
    }

    int getLength() const override {
        return delegate.getLength();
    }
public:
    // delete выполняет вызывающая сторона
    ImmutableArraySequence<T>* append(const T& item) const override {
        auto mutableDelegate{this->delegate};
        mutableDelegate.append(item);
        return new ImmutableArraySequence<T>{std::move(mutableDelegate)};
    }

    // delete выполняет вызывающая сторона
    ImmutableArraySequence<T>* prepend(const T& item) const override {
        auto mutableDelegate{this->delegate};
        mutableDelegate.prepend(item);
        return new ImmutableArraySequence<T>{std::move(mutableDelegate)};
    }

    // delete выполняет вызывающая сторона
    ImmutableArraySequence<T>* insertAt(const T& item, int index) const override {
        auto mutableDelegate{this->delegate};
        mutableDelegate.insertAt(item, index);
        return new ImmutableArraySequence<T>{std::move(mutableDelegate)};
    }

    // delete выполняет вызывающая сторона
    ImmutableArraySequence<T>* concat(const Sequence<T>& other) const override {
        auto mutableDelegate{this->delegate};
        mutableDelegate.concat(other);
        return new ImmutableArraySequence<T>{std::move(mutableDelegate)};
    }
};
