#include "matrixAlgebra.h"

template <class T>
Matrix<T>::Matrix(unsigned const &numOfRows, unsigned const &numOfCols) {
	this->rows = numOfRows;
	this->cols = numOfCols;

	for(unsigned i = 0; i < numOfRows; ++i) {
		this->matrix.push_back(vector<T>(numOfCols));
	}

	srand(time(NULL));
}

template <class T>
Matrix<T>::~Matrix() {

}

template <class T>
void Matrix<T>::fillRand() {
	for(auto &&v : this->matrix) {
		for(auto &&d : v) {
			d = rand() % 10;
		}
	}
}

template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<unsigned>;