#pragma once

#include "ImmutableSequence.hpp"

template <class T>
class ImmutableListSequence : public ImmutableSequence<T> {
private:
    const ListSequence<T> delegate;

    explicit ImmutableListSequence(ListSequence<T>&& delegate) : delegate{delegate} {
    }
public:
    ImmutableListSequence(T* items, int count) : delegate{items, count} {
    }

    ImmutableListSequence() : delegate{} {
    }

    explicit ImmutableListSequence(const LinkedList<T>& list) : delegate{list} {
    }

    // не нужно копировать ImmutableArraySequence, т.к. он неизменяемый
    ImmutableListSequence(const ImmutableListSequence&) = delete;
    ~ImmutableListSequence() = default;

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

    ImmutableListSequence<T>* getSubsequence(int startIndex, int endIndex) const override {
        auto* sub = delegate.getSubsequence(startIndex, endIndex);
        auto* result = new ImmutableListSequence{std::move(*sub)};
        delete sub;
        return result;
    }

    int getLength() const override {
        return delegate.getLength();
    }
public:
    // delete выполняет вызывающая сторона
    ImmutableListSequence<T>* append(const T& item) const override {
        auto mutableDelegate{this->delegate};
        mutableDelegate.append(item);
        return new ImmutableListSequence<T>{std::move(mutableDelegate)};
    }

    // delete выполняет вызывающая сторона
    ImmutableListSequence<T>* prepend(const T& item) const override {
        auto mutableDelegate{this->delegate};
        mutableDelegate.prepend(item);
        return new ImmutableListSequence<T>{std::move(mutableDelegate)};
    }

    // delete выполняет вызывающая сторона
    ImmutableListSequence<T>* insertAt(const T& item, int index) const override {
        auto mutableDelegate{this->delegate};
        mutableDelegate.insertAt(item, index);
        return new ImmutableListSequence<T>{std::move(mutableDelegate)};
    }

    // delete выполняет вызывающая сторона
    ImmutableListSequence<T>* concat(const Sequence<T>& other) const override {
        auto mutableDelegate{this->delegate};
        mutableDelegate.concat(other);
        return new ImmutableListSequence<T>{std::move(mutableDelegate)};
    }
};