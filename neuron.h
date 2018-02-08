#ifndef NEURON_H
#define NEURON_H

#include <vector>

#include "edge.h"
#include "matrixAlgebra.h"
#include "activationFunction.h"

template <class T>
class neuron
{
private:
	unsigned index;
	T outputValue;

public:
	neuron();
	~neuron();

	T getOutputValue();
	void setOutputValue(const T&);
	void feedForward(const std::vector<neuron<T>>&, const typename activationFunction<T>::couple &actFunc);
};

#endif