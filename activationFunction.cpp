#include "activationFunction.h"

template <class T>
activationFunction<T>::activationFunction() {
	this->couples["sigmoid"].func = activationFunction<T>::sigmoid;
	this->couples["sigmoid"].derivative_func = activationFunction<T>::derivative_sigmoid;

	this->couples["tanh"].func = activationFunction<T>::tanh;
	this->couples["tanh"].derivative_func = activationFunction<T>::derivative_tanh;
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

template <class T>
typename activationFunction<T>::couple activationFunction<T>::getActivationFunction(const std::string &funcName) {
	auto it = this->couples.find(funcName);

	if(it != this->couples.end()) {
		return this->couples[funcName];
	}
	else {
		throw std::invalid_argument("there is no such function!");
	}
}

template class activationFunction<float>;
template class activationFunction<double>;
template class activationFunction<long double>;