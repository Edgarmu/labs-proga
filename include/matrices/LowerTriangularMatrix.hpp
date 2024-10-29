#pragma once

#include "SquareMatrix.hpp"
#include "IndexOutOfRange.hpp"

template<class T>
class LowerTriangularMatrix : public SquareMatrix<T> {
public:
    // задаются только значения под главной диагональю:
    // {1, 2, 3, 4, 5, 6} -> [[1 0 0] [2 3 0] [4 5 6]]
    LowerTriangularMatrix(T *array, int size)
        : LowerTriangularMatrix{size} {

		for (int i = 0; i < size; ++i) {
			for (int j = 0; j <= i; ++j) {
				this->elements[i][j] = *array;
				array++;
			}
		}
    }

    LowerTriangularMatrix(int size)
        : SquareMatrix<T>{this->checkSize(size, "'size'")} {
    }

    // доступ к элементу матрицы по строке и столбцу

    T &at(int row, int column) override {
        if (row < column) {
            throw IndexOutOfRange{"'row' < 'column', use SquareMatrix instead"};
        }
        return Matrix<T>::at(row, column);
    }
};
