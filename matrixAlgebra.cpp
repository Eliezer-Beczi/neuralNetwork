#include "matrixAlgebra.h"

template <class T>
Matrix<T>::Matrix(unsigned const &numOfRows, unsigned const &numOfCols) {
	this->rows = numOfRows;
	this->cols = numOfCols;

	for(unsigned i = 0; i < numOfRows; ++i) {
		this->matrix.push_back(vector<T>(numOfCols));
	}
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>&cpy) {
	*this = cpy;
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

template <class T>
Matrix<T> Matrix<T>::applyFunction(const Matrix<T> &matrixObj, const function<T(const T&)> &myActFunc) {
	Matrix<T> result(matrixObj.rows, matrixObj.cols);

	for(unsigned i = 0; i < matrixObj.rows; ++i) {
		for(unsigned j = 0; j < matrixObj.cols; ++j) {
			result.matrix[i][j] = myActFunc(matrixObj.matrix[i][j]);
		}
	}

	return result;
}

template <class T>
vector<T> Matrix<T>::toArray(const Matrix<T> &matrixObj) {
	vector<T> result;

	for(auto &&v : matrixObj.matrix) {
		for(auto &&d : v) {
			result.push_back(d);
		}
	}

	return result;
}

template <class T>
Matrix<T> Matrix<T>::toRowVector(const vector<T> &v) {
	Matrix<T> result(1, v.size());

	result.matrix[0] = v;

	return result;
}

template <class T>
Matrix<T> Matrix<T>::toColumnVector(const vector<T> &v) {
	Matrix<T> result(v.size(), 1);

	for(unsigned i = 0; i < v.size(); ++i){
		result.matrix[i][0] = v[i];
	}

	return result;
}

template <class T>
Matrix<T> Matrix<T>::transpose(const Matrix<T> &matrixObj) {
	Matrix<T> result(matrixObj.cols, matrixObj.rows);

	for(unsigned i = 0; i < matrixObj.cols; ++i) {
		for(unsigned j = 0; j < matrixObj.rows; ++j) {
			result.matrix[i][j] = matrixObj.matrix[j][i];
		}
	}

	return result;
}

template class Matrix<double>;
template class Matrix<long double>;