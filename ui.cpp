
#include "Matrix.hpp"

#include <random>
#include <iostream>

std::default_random_engine random_engine{std::random_device{}()};

Matrix<int> random(int rows, int columns) {
	Matrix<int> m{rows, columns};
	std::uniform_int_distribution distribution{-10, 10};
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			m.at(i,j) = distribution(random_engine);
		}
	}
	return m;
}

int main() {
	Matrix<int> lhs{};
	Matrix<int> rhs{};
	int option;
	std::cout << "1 = создать случайную матрицу\n"
	<< "2 = умножить на скаляр\n"
	<< "3 = прибавить случайную матрицу\n"
	<< "4 = умножить на случайную матрицу\n" << std::endl;
	while (std::cout << "> ", std::cin >> option) {
		switch (option) {
			case 1: {
				int rows, columns;
				std::cout << "строк столбцов> ";
				std::cin >> rows >> columns;
				lhs = random(rows, columns);
				std::cout << lhs << std::endl;
				break;
			}
			case 2: {
				int coeff;
				std::cout << "скаляр> ";
				std::cin >> coeff;
				lhs *= coeff;
				std::cout << "= " << lhs << std::endl;
				break;
			}
			case 3: {
				rhs = random(lhs.getRows(), lhs.getColumns());
				std::cout << "+ " << rhs << std::endl;
				lhs += rhs;
				std::cout << "= " << lhs << std::endl;
				break;
			}
			case 4: {
				int columns;
				std::cout << "столбцов> ";
				std::cin >> columns;
				rhs = random(lhs.getColumns(), columns);
				std::cout << "* " << rhs << std::endl;
				lhs = lhs * rhs;
				std::cout << "= " << lhs << std::endl;
				break;
			}
			default: {
				std::cout << "sorry" << std::endl;
			}
		}
	}
}