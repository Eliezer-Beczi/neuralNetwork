#include "activationFunction.h"

template <class T>
activationFunction<T>::activationFunction() {

}

template <class T>
activationFunction<T>::~activationFunction() {

}

template <class T>
T activationFunction<T>::sigmoid(const T &x) {
	return 1 / (1 + pow(M_E, -x));
}

template <class T>
T activationFunction<T>::tanh(const T &x) {
	return tanh(x);
}

template <class T>
T activationFunction<T>::derivative_sigmoid(const T &x) {
	return x * (1 - x);
}

template <class T>
T activationFunction<T>::derivative_tanh(const T &x) {
	return 1 / pow(cosh(x), 2);
}

template class activationFunction<double>;
template class activationFunction<long double>;