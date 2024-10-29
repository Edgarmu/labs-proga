#include "LinkedListTest.hpp"
#include "DynamicArrayTest.hpp"
#include "SequenceTest.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "ImmutableListSequence.hpp"
#include "Matrix.hpp"
#include "LowerTriangularMatrix.hpp"
#include "UpperTriangularMatrix.hpp"
#include "BaseMatrixTest.hpp"
#include "BinaryHeapTest.hpp"
#include "BinaryHeap.hpp"
#include "BinaryHeapTree.hpp"
#include "BinarySearchTreeTest.hpp"

#include <iostream>

int main() {
	/* подумайте, что из тестов можно вынести в .cpp */
    LinkedListTest{};
    DynamicArrayTest{};
    SequenceTest<ArraySequence<int>>{};
    SequenceTest<ListSequence<int>>{};
    SequenceTest<ImmutableArraySequence<int>>{};
    SequenceTest<ImmutableListSequence<int>>{};

    BaseMatrixTest{};

	BinaryHeapTest<BinaryHeap<char>>{};
	BinaryHeapTest<BinaryHeapTree<char>>{};

	BinarySearchTreeTest{};

    std::cout << "Tests passed" << std::endl;
}