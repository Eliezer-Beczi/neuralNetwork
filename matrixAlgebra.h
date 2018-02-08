#ifndef MATRIXALGEBRA_H_
#define MATRIXALGEBRA_H_

#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>

template <class T>
class Matrix {
private:
	unsigned rows;
	unsigned cols;
	
	std::vector<std::vector<T>> matrix;

	unsigned width;
	unsigned precision;

public:
	Matrix(unsigned const&, unsigned const&, unsigned const &width = 12, unsigned const &precision = 4);
	Matrix(const Matrix<T>&);
	~Matrix();

	static Matrix<T> applyFunction(const Matrix<T>&, const std::function<T(const T&)>&);
	static std::vector<T> toArray(const Matrix<T>&);
	static Matrix<T> toRowVector(const std::vector<T>&);
	static Matrix<T> toColumnVector(const std::vector<T>&);

	Matrix<T> &operator=(const Matrix<T>&);
	Matrix<T> &operator+=(const Matrix<T>&);
	Matrix<T> &operator-=(const Matrix<T>&);
	Matrix<T> &operator*=(const T&);
	Matrix<T> &operator*=(const std::vector<T>&);
	Matrix<T> &operator*=(const Matrix<T>&);

	/**
	=====================================================
	||												   ||
	||												   ||
	||THIS FUNCTION PRINTS A GIVEN MATRIX TO THE SCREEN||
	||												   ||
	||												   ||
	=====================================================
	*/
	friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrixObj) {
		for(auto &&v : matrixObj.matrix) {
			for(auto &&d : v) {
				os << std::setprecision(matrixObj.precision) << std::setw(matrixObj.width) << d << ' ';
			}

			os << std::endl;
		}

		return os;
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
	friend Matrix<T> operator+(const Matrix<T> &matrixObj1, const Matrix<T> &matrixObj2) {
		if(matrixObj1.rows != matrixObj2.rows || matrixObj1.cols != matrixObj2.cols) {
			throw std::invalid_argument("the matrices don't have the same dimension!");
		}

		Matrix<T> result(matrixObj1.rows, matrixObj1.cols);

		for(unsigned i = 0; i < matrixObj1.rows; ++i) {
			for(unsigned j = 0; j < matrixObj1.cols; ++j) {
				result.matrix[i][j] = matrixObj1.matrix[i][j] + matrixObj2.matrix[i][j];
			}
		}

		return result;
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
	friend Matrix<T> operator-(const Matrix<T> &matrixObj1, const Matrix<T> &matrixObj2) {
		if(matrixObj1.rows != matrixObj2.rows || matrixObj1.cols != matrixObj2.cols) {
			throw std::invalid_argument("the matrices don't have the same dimension!");
		}

		Matrix<T> result(matrixObj1.rows, matrixObj1.cols);

		for(unsigned i = 0; i < matrixObj1.rows; ++i) {
			for(unsigned j = 0; j < matrixObj1.cols; ++j) {
				result.matrix[i][j] = matrixObj1.matrix[i][j] - matrixObj2.matrix[i][j];
			}
		}

		return result;
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
	friend Matrix<T> operator*(const Matrix<T> &matrixObj1, const Matrix<T> &matrixObj2) {
		if(matrixObj1.cols != matrixObj2.rows) {
			throw std::invalid_argument("the matrices can't be multiplied!");
		}

		Matrix<T> result(matrixObj1.rows, matrixObj2.cols);

		for(unsigned i = 0; i < matrixObj1.rows; ++i) {
			for(unsigned j = 0; j < matrixObj2.cols; ++j) {
				for(unsigned k = 0; k < matrixObj1.cols; ++k) {
					result.matrix[i][j] += matrixObj1.matrix[i][k] * matrixObj2.matrix[k][j];
				}
			}
		}

		return result;
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
	friend Matrix<T> operator*(const Matrix<T> &matrixObj, const std::vector<T> &v) {
		if(matrixObj.cols != v.size()) {
			throw std::invalid_argument("the matrix can't be multiplied by the vector!");
		}

		Matrix<T> result(matrixObj.rows, 1);

		for(unsigned i = 0; i < matrixObj.rows; ++i) {
			for(unsigned j = 0; j < v.size(); ++j) {
				result.matrix[i][0] += matrixObj.matrix[i][j] * v[j];
			}
		}

		return result;
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
	friend Matrix<T> operator*(const T &num, const Matrix<T> &matrixObj) {
		Matrix<T> result(matrixObj.rows, matrixObj.cols);

		for(unsigned i = 0; i < matrixObj.rows; ++i) {
			for(unsigned j = 0; j < matrixObj.cols; ++j) {
				result.matrix[i][j] = num * matrixObj.matrix[i][j];
			}
		}

		return result;
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
	friend Matrix<T> operator*(const Matrix<T> &matrixObj, const T &num) {
		Matrix<T> result(matrixObj.rows, matrixObj.cols);

		for(unsigned i = 0; i < matrixObj.rows; ++i) {
			for(unsigned j = 0; j < matrixObj.cols; ++j) {
				result.matrix[i][j] = num * matrixObj.matrix[i][j];
			}
		}

		return result;
	}

	/**
	============================================================================================================
	||																					 					  ||
	||																					 					  ||
	||THIS FUNCTION MULTIPLIES THE TRANSPOSE OF THE FIRST MATRIX WITH THE SECOND MATRIX AND RETURNS THE RESULT||
	||																										  ||
	||													 													  ||
	============================================================================================================
	*/
	friend Matrix<T> operator<<(const Matrix<T> &matrixObj1, const Matrix<T> &matrixObj2) {
		if(matrixObj1.rows != matrixObj2.rows) {
			throw std::invalid_argument("the matrices can't be multiplied!");
		}

		Matrix<T> result(matrixObj1.cols, matrixObj2.cols);

		for(unsigned i = 0; i < matrixObj1.cols; ++i) {
			for(unsigned j = 0; j < matrixObj2.cols; ++j) {
				for(unsigned k = 0; k < matrixObj1.rows; ++k) {
					result.matrix[i][j] += matrixObj1.matrix[k][i] * matrixObj2.matrix[k][j];
				}
			}
		}

		return result;
	}

	/**
	============================================================================================================
	||																					 					  ||
	||																					 					  ||
	||THIS FUNCTION MULTIPLIES THE FIRST MATRIX WITH THE TRANSPOSE OF THE SECOND MATRIX AND RETURNS THE RESULT||
	||																										  ||
	||													 													  ||
	============================================================================================================
	*/
	friend Matrix<T> operator>>(const Matrix<T> &matrixObj1, const Matrix<T> &matrixObj2) {
		if(matrixObj1.cols != matrixObj2.cols) {
			throw std::invalid_argument("the matrices can't be multiplied!");
		}

		Matrix<T> result(matrixObj1.rows, matrixObj2.rows);

		for(unsigned i = 0; i < matrixObj1.rows; ++i) {
			for(unsigned j = 0; j < matrixObj2.rows; ++j) {
				for(unsigned k = 0; k < matrixObj1.cols; ++k) {
					result.matrix[i][j] += matrixObj1.matrix[i][k] * matrixObj2.matrix[j][k];
				}
			}
		}

		return result;
	}

	/**
	===========================================================
	||														 ||
	||														 ||
	||THIS FUNCTION RETURNS THE TRANSPOSE OF THE GIVEN MATRIX||
	||														 ||
	||													 	 ||
	===========================================================
	*/
	friend Matrix<T> operator~(const Matrix<T> &matrixObj) {
		Matrix<T> result(matrixObj.cols, matrixObj.rows);

		for(unsigned i = 0; i < matrixObj.cols; ++i) {
			for(unsigned j = 0; j < matrixObj.rows; ++j) {
				result.matrix[i][j] = matrixObj.matrix[j][i];
			}
		}

		return result;
	}
};

#endif