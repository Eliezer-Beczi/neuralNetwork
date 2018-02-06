#include "matrixAlgebra.h"

template <class T>
Matrix<T>::Matrix(unsigned const &numOfRows, unsigned const &numOfCols, unsigned const &width, unsigned const &precision) {
	this->rows = numOfRows;
	this->cols = numOfCols;

	for(unsigned i = 0; i < numOfRows; ++i) {
		this->matrix.push_back(vector<T>(numOfCols));
	}

	this->width = width;
	this->precision = precision;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>&cpy) {
	*this = cpy;
}

template <class T>
Matrix<T>::~Matrix() {

}

template <class T>
void Matrix<T>::fillRand(const T &lowerBound, const T &upperBound) {
	random_device r;
	default_random_engine re(r());
	uniform_real_distribution<T> uniform_dist(lowerBound, upperBound);

	for(auto &&v : this->matrix) {
		for(auto &&d : v) {
			d = uniform_dist(re);
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

/**
======================================================
||													||
||													||
||THIS FUNCTION ASSIGNS ONE MATRIX TO ANOTHER MATRIX||
||													||
||													||
======================================================
*/
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &matrixObj) {
	if(this == &matrixObj){
		return *this;
	}

	vector<vector<T>>().swap(this->matrix);

	this->rows = matrixObj.rows;
	this->cols = matrixObj.cols;
	this->matrix = matrixObj.matrix;

	return *this;
}

/**
================================================================
||															  ||
||															  ||
||THIS FUNCTION ADDS THE GIVEN MATRICES AND RETURNS THE RESULT||
||															  ||
||													 		  ||
================================================================
*/
template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T> &matrixObj) {
	if(this->rows != matrixObj.rows || this->cols != matrixObj.cols) {
		throw invalid_argument("the matrices don't have the same dimension!");
	}

	for(unsigned i = 0; i < this->rows; ++i) {
		for(unsigned j = 0; j < this->cols; ++j) {
			this->matrix[i][j] += matrixObj.matrix[i][j];
		}
	}

	return *this;
}

/**
=====================================================================
||																   ||
||																   ||
||THIS FUNCTION SUBTRACTS THE GIVEN MATRICES AND RETURNS THE RESULT||
||																   ||
||													 			   ||
=====================================================================
*/
template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T> &matrixObj) {
	if(this->rows != matrixObj.rows || this->cols != matrixObj.cols) {
		throw invalid_argument("the matrices don't have the same dimension!");
	}

	for(unsigned i = 0; i < this->rows; ++i) {
		for(unsigned j = 0; j < this->cols; ++j) {
			this->matrix[i][j] -= matrixObj.matrix[i][j];
		}
	}

	return *this;
}

/**
========================================================================================
||																					  ||
||																					  ||
||THIS FUNCTION MULTIPLIES THE GIVEN MATRIX WITH A GIVEN VECTOR AND RETURNS THE RESULT||
||																					  ||
||													 								  ||
========================================================================================
*/
template <class T>
Matrix<T>& Matrix<T>::operator*=(const vector<T> &v) {
	if(this->cols != v.size()) {
		throw invalid_argument("the matrix can't be multiplied by the vector!");
	}

	Matrix<T> result(this->rows, 1);

	for(unsigned i = 0; i < this->rows; ++i) {
		for(unsigned j = 0; j < v.size(); ++j) {
			result.matrix[i][0] += this->matrix[i][j] * v[j];
		}
	}

	*this = result;

	return *this;
}

/**
======================================================================
||																	||
||																	||
||THIS FUNCTION MULTIPLIES THE GIVEN MATRICES AND RETURNS THE RESULT||
||																	||
||													 				||
======================================================================
*/
template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T> &matrixObj) {
	if(this->cols != matrixObj.rows) {
		throw invalid_argument("the matrices can't be multiplied!");
	}

	Matrix<T> result(this->rows, matrixObj.cols);

	for(unsigned i = 0; i < this->rows; ++i) {
		for(unsigned j = 0; j < matrixObj.cols; ++j) {
			for(unsigned k = 0; k < this->cols; ++k) {
				result.matrix[i][j] += this->matrix[i][k] * matrixObj.matrix[k][j];
			}
		}
	}

	*this = result;

	return *this;
}

/**
========================================================================================
||																					  ||
||																					  ||
||THIS FUNCTION MULTIPLIES THE GIVEN MATRIX WITH A GIVEN SCALAR AND RETURNS THE RESULT||
||																					  ||
||													 								  ||
========================================================================================
*/
template <class T>
Matrix<T>& Matrix<T>::operator*=(const T &num) {
	for(auto &&v : this->matrix) {
		for(auto &&d : v) {
			d *= num;
		}
	}

	return *this;
}

template class Matrix<double>;
template class Matrix<long double>;