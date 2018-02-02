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
	~Matrix();
	void fillRand();
	
	friend ostream &operator<<(ostream &os, const Matrix<T> &matrixObj) {
		for(auto &&v : matrixObj.matrix) {
			for(auto &&d : v) {
				os << d << ' ';
			}

			os << endl;
		}

		return os;
	}
};