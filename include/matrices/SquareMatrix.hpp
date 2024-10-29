#pragma once

#include "Matrix.hpp"

template<class T>
class SquareMatrix : public Matrix<T> {
public:
    SquareMatrix(T *array, int size)
        : SquareMatrix{size} {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				this->elements[i][j] = *array;
				array++;
			}
		}
    }

    SquareMatrix(int size)
        : Matrix<T>(Matrix<T>::checkSize(size, "'size'"), size) {
    }
};
