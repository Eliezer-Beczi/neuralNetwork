#include "matrixAlgebra.h"
#include "activationFunction.h"

const string ACT_FUNC = "sigmoid";

template <class T>
void init(function<T(const T&)> &myActFunc, function<T(const T&)> &derivative_myActFunc) {
	if(ACT_FUNC == "sigmoid") {
		myActFunc = activationFunction<T>::sigmoid;
		derivative_myActFunc = activationFunction<T>::derivative_sigmoid;
	}
	else {
		myActFunc = activationFunction<T>::tanh;
		derivative_myActFunc = activationFunction<T>::derivative_tanh;
	}
}

int main(int argc, char const *argv[]) {
	function<long double(const long double&)> myActFunc;
	function<long double(const long double&)> derivative_myActFunc;

	init<long double>(myActFunc, derivative_myActFunc);

	return 0;
}