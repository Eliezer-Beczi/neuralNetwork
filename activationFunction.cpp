#include "activationFunction.h"

template <class T>
std::map<std::string, typename activationFunction<T>::couple> activationFunction<T>::couples;

template <class T>
activationFunction<T>::activationFunction() {
	activationFunction<T>::couples["sigmoid"].actFunc = activationFunction<T>::sigmoid;
	activationFunction<T>::couples["sigmoid"].derivative_actFunc = activationFunction<T>::derivative_sigmoid;

	activationFunction<T>::couples["tanh"].actFunc = activationFunction<T>::tanh;
	activationFunction<T>::couples["tanh"].derivative_actFunc = activationFunction<T>::derivative_tanh;
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
	auto it = activationFunction<T>::couples.find(funcName);

	if(it != activationFunction<T>::couples.end()) {
		return activationFunction<T>::couples[funcName];
	}
	else {
		throw std::invalid_argument("there is no such function!");
	}
}

template class activationFunction<float>;
template class activationFunction<double>;
template class activationFunction<long double>;