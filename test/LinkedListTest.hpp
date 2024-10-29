#pragma once

#include "BaseTest.hpp"
#include "LinkedList.hpp"

class LinkedListTest : private BaseTest<LinkedList<int>> {
public:
    LinkedListTest() {
        this->runBaseTests();
        getSubList();
        getSubListThrowsOnNegativeStartIndex();
        getSubListThrowsOnNegativeEndIndex();
        getSubListThrowsOnBigStartIndex();
        getSubListThrowsOnBigEndIndex();

        concat();
        concatEmptyLeft();
        concatEmptyRight();

        copyEmptyList();
    }
private:
    void copyEmptyList() {
        LinkedList<int> empty = createEmpty();
        LinkedList<int> a{empty};
        assert(a.getLength() == 0);
    }

    void getSubList() {
        const LinkedList<int> list = createData();
        const LinkedList<int> a = list.getSubList(1, 1);
        assert(a.getFirst() == data[1]);
        assert(a.getLength() == 1);

    }

    void getSubListThrowsOnNegativeStartIndex() {
        const LinkedList<int> a = createData();
        try {
            a.getSubList(-1, 1);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void getSubListThrowsOnNegativeEndIndex() {
        const LinkedList<int> a = createData();
        try {
            a.getSubList(1, -1);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void getSubListThrowsOnBigStartIndex() {
        const LinkedList<int> a = createData();
        try {
            a.getSubList(dataLength, 1);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void getSubListThrowsOnBigEndIndex() {
        const LinkedList<int> a = createData();
        try {
            a.getSubList(1, dataLength);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void concat() {
        LinkedList<int> a = createData();
        LinkedList<int> b = createData2();
        assert(&a == &a.concat(std::move(b)));
        assert(a.getFirst() == data[0]);
        assert(a.getLast() == data2[data2Length - 1]);
        assert(a.getLength() == dataLength + data2Length);
        assert(b.getLength() == 0); // после выполнения concat переданный список пуст!
    }

    void concatEmptyLeft() {
        LinkedList<int> a = createEmpty().concat(createData());
        assert(a.getLength() == dataLength);

    }

    void concatEmptyRight() {
        LinkedList<int> a = createData().concat(createEmpty());
        assert(a.getLength() == dataLength);
    }
};
