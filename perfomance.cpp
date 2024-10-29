
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include "BinaryHeap.hpp"
#include "BinarySearchTree.hpp"


int myrand() {
	static std::default_random_engine random_engine{std::random_device{}()};
	static std::uniform_int_distribution distribution{std::numeric_limits<int>::min(), std::numeric_limits<int>::max()};
	return distribution(random_engine);
}

auto now() {
	return std::chrono::high_resolution_clock::now();
}

auto elapsedMs(auto from, auto to) {
	return (to - from)/std::chrono::milliseconds(1);
}

int main() {
	// чтобы компилятор не удалял холостые вызовы функций при оптимизации
	int data = 0;
	std::vector<size_t> sizes = {100000L, // 10^5
								 1000000L,
								 10000000L,
								 100000000L, // 10^8
	};
	std::ofstream log{"perfomance.csv", std::ios::app};
	for (size_t n: sizes) {
		{
			auto start = now();
			BinaryHeap<int> heap{};
			for (int i = 0; i < n; ++i) {
				heap.add(myrand());
			}
			log << "heap_fill;" << n << ';' << elapsedMs(start, now()) << std::endl;
			start = now();
			data += heap.getMin();
			log << "heap_min;" << n << ';' << elapsedMs(start, now()) << std::endl;
			start = now();
			heap.add(myrand());
			log << "heap_add;" << n << ';' << elapsedMs(start, now()) << std::endl;
			start = now();
			heap.eraseMin();
			log << "heap_erasemin;" << n << ';' << elapsedMs(start, now()) << std::endl;
			data += heap.getMin();
			log.flush();
		}
		{
			auto start = now();
			BinarySearchTree<int> tree{};
			for (int i = 0; i < n; ++i) {
				tree.add(myrand());
			}
			log << "tree_fill;" << n << ';' << elapsedMs(start, now()) << std::endl;
			for (int i = 0; i < 50; ++i) {
				start = now();
				data += tree.exist(myrand());
				log << "tree_exist;" << n << ';' << elapsedMs(start, now()) << std::endl;
			}
			start = now();
			tree.add(myrand());
			log << "tree_add;" << n << ';' << elapsedMs(start, now()) << std::endl;
			start = now();
			tree.erase(myrand());
			log << "tree_erase;" << n << ';' << elapsedMs(start, now()) << std::endl;
			data += tree.exist(0);
			log.flush();
		}
	}
	std::cout << data;
}