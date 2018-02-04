#include <functional>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

template <class T>
class Matrix {
private:
	unsigned rows;
	unsigned cols;
	vector<vector<T>> matrix;

public:
	Matrix(unsigned const&, unsigned const&);
	\\\copy constructor
	Matrix(const Matrix<T>&);
	~Matrix();
	void fillRand();
	static Matrix<T> applyFunction(const Matrix<T>&, const function<T(const T&)>&);
	static vector<T> toArray(const Matrix<T>&);
	static Matrix<T> toRowVector(const vector<T>&);
	static Matrix<T> toColumnVector(const vector<T>&);
	static Matrix<T> transpose(const Matrix<T>&);
	
	friend ostream &operator<<(ostream &os, const Matrix<T> &matrixObj) {
		for(auto &&v : matrixObj.matrix) {
			for(auto &&d : v) {
				os << d << ' ';
			}

			os << endl;
		}

		return os;
	}

	Matrix<T> &operator=(const Matrix<T> &matrixObj) {
		
		if(this==&matrixObj){
			return *this;
		}
		
		this->rows = matrixObj.rows;
		this->cols = matrixObj.cols;
		this->matrix=matrixObj.matrix;

		return *this;
	}
	
	Matrix<T> &operator+=(const Matrix<T> &matrixObj) {
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
	
	Matrix<T> &operator-=(const Matrix<T> &matrixObj) {
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

	friend const Matrix<T> operator+(const Matrix<T> &matrixObj1, const Matrix<T> &matrixObj2)const {
		Matrix<T> result;
		result = matrixObj1;
		result+=matrixObj2;
		return result;
	}

	friend Matrix<T> operator-(const Matrix<T> &matrixObj1, const Matrix<T> &matrixObj2) {
		Matrix<T> result;
		result = matrixObj1;
		result-=matrixObj2;
		return result;
	}

	Matrix<T> &operator*=(const vector<T> &v) {
		if(this->cols != v.size()){
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

	Matrix<T> &operator*=(const Matrix<T> &matrixObj) {
		if(this->cols != matrixObj.rows){
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

	friend Matrix<T> operator*(const Matrix<T> &matrixObj1, const Matrix<T> &matrixObj2) {
		Matrix<T> result;
		result = matrixObj1;
		result*=matrixObj2;
		return result;
	}

	friend Matrix<T> operator*(const Matrix<T> &matrixObj, const vector<T> &v) {
		if(matrixObj.cols != v.size()){
			throw invalid_argument("the matrix can't be multiplied by the vector!");
		}

		Matrix<T> result(matrixObj.rows, 1);

		for(unsigned i = 0; i < matrixObj.rows; ++i) {
			for(unsigned j = 0; j < v.size(); ++j) {
				result.matrix[i][0] += matrixObj.matrix[i][j] * v[j];
			}
		}

		return result;
	}
	
	Matrix<T> &operator*=(const T &num) {
		for(unsigned i = 0; i < this->rows; ++i) {
			for(unsigned j = 0; j < this->cols; ++j) {
				this->matrix[i][j] *= num;
			}
		}

		return *this;
	}

	friend Matrix<T> operator*(const T &num, const Matrix<T> &matrixObj) {
		Matrix<T> result;
		result = matrixObj;
		result*=num;
		return result;
	}

	friend Matrix<T> operator*(const Matrix<T> &matrixObj, const T &num) {
		Matrix<T> result;
		result = matrixObj;
		result*=num;
		return result;
	}

	
};
