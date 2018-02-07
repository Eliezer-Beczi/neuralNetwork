#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

#include <map>
#include <cmath>
#include <functional>

#define _USE_MATH_DEFINES

template <class T>
class activationFunction {
public:
	struct couple {
		std::function<T(const T&)> actFunc;
		std::function<T(const T&)> derivative_actFunc;
	};

	activationFunction();
	~activationFunction();

	activationFunction<T>::couple getActivationFunction(const std::string&);

	static T sigmoid(const T&);
	static T tanh(const T&);
	static T derivative_sigmoid(const T&);
	static T derivative_tanh(const T&);

private:
	std::map<std::string, activationFunction<T>::couple> couples;
};

#endif