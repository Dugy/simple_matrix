#include "simple_matrix.h"
#include <iostream>

int main() {
	matrix<2, 2> A = {{2, 3}, {3, 1}};
	matrix<2, 2> B = {{1, 0}, {2, 4}};
	matrix<2, 2> product = {{8, 12}, {5, 4}};
	if (A * B != product) {
		std::cout << "Matrix multiplication failed\n";
		return 1;
	}

	matrix<2, 2> squareA = {{53, 48}, {48, 37}};
	if ((A ^ 3) != squareA) {
		std::cout << "Matrix power failed\n";
		return 1;
	}

	matrix<2, 2> sum = {{3, 3}, {5, 5}};
	if (A + B != sum) {
		std::cout << "Matrix sum failed\n";
		return 1;
	}

	matrix<3, 2> C = {{2, 3}, {0, 1}, {3, 1}};
	matrix<3, 2> product2 = {{13, 9}, {3, 1}, {9, 10}};
	if (C * A != product2) {
		std::cout << "Heterogenous matrix multiplication failed\n";
		return 2;
	}

	matrix<2, 2> tripleA = {{6, 9}, {9, 3}};
	if (A * 3 != tripleA) {
		std::cout << "Scalar multiplication failed\n";
		return 3;
	}

	matrix<2, 3> transposedC = {{2, 0, 3}, {3, 1, 1}};
	if (transpose(C) != transposedC) {
		std::cout << "Matrix transpose failed\n" << transpose(C) << C;
		return 3;
	}

	matrix<4, 4> D = {{2, 1, 3, 5}, {8, 4, 6, 2}, {1, 2, 3, 4}, {2, 3, 4, 5}};
	if (determinant(D) != 18) {
		std::cout << "Matrix determinant failed\n";
		return 3;
	}

	lineVector<2> line = {1, 7};
	lineVector<2> multipliedByLineA = {23, 10};
	if (line * A != multipliedByLineA) {
		std::cout << "Multiplication by vector failed\n";
		return 4;
	}

	matrix<2, 1> transposedLine = {{1}, {7}};
	if (transpose(line) != transposedLine) {
		std::cout << "Vector transpose failed\n";
		return 4;
	}

	if (line * multipliedByLineA != 93) {
		std::cout << "Dot product failed\n";
		return 5;
	}

	lineVector<2> doubleLine = {2, 14};
	if (line * 2 != doubleLine) {
		std::cout << "Vector by scalar multiplication failed\n";
		return 5;
	}

	std::cout << "All tests succeeded\n";
	return 0;
}
