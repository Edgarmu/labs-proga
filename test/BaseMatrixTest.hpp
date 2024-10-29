#pragma once

#include "Complex.hpp"
#include "UpperTriangularMatrix.hpp"
#include "LowerTriangularMatrix.hpp"

#include <cassert>
#include <iostream>

/* подумайте, к чему приводит определение статической переменной в h-файле */
static const double EPSILON = 0.0001;

class BaseMatrixTest {
public:
    BaseMatrixTest() {
        createEmptyMatrix();
        getRowsColumns();
        at();
        atThrowsOnNegativeRow();
        atThrowsOnNegativeColumn();
        atThrowsOnBigRow();
        atThrowsOnBigColumn();
        addDouble();
        addComplex();
        addTriangular();
        subDouble();
        subComplex();
        multiplyScalar();
        multiplyScalarComplex();
        multiply();
        multiplyComplex();
        elementaryAddRow();
        elementaryAddRowThrowsOnNegativeToRow();
        elementaryAddRowThrowsOnNegativeFromRow();
        elementaryAddRowThrowsOnBigToRow();
        elementaryAddRowThrowsOnBigFromRow();
        elementarySwapRow();
        elementarySwapRowThrowsOnNegativeToRow();
        elementarySwapRowThrowsOnNegativeFromRow();
        elementarySwapRowThrowsOnBigToRow();
        elementarySwapRowThrowsOnBigFromRow();
        elementaryScaleRow();
        elementaryScaleRowThrowsOnNegativeRow();
        elementaryScaleRowThrowsOnBigRow();
        norm1();
        norm1Complex();
        isTriangular();
        diagonalIsTriangular();
        notTriangular();
    }

private:
    int sampleData[3 * 4]{3, 3, 3, 3,
                          2, 2, 2, 2,
                          1, 1, 1, 1};

    double sampleDataDouble[3 * 4]{3, 3, 3, 3,
                                   2, 2, 2, 2,
                                   1, 1, 1, 1};
    Complex sampleDataComplex[3 * 4]{3j, 3, 3 + 4j, 3,
                                     2 - 1j, 2 - 2j, 2, 2,
                                     1, 1j, 1, -1j};

    Matrix<int> sampleMatrix() {
        return {sampleData, 3, 4};
    }

    Matrix<double> sampleMatrixDouble() {
        return {sampleDataDouble, 3, 4};
    }

    Matrix<Complex> sampleMatrixComplex() {
        return {sampleDataComplex, 3, 4};
    }

    void createEmptyMatrix() {
        Matrix<int> empty{0, 0};
        auto temp = empty + empty * empty;
    }

    void getRowsColumns() {
        Matrix<int> m = sampleMatrix();
        assert(m.getRows() == 3);
        assert(m.getColumns() == 4);
    }

    void at() {
        Complex data[]{0, 0 + 1j, 0 + 2j,
					   1, 1 + 1j, 1 + 2j};
        Matrix<Complex> m{data, 2, 3};
        for (int x = 0; x < m.getRows(); ++x) {
            for (int y = 0; y < m.getColumns(); ++y) {
                assert(m.at(x, y) == Complex{x + y * 1j});
            }
        }
    }

