#pragma once

#include "SquareMatrix.hpp"

#include "IndexOutOfRange.hpp"

template<class T>
class UpperTriangularMatrix : public SquareMatrix<T> {
public:
    // задаются только значения над главной диагональю:
    // {1, 2, 3, 4, 5, 6} -> [[1 2 3] [4 5 0] [6 0 0]]
    UpperTriangularMatrix(T *array, int size)
        : UpperTriangularMatrix{size} {
		for (int i = 0; i < size; ++i) {
			for (int j = i; j < size; ++j) {
				this->elements[i][j] = *array;
				array++;
			}
		}
    }

    UpperTriangularMatrix(int size)
        : SquareMatrix<T>{this->checkSize(size, "'size'")} {
    }

    // доступ к элементу матрицы по строке и столбцу

    const T &at(int row, int column) const override {
        this->checkRowIndex(row);
        this->checkColumnIndex(column);
        if (row > column) {
            static const T zero{};
            return zero;
        }
        return SquareMatrix<T>::at(row, column);
    }

    T &at(int row, int column) override {
        this->checkRowIndex(row);
        this->checkColumnIndex(column);
        if (row > column) {
            throw IndexOutOfRange{"'row' < 'column', use SquareMatrix instead"};
        }
        return SquareMatrix<T>::at(row, column);
    }
};
