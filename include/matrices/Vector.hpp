#pragma once

#include <ostream>
#include "ArraySequence.hpp"
#include "VectorHasInconsistentDimensions.hpp"

template <typename T>
class Vector {
	MutableSequence<T>* sequence;

public:
	// создать вектор размера size

	Vector() : sequence{new ArraySequence<T>{}} {

	}

	Vector(int size) : sequence{new ArraySequence<T>{size}} {
    }

    Vector(T *array, int size) : sequence{new ArraySequence<T>{array, size}} {
    }


	Vector(const Vector<T>& other) : Vector() {
		*this = other;
	}

	Vector& operator=(Vector<T>&& other) {
		std::swap(sequence, (other.sequence));
		return *this;
	}

	Vector& operator=(const Vector<T>& other) {
		if (this == &other) {
			return *this;
		}
		*sequence = *other.sequence;
		return *this;
	}

	const T& operator[](int index) const {
		return (*sequence)[index];
	}

	T& operator[](int index) {
		return (*sequence)[index];
	}

	// сложение векторов

    Vector<T> &operator+=(const Vector<T> &other) {
        if (size() != other.size()) {
            throw VectorHasInconsistentDimensions{"other"};
        }
        for (int i = 0; i < size(); ++i) {
			(*sequence)[i] += (*other.sequence)[i];
        }
        return *this;
    }

    friend Vector<T> operator+(const Vector<T> & left, const Vector<T> &right) {
        Vector<T> copy{left};
        copy += right;
        return copy;
    }

    // вычитание векторов

    Vector<T> &operator-=(const Vector<T> &other) {
        if (size() != other.size()) {
            throw VectorHasInconsistentDimensions{"other"};
        }
        for (int i = 0; i < size(); ++i) {
            (*sequence)[i] -= (*other.sequence)[i];
        }
        return *this;
    }

    friend Vector<T> operator-(const Vector<T> & left, const Vector<T> &right) {
        Vector<T> copy{left};
        copy -= right;
        return copy;
    }

    // умножение на скаляр

    Vector<T> &operator*=(const T &coefficient) {
        for (int i = 0; i < size(); ++i) {
			(*sequence)[i] *= coefficient;
        }
        return *this;
    }

    friend Vector<T> operator*(const T &coefficient, const Vector<T> &vector) {
        Vector<T> result{vector};
        result *= coefficient;
        return result;
    }

	int size() const {
		return sequence->getLength();
	}

	friend std::ostream &operator<<(std::ostream &os, const Vector &vector)
	{
		os << '[';
		for (int i = 0; i < vector.size(); ++i) {
			if (i != 0) {
				os << ", ";
			}
			os << vector[i];
		}
		return os << ']';
	}

	virtual ~Vector()
	{
		delete sequence;
		sequence = nullptr;
	}
};