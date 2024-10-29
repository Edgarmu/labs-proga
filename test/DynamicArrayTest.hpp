#pragma once

#include "BaseTest.hpp"
#include "DynamicArray.hpp"
#include "NegativeSize.hpp"

class DynamicArrayTest {
    int data[4] = {1, 2, 3, 5};
    int dataLength = sizeof(data) / sizeof(data[0]);
    DynamicArray<int> createData() {
        return DynamicArray<int>{data, dataLength};
    }
public:
    DynamicArrayTest() {
        set();
        setThrowsOnNegativeIndex();
        setThrowsOnBigIndex();
        createNegativeThrows();
    }

    void set() {
        DynamicArray<int> a = this->createData();
        a.set(1, 12);
        assert(a.get(1) == 12);
    }

    void setThrowsOnNegativeIndex() {
        DynamicArray<int> a = this->createData();
        try {
            a.set(-1, 12);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void setThrowsOnBigIndex() {
        DynamicArray<int> a = this->createData();
        try {
            a.set(this->dataLength, 12);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void createNegativeThrows() {
        try {
            DynamicArray<int>{-5};
        } catch (const NegativeSize&) {
            return;
        }
        assert(false);
    }
};