    void atThrowsOnNegativeRow() {
        Matrix<int> m = sampleMatrix();
        try { m.at(-1, 0); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void atThrowsOnNegativeColumn() {
        Matrix<int> m = sampleMatrix();
        try { m.at(0, -1); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void atThrowsOnBigRow() {
        Matrix<int> m = sampleMatrix();
        try { m.at(m.getRows(), 0); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void atThrowsOnBigColumn() {
        Matrix<int> m = sampleMatrix();
        try { m.at(0, m.getColumns()); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void addDouble() {
        Matrix m = sampleMatrixDouble();
        m += sampleMatrixDouble();
        double expectedData[]{6., 6., 6., 6.,
                              4., 4., 4., 4.,
                              2., 2., 2., 2.};
        const Matrix<double> expected{expectedData, 3, 4};
        assert(m == expected);
    }

    void addComplex() {
        Matrix m = sampleMatrixComplex();
        m += sampleMatrixComplex();
        Complex expectedData[]{6j, 6, 6 + 8j, 6,
                               4 - 2j, 4 - 4j, 4, 4,
                               2, 2j, 2, -2j};
        const Matrix<Complex> expected{expectedData, 3, 4};
        assert(m == expected);
    }

    void addTriangular() {
        int data[]{1, -1,
                   2, -2};
        int otherData[]{0,
                        2, 3};
        int expectedData[]{1, -1,
                           4, 1};
        Matrix m{data, 2, 2};
        LowerTriangularMatrix triangularMatrix{otherData, 2};
        m += triangularMatrix;
        SquareMatrix expected{expectedData, 2};
        assert(m == expected);
    }

    void subDouble() {
        Matrix m = sampleMatrixDouble();
        m -= sampleMatrixDouble();
        const Matrix<double> expected{3, 4};
        assert(m == expected);

    }

    void subComplex() {
        Matrix m = sampleMatrixComplex();
        m -= sampleMatrixComplex();
        const Matrix<Complex> expected{3, 4};
        assert(m == expected);
    }

    void multiplyScalar() {
        Matrix m = sampleMatrix();
        m *= -1;

        int data[]{-3, -3, -3, -3,
                   -2, -2, -2, -2,
                   -1, -1, -1, -1};
        const Matrix<int> expected{data, 3, 4};
        assert(m == expected);
    }

    void multiplyScalarComplex() {
        Matrix m = sampleMatrixComplex();
        m *= 1j;
        Complex data[]{-3, 3j, 3j + -4, 3j,
                       2j + 1, 2j + 2, 2j, 2j,
                       1j, -1, 1j, 1};
        const Matrix<Complex> expected{data, 3, 4};
        assert(m == expected);
    }

    void multiply() {
        int data1[]{1, 2, 3,
                    4, 5, 6};
        int data2[]{1, -1,
                    2, -2,
                    3, -3};
        Matrix m1{data1, 2, 3};
        Matrix m2{data2, 3, 2};
        int expectedData[]{14, -14,
                           32, -32};
        Matrix expected{expectedData, 2, 2};
        assert(m1 * m2 == expected);
    }

    void multiplyComplex() {
        Complex data1[]{1j, 2, 3,
                        4, 5j, 6};
        Complex data2[]{1, -1,
                        2, -2j,
                        3, -3};
        Matrix m1{data1, 2, 3};
        Matrix m2{data2, 3, 2};
        Complex expectedData[]{13 + 1j, -9 - 5j,
                               22 + 10j, -12};
        Matrix expected{expectedData, 2, 2};
        assert(m1 * m2 == expected);
    }

    void elementaryAddRow() {
        Matrix<int> m = sampleMatrix();
        m.elementaryAddRow(1, 0, -1);
        int expectedData[]{3, 3, 3, 3,
                           -1, -1, -1, -1,
                           1, 1, 1, 1};
        const Matrix<int> expected{expectedData, 3, 4};
        assert(m == expected);
    }

    void elementaryAddRowThrowsOnNegativeToRow() {
        Matrix<int> m = sampleMatrix();
        try { m.elementaryAddRow(-1, 0, 3); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void elementaryAddRowThrowsOnNegativeFromRow() {
        Matrix<int> m = sampleMatrix();
        try { m.elementaryAddRow(0, -1, 3); } catch (const IndexOutOfRange &) { return; }
        assert(false);

    }

    void elementaryAddRowThrowsOnBigToRow() {
        Matrix<int> m = sampleMatrix();
        try { m.elementaryAddRow(m.getRows(), 0, 3); } catch (const IndexOutOfRange &) { return; }
        assert(false);

    }

    void elementaryAddRowThrowsOnBigFromRow() {
        Matrix<int> m = sampleMatrix();
        try { m.elementaryAddRow(0, m.getRows(), 3); } catch (const IndexOutOfRange &) { return; }
        assert(false);

    }

    void elementarySwapRow() {
        Matrix<int> m = sampleMatrix();
        m.elementarySwapRow(0, 1);
        int expectedData[]{2, 2, 2, 2,
                           3, 3, 3, 3,
                           1, 1, 1, 1};
        Matrix<int> expected{expectedData, 3, 4};
        assert(m == expected);
        m.elementarySwapRow(0, 1);
        assert(m == sampleMatrix());
    }

    void elementarySwapRowThrowsOnNegativeToRow() {
        Matrix<int> m = sampleMatrix();
        try { m.elementarySwapRow(-1, 0); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void elementarySwapRowThrowsOnNegativeFromRow() {
        Matrix<int> m = sampleMatrix();
        try { m.elementarySwapRow(0, -1); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void elementarySwapRowThrowsOnBigToRow() {
        Matrix<int> m = sampleMatrix();
        try { m.elementarySwapRow(m.getRows(), 0); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void elementarySwapRowThrowsOnBigFromRow() {
        Matrix<int> m = sampleMatrix();
        try { m.elementarySwapRow(0, m.getRows()); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void elementaryScaleRow() {
        Matrix<int> m = sampleMatrix();
        m.elementaryScaleRow(0, -1);
        int expectedData[]{-3, -3, -3, -3,
                           2, 2, 2, 2,
                           1, 1, 1, 1};
        Matrix<int> expected{expectedData, 3, 4};
        assert(m == expected);
    }

    void elementaryScaleRowThrowsOnNegativeRow() {
        Matrix<int> m = sampleMatrix();
        try { m.elementaryScaleRow(-1, 3); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void elementaryScaleRowThrowsOnBigRow() {
        Matrix<int> m = sampleMatrix();
        try { m.elementaryScaleRow(m.getRows(), 3); } catch (const IndexOutOfRange &) { return; }
        assert(false);
    }

    void norm1() {
        Matrix<int> m = sampleMatrix();
        assert(m.norm1() == 12);
    }

    void norm1Complex() {
        Matrix<Complex> m = sampleMatrixComplex();
        assert(std::abs(m.norm1() - 14.) < EPSILON);
    }

    void isTriangular() {
        int data[]{1, 2, 3, 4, 5, 6};
        LowerTriangularMatrix<int> lower{data, 3};
        UpperTriangularMatrix<int> upper{data, 3};
        assert(lower.isLowerTriangular());
        assert(upper.isUpperTriangular());
        assert(!lower.isUpperTriangular());
        assert(!upper.isLowerTriangular());
    }

    void diagonalIsTriangular() {
        int data[]{1, 0, 0,
                   0, 3, 0,
                   0, 0, -1};
        SquareMatrix<int> m{data, 3};
        assert(m.isLowerTriangular());
        assert(m.isUpperTriangular());
    }

    void notTriangular() {
        int data[]{1, 0, -1,
                   1, 1, 0,
                   1, 1, 1};
        Matrix<int> m{data, 3, 3};
        int data2[]{1, 0, 1,
                    0, 1, 0,
                    0, -1, 1};
        Matrix<int> m2{data2, 3, 3};
        assert(!m.isLowerTriangular());
        assert(!m.isUpperTriangular());
        assert(!m2.isUpperTriangular());
        assert(!m2.isLowerTriangular());
    }

};