#pragma once

#include "IndexOutOfRange.hpp"
#include <cassert>

template<class SequenceT>
class BaseTest {
protected:
    BaseTest() = default;

    void runBaseTests() {
        getFirst();
        getFirstThrowsOnEmpty();

        getLast();
        getLastThrowsOnEmpty();

        get();
        getThrowsOnNegativeIndex();
        getThrowsOnBigIndex();

        getLength();
        getLengthEmpty();

        append();
        appendEmpty();

        prepend();
        prependEmpty();

        insertAt();
        insertAtZero();
        insertAtLast();
        insertAtEmpty();

        insertAtThrowsOnNegativeIndex();
        insertAtThrowsOnBigIndex();
    }

    int data[3] = {1, 2, 3};
    int dataLength = sizeof(data) / sizeof(data[0]);
    int data2[3] = {2, 5, 8};
    int data2Length = sizeof(data2) / sizeof(data2[0]);

    SequenceT createData() {
        return SequenceT{data, dataLength};
    }

    SequenceT createData2() {
        return SequenceT{data2, data2Length};
    }

    SequenceT createEmpty() {
        return SequenceT{};
    }

private:

    void getLength() {
        const SequenceT a = createData();
        assert(a.getLength() == dataLength);
    }

    void getLengthEmpty() {
        const SequenceT a = createEmpty();
        assert(a.getLength() == 0);
    }

    void getFirstThrowsOnEmpty() {
        const SequenceT a = createEmpty();
        try {
            a.getFirst();
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void getLastThrowsOnEmpty() {
        const SequenceT a = createEmpty();
        try {
            a.getLast();
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void get() {
        const SequenceT a = createData();
        for (int i = 0; i < dataLength; ++i) {
            assert(a.get(i) == data[i]);
        }
    }

    void getThrowsOnNegativeIndex() {
        const SequenceT a = createData();
        try {
            a.get(-1);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void getThrowsOnBigIndex() {
        const SequenceT a = createData();
        try {
            a.get(dataLength);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void getFirst() {
        const SequenceT a = createData();
        assert(a.getFirst() == data[0]);
    }

    void getLast() {
        const SequenceT a = createData();
        assert(a.getLast() == data[dataLength - 1]);
    }


    virtual void append() {
        SequenceT a = createData();
        a.append(12);
        assert(a.getLast() == 12);
        assert(a.getLength() == dataLength + 1);
    }

    virtual void appendEmpty() {
        SequenceT a = createEmpty();
        a.append(12);
        assert(a.getFirst() == 12);
        assert(a.getLast() == 12);
        assert(a.getLength() == 1);
    }

    virtual void prepend() {
        SequenceT a = createData();
        a.prepend(12);
        assert(a.getFirst() == 12);
        assert(a.getLength() == dataLength + 1);
    }

    virtual void prependEmpty() {
        SequenceT a = createEmpty();
        a.prepend(12);
        assert(a.getFirst() == 12);
        assert(a.getLast() == 12);
        assert(a.getLength() == 1);
    }

    virtual void insertAt() {
        SequenceT a = createData();
        a.insertAt(12, 1);
        assert(a.get(1) == 12);
        assert(a.getLength() == dataLength + 1);
    }

    virtual void insertAtZero() {
        SequenceT a = createData();
        a.insertAt(12, 0);
        assert(a.getFirst() == 12);
        assert(a.getLength() == dataLength + 1);
    }

    virtual void insertAtLast() {
        SequenceT a = createData();
        a.insertAt(12, dataLength);
        assert(a.getLast() == 12);
        assert(a.getLength() == dataLength + 1);

    }

    virtual void insertAtEmpty() {
        SequenceT a = createEmpty();
        a.insertAt(12, 0);
        assert(a.getFirst() == 12);
        assert(a.getLast() == 12);
        assert(a.getLength() == 1);
    }

    void insertAtThrowsOnNegativeIndex() {
        SequenceT a = createData();
        try {
            a.insertAt(12, -1);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void insertAtThrowsOnBigIndex() {
        SequenceT a = createData();
        try {
            a.insertAt(12, dataLength + 1);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }
};
