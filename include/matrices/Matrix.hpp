#pragma once

#include <ostream>
#include "Dimension.hpp"
#include "MatrixHasInconsistentDimensions.hpp"
#include "Complex.hpp"
#include "Vector.hpp"

// T элемент поля (T, +, *). 0 === T{}.
// Matrix - прямоугольная матрица
template<class T>
class Matrix {
protected:
    Vector<Vector<T>> elements;
    Dimension dim;
public:
	Matrix() : Matrix(0, 0) {
	}

    // создать ноль-матрицу размеров
    Matrix(int rows, int columns)
        : elements{checkSize(rows, "'rows'")}, dim{rows, checkSize(columns, "'columns'")} {
		for (int i = 0; i < rows; ++i) {
			elements[i] = Vector<T>{columns};
		}
    }

    // создать матрицу по массиву ее элементов, перечисленных построчно
    Matrix(T *array, int rows, int columns)
        : Matrix{rows, columns} {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				at(i,j) = *array;
				array++;
			}
		}
    }

    Matrix(const Matrix<T>& other) = default;

    int getRows() const { return dim.rows; }

    int getColumns() const { return dim.columns; }

    // доступ к строке матрицы по строке и столбцу

    virtual const T &at(int row, int column) const {
        return elements[row][column];
    }

    virtual T &at(int row, int column) {
        checkRowIndex(row);
        checkColumnIndex(column);
        return elements[row][column];
    }

public:

    // сложение матриц

    Matrix<T> &operator+=(const Matrix<T> &other) {
        if (dim != other.dim) {
            throw MatrixHasInconsistentDimensions{"right"};
        }
		elements += other.elements;
        return *this;
    }

    friend Matrix<T> operator+(const Matrix<T> & left, const Matrix<T> &right) {
        Matrix<T> copy{left};
        copy += right;
        return copy;
    }

    // вычитание матриц

    Matrix<T> &operator-=(const Matrix<T> &other) {
        if (dim != other.dim) {
            throw MatrixHasInconsistentDimensions{"right"};
        }
        elements -= other.elements;
        return *this;
    }

    friend Matrix<T> operator-(const Matrix<T> & left, const Matrix<T> &right) {
        Matrix<T> copy{left};
        copy -= right;
        return copy;
    }

    // умножение на скаляр

    Matrix<T> &operator*=(const T &coefficient) {
        for (int i = 0; i < elements.size(); ++i) {
            elements[i] *= coefficient;
        }
        return *this;
    }

    friend Matrix<T> operator*(const T &coefficient, const Matrix<T> &matrix) {
        Matrix<T> result{matrix};
        result *= coefficient;
        return result;
    }

    // умножение матриц

    Matrix<T> operator*(const Matrix<T> &right) {
        if (!Dimension::canMultiply(dim, right.dim)) {
            throw MatrixHasInconsistentDimensions{"right"};
        }
        Matrix<T> result{dim.rows, right.dim.columns};
        for (int i = 0; i < dim.rows; ++i) {
            for (int j = 0; j < right.dim.columns; ++j) {
                T &x = result.at(i, j);
                x = T{};
                for (int k = 0; k < dim.columns; ++k) {
                    x += at(i, k) * right.at(k, j);
                }
            }
        }
        return result;
    }

    // элементарные преобразования строк и столбцов

    // к строке rowTo прибавить строку rowFrom умноженную на factor
    Matrix<T> &elementaryAddRow(int rowTo, int rowFrom, T factor) {
        for (int j = 0; j < dim.columns; ++j) {
            at(rowTo, j) += at(rowFrom, j) * factor;
        }
        return *this;
    }

    // поменять местами строки
    Matrix<T> &elementarySwapRow(int row, int otherRow) {
        for (int j = 0; j < dim.columns; ++j) {
            std::swap(at(row, j), at(otherRow, j));
        }
        return *this;
    }

    // домножить строку row на factor
    Matrix<T> &elementaryScaleRow(int row, T factor) {
        for (int j = 0; j < dim.columns; ++j) {
            at(row, j) *= factor;
        }
        return *this;
    }

    // к столбцу columnTo прибавить столбец columnFrom умноженный на factor
    Matrix<T> &elementaryAddColumn(int columnTo, int columnFrom, T factor) {
        for (int i = 0; i < dim.columns; ++i) {
            at(i, columnTo) += at(columnFrom) * factor;
        }
        return *this;
    }

    // поменять местами столбцы
    Matrix<T> &elementarySwapColumn(int column, int otherColumn) {
        for (int i = 0; i < dim.columns; ++i) {
            std::swap(at(i, column), at(i, otherColumn));
        }
        return *this;
    }

    // домножить столбец column на factor
    Matrix<T> &elementaryScaleColumn(int column, T factor) {
        for (int i = 0; i < dim.columns; ++i) {
            at(i, column) *= factor;
        }
        return *this;
    }

    // норма || . ||_1 матрицы (максимум сумм модулей элементов строк)
    double norm1() const {
        if (dim.rows == 0 || dim.columns == 0) {
            return 0.;
        }
        double result = -1.;
        for (int i = 0; i < dim.rows; ++i) {
            double candidate = 0.;
            for (int j = 0; j < dim.columns; ++j) {
                candidate += std::abs(at(i, j));
            }
            result = std::max(result, candidate);
        }
        return result;
    }

    bool isLowerTriangular() const {
        if (dim.rows != dim.columns) {
            return false;
        }
        T zero{};
        for (int i = 0; i < dim.rows; ++i) {
            for (int j = i + 1; j < dim.columns; ++j) {
                if (zero != this->at(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isUpperTriangular() const {
        if (dim.rows != dim.columns) {
            return false;
        }
        T zero{};
        for (int i = 0; i < dim.rows; ++i) {
            for (int j = 0; j < i; ++j) {
                if (zero != at(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator==(const Matrix& other) const {
        if (dim != other.dim) {
            return false;
        }
        for (int i = 0; i < dim.rows; ++i) {
            for (int j = 0; j < dim.columns; ++j) {
                if (at(i, j) != other.at(i,j)) {
                    return false;
                }
            }
        }
        return true;
    }

	friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
	{
		return os << matrix.elements;
	}

protected:
    void checkRowIndex(int row) const {
        if (row < 0 || row >= dim.rows) {
            throw IndexOutOfRange{"'row' is out of range"};
        }
    }

    void checkColumnIndex(int column) const {
        if (column < 0 || column >= dim.columns) {
            throw IndexOutOfRange{"'column' is out of range"};
        }
    }


    static int checkSize(int size, const char *name) {
        if (size < 0) {
            throw NegativeSize{name};
        }
        return size;
    }
};