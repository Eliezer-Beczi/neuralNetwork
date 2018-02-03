#define _USE_MATH_DEFINES

#include <cmath>

template <class T>
class activationFunction {
public:
	activationFunction();
	~activationFunction();
	static T sigmoid(const T&);
	static T tanh(const T&);
	static T derivative_sigmoid(const T&);
	static T derivative_tanh(const T&);
};