#include "matrixAlgebra.h"

int main(int argc, char const *argv[]) {
	Matrix<int> myMatrix(5, 5);
	myMatrix.fillRand();

	cout << myMatrix;

	return 0;
}