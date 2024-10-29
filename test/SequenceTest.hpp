#pragma once

#include "BaseTest.hpp"
#include "InconsistentBounds.hpp"

template<class SequenceT>
class SequenceTest : protected BaseTest<SequenceT> {
public:
    SequenceTest() {
        this->runBaseTests();
        getSubsequence();
        getSubsequenceThrowsOnNegativeStartIndex();
        getSubsequenceThrowsOnNegativeEndIndex();
        getSubsequenceThrowsOnBigStartIndex();
        getSubsequenceThrowsOnBigEndIndex();
        getSubsequenceStartAfterEnd();

        concat();
        concatEmptyLeft();
        concatEmptyRight();
    }

private:

    void append() override {
        SequenceT d = this->createData();
        SequenceT* a = d.append(12);
        assert(a->getLast() == 12);
        assert(a->getLength() == this->dataLength + 1);
    }

    void appendEmpty() override {
        SequenceT d = this->createEmpty();
        SequenceT* a = d.append(12);
        assert(a->getFirst() == 12);
        assert(a->getLast() == 12);
        assert(a->getLength() == 1);
    }

    void prepend() override {
        SequenceT d = this->createData();
        SequenceT* a = d.prepend(12);
        assert(a->getFirst() == 12);
        assert(a->getLength() == this->dataLength + 1);
    }

    void prependEmpty() override {
        SequenceT d = this->createEmpty();
        SequenceT* a = d.prepend(12);
        assert(a->getFirst() == 12);
        assert(a->getLast() == 12);
        assert(a->getLength() == 1);
    }

    void insertAt() override {
        SequenceT d = this->createData();
        SequenceT* a = d.insertAt(12, 1);
        assert(a->get(1) == 12);
        assert(a->getLength() == this->dataLength + 1);
        assert(a->get(0) == this->data[0]);
        assert(a->get(3) == this->data[2]);
    }

    void insertAtZero() override {
        SequenceT d = this->createData();
        SequenceT* a = d.insertAt(12, 0);
        assert(a->getFirst() == 12);
        assert(a->getLength() == this->dataLength + 1);
    }

    void insertAtLast() override {
        SequenceT d = this->createData();
        SequenceT* a = d.insertAt(12, this->dataLength);
        assert(a->getLast() == 12);
        assert(a->getLength() == this->dataLength + 1);

    }

    void insertAtEmpty() override {
        SequenceT d = this->createEmpty();
        SequenceT* a = d.insertAt(12, 0);
        assert(a->getFirst() == 12);
        assert(a->getLast() == 12);
        assert(a->getLength() == 1);
    }


    void getSubsequence() {
        const SequenceT d = this->createData();
        const SequenceT* a = d.getSubsequence(1, 1);
        assert(a->getFirst() == this->data[1]);
        assert(a->getLength() == 1);
        delete a;
    }

    void getSubsequenceThrowsOnNegativeStartIndex() {
        const SequenceT a = this->createData();
        try {
            a.getSubsequence(-1, 1);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void getSubsequenceThrowsOnNegativeEndIndex() {
        const SequenceT a = this->createData();
        try {
            a.getSubsequence(1, -1);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void getSubsequenceThrowsOnBigStartIndex() {
        const SequenceT a = this->createData();
        try {
            a.getSubsequence(this->dataLength, 1);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void getSubsequenceThrowsOnBigEndIndex() {
        const SequenceT a = this->createData();
        try {
            a.getSubsequence(1, this->dataLength);
        } catch (const IndexOutOfRange &e) {
            return;
        }
        assert(false);
    }

    void getSubsequenceStartAfterEnd() {
        const SequenceT a = this->createData();
        try {
            a.getSubsequence(2, 0);
        } catch (const InconsistentBounds &e) {
            return;
        }
        assert(false);
    }

    void concat() {
        SequenceT a = this->createData();
        SequenceT b = this->createData2();
        SequenceT* c = a.concat(b);
        assert(c->getFirst() == this->data[0]);
        assert(c->getLast() == this->data2[this->data2Length - 1]);
        assert(b.getLength() == this->data2Length);
        assert(c->getLength() == this->dataLength + this->data2Length);

        for (int i = 0; i < this->dataLength; ++i) {
            assert(c->get(i) ==this->data[i]);
        }
        for (int i = 0; i < this->data2Length; ++i) {
            assert(c->get(this->dataLength + i) == this->data2[i]);
        }
    }

    void concatEmptyLeft() {
        SequenceT d = this->createEmpty();
        SequenceT* a = d.concat(this->createData());
        assert(a->getLength() == this->dataLength);
    }

    void concatEmptyRight() {
        SequenceT d = this->createData();
        SequenceT* a = d.concat(this->createEmpty());
        assert(a->getLength() == this->dataLength);
    }
};
