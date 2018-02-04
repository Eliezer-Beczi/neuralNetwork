#include "activationFunction.h"

template <class T>
activationFunction<T>::activationFunction() {

}

template <class T>
activationFunction<T>::~activationFunction() {

}

template <class T>
T activationFunction<T>::sigmoid(const T &x) {
	return 1 / (1 + exp(-x));
}

template <class T>
T activationFunction<T>::tanh(const T &x) {
	return tanh(x);
}

template <class T>
T activationFunction<T>::derivative_sigmoid(const T &x) {
	T temp = sigmoid(x);

	return temp * (1 - temp);
}

template <class T>
T activationFunction<T>::derivative_tanh(const T &x) {
	return 1 / pow(cosh(x), 2);
}

template class activationFunction<double>;
template class activationFunction<long double>;